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

#ifndef SIPSTACK_H__
#define SIPSTACK_H__

#include "SipCommon.h"
#include "Sofia.h"


class SOFIA_IMS_EXPORT_FUN SipStack {
  public:
    static SipStack* makeInstance(SipCallback* pCallback, const char* realm_uri, const char* impi_uri, const char* impu_uri, int local_port);
    static SipStack* getInstance();
    SipE2eContext* getContext() const;

    bool initialize();
    bool deInitialize();
    bool start();
    bool stop();
    bool isValid();

    bool setRealm(const char* realm_uri);
    bool setIMPI(const char* impi);
    bool setIMPU(const char* impu_uri);
    bool setPassword(const char* password);
    bool setProxyCSCF(const char* fqdn, unsigned short port, const char* transport, const char* ipversion);
    bool addHeader(const char* name, const char* value);

  private:
    SipStack();
    ~SipStack();

    bool g_bInitialized;
    SipE2eContext* m_pContext;
};

#endif