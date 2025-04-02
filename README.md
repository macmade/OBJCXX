OBJCXX
======

[![Build Status](https://img.shields.io/github/actions/workflow/status/macmade/OBJCXX/ci-mac.yaml?label=macOS&logo=apple)](https://github.com/macmade/OBJCXX/actions/workflows/ci-mac.yaml)
[![Build Status](https://img.shields.io/github/actions/workflow/status/macmade/OBJCXX/ci-win.yaml?label=Windows&logo=windows)](https://github.com/macmade/OBJCXX/actions/workflows/ci-win.yaml)
[![Issues](http://img.shields.io/github/issues/macmade/OBJCXX.svg?logo=github)](https://github.com/macmade/OBJCXX/issues)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?logo=git)
![License](https://img.shields.io/badge/license-mit-brightgreen.svg?logo=open-source-initiative)  
[![Contact](https://img.shields.io/badge/follow-@macmade-blue.svg?logo=twitter&style=social)](https://twitter.com/macmade)
[![Sponsor](https://img.shields.io/badge/sponsor-macmade-pink.svg?logo=github-sponsors&style=social)](https://github.com/sponsors/macmade)

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
    
    int main()
    {
        NS::Log( "%@", NS::String( "hello, world" ) );
        
        return 0;
    }
    
Here's a more complex example:

    #include <OBJCXX.h>
    
    int main()
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
    
    int main()
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

#### Adding custom methods

The example above only adds properties to the class, but custom methods can be added as well, and bound to C++ methods.

Imagine the following C++/Objective-C wrapper class, inheriting directly from `NS::Object`:

    class Foo: public NS::Object
    {
        public:
            
            OBJCXX_USING_BASE( Bar, Object )
            
            Foo(): Object( "Foo" )
            {}
            
            NS::String test( int x )
            {
                return std::to_string( x );
            }
    };

The Objective-C class can be created the following way:

    {
        OBJCXX::ClassBuilder cls( "Foo", "NSObject" );
        
        cls.instanceMethod< Foo, NS::String, int >( "test", &Foo::test, "" ).add< id, int >();
        cls.registerClass();
    }
    
The template parameters of `instanceMethod` are the expected C++ types, while the template parameters of `add` are the expected Objective-C type.  
This is necessary in order to convert the objects to/from C++ and Objective-C.

If the types are the same, the template parameters of `add` can be omitted, as they will be deduced automatically.

The example above will effectively add a instance method to the `Foo` class, which will be callable either from Objective-C or from C++, meaning the following:

    objc_msgSend( Foo(), "test", 42 );
    
will effectively ends up calling the C++ method implementation.

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
