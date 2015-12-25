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

#include <OBJCXX/RT.hpp>

template<>
class XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( id object, const std::string & selector );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        id  _object;
        SEL _selector;
};

#define XS_PIMPL_CLASS OBJCXX::RT::MessageBase
#include <XS/PIMPL/Object-IMPL.hpp>

namespace OBJCXX
{
    namespace RT
    {
        Class GetClass( const std::string & name )
        {
            Class ret;
            
            if( name.length() == 0 )
            {
                throw std::runtime_error( "Empty class name" );
            }
            
            ret = objc_getClass( name.c_str() );
            
            if( ret == nullptr )
            {
                {
                    std::string msg;
                    
                    msg = "No class named '" + name + "'";
                    
                    throw std::runtime_error( msg );
                }
            }
            
            return ret;
        }
        
        Class GetClass( id object )
        {
            return object_getClass( object );
        }
        
        std::string GetClassName( Class cls )
        {
            const char * s;
            
            if( cls == nullptr )
            {
                return "";
            }
            
            s = class_getName( cls );
            
            if( s == nullptr )
            {
                return "";
            }
            
            return s;
        }
        
        SEL GetSelector( const std::string & name )
        {
            SEL ret;
            
            if( name.length() == 0 )
            {
                throw std::runtime_error( "Empty selector name" );
            }
            
            ret = sel_registerName( name.c_str() );
            
            if( ret == nullptr )
            {
                {
                    std::string msg;
                    
                    msg = "No selector named '" + name + "'";
                    
                    throw std::runtime_error( msg );
                }
            }
            
            return ret;
        }
              
        MessageBase::MessageBase( id object, const std::string & selector ):
            XS::PIMPL::Object< MessageBase >( object, selector )
        {}
        
        MessageBase::MessageBase( Class cls, const std::string & selector ):
            XS::PIMPL::Object< MessageBase >( reinterpret_cast< id >( cls ), selector )
        {}
        
        MessageBase::MessageBase( const std::string & cls, const std::string & selector ):
            MessageBase( GetClass( cls ), selector )
        {}
        
        id MessageBase::object( void )
        {
            return this->impl->_object;
        }
        
        SEL MessageBase::selector( void )
        {
            return this->impl->_selector;
        }
    }
}

XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL::IMPL( void ):
    _object( nullptr ),
    _selector( nullptr )
{}

XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL::IMPL( id object, const std::string & selector ):
    _object( object ),
    _selector( OBJCXX::RT::GetSelector( selector ) )
{}

XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL::IMPL( const IMPL & o ):
    _object( o._object ),
    _selector( o._selector )
{}

XS::PIMPL::Object< OBJCXX::RT::MessageBase >::IMPL::~IMPL( void )
{}
