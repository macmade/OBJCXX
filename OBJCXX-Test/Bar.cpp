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

void Bar::test()
{
    static std::once_flag once;
    
    std::call_once
    (
        once,
        []()
        {
            OBJCXX::ClassBuilder cls( "Bar", "NSObject" );
            
            cls.instanceMethod< Bar, void, int, int >( "method1", &Bar::method1, "" ).add();
            cls.instanceMethod< Bar, void           >( "method2", &Bar::method2, "" ).add();
            cls.instanceMethod< Bar, int, int, int  >( "method3", &Bar::method3, "" ).add();
            cls.instanceMethod< Bar, int            >( "method4", &Bar::method4, "" ).add();
            
            cls.instanceMethod< Bar, void,       const NS::String & >( "method5", &Bar::method5, "" ).add< void, id >();
            cls.instanceMethod< Bar, NS::String, const NS::String & >( "method6", &Bar::method6, "" ).add< id,   id >();
            
            cls.registerClass();
        }
    );
    
    {
        Bar b;
        int x;
        
        b.message< void >( "method1" ).send< int, int >( 42, -1 );
        b.message< void >( "method2" ).send();
        
        x = b.message< int >( "method3" ).send< int, int >( 42, -1 );
        std::cout << "    -> " << x << std::endl;
        
        x = b.message< int >( "method4" ).send();
        std::cout << "    -> " << x << std::endl;
        
        {
            NS::String s;
            
            b.message< void >( "method5" ).send< id >( NS::String( "hello, world" ) );
            
            s = b.message< id >( "method6" ).send< id >( NS::String( "hello, world" ) );
            std::cout << "    -> " << s << std::endl;
        }
    }
}

Bar::Bar(): Object( "Bar" )
{}

void Bar::method1( int x, int y )
{
    std::cout << "Bar::method1( " << x << ", " << y << " ): self = " << static_cast< id >( *( this ) ) << std::endl;
}

void Bar::method2()
{
    std::cout << "Bar::method2(): self = " << static_cast< id >( *( this ) ) << std::endl;
}

int Bar::method3( int x, int y )
{
    std::cout << "Bar::method3( " << x << ", " << y << " ): self = " << static_cast< id >( *( this ) ) << std::endl;
    
    return 10;
}

int Bar::method4()
{
    std::cout << "Bar::method4(): self = " << static_cast< id >( *( this ) ) << std::endl;
    
    return 20;
}

void Bar::method5( const NS::String & s )
{
    std::cout << "Bar::method5( " << s << " ): self = " << static_cast< id >( *( this ) ) << std::endl;
}

NS::String Bar::method6( const NS::String & s )
{
    std::cout << "Bar::method6( " << s << " ): self = " << static_cast< id >( *( this ) ) << std::endl;
    
    return "hello, universe";
}
