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
#include <OBJCXX.hpp>

int main( void )
{
    NS::AutoreleasePool ap;
    
    {
        NS::Object o;
        
        std::cout << o << std::endl;
    }
    
    {
        NS::String o( "hello, world" );
        
        std::cout << o << std::endl;
        std::cout << o.UTF8String() << std::endl;
    }
    
    {
        NS::MutableArray o;
        
        std::cout << o << std::endl;
        
        o.addObject( NS::String( "hello, world" ) );
        o.addObject( NS::String( "hello, universe" ) );
        
        std::cout << o << std::endl;
    }
    
    {
        NS::MutableDictionary o;
        
        std::cout << o << std::endl;
        
        o.setObjectForKey( NS::String( "hello, world" ), NS::String( "key-1" ) );
        o.setObjectForKey( NS::String( "hello, universe" ), NS::String( "key-2" ) );
        
        std::cout << o << std::endl;
    }
    
    {
        NS::String o1( "hello, world" );
        NS::String o2( o1 );
        
        std::cout << o1 << std::endl;
        std::cout << o1.UTF8String() << std::endl;
        
        std::cout << o2 << std::endl;
        std::cout << o2.UTF8String() << std::endl;
        
        std::cout << static_cast< id >( o1 ) << std::endl;
        std::cout << static_cast< id >( o2 ) << std::endl;
    }
    
    {
        NS::FileManager o1;
        NS::FileManager o2;
        NS::Error       e;
        
        o1 = NS::FileManager::defaultManager();
        o2 = NS::FileManager::defaultManager();
        
        std::cout << o1 << std::endl;
        std::cout << o2 << std::endl;
        std::cout << o1.createFileAtPath( "/tmp/OBJCXX-Test.txt", nullptr, nullptr ) << std::endl;
        std::cout << o1.attributesOfItemAtPath( "/tmp/OBJCXX-Test.txt", e ) << std::endl;
        
        if( e == nullptr )
        {
            std::cout << "No error" << std::endl;
        }
        else
        {
            std::cout << "Error: " << e << std::endl;
        }
        
        std::cout << o1.attributesOfItemAtPath( "/tmp/OBJCXX-Test-2.txt", e ) << std::endl;
        
        if( e == nullptr )
        {
            std::cout << "No error" << std::endl;
        }
        else
        {
            std::cout << "Error: " << e << std::endl;
        }
    }
    
    {
        NS::Lock o;
        
        std::cout << o << std::endl;
        
        o.setName( "test" );
        
        std::cout << o << std::endl;
        
        o.lock();
        
        std::cout << o << std::endl;
        
        o.unlock();
        
        std::cout << o << std::endl;
    }
    
    {
        std::cout << NS::Date() << std::endl;
    }
    
    {
        NS::Log( "hello, world %i %i", 42, 43 );
    }
    
    {
        NS::Data        o1{};
        NS::Data        o2{};
        NS::MutableData o3{};
        NS::String      o4{};
        
        o1 = static_cast< id >( o2 );
        o1 = static_cast< id >( o3 );
        
        try
        {
            o1 = static_cast< id >( o4 );
        }
        catch( const std::runtime_error & e )
        {
            std::cout << "Caught exception: " << e.what() << std::endl; 
        }
    }

    #ifdef _WIN32
    getchar();
    #endif
    
    return 0;
}
