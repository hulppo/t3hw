#ifndef USER_H_
#define USER_H_

#include <string>

#include "SynchronizedObject.h"

class Connection;
class Message;
class PrivateMessage;
class ChannelMessage;

/** Class User.
    Contains personal information about user and
    the connection to which it is connected.
    Is also used to send messages to the connection.
*/
class User : public SynchronizedObject {
 public:

  
  /** Constructor, creates a new user object
      @param userName User name to give for this user.
      @param realName Realname of this user.
      @param password Password to give for this user.
      @param isAdmin Is this user admin.
   */
  User(std::string userName,std::string realName,
       std::string password,bool isAdmin);
  

  /** Connects a user to a given connection.
      @param conn Connection to which user is connected.
  */
  void setConnection(Connection* connection);


  /** Sends a message to the connection.
      @param message Message to send.
   */
  void sendMsg(Message* message);


  /** Sends a channel message to the connection.
      @param chMessage Channel message to send.
  */
  void sendMsg(ChannelMessage* chMessage);


  /** Sends a private message to the connection.
      @param priMessage Private message to send.
  */
  void sendMsg(PrivateMessage* prMessage);



  /** Tells the name of this user.
      @return const string Username of this user.
   */
  std::string getUserName();


  /** Tells if this user is administrator.
      @return boolean Returns boolean true if this user
      is administrator.
   */
  bool isAdmin();


  /** Returns a string containing information about this user.
      @return string Username, realname and user type of
      this user.
   */
  std::string getInfo();

  /** Returns the real name of the user.
      @return real name
   */
  std::string getRealName();
  
  /** Returns the Password of the user.
      @return password
   */
  std::string getPassword();
  
  
 private:

  /// Username of this user
  std::string mUserName;
  /// Password of this user
  std::string mPassWord;
  /// Realname of this user
  std::string mRealName;
  /// This user's connection
  Connection* mConnection;
  /// If this user is Admin then value is true;
  bool mIsAdmin;
};

#endif // USER_H_
