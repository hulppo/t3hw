#include "MathBotConnection.h"

#include "Server.h"
#include "PrivateMessage.h"
#include "ChannelMessage.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h> // Enables sleep command

using namespace std;

MathBotConnection::MathBotConnection(long connId, 
				     std::string uName, 
				     Server* serv, 
				     string pass)
  : Connection(connId,uName,serv)
{
  this->myChannel = "test";
  this->myPass = pass;
  this->wrongMessagesReceived = 0;

  waitingMsgs = 0;
  pthread_mutex_init(&msgCount_mutex, NULL);
  pthread_cond_init(&countChange_cond, NULL);
}

void
MathBotConnection::sendMsg(Message* msg) {
  
}

void
MathBotConnection::sendMsg(PrivateMessage* msg) {
  pthread_mutex_lock(&msgCount_mutex);
  waitingMsgs++;
  this->mMsgTypeReceived = 1;
  pthread_cond_signal(&countChange_cond);
  pthread_mutex_unlock(&msgCount_mutex);
}

void
MathBotConnection::sendMsg(ChannelMessage* msg) {
  if(msg->sender != mUserName) {
    char sum[80];
    sprintf(sum,"%d",sumOfRandoms);
    string text = msg->text;

    if(text.find(sum) != text.npos )
      {
	pthread_mutex_lock(&msgCount_mutex);
	waitingMsgs++;
	this->wrongMessagesReceived = 0;
        this->mMsgTypeReceived = 0;
	pthread_cond_signal(&countChange_cond);
	pthread_mutex_unlock(&msgCount_mutex);
      }
    else
      {
	pthread_mutex_lock(&msgCount_mutex);
	waitingMsgs++;
        this->wrongMessagesReceived++;
        this->mMsgTypeReceived = 2;
	pthread_cond_signal(&countChange_cond);
	pthread_mutex_unlock(&msgCount_mutex);
      }
  }
}

void*
MathBotConnection::Execute() {
  if(pServer->authenticateUser(mUserName, myPass)) {
    if(!pServer->joinServer(this->mUserName, this))
      return 0;
  }
  else
    return 0;
      
  
  bool joinSuccess = false;
  
  while(!joinSuccess) {
    
    sleep(15);
    if(pServer->joinChannel(this->mUserName, this->myChannel))
      break;			
  }
  
  char text[80];

  int number1;
  int number2;
  number1 = 1+(int)(40.0*rand()/(RAND_MAX+1.0));
  number2 = 1+(int)(40.0*rand()/(RAND_MAX+1.0));
  this->sumOfRandoms = number1 + number2;
  
  sprintf(text,"Does someone know how much is %d + %d?",number1,number2);
  
  ChannelMessage* msg;
  msg = new ChannelMessage(this->mUserName, this->myChannel, text);
    
  pServer->recvMsg(msg);
  delete(msg);
  msg = 0;
  while(1<2) {
    pthread_mutex_lock(&msgCount_mutex);
    if(!waitingMsgs)
      pthread_cond_wait(&countChange_cond,&msgCount_mutex);
    waitingMsgs--;
    pthread_mutex_unlock(&msgCount_mutex);

    switch(mMsgTypeReceived) {
    case 0:
      {
        number1 = 1+(int)(40.0*rand()/(RAND_MAX+1.0));
        number2 = 1+(int)(40.0*rand()/(RAND_MAX+1.0));
        this->sumOfRandoms = number1 + number2;
        
        sprintf(text,"That's right!! But does someone know how much is %d + %d?",number1,number2);
        
        msg = new ChannelMessage(this->mUserName, this->myChannel, text);
        pServer->recvMsg(msg);
        delete(msg);
        break;
      }
    case 1:
      {
        msg = new ChannelMessage(this->mUserName, 
                                 this->myChannel, 
                                 "Hey don't send me any private messages");
        pServer->recvMsg(msg);
        delete(msg);
        break;
      }
      
    case 2:
      {
        if(this->wrongMessagesReceived > 10)
        {
          this->wrongMessagesReceived = 0;
          
          number1 = 1+(int)(40.0*rand()/(RAND_MAX+1.0));
          number2 = 1+(int)(40.0*rand()/(RAND_MAX+1.0));
          this->sumOfRandoms = number1 + number2;
          
          sprintf(text,"OK here is a new one. Does someone know how much is %d + %d?",number1,number2);
          
          msg = new ChannelMessage(this->mUserName, this->myChannel, text);
          pServer->recvMsg(msg);
          delete(msg);
        }
        break;
      }

    }
    mMsgTypeReceived = -1;
    
  }
  
  return 0;
}
