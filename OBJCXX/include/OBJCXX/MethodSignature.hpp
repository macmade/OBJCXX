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
#include <tuple>
#include <type_traits>
#include <functional>
#include <OBJCXX/RT.hpp>

namespace OBJCXX
{
    namespace RT
    {
        template< typename _R_, typename ... _A_ >
        class MethodSignature
        {
            public:
                
                std::string GetTypeEncoding( void ) const
                {
                    std::tuple< id, SEL, _A_ ... > t;
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
                    MethodSignature::For< 0, std::tuple_size< decltype( t ) >::value >
                    (
                        [ & ]( auto i )
                        {
                            s  = sizeof( typename std::tuple_element< i, decltype( t ) >::type );
                            a += GetEncodingForType< typename std::tuple_element< i, decltype( t ) >::type >();
                            a += std::to_string( o );
                            o += s;
                            l += s;
                        }
                    );
                    
                    e += std::to_string( l );
                    e += a;
                    
                    return e;
                }
                
            private:
                
                template< std::size_t _I_, std::size_t _N_, typename _F_ >
                static inline void For( _F_ const & f )
                {
                    /* For constexpr - We're on C++17 anyway... */
                    #ifdef __clang__
                    #pragma clang diagnostic push
                    #pragma clang diagnostic ignored "-Wc++98-c++11-c++14-compat"
                    #endif
                    if constexpr( _I_ < _N_ )
                    {
                         f( std::integral_constant< size_t, _I_ >{} );
                         MethodSignature::For< _I_ + 1, _N_ >( f );
                    }
                    #ifdef __clang__
                    #pragma clang diagnostic pop
                    #endif
                }
        };
    }
}

#endif /* OBJCXX_RT_METHOD_SIGNATURE_H */
