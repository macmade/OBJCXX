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

#include <OBJCXX/Foundation/Classes/NSRecursiveLock.hpp>

namespace Foundation
{
    NSRecursiveLock::NSRecursiveLock( void ): NSObject( "NSRecursiveLock" )
    {}
    
    void NSRecursiveLock::lock( void )
    {
        this->sendMessage< void >( "lock" );
    }
    
    void NSRecursiveLock::unlock( void )
    {
        this->sendMessage< void >( "unlock" );
    }
    
    bool NSRecursiveLock::lockBeforeDate( const NSDate & limit )
    {
        return this->sendMessage< bool, id >( "lockBeforeDate:", limit );
    }
    
    bool NSRecursiveLock::tryLock( void )
    {
        return this->sendMessage< bool >( "tryLock" );
    }
    
    NSString NSRecursiveLock::name( void )
    {
        return this->sendMessage< id >( "name" );
    }
    
    void NSRecursiveLock::setName( const NSString & name )
    {
        this->sendMessage< void, id >( "setName:", name );
    }
}
