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

#include <iostream>
#include <mutex>
#include "Bar.hpp"

void Bar::test( void )
{
    static std::once_flag once;
    
    std::call_once
    (
        once,
        []( void )
        {
            OBJCXX::ClassBuilder cls( "Bar", "NSObject" );
            
            cls.addInstanceMethod< Bar, void, int, int >( "method1", &Bar::method1, "" );
            cls.registerClass();
        }
    );
    
    {
        Bar b;
        
        b.message< void >( "method1" ).send< int, int >( 42, -1 );
    }
}

Bar::Bar( void ): Object( "Bar" )
{}

void Bar::method1( int x, int y )
{
    std::cout << "Bar::method1( " << x << ", " << y << " ): " << static_cast< id >( *( this ) ) << std::endl;
}
