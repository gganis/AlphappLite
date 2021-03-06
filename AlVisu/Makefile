#############################################################################
# Makefile for building: ../Linux/AlVisu
# Generated by qmake (1.05a) (Qt 3.1.2) on: Mon Sep  5 09:58:17 2005
# Project:  AlVisu.pro
# Template: app
# Command: $(QMAKE) -o Makefile AlVisu.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2 -g -pipe -march=i386 -mcpu=i686 -fno-use-cxa-atexit -fno-exceptions -Wno-unused -Wno-unused -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT
CXXFLAGS = -pipe -Wall -W -O2 -g -pipe -march=i386 -mcpu=i686 -fno-use-cxa-atexit -fno-exceptions -Wno-unused -Wno-unused -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I$(QTDIR)/mkspecs/default -I. -I$(QTDIR)/include -I/usr/X11R6/include -I/usr/X11R6/include -I.ui/ -I. -I.moc/
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -L/usr/X11R6/lib -L/usr/X11R6/lib -lqt-mt -lGLU -lGL -lXmu -lXext -lX11 -lm -lpthread
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY) -p
COPY_DIR = $(COPY) -pR
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = .obj/

####### Files

HEADERS = glevent.h \
		protocol.h \
		userfunction.h
SOURCES = main.cpp \
		glevent.cpp \
		protocol.cpp
OBJECTS = .obj/main.o \
		.obj/glevent.o \
		.obj/protocol.o \
		.obj/mainwindow.o \
		.obj/aboutbox.o \
		.obj/vpc.o \
		.obj/outputdialog.o \
		.obj/optionsdialog.o \
		.obj/qmake_image_collection.o
FORMS = mainwindow.ui \
		aboutbox.ui \
		vpc.ui \
		outputdialog.ui \
		optionsdialog.ui
UICDECLS = .ui/mainwindow.h \
		.ui/aboutbox.h \
		.ui/vpc.h \
		.ui/outputdialog.h \
		.ui/optionsdialog.h
UICIMPLS = .ui/mainwindow.cpp \
		.ui/aboutbox.cpp \
		.ui/vpc.cpp \
		.ui/outputdialog.cpp \
		.ui/optionsdialog.cpp
SRCMOC   = .moc/moc_glevent.cpp \
		.moc/moc_protocol.cpp \
		.moc/moc_mainwindow.cpp \
		.moc/moc_aboutbox.cpp \
		.moc/moc_vpc.cpp \
		.moc/moc_outputdialog.cpp \
		.moc/moc_optionsdialog.cpp
OBJMOC = .obj/moc_glevent.o \
		.obj/moc_protocol.o \
		.obj/moc_mainwindow.o \
		.obj/moc_aboutbox.o \
		.obj/moc_vpc.o \
		.obj/moc_outputdialog.o \
		.obj/moc_optionsdialog.o
DIST	   = AlVisu.pro
QMAKE_TARGET = AlVisu
DESTDIR  = ../Linux/
TARGET   = ../Linux/AlVisu

first: all
####### Implicit rules

.SUFFIXES: .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	test -d ../Linux/ || mkdir -p ../Linux/
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)

mocables: $(SRCMOC)

$(MOC): 
	( cd $(QTDIR)/src/moc ; $(MAKE) )

Makefile: AlVisu.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile AlVisu.pro
qmake: 
	@$(QMAKE) -o Makefile AlVisu.pro

dist: 
	@mkdir -p .obj/AlVisu && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .obj/AlVisu/ && $(COPY_FILE) --parents mainwindow.ui.h vpc.ui.h outputdialog.ui.h optionsdialog.ui.h .obj/AlVisu/ && ( cd `dirname .obj/AlVisu` && $(TAR) AlVisu.tar AlVisu && $(GZIP) AlVisu.tar ) && $(MOVE) `dirname .obj/AlVisu`/AlVisu.tar.gz . && $(DEL_FILE) -r .obj/AlVisu

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:
	-$(DEL_FILE) $(UICIMPLS) $(UICDECLS)

yaccclean:
lexclean:
clean: mocclean uiclean
	-$(DEL_FILE) $(OBJECTS) 
		-$(DEL_FILE) .ui/qmake_image_collection.cpp
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) ../Linux/$(TARGET) $(TARGET)


FORCE:

####### Compile

.obj/main.o: main.cpp .ui/mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/main.o main.cpp

.obj/glevent.o: glevent.cpp glevent.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/glevent.o glevent.cpp

.obj/protocol.o: protocol.cpp protocol.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/protocol.o protocol.cpp

.ui/mainwindow.h: mainwindow.ui userfunction.h
	$(UIC) mainwindow.ui -o .ui/mainwindow.h

.ui/mainwindow.cpp: .ui/mainwindow.h mainwindow.ui userfunction.h
	$(UIC) mainwindow.ui -i mainwindow.h -o .ui/mainwindow.cpp

.ui/aboutbox.h: aboutbox.ui 
	$(UIC) aboutbox.ui -o .ui/aboutbox.h

