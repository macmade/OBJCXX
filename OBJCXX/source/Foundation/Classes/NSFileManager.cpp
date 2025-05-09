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

#include <OBJCXX/Foundation/Classes/NSFileManager.hpp>
#include <OBJCXX/RT.hpp>

namespace NS
{
    FileManager FileManager::defaultManager()
    {
        id o;
        
        o = OBJCXX::RT::Message< id >( "NSFileManager", "defaultManager" ).send();
        
        return FileManager( o );
    }
    
    FileManager::FileManager(): Object( "NSFileManager" )
    {}
    
    bool FileManager::createFileAtPath( const String & path, const Data & contents, const Dictionary & attributes ) const
    {
        return this->message< bool >( "createFileAtPath:contents:attributes:" ).send< id, id, id >( path, contents, attributes );
    }
    
    Dictionary FileManager::attributesOfItemAtPath( const String & path, Error & error ) const
    {
        id e{};
        id d{};
        
        d     = this->message< id >( "attributesOfItemAtPath:error:" ).send< id, id * >( path, &e );
        error = e;
        
        return d;
    }
}
