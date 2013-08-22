/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2001 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "ClientAdapter.h"


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class ClientAdapter
 */

ClientAdapter::~ClientAdapter()
{
}

void *
ClientAdapter::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:ClientAdapter:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

ClientAdapter_ptr
ClientAdapter::_narrow( CORBA::Object_ptr _obj )
{
  ClientAdapter_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:ClientAdapter:1.0" )))
      return _duplicate( (ClientAdapter_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:ClientAdapter:1.0") || _obj->_is_a_remote ("IDL:ClientAdapter:1.0")) {
      _o = new ClientAdapter_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

ClientAdapter_ptr
ClientAdapter::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_ClientAdapter : public CORBA::StaticTypeInfo {
    typedef ClientAdapter_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
};


CORBA::StaticValueType _Marshaller_ClientAdapter::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_ClientAdapter::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::ClientAdapter::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_ClientAdapter::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_ClientAdapter::release( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
}

CORBA::Boolean _Marshaller_ClientAdapter::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::ClientAdapter::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_ClientAdapter::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::StaticTypeInfo *_marshaller_ClientAdapter;


/*
 * Stub interface for class ClientAdapter
 */

ClientAdapter_stub::~ClientAdapter_stub()
{
}

void ClientAdapter_stub::sendPrivateMessage( const char* _par_sender, const char* _par_text )
{
  CORBA::StaticAny _sa_sender( CORBA::_stc_string, &_par_sender );
  CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text );
  CORBA::StaticRequest __req( this, "sendPrivateMessage" );
  __req.add_in_arg( &_sa_sender );
  __req.add_in_arg( &_sa_text );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ClientAdapter_stub::sendChannelMessage( const char* _par_sender, const char* _par_channel, const char* _par_text )
{
  CORBA::StaticAny _sa_sender( CORBA::_stc_string, &_par_sender );
  CORBA::StaticAny _sa_channel( CORBA::_stc_string, &_par_channel );
  CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text );
  CORBA::StaticRequest __req( this, "sendChannelMessage" );
  __req.add_in_arg( &_sa_sender );
  __req.add_in_arg( &_sa_channel );
  __req.add_in_arg( &_sa_text );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ClientAdapter_stub::sendMessage( const char* _par_sender, const char* _par_text )
{
  CORBA::StaticAny _sa_sender( CORBA::_stc_string, &_par_sender );
  CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text );
  CORBA::StaticRequest __req( this, "sendMessage" );
  __req.add_in_arg( &_sa_sender );
  __req.add_in_arg( &_sa_text );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


void ClientAdapter_stub::sendError( const char* _par_errDescription )
{
  CORBA::StaticAny _sa_errDescription( CORBA::_stc_string, &_par_errDescription );
  CORBA::StaticRequest __req( this, "sendError" );
  __req.add_in_arg( &_sa_errDescription );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
}


struct __tc_init_CLIENTADAPTER {
  __tc_init_CLIENTADAPTER()
  {
    _marshaller_ClientAdapter = new _Marshaller_ClientAdapter;
  }
};

static __tc_init_CLIENTADAPTER __init_CLIENTADAPTER;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

ClientAdapter_skel::ClientAdapter_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:ClientAdapter:1.0", "ClientAdapter" );
  _create_ref( _id,
    0,
    _impl,
    "IDL:ClientAdapter:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper< ClientAdapter_skel>( this ) );
}

ClientAdapter_skel::ClientAdapter_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:ClientAdapter:1.0", "ClientAdapter" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper< ClientAdapter_skel>( this ) );
}

ClientAdapter_skel::~ClientAdapter_skel()
{
}

bool ClientAdapter_skel::dispatch( CORBA::StaticServerRequest_ptr __req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    switch (mico_string_hash (__req->op_name(), 7)) {
    case 1:
      if( strcmp( __req->op_name(), "sendPrivateMessage" ) == 0 ) {
        CORBA::String_var _par_sender;
        CORBA::StaticAny _sa_sender( CORBA::_stc_string, &_par_sender._for_demarshal() );
        CORBA::String_var _par_text;
        CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text._for_demarshal() );

        __req->add_in_arg( &_sa_sender );
        __req->add_in_arg( &_sa_text );

        if( !__req->read_args() )
          return true;

        sendPrivateMessage( _par_sender.inout(), _par_text.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 5:
      if( strcmp( __req->op_name(), "sendChannelMessage" ) == 0 ) {
        CORBA::String_var _par_sender;
        CORBA::StaticAny _sa_sender( CORBA::_stc_string, &_par_sender._for_demarshal() );
        CORBA::String_var _par_channel;
        CORBA::StaticAny _sa_channel( CORBA::_stc_string, &_par_channel._for_demarshal() );
        CORBA::String_var _par_text;
        CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text._for_demarshal() );

        __req->add_in_arg( &_sa_sender );
        __req->add_in_arg( &_sa_channel );
        __req->add_in_arg( &_sa_text );

        if( !__req->read_args() )
          return true;

        sendChannelMessage( _par_sender.inout(), _par_channel.inout(), _par_text.inout() );
        __req->write_results();
        return true;
      }
      break;
    case 6:
      if( strcmp( __req->op_name(), "sendMessage" ) == 0 ) {
        CORBA::String_var _par_sender;
        CORBA::StaticAny _sa_sender( CORBA::_stc_string, &_par_sender._for_demarshal() );
        CORBA::String_var _par_text;
        CORBA::StaticAny _sa_text( CORBA::_stc_string, &_par_text._for_demarshal() );

        __req->add_in_arg( &_sa_sender );
        __req->add_in_arg( &_sa_text );

        if( !__req->read_args() )
          return true;

        sendMessage( _par_sender.inout(), _par_text.inout() );
        __req->write_results();
        return true;
      }
      if( strcmp( __req->op_name(), "sendError" ) == 0 ) {
        CORBA::String_var _par_errDescription;
        CORBA::StaticAny _sa_errDescription( CORBA::_stc_string, &_par_errDescription._for_demarshal() );

        __req->add_in_arg( &_sa_errDescription );

        if( !__req->read_args() )
          return true;

        sendError( _par_errDescription.inout() );
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

ClientAdapter_ptr ClientAdapter_skel::_this()
{
  return ClientAdapter::_duplicate( this );
}

