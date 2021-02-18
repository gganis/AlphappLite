/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/

void vpc::hideEvent( QHideEvent * e )
{
    emit hidden();
}

void vpc::newZoom( int val )
{
    emit zoomChanged(val);
}

void vpc::newX( int val )
{
    emit xViewChanged(val);
}

void vpc::newY( int val )
{
    emit yViewChanged(val);
}

void vpc::newZ( int val )
{
    emit zViewChanged(val);
}

void vpc::newZpos( int val )
{
    emit zPosChanged(val);
}

void vpc::newXpos( int val )
{
    emit xPosChanged(val);
}

void vpc::newYpos( int val )
{
    emit yPosChanged(val);
}

void vpc::ressetall( int rx, int ry, int rz, int lx, int ly, int lz, int scl )
{
    Slider3->setValue(rx);
    Slider4->setValue(ry);
    Slider5->setValue(rz);
    Slider24->setValue(lx);
    Slider25->setValue(ly);
    Slider27->setValue(lz);
    Slider2->setValue(scl);
}
