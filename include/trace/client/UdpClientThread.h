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
 * File:   UdpClientThread.h
 * Author: kret
 *
 * Created on February 6, 2016, 11:53 AM
 */

#ifndef UDPCLIENTTHREAD_H
#define UDPCLIENTTHREAD_H

#include "sys/AbstractThread.h"
#include "sys/StopWatch.h"
#include "net/UdpSocket.h"
#include "net/Datagram.h"

namespace trace
{
    namespace client
    {
        class UdpClientThread : public ::sys::AbstractThread
        {
        public:
            explicit UdpClientThread( const ::std::string& ip );

        private:  
            /* @see ::sys::AbstractThread */
            virtual void run();

            /* Trace Server Address */
            ::net::Address m_srvAddress;

            /* Client UDP Socket */
            ::net::UdpSocket m_socket;

            /* Client-Present signal timestamp */
            int64_t m_timeStamp;
        };        
    }
}

#endif /* UDPCLIENTTHREAD_H */
