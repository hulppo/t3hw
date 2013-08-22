#include "ConnectionAdapter.h"

class Server;

/** Class ConnectionAdapter_impl.

*/
class ConnectionAdapter_impl : 
  virtual public ConnectionAdapter_skel, public Connection {

public:
  ConnectionAdapter_impl(Server* serv);

  void getServerInfo();
  
private:
  string mUserName;

  Server* pServer;
  
};
