#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>

/** Message class.
    This class is used as an abstraction for messages.
*/
class Message {
 public:
  /** Constructor. Constructs a new message object.
      @param sender Username of the sender
      @param text Contents of the message
  */
  Message(std::string sender, std::string text);

  
  ///a public member variable for holding the userid of the sender
  const std::string sender;

  ///a public member variable for holding the message contents
  const std::string text;
};


#endif //MESSAGE_H_
