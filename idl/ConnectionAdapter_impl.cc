#include "ConnectionAdapter_impl.h"

#include "Server.h"

#include "ServerCommand.h"


ConnectionAdapter_impl::ConnectionAdapter_impl(Server* serv)
{
  this->pServer = serv;
}

void
ConnectionAdapter_impl::getServerInfo()
{
  ServerCommand cmd = 
    new ServerCommand(mUserName, ServerCommand::serverInfo,
                      "","");
  pServer->recvCmd(cmd);
  delete(cmd);
}
