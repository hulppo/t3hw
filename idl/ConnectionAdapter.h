/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2001 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __CONNECTIONADAPTER_H__
#define __CONNECTIONADAPTER_H__


class ConnectionAdapter;
typedef ConnectionAdapter *ConnectionAdapter_ptr;
typedef ConnectionAdapter_ptr ConnectionAdapterRef;
typedef ObjVar< ConnectionAdapter > ConnectionAdapter_var;
typedef ObjOut< ConnectionAdapter > ConnectionAdapter_out;




/*
 * Base class and common definitions for interface ConnectionAdapter
 */

class ConnectionAdapter : 
  virtual public CORBA::Object
{
  public:
    virtual ~ConnectionAdapter();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ConnectionAdapter_ptr _ptr_type;
    typedef ConnectionAdapter_var _var_type;
    #endif

    static ConnectionAdapter_ptr _narrow( CORBA::Object_ptr obj );
    static ConnectionAdapter_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ConnectionAdapter_ptr _duplicate( ConnectionAdapter_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ConnectionAdapter_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void exitServer() = 0;
    virtual CORBA::Boolean joinChannel( const char* chName ) = 0;
    virtual CORBA::Boolean exitChannel( const char* chName ) = 0;
    virtual void sendChannelMsg( const char* chName, const char* text ) = 0;
    virtual void sendPrivateMsg( const char* receiverName, const char* text ) = 0;
    virtual void getServerInfo() = 0;
    virtual void getUserInfo() = 0;
    virtual void getChannelInfo() = 0;
    virtual void createUser( const char* uName, const char* pass, const char* rName, CORBA::Boolean isAdmin ) = 0;
    virtual void removeUser( const char* targetUser ) = 0;
    virtual void createChannel( const char* chName ) = 0;
    virtual void destroyChannel( const char* chName ) = 0;
    virtual void kickUserFromServer( const char* targetUser ) = 0;
    virtual void kickUserFromChannel( const char* targetUser, const char* chName ) = 0;

  protected:
    ConnectionAdapter() {};
  private:
    ConnectionAdapter( const ConnectionAdapter& );
    void operator=( const ConnectionAdapter& );
};

// Stub for interface ConnectionAdapter
class ConnectionAdapter_stub:
  virtual public ConnectionAdapter
{
  public:
    virtual ~ConnectionAdapter_stub();
    void exitServer();
    CORBA::Boolean joinChannel( const char* chName );
    CORBA::Boolean exitChannel( const char* chName );
    void sendChannelMsg( const char* chName, const char* text );
    void sendPrivateMsg( const char* receiverName, const char* text );
    void getServerInfo();
    void getUserInfo();
    void getChannelInfo();
    void createUser( const char* uName, const char* pass, const char* rName, CORBA::Boolean isAdmin );
    void removeUser( const char* targetUser );
    void createChannel( const char* chName );
    void destroyChannel( const char* chName );
    void kickUserFromServer( const char* targetUser );
    void kickUserFromChannel( const char* targetUser, const char* chName );

  private:
    void operator=( const ConnectionAdapter_stub& );
};

class ConnectionAdapter_skel :
  virtual public StaticMethodDispatcher,
  virtual public ConnectionAdapter
{
  public:
    ConnectionAdapter_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ConnectionAdapter_skel();
    ConnectionAdapter_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr __req, CORBA::Environment &_env );
    ConnectionAdapter_ptr _this();

};

#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_ConnectionAdapter;

#endif
