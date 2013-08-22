#ifndef SERVERCOMMAND_H_
#define SERVERCOMMAND_H_

#include "Command.h"

/** Class ServerCommand
    This class represents a command that is used to
    control the server. There is a method in server
    to receive ServerCommand objects.
*/
class ServerCommand : public Command {
 public:
  
  /// a public enum, specifying the different 
  /// command types
  enum eServerCom {addUser, removeUser, kickUser, 
		   modifyData, serverInfo, userInfo};


  /// A public const  member variable holding
  /// the type of the command.
  const eServerCom com;

  
  /** Constructor, creates a new ServerCommand object, 
      calls the parent constructor to set the sender.
      @param s Username of the sender of this command.
      @param c An enum that specifies the command.
      @param tUser Name of the user the action is meant for
      @param userData Contains user data, when command
      is used to modify user information.
  */
  ServerCommand(std::string s, eServerCom c, std::string tUser
		,std::string userData) : Command(s), com(c) {
    this->targetUser = tUser;
    this->userData = userData;
  };
  

  /** Returns the username of the target user for this
      command.
      @return std::string Username of the target user.
  */
  std::string getTargetUser() { return targetUser; };


  /** Returns the possible userdata in this command.
      @return std::string Userdata of this command.
  */
  std::string getUserData() { return userData; };

 private:
  
  /// The username of the target user for this command.
  std::string targetUser;
    
  /// The name of the target channel for this command.
  std::string userData;
      
};



#endif // SERVERCOMMAND_H_
