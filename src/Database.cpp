#include "User.h"
#include "Database.h"
#include "PrivateMessage.h"

#include <pthread.h>

using namespace std;

// Constructor, opens the database file and creates
// all users defined in database file.
Database::Database() {

  pthread_mutex_init(&mLock,NULL);

  this->file.open("database.dat",ios::in);

  char userName[40];
  char realName[40];
  char password[40];
  char type[40];
  bool isAdmin;
  char trash[80];
  
  User* user;

  // Create all users defined in the file.
  while(this->file.peek() != -1)
    {
      // Read the user name
      this->file.getline(userName,40,'@');

      // Read the real name
      this->file.getline(realName,40,'@');

      // Read the password
      this->file.getline(password,40,'@');

      // Read the type of user
      this->file.getline(type,40,'@');

      // Read the rest of line
      this->file.getline(trash,80);
    
      // Create the user and adds to userlist
      if(strcmp(type, "admin") == 0)
	isAdmin = true;
      else
	isAdmin = false;
      
      user = new User(std::string(userName), std::string(realName), 
		      std::string(password), isAdmin);

      mUsers[std::string(userName)] = user;
    }

  this->file.close();
}

Database::~Database() {
  this->writeToFile();

  UserList::iterator p;

  for(p = mUsers.begin(); p != mUsers.end(); ++p)
    {
      User* user = p->second;
      mUsers.erase(p);
      delete(user);
    }


}
// Checks password for given user.
bool
Database::checkUser(string userName,string userPasswd) {

  pthread_mutex_lock(&mLock);
  bool ok = false;
  UserList::iterator p = mUsers.find(userName);
  std::string password;

  if(p != mUsers.end())
    {
      password = p->second->getPassword();

      if(strcmp(password.c_str(), userPasswd.c_str()) == 0)
	ok = true;
    }

  pthread_mutex_unlock(&mLock);

  return ok;
}



// Returns a user object, according to given username.
User*
Database::getUser(string userName){

  pthread_mutex_lock(&mLock);

  User* user;
  User* returnUser;
  
  user = mUsers.find(userName)->second;

  returnUser = new User(user->getUserName(), user->getRealName(),
			user->getPassword(), user->isAdmin());

  pthread_mutex_unlock(&mLock);
  return returnUser;
}



// Writes all users to the database file,
// overwrites the old file
// No need to synch, not in interface
void
Database::writeToFile(){
  pthread_mutex_lock(&mLock);
  this->file.open("database.dat",ios::trunc | ios::out);  

  UserList::iterator p;
  std::string userName;
  std::string realName;
  std::string password;
  std::string type;
  
  for(p = mUsers.begin(); p != mUsers.end(); ++p)
    {
      userName = p->second->getUserName();
      realName = p->second->getRealName();
      password = p->second->getPassword();
      
      if(p->second->isAdmin())
	type = "admin";
      else
	type = "normal";

      this->file << userName << '@';
      this->file << realName << '@';
      this->file << password << '@';
      this->file << type << '@';
      this->file << "\n";

    }  
  this->file.close();
  pthread_mutex_unlock(&mLock);
}



// Adds one user into the database.
bool
Database::addUser(User* user){
  pthread_mutex_lock(&mLock);
  bool ok = false;
  UserList::iterator p;
  std::string userName;

  userName = user->getUserName();

  p = mUsers.find(userName);

  /// New user
  if(p == mUsers.end())
    {
      mUsers[userName] = user;
      ok = true;
    }

  pthread_mutex_unlock(&mLock);
  return ok;
}



// Updates one user's information in the database.
bool
Database::updateUser(User* user){
  pthread_mutex_lock(&mLock);
  bool ok = false;
  UserList::iterator p;
  std::string userName;

  userName = user->getUserName();

  p = mUsers.find(userName);

  // User found
  if(p != mUsers.end())
    {
      p->second = user;
      ok = true;
    }
  
  pthread_mutex_unlock(&mLock);
  return ok;
}




// Removes one user from the database.
bool
Database::removeUser(std::string userName){
  pthread_mutex_lock(&mLock);

  bool ok = false;

  UserList::iterator p;
  User* user;

  p = mUsers.find(userName);

  if(p != mUsers.end())
    {
      ok = true;
      user = mUsers.find(userName)->second;

      mUsers.erase(userName);
      delete(user);
    }

  pthread_mutex_unlock(&mLock);
  return ok;
}


// Adds a copy of unreceived private message to the database.
bool
Database::addMessage(PrivateMessage* message){
    pthread_mutex_lock(&mLock);

    bool addOK = false;
    UserList::iterator p;
    PrivateMessage* copy;

    p = mUsers.find(message->receiver);

    if(p != mUsers.end())
      {
        copy = new PrivateMessage(message->sender,
                                  message->receiver,
                                  message->text);

        MessageList::value_type t(copy->receiver, copy);
        mMessages.insert(t);
        addOK = true;
      }

    pthread_mutex_unlock(&mLock);
    return addOK;
}



/// Returns the unreceived private message and removes
/// it from the message list.
PrivateMessage*
Database::getMessage(std::string userName){
  pthread_mutex_lock(&mLock);

  PrivateMessage* message = 0;
  MessageList::iterator p;

  p = mMessages.find(userName);

  if(p != mMessages.end())
    {
      message = p->second;
      
      mMessages.erase(p);
    }

  pthread_mutex_unlock(&mLock);

  return message;
}
