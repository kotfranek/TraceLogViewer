#include "app/SimpleApp.h"
#include "sys/AbstractThread.h"
#include "sys/StopWatch.h"
#include "net/UdpSocket.h"
#include "net/Address.h"
#include "net/Datagram.h"

#include "trace/client/UdpClientThread.h"
#include "trace/client/LogOutput.h"
#include "trace/client/FileReader.h"

#include "trace/entry/LogEntry.h"

#include <iostream>

namespace
{   
    /* Default UDP Server Port */
    const uint16_t DEFAULT_UDP_CLIENT_PORT = 55555U;
    
    /* Command open file */
    const ::std::string CMD_OPEN_FILE( "-f" );
    
    /* Command open UDP */
    const ::std::string CMD_OPEN_UDP( "-u" );  
    
    /* Application name */
    const ::std::string APP_NAME( "TraceLog Viewer" );
    
    /* Application usage */
    const ::std::string APP_USAGE( \
APP_NAME + " Usage:\n"\
+ CMD_OPEN_FILE + " <file>\t: list log file content\n"\
+ CMD_OPEN_UDP + " <server_ip> [<client_port>]\t: connect to UDP Trace Backend\n\
" );
    
    void printUsage( const ::std::string& reason = "" )
    {
        if ( !reason.empty() )
        {
            ::std::cout << reason << '\n' << ::std::endl;
        }
        ::std::cout << ::APP_USAGE << ::std::endl;
    }
}



class UdpClientApp : public ::app::SimpleApp
{
public:
    UdpClientApp()
        : ::app::SimpleApp( "UdpClient" )
    {

    }
    
private:    
    virtual int32_t onRun( const TStringVector& args )
    {       
        const size_t argCount = args.size();
        
        if ( argCount >= 3U )
        {
            const ::std::string& argSwitch = args[ 1 ];
            
            if ( argSwitch == ::CMD_OPEN_FILE )
            {
                const ::std::string& fileName = args[ 2 ];
                
                ::trace::client::FileReader fileReader;
                
                if ( fileReader.open( fileName.c_str() ) )
                {
                    ::trace::entry::LogEntry entry;
                    ::printf( "Opening file: '%s'\n", fileName.c_str() );
                    
                    int i = 0;
                    
                    while ( fileReader.readEntry( entry ) )
                    {
                        ::printf( "'%s'\n", entry.toString().c_str() );
                        ++i;
                    }
                    ::printf( "Read %d entries\n", i );
                }                
            }
            else if ( argSwitch == ::CMD_OPEN_UDP )
            {
                const ::std::string& ipAddr = args[ 2 ];
                const uint16_t port = ( 4U == argCount ) ? ::strtoul ( args[ 3 ].c_str(), NULL, 10 ) : ::DEFAULT_UDP_CLIENT_PORT;
                
                const ::net::Address serverAddress( port, ipAddr.c_str() );
               
               printf( "Connect UDP Server on %s...\n", serverAddress.toString().c_str() ); 
                
                ::trace::client::LogOutput output;
                ::trace::client::UdpClientThread client( serverAddress, output );
                
                if ( client.start() )
                {
                    ::puts( "Ctrl-C to exit...\n" );
                    
                    if ( waitForExit() )
                    {
                        ::puts( "Signal received. Wait for the Receiver-Thread to stop...\n" );
                    }

                    client.requestStop();
                    client.join();                                    
                }
            }
            else
            {
                
            }            
        }
        else
        {
            ::printUsage( "Too few arguments!" );
        }        
        
        return 0;
    }
};


int32_t main( int argc, const char * const * argv )
{
    int32_t result = ::UdpClientApp().run( argc, argv );
    
    return result;
}
