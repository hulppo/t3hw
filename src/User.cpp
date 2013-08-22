#include "User.h"

#include "ChannelMessage.h"
#include "PrivateMessage.h"
#include "Connection.h"

using namespace std;

#include <iostream>

// Constructor.
User::User(string userName, 
	   string realName,
	   string password, 
	   bool isAdmin) {
  mUserName = userName;
  mRealName = realName;
  mPassWord = password;
  mIsAdmin = isAdmin;
  mConnection = 0;
}

// Sets the connection for this user.
void
User::setConnection(Connection* connection) {
  mConnection = connection;
}



// Sends a message to connection.
void
User::sendMsg(Message* message) {
  if(mConnection != 0) {
    mConnection->sendMsg(message);
  }
}



// Sends a channel message to connection.
void
User::sendMsg(ChannelMessage* chMessage) {
  if(mConnection != 0) {
    mConnection->sendMsg(chMessage);
  }
}



// Sends a private message to connection.
void
User::sendMsg(PrivateMessage* prMessage) {
  if(mConnection != 0) {
    mConnection->sendMsg(prMessage);
  }
}



// Tells username of this user.
std::string
User::getUserName() {
  return mUserName;
}



// Tells if this user is administrator.
bool
User::isAdmin() {
  return mIsAdmin;
}



// Returns a string containing information of this user
string
User::getInfo() {
  string info = "Username: ";
  info += mUserName;
  info += "\nRealname: ";
  info += mRealName;
  info += "\nUser type: ";
  if(mIsAdmin)
    info += "Admin\n";
  else
    info += "Normal\n";
  return info;
}

string
User::getRealName() {
  return mRealName;
}

string
User::getPassword() {
  return mPassWord;
}
