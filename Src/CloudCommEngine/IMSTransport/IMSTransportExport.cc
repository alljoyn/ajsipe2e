/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/
#include <qcc/platform.h>

#include "CloudCommEngine/IMSTransport/IMSTransportSipCallback.h"
#include "CloudCommEngine/IMSTransport/IMSTransport.h"
#include "CloudCommEngine/IMSTransport/IMSTransportExport.h"

#include "CloudCommEngine/IMSTransport/pidf.h"

using namespace sipe2e;
using namespace gateway;

int SIPE2E_GATEWAY_CALL ITInitialize()
{
    return IMSTransport::GetInstance()->Init();
}

int SIPE2E_GATEWAY_CALL ITShutdown()
{
    return IMSTransport::DeleteInstance();
}

int SIPE2E_GATEWAY_CALL ITGetStatus()
{
    return IMSTransport::GetInstance()->GetStatus();
}

int SIPE2E_GATEWAY_CALL ITSubscribe(const char* remoteAccount)
{
    return IMSTransport::GetInstance()->Subscribe(remoteAccount);
}

int SIPE2E_GATEWAY_CALL ITUnsubscribe(const char* remoteAccount)
{
    return IMSTransport::GetInstance()->Unsubscribe(remoteAccount);
}

int SIPE2E_GATEWAY_CALL ITPublishService(const char* introspectionXml)
{
    return IMSTransport::GetInstance()->PublishService(introspectionXml);
}

int SIPE2E_GATEWAY_CALL ITDeleteService(const char* introspectionXml)
{
    return IMSTransport::GetInstance()->DeleteService(introspectionXml);
}

int SIPE2E_GATEWAY_CALL ITReadServiceNotification(char** msgBuf)
{
    return IMSTransport::GetInstance()->ReadServiceNotification(msgBuf);
}

int SIPE2E_GATEWAY_CALL ITReadCloudMessage(char** msgBuf)
{
    return IMSTransport::GetInstance()->ReadCloudMessage(msgBuf);
}

SIPE2E_GATEWAY_EXTERN void SIPE2E_GATEWAY_CALL ITStopReadServiceNotification()
{
    IMSTransport::GetInstance()->StopReadServiceNotification();
}

SIPE2E_GATEWAY_EXTERN void SIPE2E_GATEWAY_CALL ITStopReadCloudMessage()
{
    IMSTransport::GetInstance()->StopReadCloudMessage();
}

int SIPE2E_GATEWAY_CALL ITSendCloudMessage(
    int msgType,
    const char* peer,
    const char* callId,
    const char* addr,
    const char* msgBuf,
    char** resMsgBuf)
{
    return IMSTransport::GetInstance()->SendCloudMessage(msgType, peer, callId, addr, msgBuf, resMsgBuf);
}

void SIPE2E_GATEWAY_CALL ITReleaseBuf(char* buf)
{
    if (buf) {
        delete[] buf;
    }
}