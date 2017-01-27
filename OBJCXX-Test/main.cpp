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

static bool IMP_Foo_supportsSecureCoding( Class cls, SEL _cmd );
static id   IMP_Foo_initWithCoder( id self, SEL _cmd, id coder );
static void IMP_Foo_encodeWithCoder( id self, SEL _cmd, id coder );

class Foo: public NS::Object
{
    public:
    
        OBJCXX_USING_BASE( Foo, Object )
    
        Foo( void );
    
        NS::String text( void );
        void       text( const NS::String & text );
};

int main( void )
{
    OBJCXX::RT::Init();
    
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
        
        {
            NS::String s1( "hello, world" );
            NS::String s2;
            NS::Data   d;

            NS::Log( "Original string: %@", static_cast< id >( s1 ) );

            d = NS::KeyedArchiver::archivedDataWithRootObject( s1 );

            NS::Log( "Archived data: %@", static_cast< id >( d ) );

            s2 = NS::KeyedUnarchiver::unarchiveObjectWithData( d );

            NS::Log( "Unarchived string: %@", static_cast< id >( s2 ) );
        }

        {
            OBJCXX::ClassBuilder cls( "Foo", "NSObject" );
    
            cls.addProtocol( "NSSecureCoding" );
    
            cls.addInstanceMethod( "initWithCoder:", reinterpret_cast< IMP >( IMP_Foo_initWithCoder ), "@24@0:8@16" );
            cls.addInstanceMethod( "encodeWithCoder:", reinterpret_cast< IMP >( IMP_Foo_encodeWithCoder ), "v24@0:8@16" );
            cls.addProperty( "text", OBJCXX::ClassBuilder::TypeObject );
            cls.registerClass();
            cls.addClassMethod( "supportsSecureCoding", reinterpret_cast< IMP >( IMP_Foo_supportsSecureCoding ), "c16@0:8" );
    
            {
                Foo      f1;
                Foo      f2;
                NS::Data d;
        
                NS::Log( "%@", static_cast< id >( f1.text() ) );
                f1.text( "hello, universe" );
                NS::Log( "%@", static_cast< id >( f1.text() ) );
        
                d = NS::KeyedArchiver::archivedDataWithRootObject( f1 );
        
                NS::Log( "%@", static_cast< id >( d ) );
        
                f2 = NS::KeyedUnarchiver::unarchiveObjectWithData( d );
        
                NS::Log( "%@", static_cast< id >( f2.text() ) );
            }
        }
        
        {
            try
            {
                NS::Exception e( "foo", "bar", nullptr );
            
                e.raise();
            }
            catch( const NS::Exception & e )
            {
                std::cout << "Caught Objective-C exception:"
                          << std::endl
                          << "    - Name:   "
                          << e.name().UTF8String()
                          << std::endl
                          << "    - Reason: "
                          << e.reason().UTF8String()
                          << std::endl;
            }
        }
        
        #ifdef _WIN32
        getchar();
        #endif
    }
    
    return 0;
}

Foo::Foo( void ): Object( "Foo" )
{}

NS::String Foo::text( void )
{
    return this->message< id >( "text" ).send();
}

void Foo::text( const NS::String & text )
{
    this->message< void >( "setText:" ).send< id >( text );
}

static bool IMP_Foo_supportsSecureCoding( Class cls, SEL _cmd )
{
    ( void )cls;
    ( void )_cmd;

    return true;
}

static id IMP_Foo_initWithCoder( id self, SEL _cmd, id coder )
{
    Foo       foo( self );
    NS::Coder archiver( coder );

    ( void )_cmd;

    foo = foo.message< id >( "init" ).send();

    foo.text( archiver.decodeObjectForKey( "text" ) );

    return foo;
}

static void IMP_Foo_encodeWithCoder( id self, SEL _cmd, id coder )
{
    Foo       foo( self );
    NS::Coder archiver( coder );

    ( void )_cmd;

    archiver.encodeObject( foo.text(), "text" );
}
