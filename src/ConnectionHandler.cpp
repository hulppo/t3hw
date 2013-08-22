#include "ConnectionHandler.h"
#include <iostream>

#include "SimpleBotConnection.h"
#include "MathBotConnection.h"
#include "CLConnection.h"
#include "RandomBotConnection.h"

#include <unistd.h> //Enables use of sleep

#include <pthread.h>

using namespace std;

ConnectionHandler::ConnectionHandler(unsigned int maxNumOfConnections) {
  this->mMaxNumOfConns = maxNumOfConnections;
}

void
ConnectionHandler::startServer(int maxNumOfChannels) {
  cout << "**************************\n";
  cout << "*  ChatServer ver0.02    *\n";
  cout << "*       started          *\n";
  cout << "**************************\n\n";

  this->pServer = new Server(maxNumOfChannels);
}

void
ConnectionHandler::startListening() {
  CLConnection* commandLine = new CLConnection(0, this->pServer);
  addConnection(commandLine);
  SimpleBotConnection* sConn1 = new SimpleBotConnection(1, "robo1", this->pServer, "r2d2");
  addConnection(sConn1);
  MathBotConnection* smart = new MathBotConnection(2, "Einstein", this->pServer, "uno");
  addConnection(smart);
  RandomBotConnection* whatever = new RandomBotConnection(3, "Seko", this->pServer, "salasana");
  addConnection(whatever);

  this->startConnection(sConn1);
  this->startConnection(smart);
  this->startConnection(whatever);
  commandLine->Execute();
  //this->startConnection(commandLine, true); // Waits for commandLine to finish

  delete(this->pServer);
  
}

// This is a private method
bool
ConnectionHandler::addConnection(Connection* conn) {
  long id = conn->getId();
  if(connections.size() < mMaxNumOfConns) { // Space in the list
  
    ConnectionList::iterator p = connections.find(id);
    if(p == connections.end()) { // No connection with this id found
      connections[id] = conn;
    }
    else {
      //This id already existed
      return false;
    }
  }
  else {
    //Maximun amount of connections reached
    return false;
  }
  return true;
}

void*
threadRun(void* connVoid)
{
  Connection* conn = (Connection*) connVoid;
  conn->Execute();
  return 0;
}

// Private method
void
ConnectionHandler::startConnection(Connection* conn, bool waitFor)
{
  pthread_t th1;
  pthread_create(&th1, NULL, threadRun, conn);
  int status, rc;
  sleep(1);
  //  if(waitFor)
  //    rc = pthread_join(th1, (void **)&status);
}


// Starts the whole program
int main() {
  unsigned int maxConns = 3;
  int maxChannels = 1;

  ConnectionHandler handl(maxConns);
  handl.startServer(maxChannels);

  handl.startListening();
}
