/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com / www.digidna.net
 * @brief       ...
 */

#include <OBJCXX/ClassBuilder.hpp>
#include <OBJCXX/Foundation/Classes/NSString.hpp>
#include <iostream>
#include <cmath>
#include <cctype>

/* We'll obviously do nasty casts because of the Objective-C runtime... : ) */
#ifdef __clang__
#pragma clang diagnostic ignored "-Wfloat-conversion"
#pragma clang diagnostic ignored "-Wbad-function-cast"
#pragma clang diagnostic ignored "-Wcast-align"
#endif

template<>
class XS::PIMPL::Object< OBJCXX::ClassBuilder >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const std::string & name, const std::string & super );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::string _name;
        std::string _super;
        Class       _cls;
        bool        _registered;
        bool        _hasCustomDealloc;
};

#define XS_PIMPL_CLASS OBJCXX::ClassBuilder
#include <XS/PIMPL/Object-IMPL.hpp>

extern "C"
{
    void OBJCXX_IMP_dealloc( id self, SEL _cmd );
    
    signed char         OBJCXX_IMP_SignedChar_Get( id self, SEL _cmd );
    signed short        OBJCXX_IMP_SignedShort_Get( id self, SEL _cmd );
    signed int          OBJCXX_IMP_SignedInt_Get( id self, SEL _cmd );
    signed long         OBJCXX_IMP_SignedLong_Get( id self, SEL _cmd );
    signed long long    OBJCXX_IMP_SignedLongLong_Get( id self, SEL _cmd );
    unsigned char       OBJCXX_IMP_UnsignedChar_Get( id self, SEL _cmd );
    unsigned short      OBJCXX_IMP_UnsignedShort_Get( id self, SEL _cmd );
    unsigned int        OBJCXX_IMP_UnsignedInt_Get( id self, SEL _cmd );
    unsigned long       OBJCXX_IMP_UnsignedLong_Get( id self, SEL _cmd );
    unsigned long long  OBJCXX_IMP_UnsignedLongLong_Get( id self, SEL _cmd );
    float               OBJCXX_IMP_Float_Get( id self, SEL _cmd );
    double              OBJCXX_IMP_Double_Get( id self, SEL _cmd );
    bool                OBJCXX_IMP_Bool_Get( id self, SEL _cmd );
    char              * OBJCXX_IMP_CharPointer_Get( id self, SEL _cmd );
    id                  OBJCXX_IMP_Object_Get( id self, SEL _cmd );
    Class               OBJCXX_IMP_Class_Get( id self, SEL _cmd );
    SEL                 OBJCXX_IMP_Selector_Get( id self, SEL _cmd );
    
    void OBJCXX_IMP_SignedChar_Set( id self, SEL _cmd, signed char value );
    void OBJCXX_IMP_SignedShort_Set( id self, SEL _cmd, signed short value );
    void OBJCXX_IMP_SignedInt_Set( id self, SEL _cmd, signed int value );
    void OBJCXX_IMP_SignedLong_Set( id self, SEL _cmd, signed long value );
    void OBJCXX_IMP_SignedLongLong_Set( id self, SEL _cmd, signed long long value );
    void OBJCXX_IMP_UnsignedChar_Set( id self, SEL _cmd, unsigned char value );
    void OBJCXX_IMP_UnsignedShort_Set( id self, SEL _cmd, unsigned short value );
    void OBJCXX_IMP_UnsignedInt_Set( id self, SEL _cmd, unsigned int value );
    void OBJCXX_IMP_UnsignedLong_Set( id self, SEL _cmd, unsigned long value );
    void OBJCXX_IMP_UnsignedLongLong_Set( id self, SEL _cmd, unsigned long long value );
    void OBJCXX_IMP_Float_Set( id self, SEL _cmd, float value );
    void OBJCXX_IMP_Double_Set( id self, SEL _cmd, double value );
    void OBJCXX_IMP_Bool_Set( id self, SEL _cmd, bool value );
    void OBJCXX_IMP_CharPointer_Set( id self, SEL _cmd, char * value );
    void OBJCXX_IMP_Object_Set( id self, SEL _cmd, id value );
    void OBJCXX_IMP_Class_Set( id self, SEL _cmd, Class value );
    void OBJCXX_IMP_Selector_Set( id self, SEL _cmd, SEL value );
}

