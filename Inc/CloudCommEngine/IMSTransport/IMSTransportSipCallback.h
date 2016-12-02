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

#ifndef IMSTRANSPORTSIPCALLBACK_H_
#define IMSTRANSPORTSIPCALLBACK_H_

#include "CloudCommEngine/IMSTransport/Sofia/SipCallback.h"

namespace sipe2e {
namespace gateway {

class IMSTransportSipCallback : public SipCallback {
  public:
    IMSTransportSipCallback();
    virtual ~IMSTransportSipCallback(void);

    virtual int OnDialogEvent(const DialogEvent* e);
    virtual int OnStackEvent(const StackEvent* e);

    virtual int OnRegistrationEvent(const RegistrationEvent* e);

    virtual int OnOptionsEvent(const OptionsEvent* e);

    virtual int OnMessagingEvent(const MessagingEvent* e);
    /**
     * Callback while receiving NOTIFY
     * @param e - the subscription event
     */
    virtual int OnSubscriptionEvent(const SubscriptionEvent* e);

    virtual int OnPublicationEvent(const PublicationEvent* e);

};

} // namespace gateway
} // namespace sipe2e

#endif // IMSTRANSPORTSIPCALLBACK_H_