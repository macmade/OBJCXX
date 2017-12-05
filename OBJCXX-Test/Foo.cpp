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
#include "Foo.hpp"

static bool IMP_Foo_supportsSecureCoding( Class cls, SEL _cmd );
static id   IMP_Foo_initWithCoder( id self, SEL _cmd, id coder );
static void IMP_Foo_encodeWithCoder( id self, SEL _cmd, id coder );

void Foo::test( void )
{
    static std::once_flag once;
    
    std::call_once
    (
        once,
        []( void )
        {
            OBJCXX::ClassBuilder cls( "Foo", "NSObject" );
            
            cls.addProtocol( "NSSecureCoding" );
            
            cls.addInstanceMethod( "initWithCoder:", reinterpret_cast< IMP >( IMP_Foo_initWithCoder ), OBJCXX::RT::SignatureForMethod< id, id >().GetTypeEncoding() );
            cls.addInstanceMethod( "encodeWithCoder:", reinterpret_cast< IMP >( IMP_Foo_encodeWithCoder ), OBJCXX::RT::SignatureForMethod< void, id >().GetTypeEncoding() );
            cls.addProperty( "text", OBJCXX::ClassBuilder::TypeObject );
            cls.registerClass();
            cls.addClassMethod( "supportsSecureCoding", reinterpret_cast< IMP >( IMP_Foo_supportsSecureCoding ), OBJCXX::RT::SignatureForMethod< bool >().GetTypeEncoding() );
        }
    );
    
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
