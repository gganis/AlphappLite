SOURCES	+= main.cpp glevent.cpp protocol.cpp 
HEADERS	+= glevent.h protocol.h userfunction.h 
DESTDIR = ../Linux
unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}
QMAKE_CFLAGS_RELEASE += -Wno-unused
QMAKE_CXXFLAGS_RELEASE += -Wno-unused
FORMS	= mainwindow.ui aboutbox.ui vpc.ui outputdialog.ui optionsdialog.ui 
IMAGES	= images/filenew images/fileopen images/filesave images/print images/undo images/redo images/editcut images/editcopy images/editpaste images/searchfind images/sawfish-appearance.png images/splash.png 
TEMPLATE	=app
CONFIG	+= qt warn_on release opengl 
exists( $(QTDIR)/lib/libqt-mt* ) {
      message( "Configuring for multi-threaded Qt..." )
      CONFIG += thread
}
QMAKE_CFLAGS_RELEASE += -Wno-unused
QMAKE_CXXFLAGS_RELEASE += -Wno-unused
DBFILE	= AlVisu.db
LANGUAGE	= C++
