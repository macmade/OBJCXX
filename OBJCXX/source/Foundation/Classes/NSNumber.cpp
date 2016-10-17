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

#include <OBJCXX/Foundation/Classes/NSNumber.hpp>

namespace NS
{
    Number::Number( void ): Value( "NSNumber" )
    {}
    
    Number::Number( bool value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithBool:" ).send< bool >( value );
            }
        )
    {}
    
    Number::Number( char value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithChar:" ).send< char >( value );
            }
        )
    {}
    
    Number::Number( short value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithShort:" ).send< short >( value );
            }
        )
    {}
    
    Number::Number( int value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithInt:" ).send< int >( value );
            }
        )
    {}
    
    Number::Number( long value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithLong:" ).send< long >( value );
            }
        )
    {}
    
    Number::Number( long long value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithLongLong:" ).send< long long >( value );
            }
        )
    {}
    
    Number::Number( unsigned char value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithUnsignedChar:" ).send< unsigned char >( value );
            }
        )
    {}
    
    Number::Number( unsigned short value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithUnsignedShort:" ).send< unsigned short >( value );
            }
        )
    {}
    
    Number::Number( unsigned int value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithUnsignedInt:" ).send< unsigned int >( value );
            }
        )
    {}
    
    Number::Number( unsigned long value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithUnsignedLong:" ).send< unsigned long >( value );
            }
        )
    {}
    
    Number::Number( unsigned long long value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithUnsignedLongLong:" ).send< unsigned long long >( value );
            }
        )
    {}
    
    Number::Number( float value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                /* Double - Fixes issues with variadic... */
                return this->message< id >( "initWithDouble:" ).send< double >( static_cast< double >( value ) );
            }
        )
    {}
    
    Number::Number( double value ):
        Value
        (
            "NSNumber",
            [ this, value ]
            {
                return this->message< id >( "initWithDouble:" ).send< double >( value );
            }
        )
    {}
    
    bool Number::boolValue( void )
    {
        return this->message< bool >( "boolValue" ).send();
    }
    
    char Number::charValue( void )
    {
        return this->message< char >( "charValue" ).send();
    }
    
    short Number::shortValue( void )
    {
        return this->message< short >( "shortValue" ).send();
    }
    
    int Number::intValue( void )
    {
        return this->message< int >( "intValue" ).send();
    }
    
    long Number::longValue( void )
    {
        return this->message< long >( "longValue" ).send();
    }
    
    long long Number::longLongValue( void )
    {
        return this->message< long long >( "longLongValue" ).send();
    }
    
    unsigned char Number::unsignedCharValue( void )
    {
        return this->message< unsigned char >( "unsignedCharValue" ).send();
    }
    
    unsigned short Number::unsignedShortValue( void )
    {
        return this->message< unsigned short >( "unsignedShortValue" ).send();
    }
    
    unsigned int Number::unsignedIntValue( void )
    {
        return this->message< unsigned int >( "unsignedIntValue" ).send();
    }
    
    unsigned long Number::unsignedLongValue( void )
    {
        return this->message< unsigned long >( "unsignedLongValue" ).send();
    }
    
    unsigned long long Number::unsignedLongLongValue( void )
    {
        return this->message< unsigned long long >( "unsignedLongLongValue" ).send();
    }
    
    float Number::floatValue( void )
    {
        return this->message< float >( "floatValue" ).send();
    }
    
    double Number::doubleValue( void )
    {
        return this->message< double >( "doubleValue" ).send();
    }
    
}

