/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2001 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __CHADAPTER_H__
#define __CHADAPTER_H__


class CHAdapter;
typedef CHAdapter *CHAdapter_ptr;
typedef CHAdapter_ptr CHAdapterRef;
typedef ObjVar< CHAdapter > CHAdapter_var;
typedef ObjOut< CHAdapter > CHAdapter_out;




/*
 * Base class and common definitions for interface CHAdapter
 */

class CHAdapter : 
  virtual public CORBA::Object
{
  public:
    virtual ~CHAdapter();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef CHAdapter_ptr _ptr_type;
    typedef CHAdapter_var _var_type;
    #endif

    static CHAdapter_ptr _narrow( CORBA::Object_ptr obj );
    static CHAdapter_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static CHAdapter_ptr _duplicate( CHAdapter_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static CHAdapter_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual char* registerUser( const char* userName, const char* password, const char* client ) = 0;

  protected:
    CHAdapter() {};
  private:
    CHAdapter( const CHAdapter& );
    void operator=( const CHAdapter& );
};

// Stub for interface CHAdapter
class CHAdapter_stub:
  virtual public CHAdapter
{
  public:
    virtual ~CHAdapter_stub();
    char* registerUser( const char* userName, const char* password, const char* client );

  private:
    void operator=( const CHAdapter_stub& );
};

class CHAdapter_skel :
  virtual public StaticMethodDispatcher,
  virtual public CHAdapter
{
  public:
    CHAdapter_skel( const CORBA::BOA::ReferenceData & = CORBA::BOA::ReferenceData() );
    virtual ~CHAdapter_skel();
    CHAdapter_skel( CORBA::Object_ptr obj );
    virtual bool dispatch( CORBA::StaticServerRequest_ptr __req, CORBA::Environment &_env );
    CHAdapter_ptr _this();

};

#ifndef MICO_CONF_NO_POA

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_CHAdapter;

#endif
