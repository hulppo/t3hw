#include "CLConnection.h"
#include "Server.h"
#include "ChannelCommand.h"
#include "ServerCommand.h"
#include "ChannelMessage.h"
#include "PrivateMessage.h"
#include <iostream>
#include <sstream>

using namespace std;

CLConnection::CLConnection(long connId, Server *serv, CORBA::ORB_var orb)
  : Connection(connId, "temp", serv)
{

  mORB = orb;

  //Setup of commands
  mCommands["quit"] = 0;
  mCommands["help"] = 1;
  mCommands["channels"] = 2;
  mCommands["create"] = 3;
  mCommands["destroy"] = 4;
  mCommands["join"] = 5;
  mCommands["leave"] = 6;
  mCommands["sendCh"] = 7;
  mCommands["sendPr"] = 8;
  mCommands["info"] = 9;
  mCommands["users"] = 10;
  mCommands["kick"] = 11;
  mCommands["add"] = 12;
  mCommands["remove"] = 13;
}

void
CLConnection::sendMsg(Message* msg)
{
  cout << "**" << endl;
  cout << msg->text << endl;
  cout << "**" << endl;
}

void
CLConnection::sendMsg(ChannelMessage* msg)
{
  //cout << "**Channel " << msg->channel << " **" << endl;
  cout << "<" << msg->sender << "> " << msg->text << endl;
}

void
CLConnection::sendMsg(PrivateMessage* msg)
{
  cout << "**Private: " << "<" << msg->sender << "> ";
  cout << msg->text << endl;
}

void*
CLConnection::Execute()
{
  string pass = "";
  bool cont = true;
  while(cont) {
    cout << "==================" << endl;
    cout << "Command line login" << endl;
    cout << "  for ChatServer  " << endl;
    cout << "==================" << endl;
    cout << "User name: ";
    mUserName = "";
    cin >> mUserName;
    cout << "Password: ";
    pass = "";
    cin >> pass;
    string clean;
    getline(cin, clean); //Cleans the buffer
    bool fail = false;
    if(pServer->authenticateUser(mUserName, pass)) {
      if(pServer->joinServer(this->mUserName, this))
        this->insideServer();
      else {
        cout << "User already logged in" << endl;
        fail = true;
      }
    }
    else {
      cout << "Authentication failed" << endl;
      fail = true;
    }
    if(fail) {
      cout << "1 to continue 0 to shutdown server: ";
      int res;
      cin >> res;
      if(!res)
	cont = false;
    }
  }
  CORBA::Boolean waitfor = false;
  mORB->shutdown(waitfor);
  delete(pServer); // Causes users to be written to file
  exit(0);
  return 0;
}

