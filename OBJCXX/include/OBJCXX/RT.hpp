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

extern "C"
{
    #ifdef WIN32
    #define OBJCXX_EXTERN __declspec( dllimport )
    #else
    #define OBJCXX_EXTERN extern
    #endif

    typedef struct objc_class    * Class;
    typedef struct objc_object   * id;
    typedef struct objc_selector * SEL;

    OBJCXX_EXTERN Class         objc_getClass( const char * name );
    OBJCXX_EXTERN id            objc_msgSend( id object, SEL selector, ... );
    OBJCXX_EXTERN SEL           sel_registerName( const char * name );
    OBJCXX_EXTERN Class         object_getClass( id object );
    OBJCXX_EXTERN const char *  class_getName( Class object );
}

#include <string>

namespace OBJCXX
{
    namespace RT
    {
        Class       GetClass( const std::string & name );
        Class       GetClass( id object );
        std::string GetClassName( Class cls );
        SEL         GetSelector( const std::string & name );
        
        template< typename ... _A_ >
        id SendMessage( id object, _A_ ... args )
        {
            return objc_msgSend( object, args ... );
        }
        
        template< typename _T_, typename _R_ >
        _R_ cast( _T_ v )
        {
            uintptr_t p;
            
            p = reinterpret_cast< uintptr_t >( v );
            
            return *( reinterpret_cast< _R_ * >( &p ) );
        }
    }
}

#endif /* OBJCXX_RT_H */
