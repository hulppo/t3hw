#include "Client.h"
#include <unistd.h>

#include <iostream>

#include <pthread.h>

using namespace std;

Client::Client(CORBA::ORB_var orb, CORBA::BOA_var boa, CHAdapter_var server)
{
  mORB = orb;
  mBOA = boa;
  mServer = server;
  activeConnection = 0;
 
  mPrinter = new ClientAdapter_impl();
 
  //Setup of commands
  mCommands["quit"] = 0;
  mCommands["help"] = 1;
  mCommands["channels"] = 2;
  mCommands["create"] = 3;
  mCommands["destroy"] = 4;
  mCommands["join"] = 5;
  mCommands["leave"] = 6;

  mCommands["msg"] = 8;
  mCommands["info"] = 9;
  mCommands["users"] = 10;
  mCommands["kick"] = 11;
  mCommands["add"] = 12;
  mCommands["remove"] = 13;
}

void*
startIncomingListener(void* voidOrb)
{
  CORBA::ORB_var orb = (CORBA::ORB*) voidOrb;
  orb->run();
  return 0;
}

int
Client::startParser()
{
  string pass = "";
  bool cont = true;
  string sRefToPrinter = "";
  CORBA::String_var corbaRefToPrinter = mORB->object_to_string(mPrinter);
  sRefToPrinter = corbaRefToPrinter;

  mBOA->impl_is_ready(CORBA::ImplementationDef::_nil());
  pthread_t th1;
  pthread_create(&th1, NULL, startIncomingListener, mORB); // Starts callback interface

  while(cont) {
    cout << "==================" << endl;
    cout << "   Remote  login  " << endl;
    cout << "  for ChatServer  " << endl;
    cout << "==================" << endl;
    cout << "User name: ";
    string userName = "";
    cin >> userName;
    cout << "Password: ";
    pass = "";
    cin >> pass;
    string clean;
    getline(cin, clean); //Cleans the buffer
    string sRef = "";
    CORBA::String_var connRef =
      mServer->registerUser(userName.c_str(),
                            pass.c_str(),
                            sRefToPrinter.c_str());
    
    sRef = connRef;
    if(sRef != "") {
      CORBA::Object_var obj = mORB->string_to_object(connRef);
      activeConnection = ConnectionAdapter::_narrow(obj);
      insideServer();
    }
    else {
      cout << "Login failed" << endl;
    }
    cont = false;
  }
  CORBA::Boolean waitfor = true;
  mORB->shutdown(waitfor);
  return 0;
}

void
Client::insideServer()
{
  bool cont = true;
  while(cont) {
    string line;
    getline(cin, line);
    istringstream iss(line);
    char first = iss.peek();
    if(first == '/') {
      iss >> first; // Remove / from inputstringstream
      bool quitNow = this->parseCommands(iss);
      cont = !quitNow;
    }
    else { // Message for active channel
      string channel = mPrinter->getChannel();
      string text = "";
      getline(iss, text);
      if(channel == "")
        cout << "You aren't logged in to a channel, type /help for commands" << endl;
      else
        activeConnection->
          sendChannelMsg(channel.c_str(), text.c_str());
    }
  }
}

