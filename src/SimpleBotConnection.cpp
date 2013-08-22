#include "SimpleBotConnection.h"

#include "Server.h"
#include "PrivateMessage.h"
#include "ChannelMessage.h"

#include <unistd.h> // Enables sleep command

using namespace std;

SimpleBotConnection::SimpleBotConnection(long connId, std::string uName, Server* serv, string pass)
  : Connection(connId,uName,serv)
{
  this->myChannel = "test";
  this->myPass = pass;

  waitingMsgs = 0;
  pthread_mutex_init(&msgCount_mutex, NULL);
  pthread_cond_init(&countChange_cond, NULL);
}

void
SimpleBotConnection::sendMsg(Message* msg) {
  
}

void
SimpleBotConnection::sendMsg(PrivateMessage* msg) {
  pthread_mutex_lock(&msgCount_mutex);
  waitingMsgs++;
  this->mMsgTypeReceived = 1;
  pthread_cond_signal(&countChange_cond);
  pthread_mutex_unlock(&msgCount_mutex);
}

void
SimpleBotConnection::sendMsg(ChannelMessage* msg) {
  if(msg->sender != mUserName) {
      pthread_mutex_lock(&msgCount_mutex);
      waitingMsgs++;
      this->mMsgTypeReceived = 0;
      pthread_cond_signal(&countChange_cond);
      pthread_mutex_unlock(&msgCount_mutex);

  }
}

void*
SimpleBotConnection::Execute() {
  bool cont = true;
  string pass = "r2d2";

  if(pServer->authenticateUser(mUserName, myPass)) {
    if(!pServer->joinServer(this->mUserName, this))
      return 0;
  }
  else
    return 0;

  bool joinChannelOK = false;
  
  while(!joinChannelOK) {
    sleep(10);
    if(pServer->joinChannel(this->mUserName, this->myChannel))
      break;			
  }

  while(cont) {
    pthread_mutex_lock(&msgCount_mutex);
    if(!waitingMsgs)
      pthread_cond_wait(&countChange_cond,&msgCount_mutex);
    waitingMsgs--;
    pthread_mutex_unlock(&msgCount_mutex);

    ChannelMessage* msg;
    switch(mMsgTypeReceived) {
    case 0:
      sleep(1);
      msg = new ChannelMessage(this->mUserName, this->myChannel, "Send me a private message");
            break;
    case 1:
      sleep(1);
      msg = new ChannelMessage(this->mUserName, this->myChannel, "I've got a new private message");
      break;
    }
    pServer->recvMsg(msg);
    delete(msg);

  }

  return 0;
}
