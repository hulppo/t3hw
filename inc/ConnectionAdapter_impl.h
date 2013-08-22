#ifndef _CONNECTIONADAPTER_IMPL_H_
#define _CONNECTIONADAPTER_IMPL_H_

#include "ConnectionAdapter.h"

#include "Connection.h"

#include "ClientAdapter.h"

#include <string>

class Server;
class PrivateMessage;
class ChannelMessage;
class Message;

/** Class ConnectionAdapter_impl. This is a remote interface.
    This class functions as a gateway between the client and the 
    server after the client has been authenticated. Inherits Connection 
    and can therefore be used as an output towards the client. One of
    these are created for every incoming authenticated user. This is a
    CORBA inherited class, enabling remote method calls over TCP/IP.
    Messages propagate through this class in both directions. Those coming
    from the client are called incoming and those headed for the client
    are called outgoing.
*/
class ConnectionAdapter_impl : 
  virtual public ConnectionAdapter_skel, public Connection {

public:
  /** Constructor. Constructs the ConnectionAdapter.
      @param uName Name of the user this Connection belongs to.
      @param serv Pointer to server
      @param client The outgoing messages are propagated to ClientAdapter
  */
  ConnectionAdapter_impl(std::string uName, Server* serv, ClientAdapter_var client);

  //////////////////////////////
  //Incoming - overriden from class ConnectionAdapter

  /** Incoming.Exits this user from server. 
  */
  void exitServer();

  /** Incoming. Joins user to channel
      @return Whether join was successful
      @param chName Name of channel to join
  */
  CORBA::Boolean joinChannel(const char* chName);

  /** Incoming. Exits user from channel
      @return False if user isn't on channel
      @param chName Name of channel to exit
  */
  CORBA::Boolean exitChannel( const char* chName );

  /** Incoming. Sends a channel message.
      @param chName Channel to send to
      @param text Contents of message
   */
  void sendChannelMsg( const char* chName, const char* text);

  /** Incoming. Sends a private message.
      @param receiverName Name of the receiver
      @param text Contents of message.
  */
  void sendPrivateMsg( const char* receiverName, const char* text);

  /** Incoming. Asks the server to send information about the server. Number of
      channels and active users.
   */
  void getServerInfo();

  /** Incoming. Asks the server to send information about active users.
   */
  void getUserInfo();

  /** Incoming. Asks the server to send information about the channels and 
      who is logged in on them.
   */
  void getChannelInfo();

  /** Incoming. Creates a user with user name, password and real name.
      @param uName User name for the new user
      @param pass Password for the new user
      @param rName Real name for the new user
      @param isAdmin Should the new user have admin rights
  */
  void createUser( const char* uName, 
                   const char* pass, 
                   const char* rName,
                   CORBA::Boolean isAdmin);

  /** Incoming. Removes user from database.
      @param targetUser Name of the user to remove
  */
  void removeUser( const char* targetUser);

  /** Incoming. Creates a new channel.
      @param chName Name of channel to create.
  */
  void createChannel( const char* chName );

  /** Incoming. Destroys a channel.
      @param chName Name of channel to destroy
  */
  void destroyChannel( const char* chName );

  /** Incoming. Kicks user from server.
      @param targetUser Name of user to kick
  */
  void kickUserFromServer( const char* targetUser );

  /** Incoming. Kicks user from channel
      @param targetUser Name of user to kick
      @param chName From which channel to kick user
   */
  void kickUserFromChannel( const char* targetUser, const char* chName );
  
  //////////////////////////////////////
  // Outgoing - overridden from Class Connection

  /** Outgoing. Sends a message to the client.
      @param msg Message to send
  */
  void sendMsg(Message* msg);

  /** Outgoing. Sends a private message to the client
      @param msg Message to send
  */
  void sendMsg(PrivateMessage* msg);

  /** Outgoing. Sends a channel message to the client
      @param msg Message to send
  */
  void sendMsg(ChannelMessage* msg);

private:
  /** Outgoing. Sends an error to the client. Used for sending errors
      occuring in ConnectionAdapter.
      @param info String of information
   */
  void sendError(std::string info);

  /// An adapter pointing to the callback of the owner of this class
  ClientAdapter_var mClient;
};

#endif // _CONNECTIONADAPTER_IMPL_H_
