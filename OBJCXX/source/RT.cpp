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

#include <OBJCXX/RT.hpp>

template<>
class XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( id object, const std::string & selector );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        id  _object;
        SEL _selector;
};

#define XS_PIMPL_CLASS OBJCXX::RT::MessageBase
#include <XS/PIMPL/Object-IMPL.hpp>

namespace OBJCXX
{
    namespace RT
    {
        Class GetClass( const std::string & name )
        {
            Class ret;
            
            if( name.length() == 0 )
            {
                throw std::runtime_error( "Empty class name" );
            }
            
            ret = objc_getClass( name.c_str() );
            
            if( ret == nullptr )
            {
                {
                    std::string msg;
                    
                    msg = "No class named '" + name + "'";
                    
                    throw std::runtime_error( msg );
                }
            }
            
            return ret;
        }
        
        Class GetClass( id object )
        {
            return object_getClass( object );
        }
        
        std::string GetClassName( Class cls )
        {
            const char * s;
            
            if( cls == nullptr )
            {
                return "";
            }
            
            s = class_getName( cls );
            
            if( s == nullptr )
            {
                return "";
            }
            
            return s;
        }
        
        SEL GetSelector( const std::string & name )
        {
            SEL ret;
            
            if( name.length() == 0 )
            {
                throw std::runtime_error( "Empty selector name" );
            }
            
            ret = sel_registerName( name.c_str() );
            
            if( ret == nullptr )
            {
                {
                    std::string msg;
                    
                    msg = "No selector named '" + name + "'";
                    
                    throw std::runtime_error( msg );
                }
            }
            
            return ret;
        }
              
        MessageBase::MessageBase( id object, const std::string & selector ):
            XS::PIMPL::Object< MessageBase >( object, selector )
        {}
        
        MessageBase::MessageBase( Class cls, const std::string & selector ):
            XS::PIMPL::Object< MessageBase >( reinterpret_cast< id >( cls ), selector )
        {}
        
        MessageBase::MessageBase( const std::string & cls, const std::string & selector ):
            MessageBase( GetClass( cls ), selector )
        {}
        
        id MessageBase::object( void )
        {
            return this->impl->_object;
        }
        
        SEL MessageBase::selector( void )
        {
            return this->impl->_selector;
        }
    }
}

XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL::IMPL( void ):
    _object( nullptr ),
    _selector( nullptr )
{}

XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL::IMPL( id object, const std::string & selector ):
    _object( object ),
    _selector( OBJCXX::RT::GetSelector( selector ) )
{}

XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL::IMPL( const IMPL & o ):
    _object( o._object ),
    _selector( o._selector )
{}

XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL::~IMPL( void )
{}

#ifdef _WIN32

#include <Windows.h>

Class         ( * objc_getClass )( const char * name )                              = nullptr;
id            ( * objc_msgSend )( id object, SEL selector, ... )                    = nullptr;
double        ( * objc_msgSend_fpret )( id object, SEL selector, ... )              = nullptr;
void          ( * objc_msgSend_stret )( void * addr, id object, SEL selector, ... ) = nullptr;
SEL           ( * sel_registerName )( const char * name )                           = nullptr;
Class         ( * object_getClass )( id object )                                    = nullptr;
const char *  ( * class_getName )( Class object )                                   = nullptr;
void          ( * NSLogv )( id format, va_list ap )                                 = nullptr;

#pragma section( ".CRT$XCU", read )
    
static void __cdecl win32_init( void );

__declspec( allocate( ".CRT$XCU" ) ) void ( __cdecl * win32_init_ )( void ) = win32_init;

#include <iostream>

static void __cdecl win32_init( void )
{
    char       * common;
    std::string  apple;
    wchar_t    * ws;
    int          n;
    HMODULE      objc;
    HMODULE      foundation;
    
    #ifdef _WIN64
    common = nullptr;
    #else
    common = getenv( "COMMONPROGRAMFILES(x86)" );
    #endif
    
    if( common == nullptr )
    {
        common = getenv( "COMMONPROGRAMFILES" );
    }
    
    apple = std::string( common ) + "\\Apple\\Apple Application Support";
    n     = MultiByteToWideChar( CP_UTF8, 0, apple.c_str(), -1, NULL, 0 );
    ws    = ( wchar_t * )malloc( ( ( size_t )n * sizeof( wchar_t ) ) + sizeof( wchar_t ) );
    
    if( ws != NULL )
    {
        MultiByteToWideChar( CP_UTF8, 0, apple.c_str(), -1, ws, n );
        SetDllDirectory( ws );
    }

    objc = LoadLibrary( ( std::wstring( ws ) + L"\\objc.dll" ).c_str() );

    if( objc == nullptr )
    {
        free( ws );

        return;
    }

    objc_getClass      = ( Class        ( * )( const char * )         )GetProcAddress( objc, "objc_getClass" );
    objc_msgSend       = ( id           ( * )( id, SEL, ... )         )GetProcAddress( objc, "objc_msgSend" );
    objc_msgSend_fpret = ( double       ( * )( id, SEL, ... )         )GetProcAddress( objc, "objc_msgSend_fpret" );
    objc_msgSend_stret = ( void         ( * )( void *, id, SEL, ... ) )GetProcAddress( objc, "objc_msgSend_stret" );
    sel_registerName   = ( SEL          ( * )( const char * )         )GetProcAddress( objc, "sel_registerName" );
    object_getClass    = ( Class        ( * )( id )                   )GetProcAddress( objc, "object_getClass" );
    class_getName      = ( const char * ( * )( Class )                )GetProcAddress( objc, "class_getName" );

    foundation = LoadLibrary( ( std::wstring( ws ) + L"\\Foundation.dll" ).c_str() );

    if( objc == nullptr )
    {
        free( ws );

        return;
    }

    NSLogv = ( void ( * )( id, va_list ) )GetProcAddress( foundation, "NSLogv" );

    free( ws );
}

#endif
