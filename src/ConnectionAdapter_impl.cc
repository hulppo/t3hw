#include "ConnectionAdapter_impl.h"

#include "Server.h"

#include "ServerCommand.h"
#include "ChannelCommand.h"
#include "ChannelMessage.h"
#include "PrivateMessage.h"
#include "Message.h"

using namespace std;

ConnectionAdapter_impl::ConnectionAdapter_impl(string uName, Server* serv,
                                               ClientAdapter_var client)
  : Connection(1, uName, serv)
{
  mClient = client;
}

// Incoming
void
ConnectionAdapter_impl::exitServer() {
  pServer->exitServer(mUserName);
}

// Incoming
CORBA::Boolean
ConnectionAdapter_impl::joinChannel(const char* chName) {
  bool ok = false;
  string channel = chName;
  ok = pServer->joinChannel(mUserName, channel);
  return ok;
}

// Incoming
CORBA::Boolean
ConnectionAdapter_impl::exitChannel(const char* chName) {
  bool ok = false;
  string channel = chName;
  ok = pServer->exitChannel(mUserName, channel);
  return ok;
}

// Incoming
void 
ConnectionAdapter_impl::sendChannelMsg( const char* chName, const char* text) {
  string channel = chName;
  string contents = text;

  ChannelMessage* msg =
    new ChannelMessage(mUserName, chName, contents);
  
  pServer->recvMsg(msg);
  delete(msg);
}

// Incoming
void 
ConnectionAdapter_impl::sendPrivateMsg( const char* receiverName, const char* text) {
  string receiver = receiverName;
  string sText = text;

  PrivateMessage* msg =
    new PrivateMessage(mUserName, receiver, sText);
  
  pServer->recvMsg(msg);
  delete(msg);
}

// Incoming
void
ConnectionAdapter_impl::getServerInfo()
{
  ServerCommand* cmd = 
    new ServerCommand(mUserName, ServerCommand::serverInfo,
                      "","");
  pServer->recvCmd(cmd);
  delete(cmd);
}

// Incoming
void
ConnectionAdapter_impl::getUserInfo()
{
  ServerCommand* cmd = 
    new ServerCommand(mUserName, ServerCommand::userInfo,
                      "","");
  pServer->recvCmd(cmd);
  delete(cmd);
}

// Incoming
void
ConnectionAdapter_impl::getChannelInfo()
{
  pServer->sendChannelList(mUserName);
}

// Incoming
void
ConnectionAdapter_impl::createUser(const char* uName, 
                                   const char* pass, 
                                   const char* rName,
                                   CORBA::Boolean isAdmin) {
  string sUName = uName;
  string sUData = "";
  char delim = 2;
  sUData += pass;
  sUData += delim;
  if(isAdmin)
    sUData += 'A';
  sUData += delim;
  sUData += rName;
  sUData += delim;

  ServerCommand* cmd =
    new ServerCommand(mUserName, ServerCommand::addUser,
                      sUName, sUData);

  pServer->recvCmd(cmd);
  delete(cmd);
}

// Incoming
void
ConnectionAdapter_impl::removeUser(const char* uName) {
  string sUName = uName;
  
  ServerCommand* cmd =
    new ServerCommand(mUserName, ServerCommand::removeUser,
                      sUName, "");

  pServer->recvCmd(cmd);
  delete(cmd);
}

// Incoming
void
ConnectionAdapter_impl::createChannel(const char* chName) {
  string channel = chName;
  
  ChannelCommand* cmd =
    new ChannelCommand(mUserName, ChannelCommand::createChannel,
                      "", channel);

  pServer->recvCmd(cmd);
  delete(cmd);
}

// Incoming
void
ConnectionAdapter_impl::destroyChannel(const char* chName) {
  string channel = chName;
  
  ChannelCommand* cmd =
    new ChannelCommand(mUserName, ChannelCommand::destroyChannel,
                      "", channel);

  pServer->recvCmd(cmd);
  delete(cmd);
}

// Incoming
void
ConnectionAdapter_impl::kickUserFromServer(const char* targetUser) {
  string sTarget = targetUser;
  
  ServerCommand* cmd =
    new ServerCommand(mUserName, ServerCommand::kickUser,
                      sTarget, "");

  pServer->recvCmd(cmd);
  delete(cmd);
}

// Incoming
void
ConnectionAdapter_impl::kickUserFromChannel(const char* targetUser, const char* chName) {
  string sTarget = targetUser;
  string channel = chName;
  
  ChannelCommand* cmd =
    new ChannelCommand(mUserName, ChannelCommand::kickUser,
                      sTarget, channel);

  pServer->recvCmd(cmd);
  delete(cmd);
}

// Outgoing
void
ConnectionAdapter_impl::sendMsg(PrivateMessage* msg)
{
  mClient->sendPrivateMessage(msg->sender.c_str(), msg->text.c_str());
}

// Outgoing
void
ConnectionAdapter_impl::sendMsg(ChannelMessage* msg)
{
  mClient->sendChannelMessage(msg->sender.c_str(), msg->channel.c_str(),
                              msg->text.c_str());
}

// Outgoing
void
ConnectionAdapter_impl::sendMsg(Message* msg)
{
  mClient->sendMessage(msg->sender.c_str(), msg->text.c_str());
}

// Outgoing, private
void
ConnectionAdapter_impl::sendError(string info)
{
  mClient->sendError(info.c_str());
}
