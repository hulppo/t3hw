#include "Channel.h"
#include "User.h"
#include "ChannelCommand.h"
#include "ChannelMessage.h"

#include <sstream>

using namespace std;

// Constuctor, sets some private values.
Channel::Channel(string channelName, int userLimit) {
  mChannelName = channelName;
  mUserLimit = userLimit;
  pthread_mutex_init(&mLock, NULL);
  mShutdown = false;
}



// Adds user to this channel.
bool
Channel::addUser(User* user) {
  
  bool addOK = false;
  
  // Synchronized.
  pthread_mutex_lock(&mLock);

  if(!mShutdown) { //If channel isn't shutting down

    // If not already joined to this channel
    // and channel is not full.
    if(!this->isJoined(user->getUserName()) &&
       mUsers.size() < mUserLimit) {
      
      // Add to channel
      mUsers[user->getUserName()] = user;
      
      // Send join message to everybody on this channel
      ostringstream text;
      text << "* " << user->getUserName().c_str() << " has joined.";
      this->sendToAll("", 
                      text.str());
      
      addOK = true;
    }
    else {
      addOK = false;
    }

  } //end mShutdown

  pthread_mutex_unlock(&mLock);
  
  return addOK;
}



// Removes one user from this channel and returns a reference.
User*
Channel::removeUser(string userName) {

  User* user = 0;

// Synchronized
  pthread_mutex_lock(&mLock);

  if(!mShutdown) {

    UserList::iterator p = mUsers.find(userName);
    if(p != mUsers.end()) {
      string info = userName;
      info += " has exited channel";
      this->sendToAll("", info);
      user = p->second;
      mUsers.erase(p);
    }
    
  } // end mShutdown
  
  pthread_mutex_unlock(&mLock);
    
  return user;
}



// Receives a channel message.
void
Channel::recvMsg(ChannelMessage* message) {
  
  // Synchronized
  pthread_mutex_lock(&mLock);
  
  if(!mShutdown) {

    if(this->isJoined(message->sender)) {
      this->sendToAll(message->sender, 
                      message->text);
    }

  } // end mShutdown
  
  pthread_mutex_unlock(&mLock);
}



// Receives a channel command
bool
Channel::recvCmd(ChannelCommand* command) {

  // Synchronized
  pthread_mutex_lock(&mLock);
  if(!mShutdown) {
  // Nothing here yet.
  }
  pthread_mutex_unlock(&mLock);
  return true;
}



// Returns a string containing all users on this channel.
std::string
Channel::getUsers() {
  
  ostringstream listOfUsers;
  
  // Synchronized.
  pthread_mutex_lock(&mLock);
  
  if(!mShutdown) {

    if(mUsers.empty()) {
      listOfUsers << "No users on channel";
    }
    else {
      UserList::iterator p;
      for(p = mUsers.begin(); p != mUsers.end(); ++p) {
        listOfUsers << p->first << " ";
      }
    }
    
  } //end mShutdown

  pthread_mutex_unlock(&mLock);
  
  return listOfUsers.str();
}



// Destroys this channel.
vector<User*>
Channel::destroyChannel() {
  // Synchronized
  pthread_mutex_lock(&mLock);

  if(mShutdown) { //Already shutdown
    pthread_mutex_unlock(&mLock);
    vector<User*> v;
    return v;
  }

  mShutdown = true;
  UserList::iterator p = mUsers.begin();
  vector<User*> v(mUsers.size());
  for(int i = 0;p != mUsers.end(); ++p, i++) {
    v[i] = p->second;
  }
  
  string text = "This channel is closing";
  this->sendToAll("", text);
  
  pthread_mutex_unlock(&mLock);
  return v;
}



// Private.
// Sends a channel message to all users on this channel.
void
Channel::sendToAll(string sender, string messageText) {

  ChannelMessage* msg = new ChannelMessage(sender, 
					   mChannelName, 
					   messageText);

  // Send to everybody on this channel.
  UserList::iterator p;
  for(p = mUsers.begin();p != mUsers.end(); ++p) {
    User* receiver = p->second;
    receiver->sendMsg(msg);
  }
  delete(msg);
}



// Private.
// Tells if user is joined on this channel.
bool
Channel::isJoined(string userName) {

  UserList::iterator p = mUsers.find(userName);
  if(p == mUsers.end())
    return false;
  else
    return true;
}
