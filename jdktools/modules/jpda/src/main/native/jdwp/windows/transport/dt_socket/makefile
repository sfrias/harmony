#  Licensed to the Apache Software Foundation (ASF) under one or more
#  contributor license agreements.  See the NOTICE file distributed with
#  this work for additional information regarding copyright ownership.
#  The ASF licenses this file to You under the Apache License, Version 2.0
#  (the "License"); you may not use this file except in compliance with
#  the License.  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

#
# Makefile for module jdwp - socket transport
#

HY_BIN=$(HY_TARGET)\build\jdktools\jpda\native\dt_socket\# trailing slash
!include <$(HY_TARGET)\hdk\build\make\defines.mak>

COMMON=..\..\..\common\# comment to avoid \ being treated as continuation
CMNTRANS=$(COMMON)transport\# comment to avoid \ being treated as continuation

!IF "$(HY_OS)-$(HY_ARCH)" == "windows-x86_64" 
WARNING_LEVEL=W0
PLATFORM_64=-DHYX86_64 -Oi -DWIN64 -D_WIN64 -D_AMD64_=1
CPU=AMD64
HYCOMMONCFLAGS = -GS- -EHs-c- /wd4530 $(HYCOMMONCFLAGS)
!ELSE
WARNING_LEVEL=WX
HYCOMMONCFLAGS = -GS -GX $(HYCOMMONCFLAGS)
!ENDIF

LIBBASE=dt_socket
DLLNAME=$(TOOLSDLLPATH)$(LIBBASE).dll
LIBNAME=$(LIBPATH)$(LIBBASE).lib

INCLUDES = $(INCLUDES) \
         -I$(CMNTRANS)common -I$(CMNTRANS)dt_socket \
         -I$(COMMON)generic -I. \
         -I..\common

HYCFLAGS = -I..\..\..\..\include $(HYCFLAGS) $(INCLUDES) -GX -wd4290

HYLDFLAGS = $(HYLDFLAGS) -def:$(LIBBASE).def

BUILDFILES = $(HY_BIN)LastTransportError.obj $(HY_BIN)SocketTransport.obj \
             $(HY_BIN)SocketTransport_pd.obj

HYRCFLAGS = -I..\..\..\..\include

VIRTFILES = dt_socket.res

SYSLIBFILES = 

MDLLIBFILES = $(LIBPATH)vmi.lib $(LIBPATH)hythr$(HY_LINKLIB_SUFFIX)

DLLBASE=0x13200000
COMMENT=/comment:"JDWP socket transport native code. (c) Copyright 2005 - 2009 The Apache Software Foundation or its licensors, as applicable."

!include <$(HY_HDK)\build\make\rules.mak>

{$(CMNTRANS)common}.cpp{$(HY_BIN)}.obj:
        -mkdir $(*D)
        $(cc) $(cflags) $(HYCFLAGS) -Fo$*.obj $<

{$(CMNTRANS)dt_socket}.cpp{$(HY_BIN)}.obj:
        -mkdir $(*D)
        $(cc) $(cflags) $(HYCFLAGS) -Fo$*.obj $<
