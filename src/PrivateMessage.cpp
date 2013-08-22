#include "PrivateMessage.h"


PrivateMessage::PrivateMessage(std::string sender, std::string re,
			       std::string text)
  : Message(sender,text), receiver(re)
{

}
