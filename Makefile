###########################################################
# Makefile                                                #
# Christophe Delaere - 05/09/2005                         #
###########################################################

###########################################################
# variable setting                                        #
# PROFILING=1 generates the -pg flag needed for profiling.#
# Else leave empty.                                       #
###########################################################

NO_ANSI_WARNINGS=
PROFILING=

###########################################################
# some definitions                                        #
###########################################################

OS=Linux
OSDIR = $(OS)

ifeq "$(VERBOSE)" "1"
  C++ = g++
else
  C++ = @g++
endif

#####
# Sources and objects
#####

USER          = $(wildcard *.C)
ifneq ($(words $(USER)),1)
ifneq ($(words $(USER)),0)
 $(error More than one .C file !) 
endif
endif

USER_SRCS     = $(wildcard *.cpp)
USER_OBJS     = $(addprefix $(OS)/, $(USER_SRCS:.cpp=.o))
USER_OBJS    += $(addprefix $(OS)/, $(USER:.C=.o))

DRIV_SRCS     = $(wildcard Driver/src/*.cpp)
DRIV_OBJS     = $(patsubst %.cpp, %.o, $(subst Driver/src, $(OS),$(DRIV_SRCS)))

APPL_SRCS     = $(filter-out %Dict.cpp, $(wildcard Analysis/src/*.cpp))
APPL_SRCS    += Analysis/src/BankClassesDict.cpp
APPL_SRCS    += Analysis/src/AlphaBanksDict.cpp
APPL_OBJS     = $(patsubst %.cpp, %.o, $(subst Analysis/src, $(OS),$(APPL_SRCS)))

OBJS = $(USER_OBJS) $(DRIV_OBJS) $(APPL_OBJS)

HEADERSFILES  = $(wildcard Driver/inc/*.h)
HEADERSFILES += $(wildcard Analysis/inc/*.h)
HEADERSFILES += $(wildcard *.h)

#####
# ROOT stuff
#####

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

###
# General libs
###

GEN_LIBS = -lnsl -lcrypt -ldl -lg2c -lm -lc -lgcc 

###
# Final flag setting
###

C_FLAGS += -Wall -Wno-unused -Wno-long-long -Wpointer-arith -Wnested-externs -Woverloaded-virtual -Wbad-function-cast -Wconversion 
C_FLAGS += -fPIC
C_FLAGS += -IDriver/inc -IAnalysis/inc
C_FLAGS += -I.
C_FLAGS += $(ROOTCFLAGS)

ifndef NO_ANSI_WARNINGS
C_FLAGS += -ansi
endif

ifdef PROFILING
C_FLAGS += -pg
endif

###########################################################
# the targets                                             #
###########################################################

.PHONY: all driver dictionaries analysis user bin clean libs AlVisu qmake help
all : bin AlVisu
dictionaries : Analysis/src/BankClassesDict.cpp Analysis/src/BankClassesDict.cpp
driver: $(OSDIR) $(OS)/AlphappDriver.so
analysis: $(OSDIR) $(OS)/AlphappAnalysis.so
user: $(OSDIR) $(OS)/AlphappUser.so
libs: driver analysis user
bin: $(OS)/$(basename $(USER))
AlVisu: $(OSDIR)
	@$(MAKE) -C AlVisu

$(OSDIR): 
	@echo creating platform directory...
	@mkdir $(OS)

Analysis/src/BankClassesDict.cpp: Analysis/inc/BankClasses.h Analysis/inc/BankClassesLinkDef.h
	@echo generating dictionary for BankClasses
	@rootcint -f Analysis/src/BankClassesDict.cpp -c Analysis/inc/BankClasses.h Analysis/inc/BankClassesLinkDef.h

Analysis/src/AlphaBanksDict.cpp: Analysis/inc/AlphaBanks.h Analysis/inc/AlphaBanksLinkDef.h
	@echo generating dictionary for AlphaBanks
	@rootcint -f Analysis/src/AlphaBanksDict.cpp -c Analysis/inc/AlphaBanks.h Analysis/inc/AlphaBanksLinkDef.h

$(OS)/BankClassesDict.o : Analysis/src/BankClassesDict.cpp
	@echo building BankClassesDict.cpp
	${C++} ${C_FLAGS} -c Analysis/src/BankClassesDict.cpp -o ${OS}/BankClassesDict.o

$(OS)/AlphaBanksDict.o : Analysis/src/AlphaBanksDict.cpp 
	@echo building AlphaBanksDict.cpp
	${C++} ${C_FLAGS} -c Analysis/src/AlphaBanksDict.cpp -o ${OS}/AlphaBanksDict.o

$(OS)/%.o : %.cpp $(HEADERSFILES)
	@echo building $*.cpp
	${C++} ${C_FLAGS} -c $*.cpp -o ${OS}/$*.o

$(OS)/%.o : %.C $(HEADERSFILES)
	@echo building $*.C
	${C++} ${C_FLAGS} -c $*.C -o ${OS}/$*.o

$(OS)/%.o : Analysis/src/%.cpp $(HEADERSFILES)
	@echo building $*.cpp
	${C++} ${C_FLAGS} -c Analysis/src/$*.cpp -o ${OS}/$*.o

$(OS)/%.o : Driver/src/%.cpp $(HEADERSFILES)
	@echo building $*.cpp
	${C++} ${C_FLAGS} -c Driver/src/$*.cpp  -o ${OS}/$*.o

$(OS)/AlphappDriver.so: $(DRIV_OBJS)
	@echo creating AlphappDriver.so
	$(C++) -shared -O $(DRIV_OBJS) -o $(OS)/AlphappDriver.so

$(OS)/AlphappAnalysis.so: $(APPL_OBJS)
	@echo creating AlphappAnalysis.so
	$(C++) -shared -O $(APPL_OBJS) -o $(OS)/AlphappAnalysis.so

$(OS)/AlphappUser.so: $(USER_OBJS)
	@echo creating AlphappUser.so
	$(C++) -shared -O $(USER_OBJS) -o $(OS)/AlphappUser.so

$(OS)/$(basename $(USER)): $(OSDIR) $(OS)/AlphappDriver.so $(OS)/AlphappAnalysis.so $(OS)/AlphappUser.so
	@echo creating $(OS)/$(basename $(USER))
	$(C++) $(C_FLAGS) -o $(OS)/$(basename $(USER)) $(OS)/AlphappDriver.so $(OS)/AlphappAnalysis.so $(OS)/AlphappUser.so $(ROOTLIBS) $(GEN_LIBS)
	@echo Enjoy...

clean: 
	@echo Deleting platform directory...
	@rm -rf $(OS)
	@echo Removing ROOT dictionaries...
	@rm -f Analysis/src/*Dict* Analysis/inc/*Dict*
	@echo Cleaning AlVisu...
	@$(MAKE) -C AlVisu distclean
	@echo Done.

qmake:
	@$(MAKE) -C AlVisu qmake

help:
	@echo
	@echo 'Makefile for alpha++ '
	@echo 'Christophe Delaere - 05/09/2005'
	@echo
	@echo 'Targets are:'
	@echo 'all          : Build the alpha++ binary and AlVisu'
	@echo 'bin          : Build the alpha++ binary'
	@echo 'AlVisu       : Build AlVisu, the 3D event display'
	@echo 'clean        : Clean-up everything'
	@echo 'qmake        : Re-generate the AlVisu Makefile (for new Qt)'
	@echo 'driver       : Build the driver library'
	@echo 'analysis     : Build the analysis library'
	@echo 'user         : Build the user library'
	@echo 'libs         : Build all libs (driver, analysis, user)'
	@echo 'dictionaries : Build the ROOT dictioraries'
	@echo 'help         : Display this message.'

