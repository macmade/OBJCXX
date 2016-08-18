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
        return this->message< bool >( "allowsKeyedCoding:" ).send();
    }

    bool Coder::containsValueForKey( const String & key )
    {
        return this->message< bool >( "containsValueForKey:" ).send< id >( key );
    }
    
    void Coder::encodeArrayOfObjCType( const char * type, UInteger count, const void * array )
    {
        this->message< void >( "encodeArrayOfObjCType:count:at:" ).send< const char *, UInteger, const void * >( type, count, array );
    }
    
    void Coder::encodeBool( bool boolv, const String & key )
    {
        this->message< void >( "encodeBool:forKey:" ).send< bool, id >( boolv, key );
    }

    void Coder::encodeBycopyObject( id anObject )
    {
        this->message< void >( "encodeBycopyObject:" ).send< id >( anObject );
    }

    void Coder::encodeByrefObject( id anObject )
    {
        this->message< void >( "encodeByrefObject:" ).send< id >( anObject );
    }

    void Coder::encodeBytes( const void * byteaddr, UInteger length )
    {
        this->message< void >( "encodeBytes:length:" ).send< const void *, UInteger >( byteaddr, length );
    }

    void Coder::encodeBytes( const uint8_t * bytesp, UInteger lenv, const String & key )
    {
        this->message< void >( "encodeBytes:length:forKey:" ).send< const uint8_t *, UInteger, id >( bytesp, lenv, key );
    }

    void Coder::encodeConditionalObject( id object )
    {
        this->message< void >( "encodeConditionalObject:" ).send< id >( object );
    }

    void Coder::encodeConditionalObject( id objv, const String & key )
    {
        this->message< void >( "encodeConditionalObject:forKey:" ).send< id, id >( objv, key );
    }

    void Coder::encodeDataObject( const Data & data )
    {
        this->message< void >( "encodeDataObject:" ).send< id >( data );
    }

    void Coder::encodeDouble( double realv, const String & key )
    {
        this->message< void >( "encodeDouble:forKey:" ).send< double, id >( realv, key );
    }

    void Coder::encodeFloat( float realv, const String & key )
    {
        this->message< void >( "encodeFloat:forKey:" ).send< double, id >( static_cast< double >( realv ), key );
    }

    void Coder::encodeInt( int intv, const String & key )
    {
        this->message< void >( "encodeInt:forKey:" ).send< int, id >( intv, key );
    }

    void Coder::encodeInteger( Integer intv, const String & key )
    {
        this->message< void >( "encodeInteger:forKey:" ).send< Integer, id >( intv, key );
    }

    void Coder::encodeInt32( int32_t intv, const String & key )
    {
        this->message< void >( "encodeInt32:forKey:" ).send< int32_t, id >( intv, key );
    }

    void Coder::encodeInt64( int64_t intv, const String & key )
    {
        this->message< void >( "encodeInt64:forKey:" ).send< int64_t, id >( intv, key );
    }

    void Coder::encodeNXObject( id object )
    {
        this->message< void >( "encodeNXObject:" ).send< id >( object );
    }

    void Coder::encodeObject( id object )
    {
        this->message< void >( "encodeObject:" ).send< id >( object );
    }

    void Coder::encodeObject( id object, const String & key )
    {
        this->message< void >( "encodeObject:forKey:" ).send< id, id >( object, key );
    }

    void Coder::encodePropertyList( id plist )
    {
        this->message< void >( "encodePropertyList:" ).send< id >( plist );
    }

    void Coder::encodeRootObject( id rootObject )
    {
        this->message< void >( "encodeRootObject:" ).send< id >( rootObject );
    }
    
    /*
    void Coder::encodePoint( Point point )
    {
        this->message< void >( "encodePoint:" ).send< Point >( point );
    }

    void Coder::encodePoint( Point point, const String & key )
    {
        this->message< void >( "encodePoint:forKey:" ).send< Point, id >( point, key );
    }

    void Coder::encodeRect( Rect rect )
    {
        this->message< void >( "encodeRect:" ).send< Rect >( rect );
    }

    void Coder::encodeRect( Rect rect, const String & key )
    {
        this->message< void >( "encodeRect:forKey:" ).send< Rect, id >( rect, key );
    }

    void Coder::encodeSize( Size size )
    {
        this->message< void >( "encodeSize:" ).send< Size >( size );
    }

    void Coder::encodeSize( Size size, const String & key )
    {
        this->message< void >( "encodeSize:forKey:" ).send< Size, id >( size, key );
    }
    */
    
    /*
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
    */
    
    bool Coder::decodeBoolForKey( const String & key )
    {
        return this->message< bool >( "decodeBoolForKey:" ).send< id >( key );
    }

    const uint8_t * Coder::decodeBytesForKey( const String & key, UInteger * lengthp )
    {
        return this->message< const uint8_t * >( "decodeBytesForKey:returnedLength:" ).send< id, UInteger * >( key, lengthp );
    }

    void * Coder::decodeBytesWithReturnedLength( UInteger * lengthp )
    {
        return this->message< void * >( "decodeBytesWithReturnedLength:" ).send< UInteger * >( lengthp );
    }

    Data Coder::decodeDataObject( void )
    {
        return this->message< id >( "decodeDataObject:" ).send();
    }

    double Coder::decodeDoubleForKey( const String & key )
    {
        return this->message< double >( "decodeDoubleForKey:" ).send< id >( key );
    }

    float Coder::decodeFloatForKey( const String & key )
    {
        return this->message< float >( "decodeFloatForKey:" ).send< id >( key );
    }

    int Coder::decodeIntForKey( const String & key )
    {
        return this->message< int >( "decodeIntForKey:" ).send< id >( key );
    }

    Integer Coder::decodeIntegerForKey( const String & key )
    {
        return this->message< Integer >( "decodeIntegerForKey:" ).send< id >( key );
    }

    int32_t Coder::decodeInt32ForKey( const String & key )
    {
        return this->message< int32_t >( "decodeInt32ForKey:" ).send< id >( key );
    }

    int64_t Coder::decodeInt64ForKey( const String & key )
    {
        return this->message< int64_t >( "decodeInt64ForKey:" ).send< id >( key );
    }

    id Coder::decodeNXObject( void )
    {
        return this->message< id >( "decodeNXObject" ).send();
    }

    id Coder::decodeObject( void )
    {
        return this->message< id >( "decodeObject" ).send();
    }

    id Coder::decodeObjectForKey( const String & key )
    {
        return this->message< id >( "decodeObjectForKey:" ).send< id >( key );
    }

    id Coder::decodePropertyListForKey( const String & key )
    {
        return this->message< id >( "decodePropertyListForKey:" ).send< id >( key );
    }
    
    /*
    Point Coder::decodePoint( void )
    {
        return this->message< Point >( "decodePoint" ).send();
    }

    Point Coder::decodePointForKey( const String & key )
    {
        return this->message< Point >( "decodePointForKey:" ).send< id >( key );
    }

    Rect Coder::decodeRect( void )
    {
        return this->message< Rect >( "decodeRect" ).send();
    }

    Rect Coder::decodeRectForKey( const String & key )
    {
        return this->message< Rect >( "decodeRectForKey:" ).send< id >( key );
    }

    Size Coder::decodeSize( void )
    {
        return this->message< Size >( "decodeSize" ).send();
    }

    Size Coder::decodeSizeForKey( const String & key )
    {
        return this->message< Size >( "decodeSizeForKey:" ).send< id >( key );
    }
    */
    
    /*
    void Coder::decodeArrayOfObjCType( const char * itemType, Integer count, void * array )
    {}
    
    void Coder::decodeValueOfObjCType( const char * type, void * data )
    {}

    void Coder::decodeValuesOfObjCTypes( const char * types, ... )
    {}

    id Coder::decodeObjectOfClass( Class aClass, const String & key )
    {}

    id Coder::decodeObjectOfClasses( const Set & classes, const String & key )
    {}
    
    CMTime Coder::decodeCMTimeForKey( const String & key )
    {}

    CMTimeRange Coder::decodeCMTimeRangeForKey( const String & key )
    {}

    CMTimeMapping Coder::decodeCMTimeMappingForKey( const String & key )
    {}
    */
    
    bool Coder::requiresSecureCoding( void )
    {
        return this->message< bool >( "requiresSecureCoding" ).send();
    }

    Set Coder::allowedClasses( void )
    {
        return this->message< id >( "allowedClasses" ).send();
    }

    void Coder::setAllowedClasses( const Set & allowedClasses )
    {
        this->message< void >( "setAllowedClasses:" ).send< id >( allowedClasses );
    }

    unsigned int Coder::systemVersion( void )
    {
        return this->message< unsigned int >( "systemVersion" ).send();
    }

    Integer Coder::versionForClassName( const String & className )
    {
        return this->message< Integer >( "versionForClassName" ).send< id >( className );
    }

    Zone * Coder::objectZone( void )
    {
        return this->message< Zone * >( "objectZone" ).send();
    }

    void Coder::setObjectZone( Zone * zone )
    {
        this->message< void >( "setObjectZone:" ).send< Zone * >( zone );
    }
}

