#include "Server.h"

#include "User.h"
#include "Channel.h"
#include "Message.h" // Needed in creation of SystemMsgs
#include "ChannelMessage.h"
#include "PrivateMessage.h"
#include "ServerCommand.h"
#include "ChannelCommand.h"

#include "SynchronizedMap.h"

#include <sstream>
#include <vector>

using namespace std;

Server::Server(int chLimit) {
  mChannelLimit = chLimit;
  this->myDb = new Database();
}

Server::~Server() {
  UserList::iterator p = mUsers.getIterator();
  for(;p != mUsers.end(); ++p) {
    string uName = p->first;
    this->sendSystemMsg(uName, "Server shutdown");
  }
  mUsers.returnIterator();
  delete(myDb);
}


bool
Server::authenticateUser(string uName, string pass) {
  if(myDb->checkUser(uName,pass))
    return true;
  return false;
}

bool
Server::joinServer(string uName, Connection* conn) {
  bool joinOK = false;
  User* user;

  user = myDb->getUser(uName);
  user->setConnection(conn);
  joinOK = mUsers.insert(uName, user);
  if(!joinOK)
    delete(user);


  if(joinOK) {
    ostringstream oss;
    oss << "Welcome to ChatServer, " << uName << "!!!";
    string greeting = oss.str();
    this->sendSystemMsg(uName, greeting);
    this->sendPrivateMsgs(uName);
  }

  return joinOK;
}

bool
Server::exitServer(string uName) {
  bool ok = false;
  ChannelList::iterator p = mChannels.getIterator();
  
  /* Removes user from every Channel, maybe better to let the user
     keep list of all channels he is on */
  for(; p != mChannels.end(); ++p) {
    Channel* ch = p->second;
    User* user = ch->removeUser(uName);
    if(user != 0)
      mUsers.release(user);
  }
  mChannels.returnIterator();

  if(mUsers.remove(uName))
    ok = true;

  return ok;
}

bool
Server::joinChannel(string uName, string chName) {
  User* user = mUsers.acquire(uName); // This one should be left like this unless the join fails
  bool ok = false;
  if(user != 0) {
    Channel* ch = mChannels.acquire(chName);
    if(ch != 0) {
      if(ch->addUser(user))
	ok = true;
      else {
	this->sendSystemMsg(uName, "Channel full or you are banned or already logged in");
	mUsers.release(user);
      }
      mChannels.release(ch);
    }
    else {
      string text = "No such channel to join";
      this->sendSystemMsg(uName, text);
      mUsers.release(user);
    }
  }
  return ok;
}

bool
Server::exitChannel(std::string uName, std::string chName) {
  bool ok = false;
  Channel* ch = mChannels.acquire(chName);
  if(ch != 0) {
    User* user = ch->removeUser(uName);
    mChannels.release(ch);
    if(user != 0) {
      this->sendSystemMsg(uName, "Channel exited successfully");
      mUsers.release(user);
      ok = true;
    }
    else {
      string text = "You weren't on the channel";
      this->sendSystemMsg(uName, text);
    }
  }
  else {
    string text = "Non existent channel";
    this->sendSystemMsg(uName, text);
  }
  return ok;
}


bool
Server::sendChannelList(string uName) {
  string channels = "Channels:\n";
  ChannelList::iterator p = mChannels.getIterator();

  for(; p != mChannels.end(); ++p) {
    channels += p->first + "\n";
    channels += "\t" + p->second->getUsers() + "\n"; // retrieves users for this channel
  }
  mChannels.returnIterator();
  this->sendSystemMsg(uName, channels);
  
  return true;
}

void
Server::recvMsg(ChannelMessage* msg) {
  Channel* ch = mChannels.acquire(msg->channel);
  if(ch != 0) {
    ch->recvMsg(msg);
    mChannels.release(ch);
  }
  else {
    string text = "No such channel";
    this->sendSystemMsg(msg->sender, text);
  }
}

bool
Server::recvMsg(PrivateMessage* msg) {
  User* user = mUsers.acquire(msg->receiver);
  bool ok = false;
  if(user != 0) { //Was the user found
    user->sendMsg(msg);
    ok = true;
    mUsers.release(user);
  }
  else {
    //User not online, store message in database
    myDb->addMessage(msg);
    ostringstream oss;
    oss << "User " << msg->receiver << " not online.";
    string text = oss.str();
    this->sendSystemMsg(msg->sender, text);
  }
  return ok;
}
 
