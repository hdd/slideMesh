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
CC=gcc
CCC=g++
CXX=g++
FC=

# Macros
PLATFORM=GNU-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/${PLATFORM}

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
LDLIBSOPTIONS=-L/usr/autodesk/maya8.5/lib -lOpenMaya -lFoundation -lOpenMayaAnim

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/${PLATFORM}/libslideMeshNode.so

dist/Debug/${PLATFORM}/libslideMeshNode.so: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/${PLATFORM}
	${LINK.cc} -shared -o dist/Debug/${PLATFORM}/libslideMeshNode.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/pluginMain.o: pluginMain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -DLINUX -D_BOOL -DINCLUDE_IOSTREAM -DREQUIRE_IOSTREAM -I/usr/autodesk/maya8.5/include -I/usr/include -fPIC  -o ${OBJECTDIR}/pluginMain.o pluginMain.cpp

${OBJECTDIR}/slideMeshNode.o: slideMeshNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -DLINUX -D_BOOL -DINCLUDE_IOSTREAM -DREQUIRE_IOSTREAM -I/usr/autodesk/maya8.5/include -I/usr/include -fPIC  -o ${OBJECTDIR}/slideMeshNode.o slideMeshNode.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/${PLATFORM}/libslideMeshNode.so

# Subprojects
.clean-subprojects:
