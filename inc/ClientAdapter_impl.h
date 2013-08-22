#ifndef _CLIENTADAPTER_IMPL_H_
#define _CLIENTADAPTER_IMPL_H_

#include "ClientAdapter.h"

#include <string>

/** Class ClientAdapter_impl. This is a remote interface.
    This is a callback class, enabling
    the server to send messages to the client without the client
    having to poll the server for messages. This class displays
    the received messages to the client.
*/
class ClientAdapter_impl :
  virtual public ClientAdapter_skel {
  
public:
  /** Constructor. Constructs a ClientAdapter_impl.
  */
  ClientAdapter_impl();

  /** Displays received private messages. Called over the remote.
      @param sender Who sent the message
      @param text Contents of message
   */
  virtual void sendPrivateMessage(const char* sender, const char* text);

  /** Displays received channel messages. Called over the remote.
      @param sender who sent the message
      @param channel On which channel is message
      @param text Contents of message
   */
  virtual void sendChannelMessage(const char* sender, const char* channel, const char* text);

  /** Displays received messages. Called over the remote.
      @param sender who sent the message
      @param text Contents of message
   */
  virtual void sendMessage(const char* sender, const char* text);

  /** Displays received errors. Called over the remote.
      @param errDescription Description of the occurred error
  */
  virtual void sendError(const char* errDescription);

  /** Setter. Sets the active channel.
      @param channel Name of the active channel to set
   */
  void setChannel(std::string channel);

  /** Getter. Gets the active channel.
      @return Name of the active channel
  */
  std::string getChannel();

private:
  /// The active channel. Chooses which channel msgs are displayed
  std::string mChannel;

};

#endif // _CLIENTADAPTER_IMPL_H_
