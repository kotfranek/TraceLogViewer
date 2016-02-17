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
 * File:   TraceLogFileReader.cpp
 * Author: kret
 * 
 * Created on February 15, 2016, 9:53 PM
 */

#include "trace/client/FileReader.h"
#include "trace/entry/LogEntry.h"

namespace
{
    /* File open mode: R/O + BIN */
    const ::std::ios_base::openmode OPEN_MODE = ::std::ios_base::in | ::std::ios_base::binary;
}

namespace trace
{
namespace client
{
FileReader::FileReader() 
    : m_file()
    , m_auxBuffer()
{
}


bool FileReader::open( const ::esys::TString255& fileName )
{
    bool result = false;
    
    m_file.open( fileName.c_str(), ::OPEN_MODE );
    
    if ( m_file.is_open() )
    {
        char buf[ 5 ];
        m_file.read( buf, 4 );
        buf[ 4 ] = '\0';
        
        printf( "%s\n", buf );
        
        return result = m_file.good();
    }
    
    return result;
}


bool FileReader::readEntry( ::trace::entry::LogEntry& output )
{
    return output.exposeData().deserialize( m_file );
}


FileReader::~FileReader() 
{
    m_file.close();
}

}
}

