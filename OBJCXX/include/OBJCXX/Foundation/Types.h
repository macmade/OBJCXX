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

#ifndef OBJCXX_FOUNDATION_TYPES_H
#define OBJCXX_FOUNDATION_TYPES_H

namespace Foundation
{
    #if defined( _WIN64 )
        typedef          long long      NSInteger;
        typedef unsigned long long      NSUInteger;
        typedef               double    CGFLoat;
    #elif defined( __LP64__ )
        typedef          long           NSInteger;
        typedef unsigned long           NSUInteger;
        typedef          double         CGFLoat;
    #else
        typedef          int            NSInteger;
        typedef unsigned int            NSUInteger;
        typedef          float          CGFLoat;
    #endif
    
    typedef struct
    {
        CGFLoat x;
        CGFLoat y;
    }
    CGPoint;
    
    typedef struct
    {
        CGFLoat width;
        CGFLoat height;
    }
    CGSize;
    
    typedef struct
    {
        CGPoint origin;
        CGSize  size;
    }
    CGRect;
    
    typedef CGPoint NSPoint;
    typedef CGSize  NSSize;
    typedef CGRect  NSRect;
}

#endif /* OBJCXX_FOUNDATION_TYPES_H */
