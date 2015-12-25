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

#ifndef OBJCXX_OBJECT_H
#define OBJCXX_OBJECT_H

#include <string>
#include <functional>
#include <type_traits>
#include <OBJCXX/RT.hpp>
#include <OBJCXX/Foundation/Types.hpp>
#include <OBJCXX/Foundation/Protocols/NSObject.hpp>
#include <XS/PIMPL/Object.hpp>

namespace OBJCXX
{
    class Object: XS::PIMPL::Object< Object >, NS::Protocols::Object
    {
        public:
            
            using XS::PIMPL::Object< Object >::impl;
            
            Object( const std::string & className );
            Object( const std::string & className, std::function< id( void ) > init );
            Object( id object );
            Object( const Object & o );
            Object( Object && o );
            
            Object & operator =( Object o );
            
            bool operator ==( const Object & o ) const;
            bool operator !=( const Object & o ) const;
            
            bool operator ==( id object ) const;
            bool operator !=( id object ) const;
            
            bool operator ==( std::nullptr_t n ) const;
            bool operator !=( std::nullptr_t n ) const;
            
            operator id( void ) const;
            
            id * operator &( void ) const;
            
            template < typename _T_ >
            RT::Message< _T_ > message( const std::string & selector ) const
            {
                return RT::Message< _T_ >( *( this ), selector );
            }
            
            friend std::ostream & operator << ( std::ostream & os, const Object & o );
            
            Class           getClass( void )                      const override;
            Class           superclass( void )                    const override;
            bool            isEqual( const Object & o )           const override;
            NS::UInteger    hash( void )                          const override;
            id              self( void )                          const override;
            bool            isKindOfClass( Class cls )            const override;
            bool            isMemberOfClass( Class cls )          const override;
            bool            respondsToSelector( SEL sel )         const override;
            bool            conformsToProtocol( void * protocol ) const override;
            std::string     description( void )                   const override;
            std::string     debugDescription( void )              const override;
            id              performSelector( SEL sel )                  override;
            id              performSelector( SEL sel, id o1 )           override;
            id              performSelector( SEL sel, id o1, id o2 )    override;
            bool            isProxy( void )                       const override;
            id              retain( void )                              override;
            void            release( void )                             override;
            id              autorelease( void )                   const override;
            NS::UInteger    retainCount( void )                   const override;
            void          * zone( void )                          const override;
            
    };
}

#endif /* OBJCXX_OBJECT_H */