namespace OBJCXX
{
    ClassBuilder::ClassBuilder( void ): XS::PIMPL::Object< ClassBuilder >()
    {}
    
    ClassBuilder::ClassBuilder( const std::string & name, const std::string & super, size_t extraBytes ): XS::PIMPL::Object< ClassBuilder >( name, super )
    {
        this->impl->_cls = RT::Internal::objc_allocateClassPair( RT::Internal::objc_getClass( super.c_str() ), name.c_str(), extraBytes );
    }
    
    Class ClassBuilder::cls( void ) const
    {
        return this->impl->_cls;
    }
    
    size_t ClassBuilder::sizeForType( Type type ) const
    {
        switch( type )
        {
            case TypeSignedChar:        return sizeof( signed char );
            case TypeSignedShort:       return sizeof( signed short );
            case TypeSignedInt:         return sizeof( signed int );
            case TypeSignedLong:        return sizeof( signed long );
            case TypeSignedLongLong:    return sizeof( signed long long );
            case TypeUnsignedChar:      return sizeof( unsigned char );
            case TypeUnsignedShort:     return sizeof( unsigned short );
            case TypeUnsignedInt:       return sizeof( unsigned int );
            case TypeUnsignedLong:      return sizeof( unsigned long );
            case TypeUnsignedLongLong:  return sizeof( unsigned long long );
            case TypeFloat:             return sizeof( float );
            case TypeDouble:            return sizeof( double );
            case TypeBool:              return sizeof( bool );
            case TypeCharPointer:       return sizeof( char * );
            case TypeObject:            return sizeof( id );
            case TypeClass:             return sizeof( Class );
            case TypeSelector:          return sizeof( SEL );
        }

        #ifdef _WIN32
        return 0;
        #endif
    }
    
    uint8_t ClassBuilder::alignmentForType( Type type ) const
    {
        return static_cast< uint8_t >( log2( this->sizeForType( type ) ) );
    }
    
    std::string ClassBuilder::encodingForType( Type type ) const
    {
        switch( type )
        {
            case TypeSignedChar:        return "c";
            case TypeSignedShort:       return "s";
            case TypeSignedInt:         return "i";
            case TypeSignedLong:        return "l";
            case TypeSignedLongLong:    return "q";
            case TypeUnsignedChar:      return "C";
            case TypeUnsignedShort:     return "S";
            case TypeUnsignedInt:       return "I";
            case TypeUnsignedLong:      return "L";
            case TypeUnsignedLongLong:  return "Q";
            case TypeFloat:             return "f";
            case TypeDouble:            return "d";
            case TypeBool:              return "B";
            case TypeCharPointer:       return "*";
            case TypeObject:            return "@";
            case TypeClass:             return "#";
            case TypeSelector:          return ":";
        }

        #ifdef _WIN32
        return "";
        #endif
    }
    
    bool ClassBuilder::addProtocol( const std::string & name )
    {
        return RT::Internal::class_addProtocol( this->impl->_cls, RT::Internal::objc_getProtocol( name.c_str() ) );
    }
        
    bool ClassBuilder::addInstanceVariable( const std::string & name, Type type ) const
    {
        return this->addInstanceVariable
        (
            name,
            this->sizeForType( type ),
            this->alignmentForType( type ),
            this->encodingForType( type )
        );
    }
    
    bool ClassBuilder::addInstanceVariable( const std::string & name, size_t size, uint8_t alignment, const std::string & types ) const
    {
        if( name.length() == 0 )
        {
            return false;
        }
        
        if( this->impl->_registered )
        {
            throw new std::runtime_error( std::string( "Class " ) + this->impl->_name + " is already registered. Instance variables can only be added before the class is registered." );
        }
        
        return RT::Internal::class_addIvar( this->impl->_cls, name.c_str(), size, alignment, types.c_str() );
    }
    
