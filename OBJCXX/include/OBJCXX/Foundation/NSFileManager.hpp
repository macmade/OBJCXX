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

#ifndef OBJCXX_FOUNDATION_NS_FILE_MANAGER_H
#define OBJCXX_FOUNDATION_NS_FILE_MANAGER_H

#include <OBJCXX/Foundation/NSObject.hpp>
#include <OBJCXX/Foundation/NSString.hpp>
#include <OBJCXX/Foundation/NSData.hpp>
#include <OBJCXX/Foundation/NSError.hpp>
#include <OBJCXX/Foundation/NSDictionary.hpp>

namespace Foundation
{
    class NSFileManager: public NSObject
    {
        public:
            
            using NSObject::NSObject;
            
            static NSFileManager defaultManager( void );
            
            NSFileManager( void );
            
            bool         createFileAtPath( const NSString & path, const NSData & contents, const NSDictionary & attributes ) const;
            NSDictionary attributesOfItemAtPath( const NSString & path, NSError & error ) const;
    };
}

#endif /* OBJCXX_FOUNDATION_NS_FILE_MANAGER_H */
