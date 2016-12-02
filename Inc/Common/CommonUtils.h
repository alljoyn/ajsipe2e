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

#ifndef COMMONUTILS_H_
#define COMMONUTILS_H_

#include <qcc/platform.h>

#include <qcc/String.h>
#include <qcc/XmlElement.h>

#include <alljoyn/ProxyBusObject.h>

#include "Common/GatewayConstants.h"
#include "Common/GatewayStd.h"

namespace sipe2e {

namespace gateway {

/**
 * Filling in the property store using the key/value pair
 * @param propertyStore -    the propertyStore that will be filled in
 * @param aboutKey - the key of one about data
 * @param aboutValue - the value of one about data
 */
// QStatus FillPropertyStore(ajn::services::AboutPropertyStoreImpl* propertyStore, const qcc::String& aboutKey, const qcc::String& aboutValue);

/**
 *
 * @param strPath - the relative path
 */
QStatus NormalizePath(qcc::String& strPath);

/**
 * Returns an XML string representation of this type, just exactly as ToString() does
 * @param args - input arguments
 * @param indent - number of spaces to indent the generated xml
 */
qcc::String ArgToXml(const ajn::MsgArg* args, size_t indent);
/**
 * Parse the xml string and return the result arguments array
 * @param argsStr - the result of ArgsToXml() of response argument array
 * @param args - parsed result arguments with signature 'av'
 */
QStatus XmlToArg(const qcc::XmlElement* argEle, ajn::MsgArg& arg);

void IllegalStringToObjPathString(const qcc::String& inStr, qcc::String& outStr);

void ObjPathStringToIllegalString(const qcc::String& inStr, qcc::String& outStr);

} // namespace gateway

} // namespace sipe2e

#endif