    bool ClassBuilder::addProperty( const std::string & name, Type type )
    {
        IMP         get;
        IMP         set;
        std::string getTypes;
        std::string setTypes;
        std::string setter;
        
        if( name.length() == 0 )
        {
            return false;
        }
        
        setter      = name + ":";
        setter[ 0 ] = static_cast< char >( std::toupper( setter[ 0 ] ) );
        setter      = std::string( "set" ) + setter;
        
        if( this->addInstanceVariable( std::string( "_" ) + name, type ) == false )
        {
            return false;
        }
        
        switch( type )
        {
            case TypeSignedChar:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedChar_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedChar_Set );
                getTypes = "c16@0:8";
                setTypes = "v20@0:8c16";
                
                break;
                
            case TypeSignedShort:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedShort_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedShort_Set );
                getTypes = "s16@0:8";
                setTypes = "v20@0:8s16";
                
                break;
                
            case TypeSignedInt:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedInt_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedInt_Set );
                getTypes = "i16@0:8";
                setTypes = "v20@0:8i16";
                
                break;
                
            case TypeSignedLong:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedLong_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedLong_Set );
                getTypes = "q16@0:8";
                setTypes = "v24@0:8q16";
                
                break;
                
            case TypeSignedLongLong:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedLongLong_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_SignedLongLong_Set );
                getTypes = "q16@0:8";
                setTypes = "v24@0:8q16";
                
                break;
                
            case TypeUnsignedChar:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedChar_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedChar_Set );
                getTypes = "C16@0:8";
                setTypes = "v20@0:8C16";
                
                break;
                
            case TypeUnsignedShort:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedShort_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedShort_Set );
                getTypes = "S16@0:8";
                setTypes = "v20@0:8S16";
                
                break;
                
            case TypeUnsignedInt:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedInt_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedInt_Set );
                getTypes = "I16@0:8";
                setTypes = "v20@0:8I16";
                
                break;
                
            case TypeUnsignedLong:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedLong_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedLong_Set );
                getTypes = "Q16@0:8";
                setTypes = "v24@0:8Q16";
                
                break;
                
            case TypeUnsignedLongLong:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedLongLong_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_UnsignedLongLong_Set );
                getTypes = "Q16@0:8";
                setTypes = "v24@0:8Q16";
                
                break;
                
            case TypeFloat:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_Float_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_Float_Set );
                getTypes = "f16@0:8";
                setTypes = "v20@0:8f16";
                
                break;
                
            case TypeDouble:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_Double_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_Double_Set );
                getTypes = "d16@0:8";
                setTypes = "v24@0:8d16";
                
                break;
                
            case TypeBool:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_Bool_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_Bool_Set );
                getTypes = "B16@0:8";
                setTypes = "v20@0:8B16";
                
                break;
                
            case TypeCharPointer:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_CharPointer_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_CharPointer_Set );
                getTypes = "c16@0:8";
                setTypes = "v20@0:8c16";
                
                break;
                
            case TypeObject:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_Object_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_Object_Set );
                getTypes = "@16@0:8";
                setTypes = "v24@0:8@16";
                
                break;
                
            case TypeClass:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_Class_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_Class_Set );
                getTypes = "#16@0:8";
                setTypes = "v24@0:8#16";
                
                break;
                
            case TypeSelector:
                
                get      = reinterpret_cast< IMP >( OBJCXX_IMP_Selector_Get );
                set      = reinterpret_cast< IMP >( OBJCXX_IMP_Selector_Set );
                getTypes = ":16@0:8";
                setTypes = "v24@0:8:16";
                
                break;

            #ifdef _WIN32
            default: return false;
            #endif
        }
        
        if( this->addInstanceMethod( name, get, getTypes ) == false )
        {
            return false;
        }
        
        if( this->addInstanceMethod( setter, set, setTypes ) == false )
        {
            return false;
        }
        
        return true;
    }
    
    bool ClassBuilder::addClassMethod( const std::string & name, IMP implementation, const std::string & types ) const
    {
        Class cls;
        
        if( name.length() == 0 )
        {
            return false;
        }
        
        if( this->impl->_registered == false )
        {
            throw new std::runtime_error( std::string( "Class " ) + this->impl->_name + " is not registered. Class methods can only be added after the class is registered" );
        }
        
        cls = RT::Internal::objc_getMetaClass( this->impl->_name.c_str() );
                
        return RT::Internal::class_addMethod( cls, RT::Internal::sel_registerName( name.c_str() ), implementation, types.c_str() );
    }
    
    bool ClassBuilder::addInstanceMethod( const std::string & name, IMP implementation, const std::string & types )
    {
        if( name.length() == 0 )
        {
            return false;
        }
        
        if( name == "dealloc" )
        {
            this->impl->_hasCustomDealloc = true;
        }
        
        return RT::Internal::class_addMethod( this->impl->_cls, RT::Internal::sel_registerName( name.c_str() ), implementation, types.c_str() );
    }
    
    void ClassBuilder::registerClass( void )
    {
        if( this->impl->_registered )
        {
            throw new std::runtime_error( std::string( "Class " ) + this->impl->_name + " is already registered." );
        }
        
        if( this->impl->_hasCustomDealloc == false )
        {
            this->addInstanceMethod( "dealloc", reinterpret_cast< IMP >( OBJCXX_IMP_dealloc ), "v16@0:8" );
        }
        
        RT::Internal::objc_registerClassPair( this->impl->_cls );
        
        this->impl->_registered = true;
    }
}

