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

#ifndef OBJCXX_RT_H
#define OBJCXX_RT_H

/*
 * Disable warnings about class members not having DLL-interface.
 * Eg: std::shared_ptr
 */
#ifdef _WIN32
    #pragma warning( push )
    #pragma warning( disable: 4251 )
#endif

#ifdef _WIN32
    #ifdef OBJCXX_DLL_BUILD
        #define OBJCXX_EXPORT __declspec( dllexport )
    #else
        #define OBJCXX_EXPORT __declspec( dllimport )
    #endif
#else
        #define OBJCXX_EXPORT     
#endif

#ifdef WIN32
    #define OBJCXX_EXTERN __declspec( dllimport )
#else
    #define OBJCXX_EXTERN extern
#endif

#include <type_traits>
#include <string>
#include <XS/PIMPL/Object.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstdarg>

extern "C"
{
    typedef struct objc_class    * Class;
    typedef struct objc_object   * id;
    typedef struct objc_selector * SEL;
    typedef struct objc_method   * Method;
    typedef struct objc_ivar     * Ivar;
    typedef struct objc_object     Protocol;
    
    typedef id ( * IMP )( id self, SEL _cmd, ... );
    
    struct objc_super
    {
        id    receiver;
        Class super_class;
    };
    
    #ifdef _WIN32
    
    extern Class        ( * objc_getClass             )( const char * );
    extern Class        ( * objc_getMetaClass         )( const char * );
    extern Protocol *   ( * objc_getProtocol          )( const char * );
    extern id           ( * objc_msgSend              )( id, SEL, ... );
    extern double       ( * objc_msgSend_fpret        )( id, SEL, ... );
    extern void         ( * objc_msgSend_stret        )( void *, id, SEL, ... );
    extern id           ( * objc_msgSendSuper         )( struct objc_super *, SEL, ... );
    extern Class        ( * objc_allocateClassPair    )( Class, const char *, size_t );
    extern void         ( * objc_registerClassPair    )( Class );
    extern SEL          ( * sel_registerName          )( const char * );
    extern const char * ( * sel_getName               )( SEL );
    extern Class        ( * object_getClass           )( id );
    extern IMP          ( * method_getImplementation  )( Method );
    extern SEL          ( * method_getName            )( Method );
    extern Class        ( * class_getSuperclass       )( Class );
    extern const char * ( * class_getName             )( Class );
    extern Method     * ( * class_copyMethodList      )( Class, unsigned int * );
    extern bool         ( * class_addIvar             )( Class, const char *, size_t, uint8_t, const char * );
    extern bool         ( * class_addMethod           )( Class, SEL, IMP, const char * );
    extern bool         ( * class_addProtocol         )( Class, Protocol * );
    extern Ivar         ( * class_getInstanceVariable )( Class, const char * );
    extern ptrdiff_t    ( * ivar_getOffset            )( Ivar );
    extern void         ( * NSLogv                    )( id, va_list );
    
    #else
    
    extern Class        objc_getClass             ( const char * );
    extern Class        objc_getMetaClass         ( const char * );
    extern Protocol *   objc_getProtocol          ( const char * );
    extern id           objc_msgSend              ( id, SEL, ... );
    extern double       objc_msgSend_fpret        ( id, SEL, ... );
    extern void         objc_msgSend_stret        ( void *, id, SEL, ... );
    extern id           objc_msgSendSuper         ( struct objc_super *, SEL, ... );
    extern Class        objc_allocateClassPair    ( Class, const char *, size_t );
    extern void         objc_registerClassPair    ( Class );
    extern SEL          sel_registerName          ( const char * );
    extern const char * sel_getName               ( SEL );
    extern Class        object_getClass           ( id );
    extern IMP          method_getImplementation  ( Method );
    extern SEL          method_getName            ( Method );
    extern Class        class_getSuperclass       ( Class );
    extern const char * class_getName             ( Class );
    extern Method     * class_copyMethodList      ( Class, unsigned int * );
    extern bool         class_addIvar             ( Class, const char *, size_t, uint8_t, const char * );
    extern bool         class_addMethod           ( Class, SEL, IMP, const char * );
    extern bool         class_addProtocol         ( Class, Protocol * );
    extern Ivar         class_getInstanceVariable ( Class, const char * );
    extern ptrdiff_t    ivar_getOffset            ( Ivar );
    extern void         NSLogv                    ( id, va_list );
    
    #endif
}

namespace OBJCXX
{
    namespace RT
    {
        #ifdef _WIN32
        OBJCXX_EXPORT void Win32Init( void );
        #endif

