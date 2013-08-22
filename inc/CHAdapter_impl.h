#ifndef _CHADAPTER_IMPL_H_
#define _CHADAPTER_IMPL_H_

#include "CHAdapter.h"

class Server;
class CLConnection;

/** Class CHAdapter_impl. This is remote interface. 
    This class is where the clients connect at first. They get
    authenticated and after that get their own ConnectionAdapters. 
    This class also starts up the server.
 */
class CHAdapter_impl : virtual public CHAdapter_skel {
 public:

  /** Constructor. Constructs the CHAdapter_impl.
      @param orb The object request broker. This is used for translating
      strings to objects and vice versa.
   */
  CHAdapter_impl(CORBA::ORB_var orb);

  /** Connects a new user. Called over the remote.
      @param userName Name of the user
      @param password Password for the user
      @param client ClientAdapter_var used for callbacks to client
   */
  char* registerUser(const char* userName, const char* password, const char* client);

private:
  /// Pointer to the server
  Server* pServer;
  /// Pointer for keeping the object request broker accessable
  CORBA::ORB_var mORB;
  /// Pointer to the server command line interface
  CLConnection* comLine;

};

#endif // _CHADAPTER_IMPL_H_
