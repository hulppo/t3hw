#ifndef _CHANNELMESSAGE_H_
#define _CHANNELMESSAGE_H_

#include "Message.h"

/** Class ChannelMessage.
    This class is inherited from Message,it is meant for going
    to the channels. It gets sent to everybody on one specific channel.
*/
class ChannelMessage : public Message {
 public:
  ChannelMessage(std::string sender, std::string channel,
		 std::string text);

  ///Name of the channel the message is meant for
  const std::string channel;
};


#endif // _CHANNELMESSAGE_H_
