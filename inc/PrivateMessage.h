#ifndef _PRIVATEMESSAGE_H_
#define _PRIVATEMESSAGE_H_

#include "Message.h"

/** Class PrivateMessage.
    This class inherits Message and is meant for getting sent to
    one user specifically.
*/
class PrivateMessage : public Message {
 public:
  /** Constructor. Creates a new private message object.
      @param sender Username of the sender
      @param rec Username of the receiver
      @param text Contents of message
  */
  PrivateMessage(std::string sender, std::string rec,
		 std::string text);
		 
  /// a public member variable holding the name of the receiver
  std::string receiver;

};




#endif // _PRIVATEMESSAGE_H_
