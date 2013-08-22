#ifndef _SIMPLEBOTCONNECTION_H_
#define _SIMPLEBOTCONNECTION_H_

#include "Connection.h"
#include <pthread.h>

/** Class SimpleBotConnection. This connection simulates a very simple
    person. Changed the semaphore usage to pthread_cond because semaphore
    isn't implemented on computers in Niksula.
*/
class SimpleBotConnection : public Connection {
 public:
  /** Constructor.
   */
  SimpleBotConnection(long connId, std::string uName, Server* serv, std::string pword);

  /**
     @see Connection
   */
  void sendMsg(Message* msg);

  /**
     @see Connection
   */
  void sendMsg(PrivateMessage* msg);

  /**
     @see Connection
   */
  void sendMsg(ChannelMessage* msg);

  /**
     @see Connection
   */
  void* Execute();

 private:
  // Used for sending a message when a message is received

  /// Locks the adding and decreasing of waitingMsgs
  pthread_mutex_t msgCount_mutex;
  /// Condition to signal when changes have happened to waitingMsgs
  pthread_cond_t countChange_cond;

  /// Amount of waiting messages
  int waitingMsgs;

  /// Channel to join
  std::string myChannel;
  /// What kind of message received
  int mMsgTypeReceived;
  /// Password
  std::string myPass;
};

#endif // _SIMPLEBOTCONNECTION_H_
