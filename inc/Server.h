#ifndef SERVER_H_
#define SERVER_H_

#include "Database.h"

#include <string>
#include <map>

#include "SynchronizedMap.h"

class Connection;
class User;
class Channel;
class Message;
class ChannelMessage;
class PrivateMessage;
class ServerCommand;
class ChannelCommand;


/** Class Server
    This is the central class, it keeps record of the active users
    and channels. It also works as a gateway for sending messages.
*/
class Server {
 public:

  /** Constructor.
      @param chLimit Max number of channels on server.
  */
  Server(int chLimit);

  /** Destructor.
   */
  ~Server();

  /** User is authenticated. Authenticates the user
      towards the database.
      @return Is the user real
      @param uName Name of the user
      @param pass Password for the user
  */
  bool authenticateUser(std::string uName, std::string pass);

  
  /** User joins server.
      Should be called after user has been authenticated.
      This function gets called when a user wants to join this server.
      @return bool Was the join successful
      @param uName Name of the user
      @param conn The users connection object, used for sending messages
      back to the user.
   */
  bool joinServer(std::string uName, Connection* conn);  

  /** User exits server.
      This method gets called when a user wants to exit the server.
      @return boolean was the exit successful
      @param uName Name of the user
  */
  bool exitServer(std::string uName);

  /** User joins a channel
      Gets called when a user wants to join a channel. Adds the user to
      the Channel specified. If the join fails then it returns false.
      @return boolean was the channel join successful
      @param uName Name of the user
      @param chName Channel to join
  */
  bool joinChannel(std::string uName, std::string chName);

  /**  User exits channel
       Gets called when a user wants to exit a channel. Removes the
       user from the channel.
       @return boolean was the channel exit successful
       @param uName Name of the user
       @param chName Channel to exit
  */
  bool exitChannel(std::string uName, std::string chName);
  
  /** Sends channel list
      Sends a list of channels as a string to the user.
      @return boolean Send successful
      @param std::string UserName to send to
  */
  bool sendChannelList(std::string uName);

  /** Receives ChannelMessages. The message is
      checked for which channel it is meant and sent there.
      @param msg ChannelMessage
  */
  void recvMsg(ChannelMessage* msg);

  /** Receives PrivateMessages. A check is performed whether the
      user is active, otherwise the message is sent to UserDataBase.
      @return boolean was the processing successful, i.e. did the user
      exist
  */
  bool recvMsg(PrivateMessage* msg);

  /** Receival of ServerCommands. They get processed.
      @return boolean Was the command recognized
      @param cmd ServerCommand
  */
  bool recvCmd(ServerCommand* cmd);

  /** Receival of ChannelCommands. They get processed. Some commands
      might be delegated to channels.
      @return boolean Was the command recognized
      @param cmd ChannelCommand
  */
  bool recvCmd(ChannelCommand* cmd);

 private:
  typedef std::map<std::string, Channel*> ChannelList;
  typedef std::map<std::string, User*> UserList;

  /// A synchronized map containing the channels
  SynchronizedMap<std::string, Channel*> mChannels;
  /// Max amount of channels, not implemented yet
  int mChannelLimit;
  /// A synchronized map containing the active users
  SynchronizedMap<std::string, User*> mUsers;

  /** Adds channel. If channel already exists returns false
      @return Was the channel added
      @param chName Name of channel to add
  */
  bool addChannel(std::string chName);

  /** Removes channel.
      @return Was the channel removed
      @param chName Name of channel to remove
  */
  bool removeChannel(std::string chName);

  /** Sends message. Sends a system msg to the user specified by
      receiver. 
      @return Did the user exist
      @param receiver User to receive message
      @param text Content of message
  */
  bool sendSystemMsg(std::string receiver, std::string text);


  /** Authorizes the user. Checks whether the user has
      admin rights.
      @return Does the user have admin rights
  */
  bool adminAuthorize(std::string uName);

  /** Sends private msgs from database to user.
      @param uName Name of the user

  */
  void sendPrivateMsgs(std::string uName);


  /// a private member variable for contacting the database
  Database* myDb;

};

#endif // SERVER_H_
