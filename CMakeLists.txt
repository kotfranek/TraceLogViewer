# CMake minimum version dependency
cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

# Project name
project( "TraceLogViewer" )

# Compiler and linker flags
set( CPP_COMPILE_FLAGS "-g -Wall -std=c++11" )
set( CPP_LINK_FLAGS "-pthread" )

# Header files locations
include_directories(
    include
    "/usr/local/include/ESys"
    "/usr/local/include/TraceLog"
)

# Application: main
add_executable( tlview
    src/main.cpp
    src/trace/client/UdpClientThread.cpp 
    src/trace/client/FileReader.cpp
    src/trace/client/LogOutput.cpp
)

# Demo application: required libraries
target_link_libraries( tlview
    tl
    esys
)

# Set the compiler and linker flags for particular targets
set_target_properties( tlview PROPERTIES COMPILE_FLAGS ${CPP_COMPILE_FLAGS} )
set_target_properties( tlview PROPERTIES LINK_FLAGS ${CPP_LINK_FLAGS} )

# Target Install
install( TARGETS tlview DESTINATION bin )
