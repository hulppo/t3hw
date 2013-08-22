#include "Connection.h"
#include "ChannelMessage.h"
#include "PrivateMessage.h"
#include <iostream>

using namespace std;

Connection::Connection(long connId, string userName, Server* serv)
{
  this->connectionId = connId;
  this->mUserName = userName;
  this->pServer = serv;
}

void
Connection::sendMsg(Message* msg) {
  cout << "Debug: Message received. Sender: " << msg->sender << " Text: " << msg->text << endl;
}

void*
Connection::Execute() {
  cout << "Debug: Thread start for user: " << this->mUserName << endl;
  return 0;
}

long
Connection::getId() {
  return connectionId;
}