bool // Should exit?
Client::parseCommands(istringstream& iss)
{
  bool quitNow = false;
  string choose;
  iss >> choose;
  int val = this->mapToInt(choose);
  switch(val) {
  case 0: // quit
    {
      quitNow = true;
      activeConnection->exitServer();
      CORBA::release(activeConnection);
      activeConnection = 0;
      break;
    }
  case 1: // help
    this->printCommands();
    break;
  case 2: // channels
    activeConnection->getChannelInfo();
    break;
  case 3: // create channel
    {
      string chName = "";
      if(iss >> chName) {
        activeConnection->createChannel(chName.c_str());
      }
      else
        cout << "Usage: /create <channel>" << endl;
      break;
    }
  case 4:  // destroy channel
    {
      string chName = "";
      if(iss >> chName) {
        activeConnection->destroyChannel(chName.c_str());
      }
      else
        cout << "Usage: /destroy <channel>" << endl;
      break;
    }
  case 5: // join channel
    {
      string chName = "";
      if(iss >> chName) {
        string oldChannel = mPrinter->getChannel();
        mPrinter->setChannel(chName);
        if(!activeConnection->joinChannel(chName.c_str())) // Join failed
          mPrinter->setChannel(oldChannel);
      }
      else
        cout << "Usage: /join <channel>" << endl;
      break;
    }
  case 6: // leave channel
    {
      string chName = "";
      if(iss >> chName) {        
        activeConnection->exitChannel(chName.c_str());
        mPrinter->setChannel("");
      }
      else {
        string temp = mPrinter->getChannel();
        if(temp != "") {
          activeConnection->exitChannel(temp.c_str());
          mPrinter->setChannel("");
        }
        else
          cout << "You aren't logged in a channel" << endl;
      }
        cout << "Usage: /leave (<channel>)" << endl;
      break;
    }
  case 8: // msg - Send private message
    {
      string receiver = "";
      if(iss >> receiver) {
        string text;
        getline(iss, text);
        if(!text.empty()) {
          activeConnection->sendPrivateMsg(receiver.c_str(), text.c_str());
        }
        else
          cout << "No text to send." << endl;
      }
      else
        cout << "Usage: /msg <receiver> <text to send>" << endl;
      break;
    }
  case 9: // info
    {
      activeConnection->getServerInfo();
      break;
    }
  case 10: // users
    {
      activeConnection->getUserInfo();
      break;
    }
  case 11: // kick (kicks from server or channel)
    {
      string victim = "";
      string channel = "";
      if(iss >> victim) {
        if(iss >> channel) { // Kick from channel
          activeConnection->kickUserFromChannel(victim.c_str(), channel.c_str());
        }
        else { // kick from server
          activeConnection->kickUserFromServer(victim.c_str());
        }
      }
      else {
        cout << "Usage: To kick user from server - /kick <user to kick>" << endl;
        cout << "To kick user from channel - /kick <user to kick> <from which channel>" << endl;
      }
      break;
    }
  case 12: // add user
    {
      string user = "";
      string pass = "";
      string adminInd = "";
      string rName = "";
      string uData = "";
      bool isAdmin = false;

      if(iss >> user) {
        if(iss >> pass) {
          if(iss >> adminInd) {
            if(adminInd == "Normal" || adminInd == "Admin") {
              if(adminInd == "Admin")
                isAdmin = true;
            }
            else {
              cout << "User type indicator missing Admin/Normal" << endl;
              break;
            }
            iss.get(); // Removes empty space
            if(getline(iss, rName)) { // Rest of line is real name
              activeConnection->createUser(user.c_str(), pass.c_str(), rName.c_str(), isAdmin);
            }
            else
              cout << "No real name given" << endl;
          }
          else
            cout << "Admin indicator and real name missing" << endl;
        }
        else
          cout << "User information missing" << endl;
      }
      else
        cout << "Usage: /add <user name> <user password> <Admin|Normal> <real name>" << endl;
      
      
      break;
    }
  case 13: // remove user
    {
      string user = "";
      if(iss >> user) {
        activeConnection->removeUser(user.c_str());
      }
      else
        cout << "Usage: /remove <user name>" << endl;
      break;
    }
  default:
    if(choose != "")
      cout << "Unrecognized command, for list of commands type help" << endl;
    break;
      
  }
  return quitNow;
}


int
Client::mapToInt(string val)
{
  CommandList::iterator p = mCommands.find(val);
  if(p != mCommands.end())
    return p->second;
  return -1;
}

void
Client::printCommands()
{
  cout << "Following are the commands:" << endl;
  CommandList::iterator p = mCommands.begin();
  for(; p != mCommands.end(); ++p)
    cout << "/" << p->first << endl;
  cout << "For more information on commands that aren't self explanatory";
  cout << " type the command and you will get the usage" << endl;
}


int main(int argc, char *argv[])
{
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv,"mico-local-orb");
  CORBA::BOA_var boa = orb->BOA_init(argc, argv, "mico-local-boa");

  char* serverAddr = "inet:localhost:8888";

  if(argc > 1) {
    serverAddr = argv[1];
  }
  

  CORBA::Object_var obj =
    orb->bind("IDL:CHAdapter:1.0", serverAddr);

  if(CORBA::is_nil(obj)) {
    cout << "No server found" << endl;
    return 0;
  }
  CHAdapter_var server = CHAdapter::_narrow(obj);

  Client* parser = new Client(orb, boa, server);

  parser->startParser();

  return 0;
}
