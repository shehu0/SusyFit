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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Vcb.o \
	${OBJECTDIR}/src/Vus.o \
	${OBJECTDIR}/src/HeffDF2.o \
	${OBJECTDIR}/src/Vub.o \
	${OBJECTDIR}/src/alpha_2a.o \
	${OBJECTDIR}/src/alpha.o \
	${OBJECTDIR}/src/Vud.o \
	${OBJECTDIR}/src/AmpDB2.o \
	${OBJECTDIR}/src/EvolDF2.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libflavour.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libflavour.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libflavour.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libflavour.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libflavour.a

${OBJECTDIR}/src/Vcb.o: nbproject/Makefile-${CND_CONF}.mk src/Vcb.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Vcb.o src/Vcb.cpp

${OBJECTDIR}/src/Vus.o: nbproject/Makefile-${CND_CONF}.mk src/Vus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Vus.o src/Vus.cpp

${OBJECTDIR}/src/HeffDF2.o: nbproject/Makefile-${CND_CONF}.mk src/HeffDF2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HeffDF2.o src/HeffDF2.cpp

${OBJECTDIR}/src/Vub.o: nbproject/Makefile-${CND_CONF}.mk src/Vub.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Vub.o src/Vub.cpp

${OBJECTDIR}/src/alpha_2a.o: nbproject/Makefile-${CND_CONF}.mk src/alpha_2a.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/alpha_2a.o src/alpha_2a.cpp

${OBJECTDIR}/src/alpha.o: nbproject/Makefile-${CND_CONF}.mk src/alpha.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/alpha.o src/alpha.cpp

${OBJECTDIR}/src/Vud.o: nbproject/Makefile-${CND_CONF}.mk src/Vud.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Vud.o src/Vud.cpp

${OBJECTDIR}/src/AmpDB2.o: nbproject/Makefile-${CND_CONF}.mk src/AmpDB2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AmpDB2.o src/AmpDB2.cpp

${OBJECTDIR}/src/EvolDF2.o: nbproject/Makefile-${CND_CONF}.mk src/EvolDF2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../Observables/src -I../StandardModel/src -I../gslpp/src -I../Utils/src -I./src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/EvolDF2.o src/EvolDF2.cpp

# Subprojects
.build-subprojects:
	cd ../Observables && ${MAKE}  -f Makefile CONF=Debug
	cd ../StandardModel && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libflavour.a

# Subprojects
.clean-subprojects:
	cd ../Observables && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../StandardModel && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
