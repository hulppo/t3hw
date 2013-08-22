#ifndef _MATHBOTCONNECTION_H_
#define _MATHBOTCONNECTION_H_

#include "Connection.h"

#include <pthread.h>
/** Class MathBotConnection. A bot that asks other users simple
    mathematical calculations.
*/
class MathBotConnection : public Connection {
 public:
  /** Constructor.
  */
  MathBotConnection(long connId, std::string uName, Server* serv, std::string pword);

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
  /// Sum of two random numbers
  int sumOfRandoms;
  /// Amount of wrong answers received
  int wrongMessagesReceived;
};

#endif // _MATHBOTCONNECTION_H_
