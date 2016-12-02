# # 
#    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
#    Source Project Contributors and others.
#    
#    All rights reserved. This program and the accompanying materials are
#    made available under the terms of the Apache License, Version 2.0
#    which accompanies this distribution, and is available at
#    http://www.apache.org/licenses/LICENSE-2.0

# 

# This python file contains all the utility functions used by SConstruct and SConscript.

import os

def enum(**enums):
    return type('Enum', (), enums)

EventLevel = enum(error = 'ERROR', 
                  warning = 'WARNING', 
                  info = 'INFO', 
                  verbose = 'VERBOSE')
                  
utilityName = 'Utility'
    
def PrintOneLineLog(eventLevel, sconComponent, logStr):
    print '[' + eventLevel + ']', sconComponent + ':', logStr

def GetDefaultPathFromEnvironVar(component, envName):
    defaultPath = os.environ.get(envName)
    if defaultPath:
        PrintOneLineLog(EventLevel.info, utilityName, 
        'The default {0}'.format(component) + ' path is given by ' + envName \
        + ': ' + defaultPath + '.')
    else:
        PrintOneLineLog(EventLevel.error, utilityName, 
        'The default {0}'.format(component) + ' path is not found because the \
        environment variable ' + envName + ' is not defined.')
    return defaultPath

def PrintBuildArguments(component, argumentType, argumentValueList):
    PrintOneLineLog(EventLevel.info, utilityName, 
    'The ' + argumentType + ' for ' + component + ' are:')
    for argumentValue in argumentValueList:
        PrintOneLineLog(EventLevel.info, utilityName, '\t' + str(argumentValue))

def ReplacePathSeparators(path):
    return path.replace('/', os.sep)
                
def PrintAlljoynEnv(env):
    PrintOneLineLog(EventLevel.info, utilityName, 'Related AllJoyn core build options:')
    PrintOneLineLog(EventLevel.info, utilityName, 'OS = ' + str(env['OS']))
    PrintOneLineLog(EventLevel.info, utilityName, 'CPU = ' + str(env['CPU']))
    PrintOneLineLog(EventLevel.info, utilityName, 'TARGET_ARCH = ' + str(env['TARGET_ARCH']))
    if env['OS'] == 'win7':
        PrintOneLineLog(EventLevel.info, utilityName, 'MSVC_VERSION = ' + str(env['MSVC_VERSION']))
    PrintOneLineLog(EventLevel.info, utilityName, 'VARIANT = ' + str(env['VARIANT']))
    PrintOneLineLog(EventLevel.info, utilityName, 'WS = ' + str(env['WS']))
    PrintOneLineLog(EventLevel.info, utilityName, 'CPPDEFINES = ')
    for defineMacro in env['CPPDEFINES']:
        PrintOneLineLog(EventLevel.info, utilityName, '\t' + str(defineMacro))
    
def IsBuildSupported(env):
    if (env['OS'] == 'win7') and (env['CPU'] == 'x86'):
        return True
    elif (env['OS'] == 'linux'):
        return True
    else:
        return False