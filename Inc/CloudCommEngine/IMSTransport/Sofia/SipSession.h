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

#ifndef SIPSESSION_H__
#define SIPSESSION_H__

#include "SipCommon.h"
#include "Sofia.h"
#include "SipStack.h"


class SOFIA_IMS_EXPORT_FUN SipSession {
  public:
    SipSession(SipStack* stack);
    virtual ~SipSession();

    bool addHeader(const char* name, const char* value);
    bool removeHeader(const char* name);
    bool addCaps(const char* name, const char* value);
    bool addCaps(const char* name);
    bool removeCaps(const char* name);
    bool setExpires(unsigned expires);
    bool setFromUri(const char* fromUriString);
    bool setToUri(const char* toUriString);

  protected:
    const SipStack* m_pStack;
    SipE2eOperation* m_pOperation;
};

class SOFIA_IMS_EXPORT_FUN MessagingSession : public SipSession {
  public:
    MessagingSession(SipStack* pStack, nua_handle_t* nh = NULL);
    virtual ~MessagingSession();

    bool send(const char* payload);
    bool accept();
    bool reject();

  private:
};

class SOFIA_IMS_EXPORT_FUN OptionsSession : public SipSession {
  public:
    OptionsSession(SipStack* pStack, nua_handle_t* nh = NULL);
    virtual ~OptionsSession();

    bool send();
    bool accept();
    bool reject();
    bool setToUri(const char* toUriString);
};

class SOFIA_IMS_EXPORT_FUN PublicationSession : public SipSession {
  public:
    PublicationSession(SipStack* pStack, nua_handle_t* nh = NULL);
    virtual ~PublicationSession();

    bool publish(const char* payload);
    bool unPublish();
};

class SOFIA_IMS_EXPORT_FUN RegistrationSession : public SipSession {
  public:
    RegistrationSession(SipStack* pStack, nua_handle_t* nh = NULL);
    virtual ~RegistrationSession();

    bool setReqUri(const char* reqUriString);
    bool setFromUri(const char* fromUriString);
    bool setToUri(const char* toUriString);

    bool register_();
    bool unRegister();
};

class SOFIA_IMS_EXPORT_FUN SubscriptionSession : public SipSession {
  public:
    SubscriptionSession(SipStack* pStack, nua_handle_t* nh = NULL);
    virtual ~SubscriptionSession();

    bool subscribe();
    bool unSubscribe();

  private:
};

#endif