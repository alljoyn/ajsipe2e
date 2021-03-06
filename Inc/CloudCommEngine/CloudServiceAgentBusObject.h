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
#ifndef CLOUDSERVICEAGENTBUSOBJECT_H_
#define CLOUDSERVICEAGENTBUSOBJECT_H_

#include <qcc/platform.h>

#include <qcc/XmlElement.h>

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/SessionListener.h>

#include "Common/GatewayConstants.h"
#include "Common/GatewayStd.h"
#include "CloudCommEngine/CloudCommEngineBusObject.h"

namespace sipe2e {
namespace gateway {
/**
 * CloudServiceAgentBusObject class
 * This is the Agent BusObject exposing services/interfaces on behalf of cloud services
 * Every Agent BusObject is created while subscribing a remote service (either cloud service
 * or service provided by devices in other proximal networks).
 * Every Agent BusObject is on its specific BusAttachment which is different from the one
 * of CloudCommEngineBusObject instance.
 */
class CloudServiceAgentBusObject : public ajn::BusObject {
    friend class CloudCommEngineBusObject;
    friend class CloudCommEngineBusObject::CloudMethodCallRunable;
    friend class CloudServiceAgentAboutData;

  public:
    CloudServiceAgentBusObject(
        const qcc::String& objectPath,
        const qcc::String& remoteAccount,
        const qcc::String& remoteBusName,
        CloudCommEngineBusObject* owner);
    virtual ~CloudServiceAgentBusObject();

    /**
     * Common method handler for all methods of cloud service
     * @param member - the member (method) of the interface that was executed
     * @param msg - the Message of the method
     */
    void CommonMethodHandler(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /**
     *    Parse the introspection XML string and create/activate/add interfaces included to this BusObject
     * Meantime add method handler for all methods
     * @param xml - the introspection XML string describing the interfaces and children interfaces
     * @param propertyStore - fill in the propertyStore based on the about data in the XML
     */
    QStatus ParseXml(const char* xml, ajn::BusAttachment* proxyBus);

    /**
     * Compare with specified introspection XML string, if equal, return true, otherwise false
     * @param serviceIntrospectionXml - the service introspection XML string
     * @param isTopLevel - if the AgentBusObject is the top-level parent BusObject or not
     */
    bool Compare(const qcc::String& serviceIntrospectionXml);

    /**
     * Compare with specified introspection Node XmlElemnt, if equal, return true, otherwise false
     * @param nodeElement - the XmlElemnt node, some child node of service or other node
     */
    bool Compare(const qcc::XmlElement* nodeElement);

    /**
     * Prepare the agent AllJoyn executing environment, including BusAttachment, AboutService
     * @param _bus - the BusAttachment that the Agent BusObject is registers on. if it's NULL,
     *                           then
     */
    QStatus PrepareAgent(AllJoynContext* _context, const qcc::String& serviceIntrospectionXml);

    QStatus RegisterAgent();

    /**
     * Announce the BusObject and all its children
     */
    QStatus Announce();

    /**
     * Clean up the AllJoyn execution context
     * @param topLevel - true indicates that this object is top level parent
     */
    QStatus Cleanup(bool topLevel = true);

    /**
     * Session Listeners' callbacks
     */
    static void LocalSessionJoined(void* arg, ajn::SessionPort sessionPort, ajn::SessionId id, const char* joiner);
    static void LocalSessionLost(void* arg, ajn::SessionId sessionId, ajn::SessionListener::SessionLostReason reason);

  protected:
    /**
     * Override the virtual method from its parent ProxyBusObject to handle all signals' Get
     *
     */
    virtual void GetProp(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    /**
     * Override the virtual method from its parent ProxyBusObject to handle all signals' Set
     *
     */
    virtual void SetProp(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    virtual void GetAllProps(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

  private:
    /**
     * @internal
     *    Parse the node in the introspection XML and create/activate/add interfaces included to this BusObject
     * Meantime add method handler for all methods
     * @param root - the node xml root element of the introspection XML string
     * @param bus - the BusAttachment that the agent BusObject will be registered in
     */
    QStatus ParseNode(const qcc::XmlElement* root, ajn::BusAttachment* proxyBus);

    /**
     * @internal
     *    Parse a single interface in the introspection XML and create/activate/add interfaces included to this BusObject
     * Meantime add method handler for all methods
     * @param root - the interface root element of the introspection XML string
     * @param bus - the BusAttachment that the agent BusObject will be registered in
     */
    QStatus ParseInterface(const qcc::XmlElement* root, ajn::BusAttachment* proxyBus);

  protected:
    class CloudServiceAgentAboutData : public ajn::AboutDataListener {
      public:
        CloudServiceAgentAboutData(CloudServiceAgentBusObject* _owner);
        virtual QStatus GetAboutData(ajn::MsgArg* msgArg, const char* language);
        virtual QStatus GetAnnouncedAboutData(ajn::MsgArg* msgArg);

      private:
        CloudServiceAgentBusObject* owner;
    } aboutDataHandler;

  protected:
    /* The AllJoyn execution environment */
    AllJoynContext context;
    /* The session port */
    ajn::SessionPort sp;
    /* The remote account address and remote BusName */
    qcc::String remoteAccount, remoteBusName;
    /* The supported interfaces' names */
    std::vector<qcc::String> interfaces;
    /* All the children BusObjects */
    std::vector<CloudServiceAgentBusObject*> children;
    /* The parent BusObject that owns this agent */
    CloudCommEngineBusObject* ownerBusObject;
};

} // namespace gateway
} // namespace sipe2e

#endif // CLOUDSERVICEAGENTBUSOBJECT_H_