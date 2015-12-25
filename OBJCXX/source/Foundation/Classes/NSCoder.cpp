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

#include <OBJCXX/Foundation/Classes/NSCoder.hpp>

namespace NS
{
    Coder::Coder( void ): Object( "NSCoder" )
    {}
    
    bool Coder::allowsKeyedCoding( void )
    {
        return this->message< bool >( "allowsKeyedCoding:" ).Send();
    }

    bool Coder::containsValueForKey( const String & key )
    {
        return this->message< bool >( "containsValueForKey:" ).Send< id >( key );
    }
    
    void Coder::encodeArrayOfObjCType( const char * type, UInteger count, const void * array )
    {
        this->message< void >( "encodeArrayOfObjCType:count:at:" ).Send< const char *, UInteger, const void * >( type, count, array );
    }
    
    /*
    void Coder::encodeBool( bool boolv, const String & key )
    {}

    void Coder::encodeBycopyObject( id anObject )
    {}

    void Coder::encodeByrefObject( id anObject )
    {}

    void Coder::encodeBytes( const void * byteaddr, UInteger length )
    {}

    void Coder::encodeBytes( const uint8_t * bytesp, UInteger lenv, const String & key )
    {}

    void Coder::encodeConditionalObject( id object )
    {}

    void Coder::encodeConditionalObject( id objv, const String & key )
    {}

    void Coder::encodeDataObject( const Data & data )
    {}

    void Coder::encodeDouble( double realv, const String & key )
    {}

    void Coder::encodeFloat( float realv, const String & key )
    {}

    void Coder::encodeInt( int intv, const String & key )
    {}

    void Coder::encodeInteger( Integer intv, const String & key )
    {}

    void Coder::encodeInt32( int32_t intv, const String & key )
    {}

    void Coder::encodeInt64( int64_t intv, const String & key )
    {}

    void Coder::encodeNXObject( id object )
    {}

    void Coder::encodeObject( id object )
    {}

    void Coder::encodeObject( id objv, const String & key )
    {}

    void Coder::encodePoint( Point point )
    {}

    void Coder::encodePoint( Point point, const String & key )
    {}

    void Coder::encodePropertyList( id aPropertyList )
    {}

    void Coder::encodeRect( Rect rect )
    {}

    void Coder::encodeRect( Rect rect, const String & key )
    {}

    void Coder::encodeRootObject( id rootObject )
    {}

    void Coder::encodeSize( Size size )
    {}

    void Coder::encodeSize( Size size, const String & key )
    {}

    void Coder::encodeValueOfObjCType( const char * type, const void * addr )
    {}

    void Coder::encodeValuesOfObjCTypes( const char * types, ... )
    {}

    void Coder::encodeCMTime( CMTime time, const String & key )
    {}

    void Coder::encodeCMTimeRange( CMTimeRange timeRange, const String & key )
    {}

    void Coder::encodeCMTimeMapping( CMTimeMapping timeMapping, const String & key )
    {}
    
    void Coder::decodeArrayOfObjCType( const char * itemType, Integer count, void * array )
    {}

    bool Coder::decodeBoolForKey( const String & key )
    {}

    const uint8_t * Coder::decodeBytesForKey( const String & key, UInteger * lengthp )
    {}

    void * Coder::decodeBytesWithReturnedLength( UInteger * lengthp )
    {}

    Data Coder::decodeDataObject( void )
    {}

    double Coder::decodeDoubleForKey( const String & key )
    {}

    float Coder::decodeFloatForKey( const String & key )
    {}

    int Coder::decodeIntForKey( const String & key )
    {}

    Integer Coder::decodeIntegerForKey( const String & key )
    {}

    int32_t Coder::decodeInt32ForKey( const String & key )
    {}

    int64_t Coder::decodeInt64ForKey( const String & key )
    {}

    id Coder::decodeNXObject( void )
    {}

    id Coder::decodeObject( void )
    {}

    id Coder::decodeObjectForKey( const String & key )
    {}

    Point Coder::decodePoint( void )
    {}

    Point Coder::decodePointForKey( const String & key )
    {}

    Rect Coder::decodeRect( void )
    {}

    Rect Coder::decodeRectForKey( const String & key )
    {}

    Size Coder::decodeSize( void )
    {}

    Size Coder::decodeSizeForKey( const String & key )
    {}

    void Coder::decodeValueOfObjCType( const char * type, void * data )
    {}

    void Coder::decodeValuesOfObjCTypes( const char * types, ... )
    {}

    id Coder::decodeObjectOfClass( Class aClass, const String & key )
    {}

    id Coder::decodeObjectOfClasses( const Set & classes, const String & key )
    {}

    id Coder::decodePropertyListForKey( const String & key )
    {}
    
    CMTime Coder::decodeCMTimeForKey( const String & key )
    {}

    CMTimeRange Coder::decodeCMTimeRangeForKey( const String & key )
    {}

    CMTimeMapping Coder::decodeCMTimeMappingForKey( const String & key )
    {}
    
    bool Coder::requiresSecureCoding( void )
    {}

    Set Coder::allowedClasses( void )
    {}

    void Coder::setAllowedClasses( const Set & allowedClasses )
    {}

    unsigned int systemVersion( void )
    {}

    Integer Coder::versionForClassName( const String & className )
    {}

    Zone * Coder::objectZone( void )
    {}

    void Coder::setObjectZone( Zone * zone )
    {}
    */
}

