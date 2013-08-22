#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <map>
#include <string>
#include <vector>

#include "SynchronizedObject.h"
#include "pthread.h"
class User;
class ChannelMessage;
class ChannelCommand;


/** Class Channel
    Channel represents one chat channel on server.
    It can receive channel messages and channel commands
    and send messages to all users on it.
    It has an unique name, pointers to all users that
    have joined to it and a limit for maximum number of
    users.
*/
class Channel : public SynchronizedObject {
 public:
  
  /** Consructor, creates a new Channel object with
      the given name and a limit for users.
      @param channelName Name for this channel.
      @param userLimit Limit for number of users.
   */
  Channel(std::string channelName, 
	  int userLimit);
  

  /** Adds one user to this channel.
      @return boolean Returns boolean true if add
      was OK.
      @param user Pointer to the user to add.
   */
  bool addUser(User* user);
  

  /** Removes one user from this channel.
      @return User* User* is returned so we can remove the reference from
      SynchronizedMap
      @param userName Username of the user to remove.
   */
  User* removeUser(std::string userName);
  
  /** Receives a channel message and sends it
      to all users on the channel.
      @param msq Channel message to receive.
   */
  void recvMsg(ChannelMessage* msg);


  /** Receives a channel command and makes actions
      according to it.
      @param boolean Returns boolean true if command
      was OK.
      @param cmd Channel command to receive.
   */
  bool recvCmd(ChannelCommand* cmd);


  /** Returns a string containing usernames of
      all users on this channel, each separated with
      space character.
      @return string Returns string containing the
      usernames.
   */
  std::string getUsers();


  /** Destroys this channel. Also notifies the users
      that the channel is closing.
   */
  std::vector<User*> destroyChannel();

 private:

  /** Private method.
      Sends a message to all users on this channel.
      @param sender The name of the sender.
      @param msgText The text of the message.
   */
  void sendToAll(std::string sender, 
		 std::string messageText);

  /** Private method.
      Tells if user is joined on this channel.
      @return boolean Returns boolean true if user is on this
      channel.
      @param userName Username to check.
  */
  bool isJoined(std::string userName);


  /// Name of this channel.
  std::string mChannelName;

  /// Map containing the pointers to the users.
  /// Usernames are used as keys.
  typedef std::map<std::string, User*> UserList;
  UserList mUsers;

  /// Limit for number of users on this channel.
  unsigned int mUserLimit;
  
  /// Channel lock
  pthread_mutex_t mLock;
    //MutualExclusion* mLock;

  /// Tells the methods of this class that destroy has been called
  bool mShutdown;

};

#endif //CHANNEL_H_