.ui/aboutbox.cpp: .ui/aboutbox.h aboutbox.ui 
	$(UIC) aboutbox.ui -i aboutbox.h -o .ui/aboutbox.cpp

.ui/vpc.h: vpc.ui 
	$(UIC) vpc.ui -o .ui/vpc.h

.ui/vpc.cpp: .ui/vpc.h vpc.ui 
	$(UIC) vpc.ui -i vpc.h -o .ui/vpc.cpp

.ui/outputdialog.h: outputdialog.ui 
	$(UIC) outputdialog.ui -o .ui/outputdialog.h

.ui/outputdialog.cpp: .ui/outputdialog.h outputdialog.ui 
	$(UIC) outputdialog.ui -i outputdialog.h -o .ui/outputdialog.cpp

.ui/optionsdialog.h: optionsdialog.ui 
	$(UIC) optionsdialog.ui -o .ui/optionsdialog.h

.ui/optionsdialog.cpp: .ui/optionsdialog.h optionsdialog.ui 
	$(UIC) optionsdialog.ui -i optionsdialog.h -o .ui/optionsdialog.cpp

.obj/mainwindow.o: .ui/mainwindow.cpp protocol.h \
		.ui/outputdialog.h \
		.ui/aboutbox.h \
		.ui/vpc.h \
		.ui/optionsdialog.h \
		mainwindow.ui.h \
		.ui/mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/mainwindow.o .ui/mainwindow.cpp

.obj/aboutbox.o: .ui/aboutbox.cpp .ui/aboutbox.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/aboutbox.o .ui/aboutbox.cpp

.obj/vpc.o: .ui/vpc.cpp vpc.ui.h \
		.ui/vpc.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/vpc.o .ui/vpc.cpp

.obj/outputdialog.o: .ui/outputdialog.cpp outputdialog.ui.h \
		.ui/outputdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/outputdialog.o .ui/outputdialog.cpp

.obj/optionsdialog.o: .ui/optionsdialog.cpp optionsdialog.ui.h \
		.ui/optionsdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/optionsdialog.o .ui/optionsdialog.cpp

.obj/moc_glevent.o: .moc/moc_glevent.cpp glevent.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_glevent.o .moc/moc_glevent.cpp

.obj/moc_protocol.o: .moc/moc_protocol.cpp protocol.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_protocol.o .moc/moc_protocol.cpp

.obj/moc_mainwindow.o: .moc/moc_mainwindow.cpp .ui/mainwindow.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_mainwindow.o .moc/moc_mainwindow.cpp

.obj/moc_aboutbox.o: .moc/moc_aboutbox.cpp .ui/aboutbox.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_aboutbox.o .moc/moc_aboutbox.cpp

.obj/moc_vpc.o: .moc/moc_vpc.cpp .ui/vpc.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_vpc.o .moc/moc_vpc.cpp

.obj/moc_outputdialog.o: .moc/moc_outputdialog.cpp .ui/outputdialog.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_outputdialog.o .moc/moc_outputdialog.cpp

.obj/moc_optionsdialog.o: .moc/moc_optionsdialog.cpp .ui/optionsdialog.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_optionsdialog.o .moc/moc_optionsdialog.cpp

.moc/moc_glevent.cpp: $(MOC) glevent.h
	$(MOC) glevent.h -o .moc/moc_glevent.cpp

.moc/moc_protocol.cpp: $(MOC) protocol.h
	$(MOC) protocol.h -o .moc/moc_protocol.cpp

.moc/moc_mainwindow.cpp: $(MOC) .ui/mainwindow.h
	$(MOC) .ui/mainwindow.h -o .moc/moc_mainwindow.cpp

.moc/moc_aboutbox.cpp: $(MOC) .ui/aboutbox.h
	$(MOC) .ui/aboutbox.h -o .moc/moc_aboutbox.cpp

.moc/moc_vpc.cpp: $(MOC) .ui/vpc.h
	$(MOC) .ui/vpc.h -o .moc/moc_vpc.cpp

.moc/moc_outputdialog.cpp: $(MOC) .ui/outputdialog.h
	$(MOC) .ui/outputdialog.h -o .moc/moc_outputdialog.cpp

.moc/moc_optionsdialog.cpp: $(MOC) .ui/optionsdialog.h
	$(MOC) .ui/optionsdialog.h -o .moc/moc_optionsdialog.cpp

.obj/qmake_image_collection.o: .ui/qmake_image_collection.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/qmake_image_collection.o .ui/qmake_image_collection.cpp

.ui/qmake_image_collection.cpp: images/filenew \
		images/fileopen \
		images/filesave \
		images/print \
		images/undo \
		images/redo \
		images/editcut \
		images/editcopy \
		images/editpaste \
		images/searchfind \
		images/sawfish-appearance.png \
		images/splash.png
	$(UIC)  -embed AlVisu images/filenew images/fileopen images/filesave images/print images/undo images/redo images/editcut images/editcopy images/editpaste images/searchfind images/sawfish-appearance.png images/splash.png -o .ui/qmake_image_collection.cpp

####### Install

install: all 

uninstall: 

