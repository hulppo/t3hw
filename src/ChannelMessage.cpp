#include "ChannelMessage.h"

ChannelMessage::ChannelMessage(std::string se, std::string ch,
			       std::string te)
  :Message(se,te),channel(ch)
{
  
}
