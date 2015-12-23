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
    {
        Foundation::NSObject o;
        
        std::cout << o << std::endl;
    }
    
    {
        Foundation::NSString o( "hello, world" );
        
        std::cout << o << std::endl;
        std::cout << o.UTF8String() << std::endl;
    }
    
    {
        Foundation::NSMutableArray o;
        
        std::cout << o << std::endl;
        
        o.addObject( Foundation::NSString( "hello, world" ) );
        o.addObject( Foundation::NSString( "hello, universe" ) );
        
        std::cout << o << std::endl;
    }
    
    {
        Foundation::NSMutableDictionary o;
        
        std::cout << o << std::endl;
        
        o.setObjectForKey( Foundation::NSString( "hello, world" ), Foundation::NSString( "key-1" ) );
        o.setObjectForKey( Foundation::NSString( "hello, universe" ), Foundation::NSString( "key-2" ) );
        
        std::cout << o << std::endl;
    }
    
    {
        Foundation::NSString o1( "hello, world" );
        Foundation::NSString o2( o1 );
        
        std::cout << o1 << std::endl;
        std::cout << o1.UTF8String() << std::endl;
        
        std::cout << o2 << std::endl;
        std::cout << o2.UTF8String() << std::endl;
        
        std::cout << static_cast< id >( o1 ) << std::endl;
        std::cout << static_cast< id >( o2 ) << std::endl;
    }
    
    {
        Foundation::NSFileManager o1;
        Foundation::NSFileManager o2;
        Foundation::NSError       e;
        
        o1 = Foundation::NSFileManager::defaultManager();
        o2 = Foundation::NSFileManager::defaultManager();
        
        std::cout << o1 << std::endl;
        std::cout << o2 << std::endl;
        std::cout << o1.createFileAtPath( "/tmp/OBJCXX-Test.txt", nullptr, nullptr ) << std::endl;
        std::cout << o1.attributesOfItemAtPath( "/tmp/OBJCXX-Test.txt", e ) << std::endl;
    }
    
    {
        Foundation::NSLog( "hello, world %i %i", 42, 43 );
    }
    
    return 0;
}