bool
Server::recvCmd(ServerCommand* cmd) {
  ServerCommand::eServerCom choose;
  choose = cmd->com;
  switch(choose) {
  case ServerCommand::addUser:
    {
      if(!this->adminAuthorize(cmd->sender)) {
        this->sendSystemMsg(cmd->sender, "No right to perform action!");
	return false;
      }

      char delim = 2;
      istringstream iss(cmd->getUserData());

      string newUName = cmd->getTargetUser();
      string newRName = "";
      string newPass = "";
      string isAdmin = "";
      bool admin = false;

      getline(iss, newPass, delim);
      getline(iss, isAdmin, delim);
      getline(iss, newRName,delim);


      if(isAdmin != "")
        admin = true;
      
      User* user = new User(newUName, newRName, newPass, admin);

      if(myDb->addUser(user)) {
        this->sendSystemMsg(cmd->sender, "Add successful");
        return true;
      }
      else {
        delete(user); // Has to be freed if not added to database
        this->sendSystemMsg(cmd->sender, "Add failed, user name already taken");
      }
      
      break;
    }
  case ServerCommand::removeUser: 
    {
      if(!this->adminAuthorize(cmd->sender)) {
	this->sendSystemMsg(cmd->sender, "No right to perform action!");
        return false;
      }
      string uName = cmd->getTargetUser();
      if(myDb->removeUser(uName)) {
        string text = "User ";
        text += uName;
        text += " removed from database";
        this->sendSystemMsg(cmd->sender, text);
        return true;
      }
      else {
        this->sendSystemMsg(cmd->sender, "User not found in database");
        return false;
      }
      break;
    }
  case ServerCommand::kickUser:
    {
      if(!this->adminAuthorize(cmd->sender)) {
        this->sendSystemMsg(cmd->sender, "No right to perform action!");
	return false;
      }
      string info = "You are being kicked by ";
      info += cmd->sender;
      this->sendSystemMsg(cmd->getTargetUser(), info);
      if(this->exitServer(cmd->getTargetUser()))
        this->sendSystemMsg(cmd->sender, "User kicked from server");
      else
        this->sendSystemMsg(cmd->sender, "User not found on server");
      break;
    }
  case ServerCommand::modifyData:
    if(this->adminAuthorize(cmd->sender) || cmd->sender == cmd->getTargetUser()) {
      

    }
    else // Command sender isn't admin and isn't changing his own data
      return false;
    break;
  case ServerCommand::serverInfo:
    {
      ostringstream oss;
      oss << "Channels: " << mChannels.size();
      oss << " Users: " << mUsers.size();
      string text = oss.str();
      this->sendSystemMsg(cmd->sender, text);
      
      break;
    }
  case ServerCommand::userInfo:
    {
      string usInfo;
      UserList::iterator p = mUsers.getIterator();
      for(; p != mUsers.end(); ++p) {
	User* user = p->second;
	usInfo += user->getInfo();
	usInfo += "\n";
      }
      mUsers.returnIterator();
      this->sendSystemMsg(cmd->sender, usInfo);
      break;
    }
  default:
    //Unknown command
    break;
  }
  return true;
}

bool // Only admins can send channelCommands
Server::recvCmd(ChannelCommand* cmd) {
  if(!this->adminAuthorize(cmd->sender)) {// Command fails when someone not admin sends it
    this->sendSystemMsg(cmd->sender, "No rights to perform action");
    return false;
  }
  ChannelCommand::eChannelCom choose;
  choose = cmd->com;
  bool ok = false;
  switch(choose) {
  case ChannelCommand::createChannel:
    {
      ostringstream oss;
      if(this->addChannel(cmd->getChannel())) {
	oss << "Channel " << cmd->getChannel() << " created.";
	ok = true;
      }
      else {
	oss << "Creation of channel " << cmd->getChannel() << " failed.";
	ok = false;
      }
      string text = oss.str();
      this->sendSystemMsg(cmd->sender, text);
      break;
    }
  case ChannelCommand::destroyChannel:
    {
      ostringstream oss;
      if(this->removeChannel(cmd->getChannel())) {
	oss << "Channel " << cmd->getChannel() << " removed.";
	ok = true;
      }
      else {
	oss << "Failed removal of channel " << cmd->getChannel() << ".";
	ok = false;
      }
      string text = oss.str();
      this->sendSystemMsg(cmd->sender, text);
      break;
    }
  case ChannelCommand::kickUser:
    {
      Channel* ch = mChannels.acquire(cmd->getChannel());
      if(ch != 0) {
	User* user = ch->removeUser(cmd->getTargetUser());
        string info = "You were kicked from ";
        info += cmd->getChannel();
        info += " by ";
        info += cmd->sender;
        this->sendSystemMsg(cmd->getTargetUser(), info);
	if(user != 0) {
          this->sendSystemMsg(cmd->sender, "User kicked from channel");
	  mUsers.release(user);
        }
      }
      break;
    }
  case ChannelCommand::banUser:
    break;
  default:
    break;
  }
  return ok;
}


//private method
bool
Server::addChannel(string channelName) { // Other parameters size and so on
  Channel* ch = new Channel(channelName, 10); // This is a default should be changed
  bool ok = mChannels.insert(channelName, ch);
  return ok; // If false, channel already existed
}

//private method
bool
Server::removeChannel(string channelName) {
  Channel* ch = mChannels.acquire(channelName);
  bool ok = false;
  if(ch != 0) {
    if(ok = mChannels.remove(channelName)) {
      vector<User*> v = ch->destroyChannel();
      mChannels.release(ch);
      vector<User*>::iterator p = v.begin();
      
      for(; p != v.end(); ++p) // Calls release on every user
	mUsers.release(*p);
    }
    else
      mChannels.release(ch); // Someone else was at the same time here
  }
  else {
    //This channel name didn't exist
  }
  return ok;
}

bool
Server::sendSystemMsg(string receiver, string text) {
  bool ok = false;
  User* user = mUsers.acquire(receiver);
  if(user != 0) {
    Message* msg = new Message("*server*", text);
    user->sendMsg(msg);
    mUsers.release(user);
    delete(msg);
    ok = true;
  }
  else
    ok = false;
  return ok;
}

bool
Server::adminAuthorize(string uName) {
  User* user = mUsers.acquire(uName);
  bool isAdmin = false;
  if(user != 0) {
    isAdmin = user->isAdmin();
    mUsers.release(user);
  }
  return isAdmin;
}

void
Server::sendPrivateMsgs(string uName) {
  User* user = mUsers.acquire(uName);

  if(user != 0) {
    PrivateMessage* msg = 0;
    while((msg = myDb->getMessage(uName))) {
      user->sendMsg(msg);
      delete(msg);
    }
  }
}
