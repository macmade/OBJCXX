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

Class        ( * objc_getClass             )( const char * )                                        = nullptr;
Class        ( * objc_getMetaClass         )( const char * )                                        = nullptr;
Protocol *   ( * objc_getProtocol          )( const char * )                                        = nullptr;
id           ( * objc_msgSend              )( id, SEL, ... )                                        = nullptr;
double       ( * objc_msgSend_fpret        )( id, SEL, ... )                                        = nullptr;
void         ( * objc_msgSend_stret        )( void *, id, SEL, ... )                                = nullptr;
id           ( * objc_msgSendSuper         )( struct objc_super *, SEL, ... )                       = nullptr;
Class        ( * objc_allocateClassPair    )( Class, const char *, size_t )                         = nullptr;
void         ( * objc_registerClassPair    )( Class )                                               = nullptr;
SEL          ( * sel_registerName          )( const char * )                                        = nullptr;
const char * ( * sel_getName               )( SEL )                                                 = nullptr;
Class        ( * object_getClass           )( id )                                                  = nullptr;
IMP          ( * method_getImplementation  )( Method )                                              = nullptr;
SEL          ( * method_getName            )( Method )                                              = nullptr;
Class        ( * class_getSuperclass       )( Class )                                               = nullptr;
const char * ( * class_getName             )( Class )                                               = nullptr;
Method     * ( * class_copyMethodList      )( Class, unsigned int * )                               = nullptr;
bool         ( * class_addIvar             )( Class, const char *, size_t, uint8_t, const char * )  = nullptr;
bool         ( * class_addMethod           )( Class, SEL, IMP, const char * )                       = nullptr;
bool         ( * class_addProtocol         )( Class, Protocol * )                                   = nullptr;
Ivar         ( * class_getInstanceVariable )( Class, const char * )                                 = nullptr;
ptrdiff_t    ( * ivar_getOffset            )( Ivar )                                                = nullptr;
void         ( * NSLogv                    )( id, va_list )                                         = nullptr;

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
    
    if( ws == NULL )
    {
        return;
    }
    
    objc       = LoadLibrary( ( std::wstring( ws ) + L"\\objc.dll" ).c_str() );
    foundation = LoadLibrary( ( std::wstring( ws ) + L"\\Foundation.dll" ).c_str() );
    
    if( objc == nullptr || foundation == nullptr )
    {
        free( ws );
    
        return;
    }
    
    objc_getClass               = ( Class        ( * )( const char * )                                       )GetProcAddress( objc, "objc_getClass" );
    objc_getMetaClass           = ( Class        ( * )( const char * )                                       )GetProcAddress( objc, "objc_getMetaClass" );
    objc_getProtocol            = ( Protocol *   ( * )( const char * )                                       )GetProcAddress( objc, "objc_getProtocol" );
    objc_msgSend                = ( id           ( * )( id, SEL, ... )                                       )GetProcAddress( objc, "objc_msgSend" );
    objc_msgSend_fpret          = ( double       ( * )( id, SEL, ... )                                       )GetProcAddress( objc, "objc_msgSend_fpret" );
    objc_msgSend_stret          = ( void         ( * )( void *, id, SEL, ... )                               )GetProcAddress( objc, "objc_msgSend_stret" );
    objc_msgSendSuper           = ( id           ( * )( struct objc_super *, SEL, ... )                      )GetProcAddress( objc, "objc_msgSendSuper" );
    objc_allocateClassPair      = ( Class        ( * )( Class, const char *, size_t )                        )GetProcAddress( objc, "objc_allocateClassPair" );
    objc_registerClassPair      = ( void         ( * )( Class )                                              )GetProcAddress( objc, "objc_registerClassPair" );
    sel_registerName            = ( SEL          ( * )( const char * )                                       )GetProcAddress( objc, "sel_registerName" );
    sel_getName                 = ( const char * ( * )( SEL )                                                )GetProcAddress( objc, "sel_getName" );
    object_getClass             = ( Class        ( * )( id )                                                 )GetProcAddress( objc, "object_getClass" );
    method_getImplementation    = ( IMP          ( * )( Method )                                             )GetProcAddress( objc, "method_getImplementation" );
    method_getName              = ( SEL          ( * )( Method )                                             )GetProcAddress( objc, "method_getName" );
    class_getSuperclass         = ( Class        ( * )( Class )                                              )GetProcAddress( objc, "class_getSuperclass" );
    class_getName               = ( const char * ( * )( Class )                                              )GetProcAddress( objc, "class_getName" );
    class_copyMethodList        = ( Method     * ( * )( Class, unsigned int * )                              )GetProcAddress( objc, "class_copyMethodList" );
    class_addIvar               = ( bool         ( * )( Class, const char *, size_t, uint8_t, const char * ) )GetProcAddress( objc, "class_addIvar" );
    class_addMethod             = ( bool         ( * )( Class, SEL, IMP, const char * )                      )GetProcAddress( objc, "class_addMethod" );
    class_addProtocol           = ( bool         ( * )( Class, Protocol * )                                  )GetProcAddress( objc, "class_addProtocol" );
    class_getInstanceVariable   = ( Ivar         ( * )( Class, const char * )                                )GetProcAddress( objc, "class_getInstanceVariable" );
    ivar_getOffset              = ( ptrdiff_t    ( * )( Ivar )                                               )GetProcAddress( objc, "ivar_getOffset" );
    NSLogv                      = ( void         ( * )( id, va_list )                                        )GetProcAddress( foundation, "NSLogv" );
    
    free( ws );
}

#endif
