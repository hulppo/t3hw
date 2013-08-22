#ifndef CHANNELCOMMAND_H_
#define CHANNELCOMMAND_H_

#include "Command.h"

/** Class ChannelCommand
    This class represents a command that is used to
    control the channels. There is a method in channels
    to receive ChannelCommand objects.
*/
class ChannelCommand : public Command {
 public:

  /// a public enum, specifying the different command
  /// types.
  enum eChannelCom { createChannel, destroyChannel, 
		     kickUser, banUser };

  /// A public const member variable holding
  /// the type of the command.
  const eChannelCom com;


  /** Constructor, creates a new ServerCommand object,
      calls the parent constructor to set the sender.
      @param s Name of the sender of the command
      @param com An enum that specifies the command.
      @param tUser Name of the user the action is meant for
      @param userData Contains user data, for example when adding
      a user it contains the password
  */
  ChannelCommand(std::string s, eChannelCom c, std::string tUser,
		std::string ch) : Command(s), com(c) {
    this->targetUser = tUser;
    this->channel = ch;
  };

  /** Returns the username of the target user for this
      command.
      @return std::string Username of the target user.
  */
  std::string getTargetUser() { return targetUser; };
  
  /** Returns the channel to which this command
      is targeted.
      @return std::string
  */
  std::string getChannel() { return channel; };


 private:

  /// The username of the target user for this command.
  std::string targetUser;
  /// The name of the target channel for this command.
  std::string channel;

};



#endif //  CHANNELCOMMAND_H_
