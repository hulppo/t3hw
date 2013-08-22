#include "RandomBotConnection.h"

#include "Server.h"
#include "PrivateMessage.h"
#include "ChannelMessage.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h> // Enables sleep command

using namespace std;

RandomBotConnection::RandomBotConnection(long connId, 
				     std::string uName, 
				     Server* serv, 
				     string pass)
  : Connection(connId,uName,serv)
{
  this->myChannel = "test";
  this->myPass = pass;
  mPhraseList[0] = "Hello";
  mPhraseList[1] = "To you too";
  mPhraseList[2] = "We don't understand the software, and sometimes we don't understand the hardware, but we can *see* the blinking lights!";
  mPhraseList[3] = "The chief danger in life is that you may take too may precautions.";
  mPhraseList[4] = "Beauty is only skin deep, but ugly goes clean to the bone.";
  mPhraseList[5] = "And on the seventh day, He exited from append mode.";
  mPhraseList[6] = "Reality is bad enough, why should I tell the truth?";
  mPhraseList[7] = "If entropy is increasing, where is it coming from?";
  mPhraseList[8] = "I'm defending her honor, which is more than she ever did.";
  mPhraseList[9] = "It is impossible to travel faster than light, and certainly not desirable, as one's hat keeps blowing off.";
  mPhraseList[10] = "The world is coming to an end.  Please log off.";

}

void
RandomBotConnection::sendMsg(Message* msg) {
  
}
void
RandomBotConnection::sendMsg(PrivateMessage* msg) {

}

void
RandomBotConnection::sendMsg(ChannelMessage* msg) {
  
}

void*
RandomBotConnection::Execute() {
  if(pServer->authenticateUser(mUserName, myPass)) {
    if(!pServer->joinServer(this->mUserName, this))
      return 0;
  }
  else
    return 0;

  bool joinSuccess = false;
  
  while(!joinSuccess) {
    sleep(5);
    if(pServer->joinChannel(this->mUserName, this->myChannel))
      break;			
  }

  
  while(1<2) {
    int sleepTime = 5+(int)(5*rand()/(RAND_MAX+1.0)); //Sleeps 5-10s
    sleep(sleepTime);

    int phraseNum = (int)((float)(mPhraseList.size())*rand()/(RAND_MAX+1.0));
    string msgText = mPhraseList[phraseNum];

    ChannelMessage * msg =
      new ChannelMessage(mUserName, this->myChannel, msgText);

    pServer->recvMsg(msg);

    delete(msg);
  }

  return 0;
}
