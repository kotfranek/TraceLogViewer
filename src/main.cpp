#include "app/SimpleApp.h"
#include "sys/AbstractThread.h"
#include "sys/StopWatch.h"
#include "net/UdpSocket.h"
#include "net/Datagram.h"

#include "trace/client/UdpClientThread.h"
#include "trace/client/LogOutput.h"

#include <iostream>

namespace
{   

}



class UdpClientApp : public ::app::SimpleApp
{
public:
    UdpClientApp()
        : ::app::SimpleApp( "UdpClientApp" )
    {

    }
    
private:    
    virtual int32_t onRun( const TStringVector& args )
    {       
        if ( args.size() == 2U )
        {
            ::trace::client::LogOutput output;
            ::trace::client::UdpClientThread client( args[ 1 ], output );
            client.start();
            
            waitForSignal();
            
            ::std::cout << "Signal received. Wait for the Receiver Thread..." << ::std::endl;
            
            client.requestStop();
            client.join();
        }
        else
        {
            ::std::cerr << "Missing Trace Server IP Address, eg. 127.0.0.1" << ::std::endl;
        }        
        
        return 0;
    }
};


int32_t main( int argc, const char * const * argv )
{
    int32_t result = ::UdpClientApp().run( argc, argv );
    
    return result;
}
