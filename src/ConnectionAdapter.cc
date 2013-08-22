/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2001 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "ConnectionAdapter.h"


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class ConnectionAdapter
 */

ConnectionAdapter::~ConnectionAdapter()
{
}

void *
ConnectionAdapter::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:ConnectionAdapter:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

ConnectionAdapter_ptr
ConnectionAdapter::_narrow( CORBA::Object_ptr _obj )
{
  ConnectionAdapter_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:ConnectionAdapter:1.0" )))
      return _duplicate( (ConnectionAdapter_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:ConnectionAdapter:1.0") || _obj->_is_a_remote ("IDL:ConnectionAdapter:1.0")) {
      _o = new ConnectionAdapter_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

ConnectionAdapter_ptr
ConnectionAdapter::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_ConnectionAdapter : public CORBA::StaticTypeInfo {
    typedef ConnectionAdapter_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
};


CORBA::StaticValueType _Marshaller_ConnectionAdapter::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_ConnectionAdapter::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::ConnectionAdapter::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_ConnectionAdapter::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_ConnectionAdapter::release( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
}

CORBA::Boolean _Marshaller_ConnectionAdapter::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::ConnectionAdapter::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_ConnectionAdapter::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::StaticTypeInfo *_marshaller_ConnectionAdapter;


/*
 * Stub interface for class ConnectionAdapter
 */

ConnectionAdapter_stub::~ConnectionAdapter_stub()
{
}

void ConnectionAdapter_stub::exitServer()
{
  CORBA::StaticRequest __req( this, "exitServer" );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


CORBA::Boolean ConnectionAdapter_stub::joinChannel( const char* _par_chName )
{
  CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName );
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "joinChannel" );
  __req.add_in_arg( &_sa_chName );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


CORBA::Boolean ConnectionAdapter_stub::exitChannel( const char* _par_chName )
{
  CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName );
  CORBA::Boolean _res;
  CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );

  CORBA::StaticRequest __req( this, "exitChannel" );
  __req.add_in_arg( &_sa_chName );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


void ConnectionAdapter_stub::sendChannelMsg( const char* _par_chName, const char* _par_text )
{
  CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName );
  CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text );
  CORBA::StaticRequest __req( this, "sendChannelMsg" );
  __req.add_in_arg( &_sa_chName );
  __req.add_in_arg( &_sa_text );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::sendPrivateMsg( const char* _par_receiverName, const char* _par_text )
{
  CORBA::StaticAny _sa_receiverName( CORBA::_stc_string, &_par_receiverName );
  CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text );
  CORBA::StaticRequest __req( this, "sendPrivateMsg" );
  __req.add_in_arg( &_sa_receiverName );
  __req.add_in_arg( &_sa_text );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::getServerInfo()
{
  CORBA::StaticRequest __req( this, "getServerInfo" );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::getUserInfo()
{
  CORBA::StaticRequest __req( this, "getUserInfo" );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::getChannelInfo()
{
  CORBA::StaticRequest __req( this, "getChannelInfo" );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::createUser( const char* _par_uName, const char* _par_pass, const char* _par_rName, CORBA::Boolean _par_isAdmin )
{
  CORBA::StaticAny _sa_uName( CORBA::_stc_string, &_par_uName );
  CORBA::StaticAny _sa_pass( CORBA::_stc_string, &_par_pass );
  CORBA::StaticAny _sa_rName( CORBA::_stc_string, &_par_rName );
  CORBA::StaticAny _sa_isAdmin( CORBA::_stc_boolean, &_par_isAdmin );
  CORBA::StaticRequest __req( this, "createUser" );
  __req.add_in_arg( &_sa_uName );
  __req.add_in_arg( &_sa_pass );
  __req.add_in_arg( &_sa_rName );
  __req.add_in_arg( &_sa_isAdmin );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::removeUser( const char* _par_targetUser )
{
  CORBA::StaticAny _sa_targetUser( CORBA::_stc_string, &_par_targetUser );
  CORBA::StaticRequest __req( this, "removeUser" );
  __req.add_in_arg( &_sa_targetUser );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::createChannel( const char* _par_chName )
{
  CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName );
  CORBA::StaticRequest __req( this, "createChannel" );
  __req.add_in_arg( &_sa_chName );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::destroyChannel( const char* _par_chName )
{
  CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName );
  CORBA::StaticRequest __req( this, "destroyChannel" );
  __req.add_in_arg( &_sa_chName );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::kickUserFromServer( const char* _par_targetUser )
{
  CORBA::StaticAny _sa_targetUser( CORBA::_stc_string, &_par_targetUser );
  CORBA::StaticRequest __req( this, "kickUserFromServer" );
  __req.add_in_arg( &_sa_targetUser );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ConnectionAdapter_stub::kickUserFromChannel( const char* _par_targetUser, const char* _par_chName )
{
  CORBA::StaticAny _sa_targetUser( CORBA::_stc_string, &_par_targetUser );
  CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName );
  CORBA::StaticRequest __req( this, "kickUserFromChannel" );
  __req.add_in_arg( &_sa_targetUser );
  __req.add_in_arg( &_sa_chName );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct __tc_init_CONNECTIONADAPTER {
  __tc_init_CONNECTIONADAPTER()
  {
    _marshaller_ConnectionAdapter = new _Marshaller_ConnectionAdapter;
  }
};

static __tc_init_CONNECTIONADAPTER __init_CONNECTIONADAPTER;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

ConnectionAdapter_skel::ConnectionAdapter_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:ConnectionAdapter:1.0", "ConnectionAdapter" );
  _create_ref( _id,
    0,
    _impl,
    "IDL:ConnectionAdapter:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper< ConnectionAdapter_skel>( this ) );
}

ConnectionAdapter_skel::ConnectionAdapter_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:ConnectionAdapter:1.0", "ConnectionAdapter" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper< ConnectionAdapter_skel>( this ) );
}

ConnectionAdapter_skel::~ConnectionAdapter_skel()
{
}

bool ConnectionAdapter_skel::dispatch( CORBA::StaticServerRequest_ptr __req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    switch (mico_string_hash (__req->op_name(), 23)) {
    case 2:
      if( strcmp( __req->op_name(), "exitServer" ) == 0 ) {

        if( !__req->read_args() )
          return true;

        exitServer();
        __req->write_results();
        return true;
      }
      break;
    case 4:
      if( strcmp( __req->op_name(), "sendChannelMsg" ) == 0 ) {
        CORBA::String_var _par_chName;
        CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName._for_demarshal() );
        CORBA::String_var _par_text;
        CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text._for_demarshal() );

        __req->add_in_arg( &_sa_chName );
        __req->add_in_arg( &_sa_text );

        if( !__req->read_args() )
          return true;

        sendChannelMsg( _par_chName.inout(), _par_text.inout() );
        __req->write_results();
        return true;
      }
      if( strcmp( __req->op_name(), "getUserInfo" ) == 0 ) {

        if( !__req->read_args() )
          return true;

        getUserInfo();
        __req->write_results();
        return true;
      }
      break;
    case 5:
      if( strcmp( __req->op_name(), "joinChannel" ) == 0 ) {
        CORBA::String_var _par_chName;
        CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName._for_demarshal() );

        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        __req->add_in_arg( &_sa_chName );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = joinChannel( _par_chName.inout() );
        __req->write_results();
        return true;
      }
      if( strcmp( __req->op_name(), "kickUserFromServer" ) == 0 ) {
        CORBA::String_var _par_targetUser;
        CORBA::StaticAny _sa_targetUser( CORBA::_stc_string, &_par_targetUser._for_demarshal() );

        __req->add_in_arg( &_sa_targetUser );

        if( !__req->read_args() )
          return true;

        kickUserFromServer( _par_targetUser.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 6:
      if( strcmp( __req->op_name(), "kickUserFromChannel" ) == 0 ) {
        CORBA::String_var _par_targetUser;
        CORBA::StaticAny _sa_targetUser( CORBA::_stc_string, &_par_targetUser._for_demarshal() );
        CORBA::String_var _par_chName;
        CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName._for_demarshal() );

        __req->add_in_arg( &_sa_targetUser );
        __req->add_in_arg( &_sa_chName );

        if( !__req->read_args() )
          return true;

        kickUserFromChannel( _par_targetUser.inout(), _par_chName.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 7:
      if( strcmp( __req->op_name(), "sendPrivateMsg" ) == 0 ) {
        CORBA::String_var _par_receiverName;
        CORBA::StaticAny _sa_receiverName( CORBA::_stc_string, &_par_receiverName._for_demarshal() );
        CORBA::String_var _par_text;
        CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text._for_demarshal() );

        __req->add_in_arg( &_sa_receiverName );
        __req->add_in_arg( &_sa_text );

        if( !__req->read_args() )
          return true;

        sendPrivateMsg( _par_receiverName.inout(), _par_text.inout() );
        __req->write_results();
        return true;
      }
      if( strcmp( __req->op_name(), "createUser" ) == 0 ) {
        CORBA::String_var _par_uName;
        CORBA::StaticAny _sa_uName( CORBA::_stc_string, &_par_uName._for_demarshal() );
        CORBA::String_var _par_pass;
        CORBA::StaticAny _sa_pass( CORBA::_stc_string, &_par_pass._for_demarshal() );
        CORBA::String_var _par_rName;
        CORBA::StaticAny _sa_rName( CORBA::_stc_string, &_par_rName._for_demarshal() );
        CORBA::Boolean _par_isAdmin;
        CORBA::StaticAny _sa_isAdmin( CORBA::_stc_boolean, &_par_isAdmin );

        __req->add_in_arg( &_sa_uName );
        __req->add_in_arg( &_sa_pass );
        __req->add_in_arg( &_sa_rName );
        __req->add_in_arg( &_sa_isAdmin );

        if( !__req->read_args() )
          return true;

        createUser( _par_uName.inout(), _par_pass.inout(), _par_rName.inout(), _par_isAdmin );
        __req->write_results();
        return true;
      }
      break;
    case 10:
      if( strcmp( __req->op_name(), "getServerInfo" ) == 0 ) {

        if( !__req->read_args() )
          return true;

        getServerInfo();
        __req->write_results();
        return true;
      }
      if( strcmp( __req->op_name(), "createChannel" ) == 0 ) {
        CORBA::String_var _par_chName;
        CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName._for_demarshal() );

        __req->add_in_arg( &_sa_chName );

        if( !__req->read_args() )
          return true;

        createChannel( _par_chName.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 12:
      if( strcmp( __req->op_name(), "exitChannel" ) == 0 ) {
        CORBA::String_var _par_chName;
        CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName._for_demarshal() );

        CORBA::Boolean _res;
        CORBA::StaticAny __res( CORBA::_stc_boolean, &_res );
        __req->add_in_arg( &_sa_chName );
        __req->set_result( &__res );

        if( !__req->read_args() )
          return true;

        _res = exitChannel( _par_chName.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 14:
      if( strcmp( __req->op_name(), "destroyChannel" ) == 0 ) {
        CORBA::String_var _par_chName;
        CORBA::StaticAny _sa_chName( CORBA::_stc_string, &_par_chName._for_demarshal() );

        __req->add_in_arg( &_sa_chName );

        if( !__req->read_args() )
          return true;

        destroyChannel( _par_chName.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 17:
      if( strcmp( __req->op_name(), "getChannelInfo" ) == 0 ) {

        if( !__req->read_args() )
          return true;

        getChannelInfo();
        __req->write_results();
        return true;
      }
      break;
    case 21:
      if( strcmp( __req->op_name(), "removeUser" ) == 0 ) {
        CORBA::String_var _par_targetUser;
        CORBA::StaticAny _sa_targetUser( CORBA::_stc_string, &_par_targetUser._for_demarshal() );

        __req->add_in_arg( &_sa_targetUser );

        if( !__req->read_args() )
          return true;

        removeUser( _par_targetUser.inout() );
        __req->write_results();
        return true;
      }
      break;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    __req->set_exception( _ex->_clone() );
    __req->write_results();
    return true;
  } catch( ... ) {
    assert( 0 );
    return true;
  }
  #endif
  return false;
}

ConnectionAdapter_ptr ConnectionAdapter_skel::_this()
{
  return ConnectionAdapter::_duplicate( this );
}

