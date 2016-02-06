/*
 * Copyright (c) 2016, Przemysław Podwapiński <p.podwapinski@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Przemysław Podwapiński ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Przemysław Podwapiński BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* 
 * File:   UdpClientThread.cpp
 * Author: kret
 * 
 * Created on February 6, 2016, 11:53 AM
 */

#include "trace/client/UdpClientThread.h"
#include <iostream>

namespace
{
    /* Trace Server's port */
    const uint16_t TRACE_SRV_PORT = 55555;
    
    /* Maximum time between the Presence Signal (us) */
    const int64_t TRACE_SRV_PRESENCE_SIGNAL_TIME = 500000;    
}

namespace trace
{
namespace client
{
    
UdpClientThread::UdpClientThread( const ::std::string& ip )
    : ::sys::AbstractThread( "UdpClient" )
    , m_srvAddress( TRACE_SRV_PORT, ip )
    , m_socket()
    , m_timeStamp( 0 )
{
}


void UdpClientThread::run()
{
    if ( m_socket.open( 55557 ) )
    {
        m_socket.setTimeouts( 50U, 100U );

        ::std::cout << "Port opened" << ::std::endl;
        ::net::Datagram outMsg( m_srvAddress );
        ::net::Datagram inMsg;

        outMsg.setContent( "TRACELOG-CLIENT-HELLO" );
        m_socket.send( outMsg );

        ::sys::StopWatch sw( true );

        while ( !isStopRequested() )
        {
            if ( m_socket.receive( inMsg ) )
            {
                ::std::string auxStr;
                inMsg.toString( auxStr );
                ::std::cout << auxStr << ::std::endl;
            }

            const int64_t current = sw.elapsed();

            if ( ( current - m_timeStamp ) > TRACE_SRV_PRESENCE_SIGNAL_TIME )
            {
                m_timeStamp = current;
                outMsg.setContent( "TRACELOG-CLIENT-PRESENT" );
                m_socket.send( outMsg );
            }
        }
    }
}

}
};

