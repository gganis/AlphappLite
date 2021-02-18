#include <qpixmap.h>
#include <qimage.h>
#include <qmime.h>
#include <qdragobject.h>
#include <qlabel.h>
#include <qsettings.h>
#include <qrect.h>
#include <qdatetime.h>
#include <qapplication.h>
#include "mainwindow.h"


static QPixmap splashScreen()
{
    const QMimeSource *m = QMimeSourceFactory::defaultFactory()->data( "splash.png" );
    if ( !m )
	    return QPixmap();
    QPixmap pix;
    QImageDrag::decode( m, pix );
    return pix;
}


int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    QLabel *splash = 0;
    QSettings settings;
    settings.insertSearchPath( QSettings::Windows, "/ALEPH" );
    bool show = settings.readBoolEntry("/AlVisu/splash",TRUE);
    if ( show )
    {
	    splash = new QLabel( 0, "splash", QLabel::WDestructiveClose | QLabel::WStyle_Customize | QLabel::WStyle_NoBorder | QLabel::WX11BypassWM | QLabel::WStyle_StaysOnTop );
	    splash->setFrameStyle( QFrame::WinPanel | QFrame::Raised );
	    splash->setPixmap( splashScreen() );
	    splash->adjustSize();
	    splash->setCaption( "AlVisu" );
	    QRect screen = QApplication::desktop()->screenGeometry();
	    splash->move( screen.center() - QPoint( splash->width() / 2, splash->height() / 2 ) );
	    splash->show();
	    splash->repaint( FALSE );
	    QApplication::flush();
    }
    MainWindow *w = new MainWindow;
    w->show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    if( show )
    {
	    QTime chronostart;
	    chronostart.start();
	    for(;chronostart.elapsed()<5000;) {}
	    delete splash;
    }
    return a.exec();
}
