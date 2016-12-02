/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef IMSTRANSPORTEXPORT_H_
#define IMSTRANSPORTEXPORT_H_

#include <Common/GatewayExport.h>


#ifdef __cplusplus
extern "C"
{
#endif
SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITInitialize();
SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITShutdown();

SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITGetStatus();

SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITSubscribe(const char* remoteAccount);

SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITUnsubscribe(const char* remoteAccount);

SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITPublishService(const char* introspectionXml);

SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITDeleteService(const char* introspectionXml);

SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITReadServiceNotification(char** msgBuf);

SIPE2E_GATEWAY_EXTERN void SIPE2E_GATEWAY_CALL ITStopReadServiceNotification();

SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITReadCloudMessage(char** msgBuf);

SIPE2E_GATEWAY_EXTERN void SIPE2E_GATEWAY_CALL ITStopReadCloudMessage();

SIPE2E_GATEWAY_EXTERN int SIPE2E_GATEWAY_CALL ITSendCloudMessage(
    int msgType,
    const char* peer,
    const char* callId,
    const char* addr,
    const char* msgBuf,
    char** resMsgBuf);

SIPE2E_GATEWAY_EXTERN void SIPE2E_GATEWAY_CALL ITReleaseBuf(char* buf);
#ifdef __cplusplus
}
#endif

#endif // IMSTRANSPORTEXPORT_H_