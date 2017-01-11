OBJCXX
======

[![Build Status](https://img.shields.io/travis/macmade/OBJCXX.svg?branch=master&style=flat)](https://travis-ci.org/macmade/OBJCXX)
[![Coverage Status](https://img.shields.io/coveralls/macmade/OBJCXX.svg?branch=master&style=flat)](https://coveralls.io/r/macmade/OBJCXX?branch=master)
[![Issues](http://img.shields.io/github/issues/macmade/OBJCXX.svg?style=flat)](https://github.com/macmade/OBJCXX/issues)
![Status](https://img.shields.io/badge/status-prototype-orange.svg?style=flat)
![License](https://img.shields.io/badge/license-mit-brightgreen.svg?style=flat)
[![Contact](https://img.shields.io/badge/contact-@macmade-blue.svg?style=flat)](https://twitter.com/macmade)  
[![Donate-Patreon](https://img.shields.io/badge/donate-patreon-yellow.svg?style=flat)](https://patreon.com/macmade)
[![Donate-Gratipay](https://img.shields.io/badge/donate-gratipay-yellow.svg?style=flat)](https://www.gratipay.com/macmade)
[![Donate-Paypal](https://img.shields.io/badge/donate-paypal-yellow.svg?style=flat)](https://paypal.me/xslabs)

About
-----

OBJCXX is a C++ wrapper library for the Objective-C language and the Apple's Foundation framework.

It allows you to use the complete Foundation framework using C++ on macOS and Windows without the need of an Objective-C compiler.

### Technical Details

This library uses the Objective-C runtime to interact with the Foundation framework's classes.  
As the Objective-C runtime is a C API, an Objective-C compiler is not required.

All Foundation classes are wrapped by C++ counterparts, which can be used with automatic allocation.  
Memory is automatically managed. Objective-C instances are retained by their C++ counterparts, and released when necessary.

Example
-------

Here's an hello world example using OBJCXX:
    
    #include <OBJCXX.h>
    
    int main( void )
    {
        NS::Log( "%@", NS::String( "hello, world" ) );
        
        return 0;
    }
    
Here's a more complex example:

    #include <OBJCXX.h>
    
    int main( void )
    {
        /* Equivalent to @autoreleasepool */
        NS::AutoreleasePool ap;
        
        /* NSMutableArray */
        {
            NS::MutableArray o;
            
            std::cout << o << std::endl;
            
            o.addObject( NS::String( "hello, world" ) );
            o.addObject( NS::String( "hello, universe" ) );
            
            std::cout << o << std::endl;
        }
        
        /* NSMutableDictionary */
        {
            NS::MutableDictionary o;
            
            std::cout << o << std::endl;
            
            o.setObjectForKey( NS::String( "hello, world" ),    NS::String( "key-1" ) );
            o.setObjectForKey( NS::String( "hello, universe" ), NS::String( "key-2" ) );
            
            std::cout << o << std::endl;
        }
        
        /* NSFileManager */
        {
            NS::Error e;
            
            std::cout << NS::FileManager::defaultManager().attributesOfItemAtPath( "/~/Desktop/", e ) << std::endl;
        }
        
        return 0;
    }

### Creating Objective-C classes from C++

OBJCXX also allows you to dynamically create Objective-C classes at runtime.  
While this is of course possible using the Objective-C runtime, OBJCXX makes this process much more simpler.

As an example:


    #include <OBJCXX.h>
    
    int main( void )
    {
        /* Class Foo inheriting from NSObject */
        OBJCXX::ClassBuilder cls( "Foo", "NSObject" );
        
        /* Adds properties - Getters and setters are automatically generated */
        cls.addProperty( "title",     OBJCXX::ClassBuilder::TypeObject );
        cls.addProperty( "isEnabled", OBJCXX::ClassBuilder::TypeBool );
        cls.addProperty( "index",     OBJCXX::ClassBuilder::TypeSignedInt );
        
        /* Registers the class so it can be used */
        cls.registerClass();
        
        return 0;
    }
    
The above example creates and registers a fully working Objective-C class similar to:

    @interface Foo: NSObject
    
    @property( nonatomic, readwrite, strong ) id   title;
    @property( nonatomic, readwrite, assign ) BOOL isEnabled;
    @property( nonatomic, readwrite, assign ) int  index;
    
    @end

License
-------

OBJCXX is released under the terms of the MIT license.

Repository Infos
----------------

    Owner:			Jean-David Gadina - XS-Labs
    Web:			www.xs-labs.com
    Blog:			www.noxeos.com
    Twitter:		@macmade
    GitHub:			github.com/macmade
    LinkedIn:		ch.linkedin.com/in/macmade/
    StackOverflow:	stackoverflow.com/users/182676/macmade