void
CLConnection::insideServer()
{
  bool cont = true;
  while(cont) {
    string line;
    getline(cin, line);
    istringstream iss(line);
    string choose;
    iss >> choose;
    int val = this->mapToInt(choose);
    switch(val) {
    case 0: // quit
      {
      cont = false;
      pServer->exitServer(mUserName);
      break;
      }
    case 1: // help
      this->printCommands();
      break;
    case 2: // channels
      pServer->sendChannelList(mUserName);
      break;
    case 3: // create
      {
	string chName = "";
	if(iss >> chName) {
	  ChannelCommand* cmd =
	    new ChannelCommand(mUserName, ChannelCommand::createChannel,
			       "", chName);
	  pServer->recvCmd(cmd);
	  delete(cmd);
	}
	else
	  cout << "Usage: create <channel>" << endl;
	break;
      }
    case 4:  // destroy
      {
	string chName = "";
	if(iss >> chName) {
	  ChannelCommand* cmd =
	    new ChannelCommand(mUserName, ChannelCommand::destroyChannel,
			       "", chName);
	  pServer->recvCmd(cmd);
	  delete(cmd);
	}
	else
	  cout << "Usage: destroy <channel>" << endl;
	break;
      }
    case 5: // join
      {
	string chName = "";
	if(iss >> chName)
	  pServer->joinChannel(mUserName, chName);
	else
	  cout << "Usage: join <channel>" << endl;
	break;
      }
    case 6: // leave
      {
	string chName = "";
	if(iss >> chName)
	  pServer->exitChannel(mUserName, chName);
	else
	  cout << "Usage: leave <channel>" << endl;
	break;
      }
    case 7: // sendCh - Send Channel message
      {
	string chName = "";
	if(iss >> chName) {
	  string text;
	  getline(iss, text);
	  if(!text.empty()) {
	    ChannelMessage* msg = new ChannelMessage(mUserName, chName, text);
	    pServer->recvMsg(msg);
	    delete(msg);
	  }
	  else
	    cout << "No text to send." << endl;
	}
	else
	  cout << "Usage: sendCh <channel> <text to send>" << endl;
	break;
      }
    case 8: // sendPr - Send private message
      {
	string receiver = "";
	if(iss >> receiver) {
	  string text;
	  getline(iss, text);
	  if(!text.empty()) {
	    PrivateMessage* msg = new PrivateMessage(mUserName, receiver, text);
	    pServer->recvMsg(msg);
	    delete(msg);
	  }
	  else
	    cout << "No text to send." << endl;
	}
	else
	  cout << "Usage: sendPr <receiver> <text to send>" << endl;
	break;
      }
    case 9: // info
      {
	ServerCommand* cmd =
	  new ServerCommand(mUserName, ServerCommand::serverInfo,
			    "", "");
	pServer->recvCmd(cmd);
	delete(cmd);
	break;
      }
    case 10: // users
      {
	ServerCommand* cmd =
	  new ServerCommand(mUserName, ServerCommand::userInfo,
			    "", "");
	pServer->recvCmd(cmd);
	delete(cmd);
	break;
      }
    case 11: // kick (kicks from server or channel)
      {
	string victim = "";
	string channel = "";
	if(iss >> victim) {
	  if(iss >> channel) { // Kick from channel
	    ChannelCommand* cmd =
	      new ChannelCommand(mUserName, ChannelCommand::kickUser,
				 victim, channel);
	    pServer->recvCmd(cmd);
	    delete(cmd);
	  }
	  else { // kick from server
	    ServerCommand* cmd =
	      new ServerCommand(mUserName, ServerCommand::kickUser,
				victim, "");
	    pServer->recvCmd(cmd);
	    delete(cmd);
	  }
	}
	else {
	  cout << "Usage: To kick user from server - kick <user to kick>" << endl;
	  cout << "To kick user from channel - kick <user to kick> <from which channel>" << endl;
	}
	break;
      }
    case 12: // add
      {
	string user = "";
        string pass = "";
        string adminInd = "";
        string rName = "";
        string uData = "";
        char delim = 2;

        if(iss >> user) {
          if(iss >> pass) {
            uData += pass;
            uData += delim;
            if(iss >> adminInd) {
              if(adminInd == "Normal" || adminInd == "Admin") {
                if(adminInd == "Admin") {
                  uData += 'A';
                }
                uData += delim;
              }
              else {
                cout << "User type indicator missing Admin/Normal" << endl;
                break;
              }
              iss.get(); // Removes empty space
              if(getline(iss, rName)) { // Rest of line is real name
                uData += rName;
                uData += delim;
                
                ServerCommand* cmd =
                  new ServerCommand(mUserName, ServerCommand::addUser,
                                    user, uData);
                pServer->recvCmd(cmd);
                delete(cmd);
              }
              else
                cout << "No real name given" << endl;
            }
            else
              cout << "Admin indicator and real name missing" << endl;
          }
          else
            cout << "User information missing" << endl;
        }
        else
          cout << "Usage: add <user name> <user password> <Admin|Normal> <real name>" << endl;
        
        
	break;
      }
    case 13: // remove
      {
        string user = "";
        if(iss >> user) {
          ServerCommand* cmd =
            new ServerCommand(mUserName, ServerCommand::removeUser,
                              user, "");
          pServer->recvCmd(cmd);
          delete(cmd);
        }
        else
          cout << "Usage: remove <user name>" << endl;
        break;
      }
    default:
      if(choose != "")
	cout << "Unrecognized command, for list of commands type help" << endl;
      break;
      
    }
  }
}

int
CLConnection::mapToInt(string val)
{
  CommandList::iterator p = mCommands.find(val);
  if(p != mCommands.end())
    return p->second;
  return -1;
}

void
CLConnection::printCommands()
{
  cout << "Following are the commands:" << endl;
  CommandList::iterator p = mCommands.begin();
  for(; p != mCommands.end(); ++p)
    cout << p->first << endl;
}
