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
#include <OBJCXX/Foundation/Classes/NSException.hpp>

#if defined( __APPLE__ )

#include <pthread.h>

static pthread_key_t  exception;
static pthread_once_t once = PTHREAD_ONCE_INIT;

extern "C"
{
    static void OBJCXX_Exception_MakeKey( void );
    static void OBJCXX_Exception_MakeKey( void )
    {
        pthread_key_create( &exception, nullptr );
        pthread_setspecific( exception, nullptr );
    }
}

#elif defined( _WIN32 )

static __declspec( thread ) id exception = nullptr;

#else

static thread_local id exception = nullptr;

#endif

id OBJCXX_Exception_Preprocessor( id e )
{
    #if defined( __APPLE__ )
    
    pthread_once( &once, OBJCXX_Exception_MakeKey );
    
    OBJCXX::RT::Message< id >( static_cast< id >( pthread_getspecific( exception ) ), "release" ).send();
    pthread_setspecific( exception, OBJCXX::RT::Message< id >( e, "retain" ).send() );
    
    #else
    
    OBJCXX::RT::Message< id >( exception, "release" ).send();
    
    exception = OBJCXX::RT::Message< id >( e, "retain" ).send();
    
    #endif
    
    return e;
}

namespace OBJCXX
{
    namespace RT
    {
        id GetLastException( void )
        {
            #if defined( __APPLE__ )
            return static_cast< id >( pthread_getspecific( exception ) );
            #else
            return exception;
            #endif
        }
        
        void RethrowLastException( void )
        {
            NS::Exception e( GetLastException() );
            
            if( e != nullptr )
            {
                throw e;
            }
        }
    }
}