        OBJCXX_EXPORT Class       GetClass( const std::string & name );
        OBJCXX_EXPORT Class       GetClass( id object );
        OBJCXX_EXPORT std::string GetClassName( Class cls );
        OBJCXX_EXPORT SEL         GetSelector( const std::string & name );

        template< typename _T_, typename _R_ >
        _R_ UnsafeCast( _T_ v )
        {
            uintptr_t p;
            
            p = reinterpret_cast< uintptr_t >( v );
            
            return *( reinterpret_cast< _R_ * >( &p ) );
        }
        
        class OBJCXX_EXPORT MessageBase: public XS::PIMPL::Object< MessageBase >
        {
            public:
                
                using XS::PIMPL::Object< MessageBase >::impl;
                
                MessageBase( id object, const std::string & selector );
                MessageBase( Class cls, const std::string & selector );
                MessageBase( const std::string & cls, const std::string & selector );
                
                id object( void );
                SEL selector( void );
        };
        
        template< typename _T_, class _E_ = void >
        class Message;
        
        template< class _U_ > struct IsVoidReturnType:   public std::integral_constant< bool, std::is_void< _U_ >::value > {};
        template< class _U_ > struct IsFloatReturnType:  public std::integral_constant< bool, std::is_floating_point< _U_ >::value > {};
        template< class _U_ > struct IsStructReturnType: public std::integral_constant< bool, std::is_class< _U_ >::value > {};
        template< class _U_ > struct IsSimpleReturnType: public std::integral_constant< bool, !IsVoidReturnType< _U_ >::value && !IsStructReturnType< _U_ >::value && !IsFloatReturnType< _U_ >::value > {};
        
        template< typename _T_ >
        class OBJCXX_EXPORT Message< _T_, typename std::enable_if< IsSimpleReturnType< _T_ >::value >::type >: public MessageBase
        {
            public:
                
                Message( id object, const std::string & selector ): MessageBase( object, selector )
                {}
                
                Message( Class cls, const std::string & selector ): MessageBase( cls, selector )
                {}
                
                Message( const std::string & cls, const std::string & selector ): MessageBase( cls, selector )
                {}
                   
                template< typename ... _A_ >
                _T_ send( _A_ ... args )
                {
                    return UnsafeCast< id, _T_ >( objc_msgSend( this->object(), this->selector(), args ... ) );
                }
        };
        
        template< typename _T_ >
        class OBJCXX_EXPORT Message< _T_, typename std::enable_if< IsVoidReturnType< _T_ >::value >::type >: public MessageBase
        {
            public:
                
                Message( id object, const std::string & selector ): MessageBase( object, selector )
                {}
                
                Message( Class cls, const std::string & selector ): MessageBase( cls, selector )
                {}
                
                Message( const std::string & cls, const std::string & selector ): MessageBase( cls, selector )
                {}
                   
                template< typename ... _A_ >
                void send( _A_ ... args )
                {
                    objc_msgSend( this->object(), this->selector(), args ... );
                }
        };
        
        template< typename _T_ >
        class OBJCXX_EXPORT Message< _T_, typename std::enable_if< IsFloatReturnType< _T_ >::value >::type >: public MessageBase
        {
            public:
                
                Message( id object, const std::string & selector ): MessageBase( object, selector )
                {}
                
                Message( Class cls, const std::string & selector ): MessageBase( cls, selector )
                {}
                
                Message( const std::string & cls, const std::string & selector ): MessageBase( cls, selector )
                {}
                   
                template< typename ... _A_ >
                _T_ send( _A_ ... args )
                {
                    return static_cast< _T_ >( objc_msgSend_fpret( this->object(), this->selector(), args ... ) );
                }
        };
        
        template< typename _T_ >
        class OBJCXX_EXPORT Message< _T_, typename std::enable_if< IsStructReturnType< _T_ >::value >::type >: public MessageBase
        {
            public:
                
                Message( id object, const std::string & selector ): MessageBase( object, selector )
                {}
                
                Message( Class cls, const std::string & selector ): MessageBase( cls, selector )
                {}
                
                Message( const std::string & cls, const std::string & selector ): MessageBase( cls, selector )
                {}
                   
                template< typename ... _A_ >
                _T_ send( _A_ ... args )
                {
                    _T_ s {};
                    
                    static_cast< _T_ >( objc_msgSend_stret( &s, this->object(), this->selector(), args ... ) );
                    
                    return s;
                }
        };
    }
}

#endif /* OBJCXX_RT_H */
