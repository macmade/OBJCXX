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

#include <OBJCXX/Foundation/Classes/NSError.hpp>

namespace NS
{
    Error::Error( void ):
        Object
        (
            "NSError",
            [ = ]
            {
                return nullptr;
            }
        )
    {}
    
    Error::Error( NS::String domain, NS::Integer code, NS::Dictionary userInfo ):
        Object
        (
            "NSError",
            [ = ]
            {
                return this->message< id >( "initWithDomain:code:userInfo:" ).send< id, NS::Integer, id >( domain, code, userInfo );
            }
        )
    {}
    
    NS::Integer Error::code( void ) const
    {
        return this->message< NS::Integer >( "code" ).send();
    }
    
    NS::String Error::domain( void ) const
    {
        return this->message< id >( "domain" ).send();
    }
    
    NS::Dictionary Error::userInfo( void ) const
    {
        return this->message< id >( "userInfo" ).send();
    }
    
    NS::String Error::localizedDescription( void ) const
    {
        return this->message< id >( "localizedDescription" ).send();
    }
    
    NS::Array Error::localizedRecoveryOptions( void ) const
    {
        return this->message< id >( "localizedRecoveryOptions" ).send();
    }
    
    NS::String Error::localizedRecoverySuggestion( void ) const
    {
        return this->message< id >( "localizedRecoverySuggestion" ).send();
    }
    
    NS::String Error::localizedFailureReason( void ) const
    {
        return this->message< id >( "localizedFailureReason" ).send();
    }
}
