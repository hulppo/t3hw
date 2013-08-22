#include "ClientAdapter_impl.h"

#include <iostream>

using namespace std;

ClientAdapter_impl::ClientAdapter_impl()
{
  mChannel = "";
}

void
ClientAdapter_impl::sendPrivateMessage(const char* sender, 
                                       const char* text)
{
  cout << "Private:<" << sender << "> " << text << endl;
}

void
ClientAdapter_impl::sendChannelMessage(const char* sender,
                                       const char* channel, 
                                       const char* text)
{
  string sChannel(channel);
  if(mChannel == "")
    mChannel = sChannel;
  if(mChannel == sChannel)
    cout << "<" << sender << "> " << text << endl;
}

void
ClientAdapter_impl::sendMessage(const char* sender, 
                                const char* text)
{
  cout << "*" << sender << "*" << endl;
  cout << text << endl;
  cout << "**" << endl;
}

void
ClientAdapter_impl::sendError(const char* errDescription)
{
  cout << "Error: " << errDescription << endl;
}

void
ClientAdapter_impl::setChannel(string channel)
{
  mChannel = channel;
}

string
ClientAdapter_impl::getChannel()
{
  return mChannel;
}
