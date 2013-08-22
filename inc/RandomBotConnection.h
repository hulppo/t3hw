#ifndef RANDOMBOTCONNECTION_H_
#define RANDOMBOTCONNECTION_H_

#include "Connection.h"
#include <map>
#include <string>

/** Class RandomBotConnection. Sends random messages.
*/
class RandomBotConnection : public Connection {
 public:
  /**
     Constructor.
   */
  RandomBotConnection(long connId, std::string uName, Server* serv, std::string pword);

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
  /// Channel to join
  std::string myChannel;
  /// Password
  std::string myPass;
  /// List of phrases
  std::map<int, std::string> mPhraseList;
};




#endif //RANDOMBOTCONNECTION_H_
