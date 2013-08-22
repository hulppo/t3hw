#include "CHAdapter.h"

#include "Server.h"

//#include "ConnectionAdapter_impl.h"

#include <iostream>

CORBA::ORB_var orb;
CORBA::BOA_var boa;

class CHAdapter_impl : virtual public CHAdapter_skel {
private:
  Server* pServer;


public:

  CHAdapter_impl() {
    this->pServer = new Server(10);
  };

  char* registerUser(const char* userName, const char* password, const char* client) {
    string uName(userName);
    string pWord(password);
    if(pServer->authenticateUser(uName, pWord)) {
      //ConnectionAdapter_impl* cAdapter =
      //  new ConnectionAdapter_impl(uName);
    cout << "Authentication successful for " << uName << endl;
    }
  };

};

int main(int argc, char* argv[])
{
  orb = CORBA::ORB_init(argc, argv,"mico-local-orb");
  boa = orb->BOA_init(argc, argv, "mico-local-boa");

  CHAdapter_impl* connHandler = new CHAdapter_impl();
  
  CORBA::String_var ref = orb->object_to_string(connHandler);

  cout << "Server reference: " << ref << endl;

  //-- client
  CORBA::Object_var obj = orb->string_to_object(ref);
  CHAdapter_var client = CHAdapter::_narrow(obj);

  client->registerUser("tommy", "cool", "test");

  CORBA::release(connHandler);
  return 0;

}