XS::PIMPL::Object< OBJCXX::ClassBuilder >::IMPL::IMPL( void ):
    _name( "" ),
    _super( "" ),
    _cls( nullptr ),
    _registered( false ),
    _hasCustomDealloc( false )
{}

XS::PIMPL::Object< OBJCXX::ClassBuilder >::IMPL::IMPL( const std::string & name, const std::string & super ):
    _name( name ),
    _super( super ),
    _cls( nullptr ),
    _registered( false ),
    _hasCustomDealloc( false )
{}

XS::PIMPL::Object< OBJCXX::ClassBuilder >::IMPL::IMPL( const IMPL & o ):
    _name( o._name ),
    _super( o._super ),
    _cls( o._cls ),
    _registered( o._registered ),
    _hasCustomDealloc( o._hasCustomDealloc )
{}

XS::PIMPL::Object< OBJCXX::ClassBuilder >::IMPL::~IMPL( void )
{}

void OBJCXX_IMP_dealloc( id self, SEL _cmd )
{
    Method     * methods;
    unsigned int count;
    unsigned int i;
    IMP          imp;
    id           object;
    
    methods = OBJCXX::RT::Internal::class_copyMethodList( OBJCXX::RT::Internal::object_getClass( self ), &count );
    
    if( methods )
    {
        for( i = 0; i < count; i++ )
        {
            imp = OBJCXX::RT::Internal::method_getImplementation( methods[ i ] );
            
            if( imp == reinterpret_cast< IMP >( OBJCXX_IMP_Object_Get ) )
            {
                object = imp( self, OBJCXX::RT::Internal::method_getName( methods[ i ] ) );
                
                OBJCXX::RT::Internal::objc_msgSend( object, OBJCXX::RT::Internal::sel_registerName( "release" ) );
            }
        }
        
        free( methods );
    }
    
    {
        struct objc_super sup;
        
        memset( &sup, 0, sizeof( struct objc_super ) );
        
        sup.super_class = OBJCXX::RT::Internal::class_getSuperclass( OBJCXX::RT::Internal::object_getClass( self ) );
        sup.receiver    = self;
        
        OBJCXX::RT::Internal::objc_msgSendSuper( &sup, _cmd );
    }
}

signed char OBJCXX_IMP_SignedChar_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< signed char * >( p ) );
}

signed short OBJCXX_IMP_SignedShort_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< signed short * >( p ) );
}

signed int OBJCXX_IMP_SignedInt_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< signed int * >( p ) );
}

signed long OBJCXX_IMP_SignedLong_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< signed long * >( p ) );
}

signed long long OBJCXX_IMP_SignedLongLong_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< signed long long * >( p ) );
}

unsigned char OBJCXX_IMP_UnsignedChar_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< unsigned char * >( p ) );
}

unsigned short OBJCXX_IMP_UnsignedShort_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< unsigned short * >( p ) );
}

unsigned int OBJCXX_IMP_UnsignedInt_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< unsigned int * >( p ) );
}

unsigned long OBJCXX_IMP_UnsignedLong_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< unsigned long * >( p ) );
}

unsigned long long OBJCXX_IMP_UnsignedLongLong_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< unsigned long long * >( p ) );
}

float OBJCXX_IMP_Float_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< float * >( p ) );
}

