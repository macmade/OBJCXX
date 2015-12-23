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
#include <OBJCXX/RT.hpp>
#include <OBJCXX/Foundation/Types.hpp>
#include <XS/PIMPL/Object.hpp>

namespace OBJCXX
{
    class Object: XS::PIMPL::Object< Object >
    {
        public:
            
            using XS::PIMPL::Object< Object >::impl;
            
            Object( const std::string & className );
            Object( const std::string & className, std::function< id( void ) > init );
            Object( id object );
            
            bool operator ==( const Object & o ) const;
            bool operator !=( const Object & o ) const;
            
            operator id( void ) const;
            
            Class                   getClass( void ) const;
            Class                   superclass( void ) const;
            bool                    isEqual( const Object & o ) const;
            Foundation::NSUInteger  hash( void ) const;
            id                      self( void ) const;
            bool                    isKindOfClass( Class cls ) const;
            bool                    isMemberOfClass( Class cls ) const;
            bool                    respondsToSelector( SEL sel ) const;
            bool                    conformsToProtocol( void * protocol ) const;
            std::string             description( void ) const;
            std::string             debugDescription( void ) const;
            id                      performSelector( SEL sel );
            id                      performSelector( SEL sel, id o1 );
            id                      performSelector( SEL sel, id o1, id o2 );
            bool                    isProxy( void ) const;
            id                      retain( void );
            void                    release( void );
            id                      autorelease( void ) const;
            Foundation::NSUInteger  retainCount( void ) const;
            void                  * zone( void ) const;
            
            friend std::ostream & operator << ( std::ostream & os, const Object & o );
            
            template< typename _R_, typename ... _A_, typename = typename std::enable_if< std::is_void< _R_ >::value >::type >
            void sendMessage( const std::string & sel, _A_ ... args ) const
            {
                RT::SendMessage( *( this ), RT::GetSelector( sel ), args ... );
            }
            
            template< typename _R_, typename ... _A_, typename = typename std::enable_if< !std::is_void< _R_ >::value >::type >
            _R_ sendMessage( const std::string & sel, _A_ ... args ) const
            {
                return RT::UnsafeCast< id, _R_ >( RT::SendMessage( *( this ), RT::GetSelector( sel ), args ... ) );
            }
    };
}

#endif /* OBJCXX_OBJECT_H */
