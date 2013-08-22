#include "CHAdapter_impl.h"

#include "Server.h"

#include "ConnectionAdapter_impl.h"

#include <pthread.h>

#include "CLConnection.h" // Includes connection
//Other bots
#include "MathBotConnection.h"
#include "RandomBotConnection.h"

#include "ClientAdapter.h"

void startConnection(Connection* conn); // Forward declaration

CHAdapter_impl::CHAdapter_impl(CORBA::ORB_var orb) {
  this->pServer = new Server(10);
  mORB = orb;
  comLine = new CLConnection(0, this->pServer, orb);
  startConnection(comLine);
  MathBotConnection* mathBot =
    new MathBotConnection(1, "Einstein", this->pServer,
                          "uno");
  startConnection(mathBot);
  RandomBotConnection* randBot =
    new RandomBotConnection(2, "Seko", this->pServer,
                            "salasana");
  startConnection(randBot);
}

// Client calls
char* 
CHAdapter_impl::registerUser(const char* userName, const char* password, const char* client) {
  string uName(userName);
  string pWord(password);
  
  string connectionRef = "";
  
  if(pServer->authenticateUser(uName, pWord)) {
    CORBA::String_var clientRef = client;
    
    CORBA::Object_var obj = mORB->string_to_object(clientRef);
    ClientAdapter_var clientA = ClientAdapter::_narrow(obj);
    
    
    ConnectionAdapter_impl* cAdapter =
      new ConnectionAdapter_impl(uName, pServer, clientA);
    
    if(pServer->joinServer(uName, cAdapter)) { 
      CORBA::String_var ref = mORB->object_to_string(cAdapter);
      connectionRef = ref;
    }
    else {
      CORBA::release(cAdapter);
      connectionRef = "";
    }
      
  }
  
  char* temp = const_cast<char*>( connectionRef.c_str() );
    
  return temp;
}

void*
threadRun(void* connVoid)
{
  Connection* conn = (Connection*) connVoid;
  conn->Execute();
  delete(conn);
  return 0;
}

void
startConnection(Connection* conn)
{
  pthread_t th1;
  pthread_create(&th1, NULL, threadRun, conn);
}


int main(int argc, char* argv[])
{
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv,"mico-local-orb");
  CORBA::BOA_var boa = orb->BOA_init(argc, argv, "mico-local-boa");

  CHAdapter_impl* connHandler = new CHAdapter_impl(orb);
  
  CORBA::String_var ref = orb->object_to_string(connHandler);

  boa->impl_is_ready(CORBA::ImplementationDef::_nil());

  orb->run();

  CORBA::release(connHandler);
  return 0;

}