double OBJCXX_IMP_Double_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< double * >( p ) );
}

bool OBJCXX_IMP_Bool_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< bool * >( p ) );
}

char * OBJCXX_IMP_CharPointer_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< char ** >( p ) );
}

id OBJCXX_IMP_Object_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< id * >( p ) );
}

Class OBJCXX_IMP_Class_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< Class * >( p ) );
}

SEL OBJCXX_IMP_Selector_Get( id self, SEL _cmd )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n = std::string( "_" ) + OBJCXX::RT::Internal::sel_getName( _cmd );
    c = OBJCXX::RT::Internal::object_getClass( self );
    v = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    return *( reinterpret_cast< SEL * >( p ) );
}

void OBJCXX_IMP_SignedChar_Set( id self, SEL _cmd, signed char value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< signed char * >( p ) ) = value;
}

void OBJCXX_IMP_SignedShort_Set( id self, SEL _cmd, signed short value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< signed short * >( p ) ) = value;
}

void OBJCXX_IMP_SignedInt_Set( id self, SEL _cmd, signed int value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< signed int * >( p ) ) = value;
}

void OBJCXX_IMP_SignedLong_Set( id self, SEL _cmd, signed long value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< signed long * >( p ) ) = value;
}

void OBJCXX_IMP_SignedLongLong_Set( id self, SEL _cmd, signed long long value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< signed long long * >( p ) ) = value;
}

void OBJCXX_IMP_UnsignedChar_Set( id self, SEL _cmd, unsigned char value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< unsigned char * >( p ) ) = value;
}

void OBJCXX_IMP_UnsignedShort_Set( id self, SEL _cmd, unsigned short value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< unsigned short * >( p ) ) = value;
}

void OBJCXX_IMP_UnsignedInt_Set( id self, SEL _cmd, unsigned int value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< unsigned int * >( p ) ) = value;
}

void OBJCXX_IMP_UnsignedLong_Set( id self, SEL _cmd, unsigned long value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< unsigned long * >( p ) ) = value;
}

void OBJCXX_IMP_UnsignedLongLong_Set( id self, SEL _cmd, unsigned long long value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< unsigned long long * >( p ) ) = value;
}

void OBJCXX_IMP_Float_Set( id self, SEL _cmd, float value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< float * >( p ) ) = value;
}

void OBJCXX_IMP_Double_Set( id self, SEL _cmd, double value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< double * >( p ) ) = value;
}

void OBJCXX_IMP_Bool_Set( id self, SEL _cmd, bool value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< bool * >( p ) ) = value;
}

void OBJCXX_IMP_CharPointer_Set( id self, SEL _cmd, char * value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< char ** >( p ) ) = value;
}

void OBJCXX_IMP_Object_Set( id self, SEL _cmd, id value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    id          o;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    o      = *( reinterpret_cast< id * >( p ) );
    
    if( o != value )
    {
        OBJCXX::RT::Internal::objc_msgSend( o, OBJCXX::RT::Internal::sel_registerName( "release" ) );
    }
    
    value = OBJCXX::RT::Internal::objc_msgSend( value, OBJCXX::RT::Internal::sel_registerName( "retain" ) );
    
    *( reinterpret_cast< id * >( p ) ) = value;
}

void OBJCXX_IMP_Class_Set( id self, SEL _cmd, Class value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< Class * >( p ) ) = value;
}

void OBJCXX_IMP_Selector_Set( id self, SEL _cmd, SEL value )
{
    Class       c;
    Ivar        v;
    char      * p;
    std::string n;
    
    n      = OBJCXX::RT::Internal::sel_getName( _cmd );
    n      = n.substr( 3 );
    n      = n.substr( 0, n.length() - 1 );
    n[ 0 ] = static_cast< char >( std::tolower( n[ 0 ] ) );
    n      = std::string( "_" ) + n;
    c      = OBJCXX::RT::Internal::object_getClass( self );
    v      = OBJCXX::RT::Internal::class_getInstanceVariable( c, n.c_str() );
    p      = reinterpret_cast< char * >( self ) + OBJCXX::RT::Internal::ivar_getOffset( v );
    
    *( reinterpret_cast< SEL * >( p ) ) = value;
}
