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

#include <OBJCXX/MethodSignature.hpp>
#include <vector>

template<>
class XS::PIMPL::Object< OBJCXX::RT::MethodSignature >::IMPL
{
    public:
        
        IMPL( const std::string & encoding = "" );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        std::string                _encoding;
        std::string                _returnType;
        std::vector< std::string > _arguments;
};

#define XS_PIMPL_CLASS OBJCXX::RT::MethodSignature
#include <XS/PIMPL/Object-IMPL.hpp>

namespace OBJCXX
{
    namespace RT
    {
        MethodSignature::MethodSignature( const std::string & encoding ): XS::PIMPL::Object< MethodSignature >( encoding )
        {}
        
        std::string MethodSignature::GetTypeEncoding( void ) const
        {
            return this->impl->_encoding;
        }
        
        std::size_t MethodSignature::GetNumberOfArguments( void ) const
        {
            return this->impl->_arguments.size();
        }
        
        std::string MethodSignature::GetArgumentTypeAtIndex( std::size_t index ) const
        {
            if( index < this->impl->_arguments.size() )
            {
                return this->impl->_arguments[ index ];
            }
            
            throw std::runtime_error( "Invalid index " + std::to_string( index ) );
        }
        
        std::string MethodSignature::GetReturnType() const
        {
            return this->impl->_returnType;
        }
    }
}

XS::PIMPL::Object< OBJCXX::RT::MethodSignature >::IMPL::IMPL( const std::string & encoding )
{
    const char * cp;
    char         c;
    
    if( encoding.length() == 0 )
    {
        throw new std::runtime_error( "Empty type encoding" );
    }
    
    cp = encoding.c_str();
    
    while( ( c = *( cp++ ) ) )
    {
        if
        (
               c != 'v'
            && c != 'c' && c != 's' && c != 'i' && c != 'l' && c != 'q'
            && c != 'C' && c != 'S' && c != 'I' && c != 'L' && c != 'Q'
            && c != 'f' && c != 'd' && c != 'B' && c != 'v' && c != '*'
            && c != '@' && c != '#' && c != ':' && c != '^' && c != '?'
        )
        {
            if( isdigit( c ) == 0 )
            {
                throw new std::runtime_error( "Invalid type encoding" );
            }
            
            continue;
        }
        
        if( this->_returnType.length() == 0 )
        {
            this->_returnType = std::string( 1, c );
        }
        else
        {
            this->_arguments.push_back( std::string( 1, c ) );
        }

        this->_encoding = encoding;
    }
}

XS::PIMPL::Object< OBJCXX::RT::MethodSignature >::IMPL::IMPL( const IMPL & o ):
    _encoding( o._encoding ),
    _returnType( o._returnType ),
    _arguments( o._arguments )
{}

XS::PIMPL::Object< OBJCXX::RT::MethodSignature >::IMPL::~IMPL( void )
{}
