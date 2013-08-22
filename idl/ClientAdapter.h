/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2001 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __CLIENTADAPTER_H__
#define __CLIENTADAPTER_H__


class ClientAdapter;
typedef ClientAdapter *ClientAdapter_ptr;
typedef ClientAdapter_ptr ClientAdapterRef;
typedef ObjVar< ClientAdapter > ClientAdapter_var;
typedef ObjOut< ClientAdapter > ClientAdapter_out;




/*
 * Base class and common definitions for interface ClientAdapter
 */

class ClientAdapter : 
  virtual public CORBA::Object
{
  public:
    virtual ~ClientAdapter();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef ClientAdapter_ptr _ptr_type;
    typedef ClientAdapter_var _var_type;
    #endif

    static ClientAdapter_ptr _narrow( CORBA::Object_ptr obj );
    static ClientAdapter_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static ClientAdapter_ptr _duplicate( ClientAdapter_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static ClientAdapter_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void sendPrivateMessage( const char* sender, const char* text ) = 0;
    virtual void sendChannelMessage( const char* sender, const char* channel, const char* text ) = 0;
    virtual void sendMessage( const char* sender, const char* text ) = 0;
    virtual void sendError( const char* errDescription ) = 0;

  protected:
    ClientAdapter() {};
  private:
    ClientAdapter( const ClientAdapter& );
    void operator=( const ClientAdapter& );
};

// Stub for interface ClientAdapter
class ClientAdapter_stub:
  virtual public ClientAdapter
{
  public:
    virtual ~ClientAdapter_stub();
    void sendPrivateMessage( const char* sender, const char* text );
    void sendChannelMessage( const char* sender, const char* channel, const char* text );
    void sendMessage( const char* sender, const char* text );
    void sendError( const char* errDescription );

  private:
    void operator=( const ClientAdapter_stub& );
};

class ClientAdapter_skel :
  virtual public StaticMethodDispatcher,
  virtual public ClientAdapter
{
  public:
    ClientAdapter_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~ClientAdapter_skel();
    ClientAdapter_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr __req, CORBA::Environment &_env );
    ClientAdapter_ptr _this();

};

#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_ClientAdapter;

#endif
