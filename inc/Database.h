#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
// For file operations.
#include <fstream>
#include <map>

#include <pthread.h> //For mutex

class User;
class PrivateMessage;

/** Class Database
    This class accesses the file "database.dat", which
    contains all the information from every user registered for 
    this ChatServer.
    There are methods for accessing and modifying the file
    "database.dat", in this class.
*/

class Database{

 public:

  /** Constructor, creater a new Database object that
      reads and modifies file "database.dat"
  */
  Database();

  /** Destructor.
   */
  ~Database();

  /**
     Checks if there is a user registered in the database
     with given username and password.
     @return boolean Returns boolean true if given username and
     password match.
     @param userName Username to check.
     @param userPasswd User password to check.
  */
  bool checkUser(std::string userName, std::string userPasswd);

  /**
     Creates and returns a new User object, which is initialized
     to the information found in the database for given username.
     @return User* Pointer to the created User object.
     @param userName Username whose information is used.
  */
  User* getUser(std::string userName);

  /** Writes the database into the database file.
   */
  void writeToFile();


  /** Adds one new user to the database.
      @return boolean Returns boolean true if add was OK
      @param user User to add into the database.
   */
  bool addUser(User* user);


  /** Updates one user's information in the database.
      @return boolean Returns boolean true if update was OK.
      @param user User to be updated.
   */
  bool updateUser(User* user);


  /** Removes one user from the database.
      @return boolean Was the user in the database
      @param userName Name of the user to be removed.
   */
  bool removeUser(std::string userName);


  /** Adds one unreceived private message to the database.
      Note that these messages are never written to file.
      @return boolean Returns boolean true if message receiver
      has registered to server and add was OK.
      @param message Unreceived private message to add in the
      database.
   */
  bool addMessage(PrivateMessage* message);
  

  /** Returns one unreceived message send to given user.
      @return PrivateMessage Returns one unreceived private
      message send to given user or 0 if there were none.
      @param userName Name of the user whose messages are
      wanted.
  */
  PrivateMessage* getMessage(std::string userName);

     
 private:

  /// Map for users
  typedef std::map<std::string, User*> UserList;
  UserList mUsers;


  /// Map for unreceived private messages
  typedef std::multimap<std::string, PrivateMessage*> MessageList;
  MessageList mMessages;


  /// File
  std::fstream file;

  /// Lock
  pthread_mutex_t mLock;


};

#endif // DAtABASE_H_
