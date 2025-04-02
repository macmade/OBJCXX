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

#ifndef OBJCXX_RT_METHOD_SIGNATURE_H
#define OBJCXX_RT_METHOD_SIGNATURE_H

#include <string>
#include <memory>
#include <algorithm>
#include <OBJCXX/RT.hpp>

namespace OBJCXX
{
    namespace RT
    {
        class OBJCXX_EXPORT MethodSignature
        {
            public:
                
                MethodSignature( const std::string & encoding );
                MethodSignature( const MethodSignature & o );
                MethodSignature( MethodSignature && o ) noexcept;
                ~MethodSignature();
                
                MethodSignature & operator =( MethodSignature o );
                
                friend void swap( MethodSignature & o1, MethodSignature & o2 );
                
                std::string GetTypeEncoding()                           const;
                std::size_t GetNumberOfArguments()                      const;
                std::string GetArgumentTypeAtIndex( std::size_t index ) const;
                std::string GetReturnType()                             const;
                
            private:
                
                class IMPL;
                
                std::unique_ptr< IMPL > impl;
        };
        
        template< typename _R_, typename ... _A_ >
        MethodSignature SignatureForMethod()
        {
            std::tuple< id, SEL, _A_ ... > t1;
            std::string                    e;
            std::string                    a;
            std::size_t                    o;
            std::size_t                    l;
            std::size_t                    s;
            
            e = GetEncodingForType< _R_ >();
            o = 0;
            l = 0;
            
            /* For lambdas - We're on C++17 anyway... */
            #ifdef __clang__
            #pragma clang diagnostic push
            #pragma clang diagnostic ignored "-Wc++98-compat"
            #endif
            For< 0, std::tuple_size< decltype( t1 ) >::value >
            (
                [ & ]( auto i )
                {
                    std::tuple< id, SEL, _A_ ... > t2;
                    
                    s  = sizeof( typename std::tuple_element< i, decltype( t2 ) >::type );
                    a += GetEncodingForType< typename std::tuple_element< i, decltype( t2 ) >::type >();
                    a += std::to_string( o );
                    o += s;
                    l += s;
                }
            );
            
            e += std::to_string( l );
            e += a;
            
            return MethodSignature( e );
        }
    }
}

#endif /* OBJCXX_RT_METHOD_SIGNATURE_H */
