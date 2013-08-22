#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "CHAdapter.h"
#include "ConnectionAdapter.h"
#include "ClientAdapter_impl.h"

#include <map>
#include <string>
#include <sstream>

/** Class Client. Works as a parser for the client command line. Starts up
    the ClientAdapter, which receives message calls from the server.
 */
class Client {
 public:
  /** Constructor. Constructs a new Client.
      @param orb object request broker, needed for startup of ClientAdapter
      @param boa basic object adapter, needed for startup of ClientAdapter
      @param server CHAdapter reference to the server
  */
  Client(CORBA::ORB_var orb, CORBA::BOA_var boa, CHAdapter_var server);

  /** Starts the command line parser.
      @return No errors occured
  */
  int startParser();

 private:
  ///User has been authenticated by server
  void insideServer();

  /// Parses commands in iss and acts upon them.
  bool parseCommands(std::istringstream& iss);

  /// Turns string commands to int
  int mapToInt(std::string);
  /// Prints available commands to cout
  void printCommands();
  /// Map for holding the commands
  typedef std::map<std::string, int> CommandList;
  CommandList mCommands;

  /// Pointer to orb
  CORBA::ORB_var mORB;
  /// Pointer to boa
  CORBA::BOA_var mBOA;
  /// Pointer to ConnectionHandlerAdapter
  CHAdapter_var mServer;
  /// Pointer to ConnectionAdapter
  ConnectionAdapter_var activeConnection;

  /// Pointer to the printer of received messages
  ClientAdapter_impl* mPrinter;
};

#endif // _CLIENT_H_
