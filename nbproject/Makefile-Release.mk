#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=
CCC=g++412
CXX=g++412
FC=

# Macros
PLATFORM=FOR_MAYA-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/pluginMain.o \
	${OBJECTDIR}/slideMeshNode.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/autodesk/maya/lib -lOpenMaya -lFoundation -lOpenMayaAnim -lOpenMayaUI

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/slideMeshNode.so

dist/Release/GNU-Linux-x86/slideMeshNode.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -shared -o dist/Release/GNU-Linux-x86/slideMeshNode.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/pluginMain.o: pluginMain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DLINUX -D_BOOL -DINCLUDE_IOSTREAM -DREQUIRE_IOSTREAM -DAW_NEW_IOSTREAMS -I/usr/autodesk/maya/include -I/opt/gcc412/include/c++/4.1.2 -fPIC  -o ${OBJECTDIR}/pluginMain.o pluginMain.cpp

${OBJECTDIR}/slideMeshNode.o: slideMeshNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DLINUX -D_BOOL -DINCLUDE_IOSTREAM -DREQUIRE_IOSTREAM -DAW_NEW_IOSTREAMS -I/usr/autodesk/maya/include -I/opt/gcc412/include/c++/4.1.2 -fPIC  -o ${OBJECTDIR}/slideMeshNode.o slideMeshNode.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/slideMeshNode.so

# Subprojects
.clean-subprojects:
