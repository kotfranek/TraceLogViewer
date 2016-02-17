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
 * File:   TraceLogFileReader.h
 * Author: kret
 *
 * Created on February 15, 2016, 9:53 PM
 */

#ifndef TRACELOGFILEREADER_H
#define TRACELOGFILEREADER_H

#include "esys/AutoString.h"
#include "sys/AutoArray.h"
#include <fstream>

namespace trace
{
    namespace entry
    {
        class LogEntry;
    }
    
    namespace client
    {

        class FileReader 
        {
        public:
            FileReader();
            ~FileReader();
            
            /**
             * Open the log file
             * @param fileName
             * @return true on success
             */
            bool open( const ::esys::TString255& fileName );
            
            
            bool readEntry( ::trace::entry::LogEntry& output );
        private:
            /* Log File */
            ::std::ifstream m_file;
            
            /* Buffer to read the data */
            ::sys::TByteBuffer512 m_auxBuffer;
        };
    }; 

};
#endif /* TRACELOGFILEREADER_H */

