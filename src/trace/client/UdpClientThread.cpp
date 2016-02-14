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
#include "trace/client/LogOutput.h"
#include <iostream>

namespace
{
    /* Trace Server's port */
    const uint16_t TRACE_SRV_PORT = 55555;
    
    /* Maximum time between the Presence Signal (us) */
    const int64_t UDP_SERVER_HEARTBEAT_TIMEOUT = 1000000; 
    
    /* UDP Client identification */
    const ::std::string UDP_CLIENT_HANDSHAKE( "TRACELOG_UDP_CLIENT_HS" );  
    
    /* UDP Client Disconnect */
    const ::std::string UDP_CLIENT_CLOSE( "TRACELOG_UDP_CLIENT_CLOSE" );
    
    /* UDP Client Disconnect */
    const ::std::string UDP_CLIENT_ID( "TRACELOG_UDP_CLIENT_ID" );    
    
    /* UDP Server identification */
    const ::std::string UDP_SERVER_HANDSHAKE( "TRACELOG_UDP_SRV_HS" );    
    
    /* UDP Server Heartbeat signal */
    const ::std::string UDP_SERVER_HEARTBEAT( "TRACELOG_UDP_SRV_HB" );
    
    /* UDP Client Disconnect */
    const ::std::string UDP_SERVER_CLOSE( "TRACELOG_UDP_SRV_CLOSE" );       
}

namespace trace
{
namespace client
{
    
UdpClientThread::UdpClientThread( const ::net::TStringIp& ip, ::trace::client::LogOutput& output )
    : ::sys::AbstractThread( "UdpClient" )
    , m_output( output )
    , m_state( State_Disconnected )
    , m_srvAddress( TRACE_SRV_PORT, ip )
    , m_socket()
    , m_timeStamp( 0 )
    , m_entryCounter( 0U )
    , m_logDataSize( 0U )
{
}


void UdpClientThread::run()
{
    if ( m_socket.open( 55557 ) )
    {
        m_socket.setTimeouts( 50U, 500U );

        ::std::cout << "Port opened" << ::std::endl;
        ::net::Datagram outMsg( m_srvAddress );
        ::net::Datagram inMsg;

        ::sys::StopWatch heartBeatTimer;

        while ( !isStopRequested() )
        {
            switch ( m_state )
            {
                case State_Disconnected:
                {
                    outMsg.setContent( ::UDP_CLIENT_HANDSHAKE );
                    m_socket.send( outMsg ); 
                    
                    m_state = State_Waiting;
                }
                break;
                
                case State_Waiting:
                {
                    m_state = State_Disconnected;
                    
                    if ( m_socket.receive( inMsg ) )
                    {
                        ::std::string auxStr;
                        inMsg.toString( auxStr );

                        if ( 0 == auxStr.find( ::UDP_SERVER_HANDSHAKE ) )
                        {
                            ::std::cout << "RCV: HANDSHAKE" << ::std::endl;
                            outMsg.setContent( ::UDP_CLIENT_ID + ":Test_v0.1" );
                            m_socket.send( outMsg ); 
                            heartBeatTimer.start();
                            m_state = State_Connected;
                        }                            
                    }
                }
                break;
                
                case State_Connected:
                {
                    if ( m_socket.receive( inMsg ) )
                    {
                        ::std::string auxStr;
                        inMsg.toString( auxStr );
                        
                        if ( 0 == auxStr.compare( ::UDP_SERVER_HEARTBEAT ) )
                        {
                            ::std::cout << "RCV: HB" << ::std::endl;
                            heartBeatTimer.reStart();
                        }
                        else if ( 0 == auxStr.compare( ::UDP_SERVER_CLOSE ) )
                        {
                            ::std::cout << "RCV: CLOSE" << ::std::endl;
                            heartBeatTimer.stop();
                            m_state = State_Disconnected;
                            sessionClose( false );
                        }
                        else
                        {
                            ++m_entryCounter;
                            m_logDataSize += auxStr.size();
                            
                            m_output.write( auxStr );
                        }
                    }  
                    else
                    {
                        if( heartBeatTimer.elapsed( ::UDP_SERVER_HEARTBEAT_TIMEOUT ) )
                        {
                            ::std::cout << "RCV: TIMEOUT DISCONNECT" << ::std::endl;
                            heartBeatTimer.stop();
                            m_state = State_Disconnected;
                            sessionClose( true );
                        }
                    }
                }
                break;
            }            
        }
    }
}


void UdpClientThread::sessionClose( const bool timeout )
{
    ::std::cout << "Session closed" << ::std::endl; 
    ::std::cout << "- reason: \t" << ( timeout ? "Server timeout" : "Server requested stop" ) << ::std::endl; 
    ::std::cout << "- entries:\t" << m_entryCounter << ::std::endl;
    ::std::cout << "- overall:\t" << m_logDataSize / 1024U << " kb" << ::std::endl;
    m_entryCounter = 0U;
    m_logDataSize = 0U;
}

}
};

