#ifndef _CONNECTIONHANDLER_H_
#define _CONNECTIONHANDLER_H_

#include "Server.h"
#include "Connection.h"

//Includes map because the connections are stored in map
//where long is used as the key
#include <map>

/** ConnectionHandler class.
    This class is used for listening to the TCP/IP port
    and accepting connections from it. It creates Connection
    objects for every incoming connection when it is accepted. 
*/
class ConnectionHandler {
 public:
  /** Constructor. Creates a new ConnectionHandler object.
      @param maxNumOfConnections Maximum number of connections
  */
  ConnectionHandler(unsigned int maxNumOfConnections);

  /** Starts the server with the specified maximum channel
      amount.
       @param maxNumOfChannels Maximum number of Channels
   */
  void startServer(int maxNumOfChannels);

  /** Sets the connection handler to listen for incoming
      connections.

  */
  void startListening();

 private:
  
  /** Method for adding connections
      @param conn Pointer to the Connection object
  */
  bool addConnection(Connection* conn);

  /** Starts the given connection
      @param conn Pointer to the Connection object
      @param opt Tells whether to wait for the thread to finish
  */
  void startConnection(Connection* conn, bool waitFor = false);

  /** A private map holding all the Connections.
      It also holds those connections that aren't verified yet.
  */ 
  typedef std::map<long,Connection*> ConnectionList;
  ConnectionList connections;

  ///Max amount of connections
  unsigned int mMaxNumOfConns;

  /// a pointer to the server
  Server* pServer;
};



#endif // _CONNECTIONHANDLER_H_
