/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2001 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "CHAdapter.h"


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class CHAdapter
 */

CHAdapter::~CHAdapter()
{
}

void *
CHAdapter::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:CHAdapter:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

CHAdapter_ptr
CHAdapter::_narrow( CORBA::Object_ptr _obj )
{
  CHAdapter_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:CHAdapter:1.0" )))
      return _duplicate( (CHAdapter_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:CHAdapter:1.0") || _obj->_is_a_remote ("IDL:CHAdapter:1.0")) {
      _o = new CHAdapter_stub;
      _o->MICO_SCOPE(CORBA,Object::operator=)( *_obj );
      return _o;
    }
  }
  return _nil();
}

CHAdapter_ptr
CHAdapter::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_CHAdapter : public CORBA::StaticTypeInfo {
    typedef CHAdapter_ptr _MICO_T;
  public:
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    CORBA::Boolean demarshal (CORBA::DataDecoder&, StaticValueType) const;
    void marshal (CORBA::DataEncoder &, StaticValueType) const;
};


CORBA::StaticValueType _Marshaller_CHAdapter::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_CHAdapter::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::CHAdapter::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_CHAdapter::free( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_CHAdapter::release( StaticValueType v ) const
{
  CORBA::release( *(_MICO_T *) v );
}

CORBA::Boolean _Marshaller_CHAdapter::demarshal( CORBA::DataDecoder &dc, StaticValueType v ) const
{
  CORBA::Object_ptr obj;
  if (!CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::CHAdapter::_narrow( obj );
  CORBA::Boolean ret = CORBA::is_nil (obj) || !CORBA::is_nil (*(_MICO_T *)v);
  CORBA::release (obj);
  return ret;
}

void _Marshaller_CHAdapter::marshal( CORBA::DataEncoder &ec, StaticValueType v ) const
{
  CORBA::Object_ptr obj = *(_MICO_T *) v;
  CORBA::_stc_Object->marshal( ec, &obj );
}

CORBA::StaticTypeInfo *_marshaller_CHAdapter;


/*
 * Stub interface for class CHAdapter
 */

CHAdapter_stub::~CHAdapter_stub()
{
}

char* CHAdapter_stub::registerUser( const char* _par_userName, const char* _par_password, const char* _par_client )
{
  CORBA::StaticAny _sa_userName( CORBA::_stc_string, &_par_userName );
  CORBA::StaticAny _sa_password( CORBA::_stc_string, &_par_password );
  CORBA::StaticAny _sa_client( CORBA::_stc_string, &_par_client );
  char* _res;
  CORBA::StaticAny __res( CORBA::_stc_string, &_res );

  CORBA::StaticRequest __req( this, "registerUser" );
  __req.add_in_arg( &_sa_userName );
  __req.add_in_arg( &_sa_password );
  __req.add_in_arg( &_sa_client );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return _res;
}


struct __tc_init_CHADAPTER {
  __tc_init_CHADAPTER()
  {
    _marshaller_CHAdapter = new _Marshaller_CHAdapter;
  }
};

static __tc_init_CHADAPTER __init_CHADAPTER;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

CHAdapter_skel::CHAdapter_skel( const CORBA::BOA::ReferenceData &_id )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:CHAdapter:1.0", "CHAdapter" );
  _create_ref( _id,
    0,
    _impl,
    "IDL:CHAdapter:1.0" );
  register_dispatcher( new StaticInterfaceDispatcherWrapper< CHAdapter_skel>( this ) );
}

CHAdapter_skel::CHAdapter_skel( CORBA::Object_ptr _obj )
{
  CORBA::ImplementationDef_var _impl =
    _find_impl( "IDL:CHAdapter:1.0", "CHAdapter" );
  assert( !CORBA::is_nil( _impl ) );
  _restore_ref( _obj,
    CORBA::BOA::ReferenceData(),
    0,
    _impl );
  register_dispatcher( new StaticInterfaceDispatcherWrapper< CHAdapter_skel>( this ) );
}

CHAdapter_skel::~CHAdapter_skel()
{
}

bool CHAdapter_skel::dispatch( CORBA::StaticServerRequest_ptr __req, CORBA::Environment & /*_env*/ )
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "registerUser" ) == 0 ) {
      CORBA::String_var _par_userName;
      CORBA::StaticAny _sa_userName( CORBA::_stc_string, &_par_userName._for_demarshal() );
      CORBA::String_var _par_password;
      CORBA::StaticAny _sa_password( CORBA::_stc_string, &_par_password._for_demarshal() );
      CORBA::String_var _par_client;
      CORBA::StaticAny _sa_client( CORBA::_stc_string, &_par_client._for_demarshal() );

      char* _res;
      CORBA::StaticAny __res( CORBA::_stc_string, &_res );
      __req->add_in_arg( &_sa_userName );
      __req->add_in_arg( &_sa_password );
      __req->add_in_arg( &_sa_client );
      __req->set_result( &__res );

      if( !__req->read_args() )
        return true;

      _res = registerUser( _par_userName.inout(), _par_password.inout(), _par_client.inout() );
      __req->write_results();
      CORBA::string_free( _res );
      return true;
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

CHAdapter_ptr CHAdapter_skel::_this()
{
  return CHAdapter::_duplicate( this );
}

