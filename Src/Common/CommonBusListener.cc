/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/
#include <qcc/platform.h>

#include "Common/CommonBusListener.h"

#include <qcc/String.h>

#define QCC_MODULE "CommonBusListener"

namespace sipe2e {

namespace gateway {

CommonBusListener::CommonBusListener(ajn::BusAttachment* bus /*= NULL*/,
                                     daemonDisconnectCB dDCB /*= NULL*/,
                                     sessionJoinedCB sJCB /*= NULL*/,
                                     sessionLostCB sLCB /*= NULL*/,
                                     void* arg /*= NULL*/)
    : BusListener(), SessionPortListener(), m_SessionPort(0), m_Bus(bus),
    m_DaemonDisconnectCB(dDCB),
    m_sessionJoinedCB(sJCB),
    m_sessionLostCB(sLCB),
    m_arg(arg)
{

}

CommonBusListener::~CommonBusListener()
{

}

void CommonBusListener::setSessionPort(ajn::SessionPort sessionPort)
{
    m_SessionPort = sessionPort;
}

ajn::SessionPort CommonBusListener::getSessionPort()
{
    return m_SessionPort;
}

bool CommonBusListener::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
/*
    if (sessionPort != m_SessionPort) {
        return false;
    }
 */

    std::cout << "Accepting JoinSessionRequest" << std::endl;
    return true;
}

void CommonBusListener::SessionJoined(ajn::SessionPort sessionPort, ajn::SessionId id, const char* joiner)
{
    std::cout << "Session has been joined successfully" << std::endl;
    if (m_Bus) {
        m_Bus->SetSessionListener(id, this);
    }
//     m_SessionIds.push_back(id);
    SessionInfo sInfo;
    sInfo.id = id;
    sInfo.joiner = joiner;
    sInfo.port = sessionPort;
    m_SessionInfos.insert(std::make_pair(id, sInfo));
    if (m_sessionJoinedCB) {
        m_sessionJoinedCB(m_arg, sessionPort, id, joiner);
    }
}

void CommonBusListener::SessionLost(ajn::SessionId sessionId, SessionLostReason reason)
{
    std::cout << "Session has been lost" << std::endl;
//     std::vector<ajn::SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
//     if (it != m_SessionIds.end()) {
//         m_SessionIds.erase(it);
//     }
    if (m_sessionLostCB) {
        m_sessionLostCB(m_arg, sessionId, reason);
    }
    std::map<ajn::SessionId, SessionInfo>::iterator it = m_SessionInfos.find(sessionId);
    if (it != m_SessionInfos.end()) {
        m_SessionInfos.erase(it);
    }
}

// const std::vector<ajn::SessionId>& CommonBusListener::getSessionIds() const
// {
//     return m_SessionIds;
// }

/*
   const std::map<ajn::SessionId, qcc::String>& CommonBusListener::getSessionIdJoinerMap() const
   {
    return m_SessionInfos;
   }
 */

void CommonBusListener::BusDisconnected()
{
    std::cout << "Bus has been disconnected" << std::endl;
    if (m_DaemonDisconnectCB) {
        m_DaemonDisconnectCB(m_arg);
    }
}

qcc::String CommonBusListener::getJoinerBySessionId(ajn::SessionId id)
{
    std::map<ajn::SessionId, SessionInfo>::const_iterator it = m_SessionInfos.find(id);
    if (it != m_SessionInfos.end()) {
        return it->second.joiner;
    }
    return qcc::String("");
}

ajn::SessionPort CommonBusListener::getSessionPortBySessionId(ajn::SessionId id)
{
    std::map<ajn::SessionId, SessionInfo>::const_iterator it = m_SessionInfos.find(id);
    if (it != m_SessionInfos.end()) {
        return it->second.port;
    }
    return ajn::SESSION_PORT_ANY;
}


} // namespace gateway

} // namespace sipe2e