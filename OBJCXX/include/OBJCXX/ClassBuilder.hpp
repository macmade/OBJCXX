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

#ifndef OBJCXX_CLASS_BUILDER_H
#define OBJCXX_CLASS_BUILDER_H

#include <string>
#include <OBJCXX/RT.hpp>
#include <XS/PIMPL/Object.hpp>

#include <iostream>

namespace OBJCXX
{
    class OBJCXX_EXPORT ClassBuilder: public XS::PIMPL::Object< ClassBuilder >
    {
        public:
            
            using XS::PIMPL::Object< ClassBuilder >::impl;
            
            typedef enum
            {
                TypeSignedChar,
                TypeSignedShort,
                TypeSignedInt,
                TypeSignedLong,
                TypeSignedLongLong,
                TypeUnsignedChar,
                TypeUnsignedShort,
                TypeUnsignedInt,
                TypeUnsignedLong,
                TypeUnsignedLongLong,
                TypeFloat,
                TypeDouble,
                TypeBool,
                TypeCharPointer,
                TypeObject,
                TypeClass,
                TypeSelector,
            }
            Type;
            
            ClassBuilder( void );
            ClassBuilder( const std::string & name, const std::string & super, size_t extraBytes = 0 );
            
            Class cls( void ) const;
            
            size_t      sizeForType( Type type )      const;
            uint8_t     alignmentForType( Type type ) const;
            std::string encodingForType( Type type )  const;
            
            bool addProtocol( const std::string & name );
            
            bool addInstanceVariable( const std::string & name, Type type ) const;
            bool addInstanceVariable( const std::string & name, size_t size, uint8_t alignment, const std::string & types ) const;
            
            bool addProperty( const std::string & name, Type type );
            
            bool addClassMethod( const std::string & name, IMP implementation, const std::string & types ) const;
            bool addInstanceMethod( const std::string & name, IMP implementation, const std::string & types );
            
            template< typename ... _A_ >
            static void IMPL_V( id self, SEL _cmd, _A_ ... args )
            {
                id                                     assoc;
                std::function< void( id, _A_ ... ) > * f;
                
                assoc = RT::Internal::objc_getAssociatedObject
                (
                    reinterpret_cast< id >( RT::Internal::object_getClass( self ) ),
                    _cmd
                );
                
                if( assoc == nullptr )
                {
                    return;
                }
                
                f = reinterpret_cast< decltype( f ) >( assoc );
                
                ( *( f ) )( self, std::forward< _A_ >( args ) ... );
            }
            
            template< typename _R_, typename ... _A_ >
            static _R_ IMPL_R( id self, SEL _cmd, _A_ ... args )
            {
                id                                     assoc;
                std::function< _R_( id, _A_ ... ) > * f;
                
                assoc = RT::Internal::objc_getAssociatedObject
                (
                    reinterpret_cast< id >( RT::Internal::object_getClass( self ) ),
                    _cmd
                );
                
                if( assoc == nullptr )
                {
                    return {};
                }
                
                f = reinterpret_cast< decltype( f ) >( assoc );
                
                return ( *( f ) )( self, std::forward< _A_ >( args ) ... );
            }
            
            template< class _C_, typename _R_, typename ... _A_ >
            bool addInstanceMethod( const std::string & name, void ( _C_::* imp )( _A_ ... ), const std::string & types )
            {
                SEL s;
                
                ( void )imp;
                
                s = RT::Internal::sel_registerName( name.c_str() );
                
                if
                (
                    RT::Internal::class_addMethod
                    (
                        this->cls(),
                        s,
                        reinterpret_cast< IMP >( IMPL_V< _A_ ... > ),
                        types.c_str()
                    )
                    == false
                )
                {
                    return false;
                }
                
                RT::Internal::objc_setAssociatedObject
                (
                    reinterpret_cast< id >( this->cls() ),
                    s,
                    reinterpret_cast< id >
                    (
                        new std::function< _R_( id, _A_ ... ) >
                        (
                            [ = ]( id self, _A_ ... args )
                            {
                                _C_ o( self );
                                
                                ( o.* imp )( std::forward< _A_ >( args )... );
                            }
                        )
                    ),
                    RT::Internal::AssociationPolicy::Assign
                );
                
                return true;
            }
            
            template< class _C_, typename _R_, typename ... _A_ >
            bool addInstanceMethod( const std::string & name, _R_ ( _C_::* imp )( _A_ ... ), const std::string & types )
            {
                SEL s;
                
                ( void )imp;
                
                s = RT::Internal::sel_registerName( name.c_str() );
                
                if
                (
                    RT::Internal::class_addMethod
                    (
                        this->cls(),
                        s,
                        reinterpret_cast< IMP >( IMPL_V< _A_ ... > ),
                        types.c_str()
                    )
                    == false
                )
                {
                    return false;
                }
                
                RT::Internal::objc_setAssociatedObject
                (
                    reinterpret_cast< id >( this->cls() ),
                    s,
                    reinterpret_cast< id >
                    (
                        new std::function< _R_( id, _A_ ... ) >
                        (
                            [ = ]( id self, _A_ ... args )
                            {
                                _C_ o( self );
                                
                                return ( o.* imp )( std::forward< _A_ >( args )... );
                            }
                        )
                    ),
                    RT::Internal::AssociationPolicy::Assign
                );
                
                return true;
            }
            
            void registerClass( void );
    };
}

#endif /* OBJCXX_CLASS_BUILDER_H */
