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

#include <OBJCXX/Foundation/Classes/NSTask.hpp>

namespace NS
{
    Task::Task(): Object( "NSTask" )
    {}
    
    NS::String Task::launchPath() const
    {
        return this->message< id >( "launchPath" ).send();
    }
    
    NS::Array Task::arguments() const
    {
        return this->message< id >( "arguments" ).send();
    }
    
    void Task::setLaunchPath( const NS::String & value )
    {
        this->message< void >( "setLaunchPath:" ).send< id >( value );
    }
    
    void Task::setArguments( const NS::Array & value )
    {
        this->message< void >( "setArguments:" ).send< id >( value );
    }
    
    void Task::launch() const
    {
        this->message< void >( "launch" ).send();
    }
    
    void Task::waitUntilExit() const
    {
        this->message< void >( "waitUntilExit" ).send();
    }
}

