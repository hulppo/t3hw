#ifndef CLCONNECTION_H_
#define CLCONNECTION_H_

#include "CORBA.h"

#include "Connection.h"
#include <map>
#include <string>

/** Class CLConnection. This class makes a connection
    to the command line. Taking commands and letting users log
    in from the commandline. This class also is used for shutting
    down the server.
*/
class CLConnection : public Connection {
 public:
  /** Constructor.
      @param connId Connection demands the Connection Id
      @param serv Pointer to the server
      @param orb object request broker. Needed for shutdown of server
   */
  CLConnection(long connId, Server* serv, CORBA::ORB_var orb);

  /**
     @see Connection
  */
  void sendMsg(Message* msg);

  /**
     @see Connection
  */
  void sendMsg(PrivateMessage* msg);

  /**
     @see Connection
  */
  void sendMsg(ChannelMessage* msg);

  /**
     @see Connection
  */
  void* Execute();

 private:
  ///User has been authenticated by server
  void insideServer();
  /// Turns string commands to int
  int mapToInt(std::string);
  /// Prints available commands to cout
  void printCommands();
  /// Map for holding the commands
  typedef std::map<std::string, int> CommandList;
  CommandList mCommands;

  /// Pointer to the orb
  CORBA::ORB_var mORB;
};



#endif // CLCONNECTION_H_
