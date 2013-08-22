#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <string>

class Server; // Server.h gets included in the cpp file
class Message;
class ChannelMessage;
class PrivateMessage;

/** Class Connection.
    This is an abstract class from where a real connection
    should inherit. The inheriting connection specifies fully
    if it is a command-line, TCP/IP or a dummy connection.
    Connection uses a pointer to the Server class. Connection is started
    by ConnectionHandler as a thread.
*/
class Connection {
 public:
  
  /** Constructor.
      This is the constructor for Connection, every inheriting class should
      call the constructor of this class before making their own initializations.

      @param connId Identification of type long. 
      Should be unique for every Connection object.

      @param userName Name of the user, type std::string

      @param serv Pointer to the Server, type Server*
  */
  Connection(long connId, std::string userName, Server* serv);

  /** Destructor
   */
  virtual ~Connection() { };

  
  /** Sends Message* to user.
      Used for outgoing messages. This method gets called when there is a message
      to send to the user of this connection. It should be overwritten in the
      inheriting class.

      @param msg Type Message*
   */
  virtual void sendMsg(Message* msg);

  /** Sends PrivateMessage* to user.
      Used for outgoing messages. Should implement the sending of a
      private message. Can be overwritten in the inheriting class,
      otherwise calls sendMsg(Message*).

      @param pMsg Type PrivateMessage*

  */
  virtual void sendMsg(PrivateMessage* pMsg) {
    sendMsg((Message*) pMsg);
  };
  
  /** Sends ChannelMessage* to user.
      Used for outgoing messages. Should implement the sending of a 
      channel message. Can be overwritten in the inheriting class
      otherwise calls sendMsg(Message*).

      @param cMsg Type ChannelMessage*
   */
  virtual void sendMsg(ChannelMessage* cMsg) {
    sendMsg((Message*) cMsg);
  };

  ///Thread start
  virtual void*  Execute();

  ///Returns the connection id
  long getId();

 protected:
  /// a protected member variable, holding the name of the user
  std::string mUserName;
  
  /// a protected pointer to server, needed for processing incomming msgs
  Server* pServer;

 private:
  
  /// a private member variable, holding the system level unique id
  long connectionId;

};



#endif //CONNECTION_H_
