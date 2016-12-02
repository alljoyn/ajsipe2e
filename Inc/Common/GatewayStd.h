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

#ifndef GATEWAYSTD_H_
#define GATEWAYSTD_H_

#include "Common/CommonBusListener.h"
#include <alljoyn/AboutListener.h>
// #include <alljoyn/about/AboutPropertyStoreImpl.h>
#include <alljoyn/AboutObj.h>


#define CHECK_RETURN(x) if ((status = x) != ER_OK) { return status; }

#define CHECK_STATUS_AND_REPLY(errorInfo) \
    if (ER_OK != status) { \
        QCC_LogError(status, (errorInfo)); \
        status = MethodReply(msg, status); \
        if (ER_OK != status) { \
            QCC_LogError(status, ("Method Reply did not complete successfully")); \
        } \
        return; \
    }

#define CHECK_STATUS_AND_LOG(errorInfo) \
    if (ER_OK != status) { \
        QCC_LogError(status, (errorInfo)); \
        return; \
    }

namespace sipe2e {

namespace gateway {

typedef struct _AllJoynContext {
    ajn::BusAttachment* bus;
    ajn::MsgArg* aboutData;
    CommonBusListener* busListener;
    ajn::AboutListener* aboutListener;
    ajn::AboutObj* aboutObj;

    _AllJoynContext() :
        bus(NULL),
        aboutData(NULL),
        busListener(NULL),
        aboutListener(NULL),
        aboutObj(NULL)
    {

    }
} AllJoynContext;

typedef struct _AnnounceContent {
    uint16_t version; // version of AboutService
    uint16_t port; // port used by the AboutService
    qcc::String busName; // unique bus name of the service
    ajn::MsgArg objectDescsArg; // map of ObjectDescriptions describing objects/interfaces
    ajn::MsgArg aboutDataArg; // map of AboutData describing properties of app/device/services
} AnnounceContent;

/*
   typedef struct _AsyncReplyContext {
    ajn::Message msg;
    ajn::InterfaceDescription::Member* member;
    _AsyncReplyContext(ajn::Message& _msg, const ajn::InterfaceDescription::Member* _member)
        : msg(_msg), member(new ajn::InterfaceDescription::Member(*_member))
    {
    }
    ~_AsyncReplyContext()
    {
        if (member) {
            delete member;
            member = NULL;
        }
    }
   } AsyncReplyContext;
 */

}

}

#endif