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

#include <OBJCXX/Foundation/Classes/NSAttributedString.hpp>
#include <OBJCXX/Foundation/Classes/NSString.hpp>
#include <OBJCXX/Foundation/Classes/NSDictionary.hpp>

namespace NS
{
    AttributedString::AttributedString( void ): Object( "NSAttributedString" )
    {}
    
    NS::Dictionary AttributedString::attributesAtIndex( UInteger index, Range * outRange )
    {
        return this->message< id >( "attributesAtIndex:effectiveRange:" ).send< UInteger, Range * >( index, outRange );
    }
    
    id AttributedString::attributeValueAtIndex( NS::String attributeName, UInteger index, Range * outRange )
    {
        return this->message< id >( "attribute:atIndex:effectiveRange:" ).send< id, UInteger, Range * >( attributeName, index, outRange );
    }
    
    NS::String AttributedString::string( void )
    {
        return this->message<id>( "string" ).send();
    }
    
    void AttributedString::enumerateAttributes( std::function< void( NS::Dictionary attributes, NS::Range range, bool * stop ) > callback )
    {
        if( callback == nullptr )
        {
            return;
        }
        
        NS::UInteger length = this->string().length();
        
        if( length == 0 )
        {
            return;
        }
        
        NS::Range range;
        NS::UInteger index = 0;
        bool stop = false;
        
        while( true )
        {
            NS::Dictionary attributes = this->attributesAtIndex( index, &range );
            
            callback( attributes, range, &stop );
            
            if( stop )
            {
                break;
            }
            
            if( length == 0 )
            {
                break;
            }
            
            if( range.length == 0 )
            {
                index = range.location + 1;
            }
            else
            {
                index = range.location + range.length;
            }
            
            if( index >= length - 1 )
            {
                break;
            }
        }
    }
}

