/***************************************************************************
                                 glevent.cpp
                             -------------------
    copyright            : (C) 2001 by Christophe Delaere
    email                : delaere@fynu.ucl.ac.be
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "glevent.h"
#include <math.h>
#include <qimage.h>
#include <qtimer.h>
#if defined(Q_OS_MAC)
#include <glu.h>
#else
#include <GL/glu.h>
#endif

#include <iostream>


/*!
  Create a GLevent widget
*/

GLevent::GLevent( QWidget* parent, const char* name )
    : QGLWidget( parent, name )
{
    xRot = yRot = zRot = 0.0;		// default object rotation
    xPos = yPos = 0.0;			// default observer position
    zPos = -5.0;
    // there is one list per object type. Those lists are drawn iff the value is not zero.
    // The lists are build by the "make" methods (makeDetector, makeTracks, ...)
    scale = .7;				// default object scale
    detector = 0;              		// no default detector
    tracks = 0;				// no default tracks
    leptons = 0;				// no default leptons
    jets = 0;				// no default jets
    userObjects = NULL;
    listNumber = 0;
    energyRadius = 50;
    energyLength = 50;
    VDETcolor 	= QColor();
    ITCcolor  	= QColor();
    TPCcolor  	= QColor();
    ECALcolor	= QColor();
    HCALcolor	= QColor();
    MUONcolor	= QColor();
    BACKcolor	= QColor();
    light_on = FALSE;
}

/*!
  Release allocated resources
*/

GLevent::~GLevent()
{
    makeCurrent();
    if (detector) glDeleteLists( detector, 1 );
    if (tracks) glDeleteLists( tracks, 1 );
    if (leptons) glDeleteLists( leptons, 1 );
    if (jets) glDeleteLists( jets, 1 );
    if (userObjects) delete[] userObjects;
}

/*!
   Configure the widget (colors, scales, ...)
*/

void GLevent::setListNumber(int size)
{
    if(!userObjects) 
    { 
	userObjects = new GLuint[size]; 
	for(int i = 0; i < size; i++)
	    userObjects[i] = 0;
	listNumber = size; 
    }
}

void GLevent::configure(QColor c1, QColor c2,QColor c3,QColor c4,QColor c5,QColor c6,QColor c7,int r, int l, bool light, bool full)
{
    VDETcolor 	= c1;
    ITCcolor  	= c2;
    TPCcolor  	= c3;
    ECALcolor	= c4;
    HCALcolor	= c5;
    MUONcolor	= c6;
    BACKcolor	= c7;
    energyRadius = r;
    energyLength = l;
    if(full)
    {
	    qglClearColor(BACKcolor);
	    paintGL();
    }
    light_on = light;
    if (light)
	glEnable(GL_LIGHTING);
    else
	glDisable(GL_LIGHTING); 
    paintGL();
}

void GLevent::reset()
{
    if (tracks) glDeleteLists( tracks, 1 );
    tracks = 0;
    if(leptons) glDeleteLists( leptons, 1 );
    leptons = 0;
    if(jets) glDeleteLists( jets, 1 );
    jets = 0;
    for(int i=0; i< listNumber; i++)
    {
	if(userObjects[i]) glDeleteLists(userObjects[i], 1 ) ;
    }
    if (userObjects) delete[] userObjects;
    userObjects = NULL;
    listNumber = 0;
    paintGL();
}

/*!
  Paint the event. The actual openGL commands for drawing the event are
  performed here.
*/

void GLevent::paintGL()
{
    if (light_on)
	glEnable(GL_LIGHTING);
    else
	glDisable(GL_LIGHTING); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();                           					// Reset The View
    glTranslatef(xPos,yPos,zPos); 					// this is related to the user position...
    glRotatef( xRot, 1.0, 0.0, 0.0 ); 					// this is the object orientation
    glRotatef( yRot, 0.0, 1.0, 0.0 ); 
    glRotatef( zRot, 0.0, 0.0, 1.0 );
    glScalef( scale, scale, scale );					// the object scale (zoom)
    glTranslatef(0.0f,0.0f,-1.0f);						// put the object into the screen
    if (detector) glCallList( detector );					// build the objects using lists
    if (tracks)   glCallList( tracks );
    if (leptons)  glCallList( leptons );
    if (jets)     glCallList( jets );
    for(int i=0; i<listNumber;i++)
    {
	if(userObjects[i]) glCallList(userObjects[i]);
    }
}

/*!
  Set up the OpenGL rendering state, and define display list
*/

void GLevent::initializeGL()
{
    qglClearColor(BACKcolor);
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS); 			// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
    glShadeModel(GL_SMOOTH);		// Enables Smooth Color Shading
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    glMatrixMode(GL_MODELVIEW);
    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT1);
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess [] = { 100.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    if (light_on)
	glEnable(GL_LIGHTING);
    else
	glDisable(GL_LIGHTING); 
}

/*!
  Set up the OpenGL view port, matrix mode, etc.
*/

void GLevent::resizeGL( int w, int h )
{
    if (h==0)  h=1;		// Prevent A Divide By Zero If The Window Is Too Small
    glViewport(0, 0, w, h);	// Reset The Current Viewport And Perspective Transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w/ (GLfloat)h,0.1f,100.0f );
    glMatrixMode(GL_MODELVIEW);
}

void GLevent::mouseMoveEvent(QMouseEvent *e)
{
    float presentXshift = (e->x() - onscreenXorigin)/100.;
    float presentYshift = (e->y() - onscreenYorigin)/100.;
    if(e->state()&Qt::LeftButton)
    {
	if(e->state()&Qt::ShiftButton)
	    zPos = zPos0-(presentYshift*2);
	else
	    yPos = yPos0-(presentYshift/height()*450);
	xPos = xPos0+(presentXshift/width()*450);
    }
    else if(e->state()&Qt::RightButton)
    {
	if(e->state()&Qt::ShiftButton)
	    zRot = zRot0+presentYshift*100;
	else
	    xRot = xRot0+presentYshift*100;
	yRot = yRot0+presentXshift*100;
   }
    updateGL();
}

void GLevent::mousePressEvent(QMouseEvent *e)
{
    onscreenXorigin = e->x();
    onscreenYorigin = e->y();
    xPos0 = xPos;
    yPos0 = yPos;
    zPos0 = zPos;
    xRot0 = xRot;
    yRot0 = yRot;
    zRot0 = zRot;
}

void GLevent::mouseReleaseEvent(QMouseEvent *e)
{
    emit glViewChanged((((int)xRot%360)+360)%360, (((int)yRot%360)+360)%360, (((int)zRot%360)+360)%360, (int)((xPos+2)*25), (int)((yPos+2)*25), (int)((zPos+5.)*10), (int)(scale*10));
}

/*!
  Generate an OpenGL display list for the object to be shown, i.e. the event
*/

void GLevent::makeDetector(int pattern) 
{
    // up to now, this is only a simplified detector made of cylinders...
    // all the sizes are computed w.r.t. the barel muon length, set to 2.
    if (detector) glDeleteLists( detector, 1 );
    if (!pattern) { detector = 0; updateGL(); return; }
    detector = glGenLists(1);
    GLUquadricObj* q = gluNewQuadric();
    glNewList( detector, GL_COMPILE );
    if(pattern&(1<<0))
    {
	    // VDET
	    qglColor(VDETcolor);
	    glTranslatef(0.0f,0.0f,0.96f);
	    gluCylinder(q, 0.02, 0.02, 0.08, 15, 1);
	    glTranslatef(0.0f,0.0f,-0.96f);
    }
    if(pattern&(1<<1))
    {
	    // ITC
	    qglColor(ITCcolor);
	    glTranslatef(0.0f,0.0f,0.775f);
	    gluCylinder(q, 0.06, 0.06, 0.45, 30, 1);
	    glTranslatef(0.0f,0.0f,-0.775f);
    }
    if(pattern&(1<<2))
    {
	    // TPC
	    qglColor(TPCcolor);
	    glTranslatef(0.0f,0.0f,0.575f);
	    gluCylinder(q, 0.38, 0.38, 0.85, 30, 1);
	    glTranslatef(0.0f,0.0f,-0.575f);
    }
    if(pattern&(1<<3))
    {
	    // ECAL
	    qglColor(ECALcolor);
	    glTranslatef(0.0f,0.0f,0.55f);
	    gluCylinder(q, 0.43, 0.43, 0.9, 12, 1);
	    glTranslatef(0.0f,0.0f,-0.55f);
    }
    if(pattern&(1<<4))
    {
	    // HCAL
	    qglColor(HCALcolor);
	    glTranslatef(0.0f,0.0f,0.315f);
	    gluCylinder(q, 0.50, 0.50, 1.37, 12, 1);
	    glTranslatef(0.0f,0.0f,-0.315f);
    }
    if(pattern&(1<<5))
    {
	    // MU
	    qglColor(MUONcolor);
	    gluCylinder(q, 0.82, 0.82, 2., 12, 1);
    }
    if(pattern&(1<<6))
    {
	    // ECAL ENDCAP
	    qglColor(ECALcolor);
	    glTranslatef(0.0f,0.0f,0.55f);
	    glTranslatef( 0.0, 0.0, 0.9 );
	    gluDisk( q, 0.0, 0.43, 12, 1 );
	    glTranslatef( 0.0, 0.0, -0.9 );
	    gluDisk( q, 0.0, 0.43, 12, 1 );
	    glTranslatef(0.0f,0.0f,-0.55f);
    }
    if(pattern&(1<<7))
    {
	    // HCAL ENDCAP
	    qglColor(HCALcolor);
	    glTranslatef(0.0f,0.0f,0.315f);
	    glTranslatef( 0.0, 0.0, 1.37 );
	    gluDisk( q, 0.0, 0.5, 12, 1 );
	    glTranslatef( 0.0, 0.0, -1.37 );
	    gluDisk( q, 0.0, 0.5, 12, 1 );
	    glTranslatef(0.0f,0.0f,-0.315f);
    }
    if(pattern&(1<<8))
    {
	    // MU ENDCAP
	    qglColor(MUONcolor);
	    glTranslatef( 0.0, 0.0, 2.0 );
	    gluDisk( q, 0.0, 0.82, 12, 1 );
	    glTranslatef( 0.0, 0.0, -2.0 );
	    gluDisk( q, 0.0, 0.82, 12, 1 );
    }
    glEndList();
    updateGL();
    return;
}

void GLevent::makeTracks(QValueVector< float* > *tracklist,QColor pcolor, QColor mcolor, QColor ncolor)
{
    if (tracks) glDeleteLists( tracks, 1 );
    if (!tracklist) { tracks = 0; updateGL(); return; }
    tracks = glGenLists(1);
    GLUquadricObj* q = gluNewQuadric();
    glNewList( tracks, GL_COMPILE );
    glTranslatef(0.0f,0.0f,1.0f);
    for (QValueVector< float* >::iterator current = tracklist->begin(); current<tracklist->end(); current++)
    {
	float* track = *current;
	// set the track color
	if((track[4])>0)
	    qglColor(pcolor);
	else if ((track[4])<0)
	    qglColor(mcolor);
	else
	    qglColor(ncolor);
	// find the track direction
	float norm = pow(pow(track[1],2) + pow(track[2],2) + pow(track[3],2),0.5);
	float cth = track[3]/norm;
	glRotatef(acos(cth)*57.2957795131,track[2],-track[1],0.0f);
	float length=0;
	if(fabs(cth) > 0.723)
		length = fabs(0.45/cth);
	else
       		length = 0.43/pow(1-pow(cth,2),0.5);
	// eventually draw a track
	if((track[4])!=0)
	{
	    glBegin(GL_LINES);
	    glVertex3f(0.0f, 0.0f, 0.0f);
	    glVertex3f(0.0f, 0.0f, length);
	    glEnd();
	}
	// go to the calorimeter layer
	glTranslatef(0.0f, 0.0f, length);
	// draw the energy-cylinder
	// here 1 is the maximum length and 200 the maximum energy --> scale factor
	float energy_gauge = (energyLength/10000.)*track[0];
	gluDisk( q, 0.0, (energyRadius/1000.), 30, 1 );
	gluCylinder(q, (energyRadius/1000.), (energyRadius/1000.),energy_gauge, 30, 1);
	glTranslatef( 0.0, 0.0, energy_gauge );
	gluDisk( q, 0.0, (energyRadius/1000.), 30, 1 );
	glTranslatef( 0.0, 0.0, -energy_gauge );
	// return to the origin and realign to z-axis
	glTranslatef(0.0f, 0.0f, -length);
	glRotatef(-acos(cth)*57.2957795131,track[2],-track[1],0.0f);
    }
    glTranslatef(0.0f,0.0f,-1.0f);
    glEndList();
    updateGL();
    return;
}

void GLevent::makeLeptons(QValueVector< float* > *tracklist,QColor pColorEl,QColor mColorEl,QColor pColorMu,QColor mColorMu,QColor pColorTau,QColor mColorTau)
{
    if (leptons) glDeleteLists( leptons, 1 );
    if (!tracklist) { leptons = 0; updateGL(); return; }
    leptons = glGenLists(1);
    GLUquadricObj* q = gluNewQuadric();
    glNewList( leptons, GL_COMPILE );
    glTranslatef(0.0f,0.0f,1.0f);
    for (QValueVector< float* >::iterator current = tracklist->begin(); current<tracklist->end(); current++)
    {
	float* track = *current;
	// set the lepton color
	if((track[4]) >0)
	    switch ((int)(track[5]))
	    {
	    case 1: // electron
		{
	            qglColor(pColorEl);
		    break;
		}
	    case 2: // muon
		{
		    qglColor(pColorMu);
		    break;
		}
	    case 3: // tau
		{
		    qglColor(pColorTau);
		    break;
		}
	    default:
		{
		    // nothing to do....
		}
	    }
	else
	    switch ((int)(track[5]))
	    {
	    case 1: // electron
		{
		    qglColor(mColorEl);
		    break;
		}
	    case 2: // muon
		{
		    qglColor(mColorMu);
		    break;
		}
	    case 3: // tau
		{
		    qglColor(mColorTau);
		    break;
		}
	    default:
		{
		    // nothing to do....
		}
	    }
	// find the lepton direction
	float norm = pow(pow(track[1],2) + pow(track[2],2) + pow(track[3],2),0.5);
	float cth = track[3]/norm;
	glRotatef(acos(cth)*57.2957795131,track[2],-track[1],0.0f);
	// find the lepton length
	float length=0;
	float l1 = 0;
	float l2 = 0;
	if ( track[5] == 1) { l1 = 0.45; l2 = 0.43;}
	else if ( track[5] == 3) { l1 = 0.685; l2 = 0.5;}
	else { l1 = 1.; l2 = 0.82;}
	if(fabs(cth) > 0.723)
		length = l1/cth;
	else
       		length = l2/pow(1-pow(cth,2),0.5);
	// draw a track
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, length);
	glEnd();
	// go to the calorimeter layer
	glTranslatef(0.0f, 0.0f, length);
	// draw the energy-cylinder
	// here 1 is the maximum length and 200 the maximum energy --> scale factor
	float energy_gauge = ((energyLength/10000.)*track[0])+0.005;
	gluDisk( q, 0.0, (energyRadius/1000.)+0.005, 30, 1 );
	gluCylinder(q, (energyRadius/1000.)+0.005, (energyRadius/1000.)+0.005,energy_gauge, 30, 1);
	glTranslatef( 0.0, 0.0, energy_gauge );
	gluDisk( q, 0.0, (energyRadius/1000.)+0.005, 30, 1 );
	glTranslatef( 0.0, 0.0, -energy_gauge );
	// return to the origin and realign to z-axis
	glTranslatef(0.0f, 0.0f, -length);
	glRotatef(-acos(cth)*57.2957795131,track[2],-track[1],0.0f);
    }
    glTranslatef(0.0f,0.0f,-1.0f);
    glEndList();
    updateGL();
    return;
}

void GLevent::makeJets(QValueVector< float* > *jetlist, QColor *jetcolor, int nJetcolor)
{
    if (jets) glDeleteLists( jets, 1 );
    if (!jetlist) { jets = 0; updateGL(); return; }
    jets = glGenLists(1);
    GLUquadricObj* q = gluNewQuadric();
    glNewList( jets, GL_COMPILE );
    glTranslatef(0.0f,0.0f,1.0f);
    int count = 0;
    for (QValueVector< float* >::iterator current = jetlist->begin(); current<jetlist->end(); current++)
    {
	float* jet = *current;
	// set the jet color
	qglColor(jetcolor[(count++)%nJetcolor]);
	// find the jet direction
	float norm = pow(pow(jet[1],2) + pow(jet[2],2) + pow(jet[3],2),0.5);
	float cth = jet[3]/norm;
	glRotatef(acos(cth)*57.2957795131,jet[2],-jet[1],0.0f);
	// find the jet length
	float length=0;
	if(fabs(cth) > 0.723)
		length = fabs(0.685/cth);
	else
       		length = 0.5/pow(1-pow(cth,2),0.5);
	// compute the radius
	float radius = fabs(length*pow(1-pow(jet[0],2),.5)/jet[0]);
	// renormalize ...
	if(radius>1.) {length /= radius; radius=1.;}
	// draw a jet
	gluCylinder(q, 0., radius, length, 30, 1);
	// realign to z-axis
	glRotatef(-acos(cth)*57.2957795131,jet[2],-jet[1],0.0f);
    }
    glTranslatef(0.0f,0.0f,-1.0f);
    glEndList();
    updateGL();
    return;
}

void GLevent::makeUserObjects(QValueVector< float* > *objectlist,int code, QColor *colors, int ncolors) 
{
    if (userObjects[code]) 
    {
	glDeleteLists( userObjects[code], 1 );
    }
    if (!objectlist) 
    { 
	userObjects[code] = 0; 
	updateGL(); 
	return; 
    }
    userObjects[code] = glGenLists(1);
    GLUquadricObj* q = gluNewQuadric();
    glNewList( userObjects[code], GL_COMPILE );
    glTranslatef(0.0f,0.0f,1.0f);
    int count = 0;
    for (QValueVector< float* >::iterator current = objectlist->begin(); current<objectlist->end(); current++)
    { 
	// set the color
	qglColor(colors[(count++)%ncolors]);
	// switch on the object type
	switch(int(**current))
	{
	case 1:
	    {
		// track
		float* track = *current;
		// find the track direction
		float norm = pow(pow(track[1],2) + pow(track[2],2) + pow(track[3],2),0.5);
		float cth = track[3]/norm;
		glRotatef(acos(cth)*57.2957795131,track[2],-track[1],0.0f);
		float length=0;
		if(fabs(cth) > 0.723)
		    length = fabs(0.45/cth);
		else
		    length = 0.43/pow(1-pow(cth,2),0.5);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, length);
		glEnd();
		// return to the origin and realign to z-axis
		glRotatef(-acos(cth)*57.2957795131,track[2],-track[1],0.0f);
		break;
	    }
	case 2:
	    {
		// eflow
		float* track = *current;
		// find the eflow direction
		float norm = pow(pow(track[2],2) + pow(track[3],2) + pow(track[4],2),0.5);
		float cth = track[4]/norm;
		glRotatef(acos(cth)*57.2957795131,track[3],-track[2],0.0f);
		float length=0;
		if(fabs(cth) > 0.723)
		{
		    length = fabs(0.45/cth);
		}
		else
		{
		    length = 0.43/pow(1-pow(cth,2),0.5);
		}
		// eventually draw a track
		if((track[5])!=0)
		{
		    glBegin(GL_LINES);
		    glVertex3f(0.0f, 0.0f, 0.0f);	
		    glVertex3f(0.0f, 0.0f, length);
		    glEnd();
		}
		// go to the calorimeter layer
		glTranslatef(0.0f, 0.0f, length);
		// draw the energy-cylinder
		// here 1 is the maximum length and 200 the maximum energy --> scale factor
		float energy_gauge = (energyLength/10000.)*track[1];
		gluDisk( q, 0.0, (energyRadius/1000.), 30, 1 );
		gluCylinder(q, (energyRadius/1000.), (energyRadius/1000.),energy_gauge, 30, 1);
		glTranslatef( 0.0, 0.0, energy_gauge );
		gluDisk( q, 0.0, (energyRadius/1000.), 30, 1 );
		glTranslatef( 0.0, 0.0, -energy_gauge );
		// return to the origin and realign to z-axis
		glTranslatef(0.0f, 0.0f, -length);
		glRotatef(-acos(cth)*57.2957795131,track[3],-track[2],0.0f);
		break;
	    }
	case 3:
	    {
		// lepton
		float* track = *current;
		// find the lepton direction
		float norm = pow(pow(track[2],2) + pow(track[3],2) + pow(track[4],2),0.5);
		float cth = track[4]/norm;
		glRotatef(acos(cth)*57.2957795131,track[3],-track[2],0.0f);
		// find the lepton length
		float length=0;
		float l1 = 0;
		float l2 = 0;
		if ( track[6] == 1) { l1 = 0.45; l2 = 0.43;}
		else if ( track[6] == 3) { l1 = 0.685; l2 = 0.5;}
		else { l1 = 1.; l2 = 0.82;}
		if(fabs(cth) > 0.723)
		    length = l1/cth;
		else
		    length = l2/pow(1-pow(cth,2),0.5);
		// draw a track
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, length);
		glEnd();
		// go to the calorimeter layer
		glTranslatef(0.0f, 0.0f, length);
		// draw the energy-cylinder
		// here 1 is the maximum length and 200 the maximum energy --> scale factor
		float energy_gauge = ((energyLength/10000.)*track[1])+0.005;
		gluDisk( q, 0.0, (energyRadius/1000.)+0.005, 30, 1 );
		gluCylinder(q, (energyRadius/1000.)+0.005, (energyRadius/1000.)+0.005,energy_gauge, 30, 1);
		glTranslatef( 0.0, 0.0, energy_gauge );
		gluDisk( q, 0.0, (energyRadius/1000.)+0.005, 30, 1 );
		glTranslatef( 0.0, 0.0, -energy_gauge );
		// return to the origin and realign to z-axis
		glTranslatef(0.0f, 0.0f, -length);
		glRotatef(-acos(cth)*57.2957795131,track[3],-track[2],0.0f);
		break;
	    }
	case 4:
	    {
		// jet
		float* jet = *current;
		// find the jet direction
		float norm = pow(pow(jet[2],2) + pow(jet[3],2) + pow(jet[4],2),0.5);
		float cth = jet[4]/norm;
		glRotatef(acos(cth)*57.2957795131,jet[3],-jet[2],0.0f);
		// find the jet length
		float length=0;
		if(fabs(cth) > 0.723)
		    length = fabs(0.685/cth);
		else
		    length = 0.5/pow(1-pow(cth,2),0.5);
		// compute the radius
		float radius = fabs(length*pow(1-pow(jet[1],2),.5)/jet[1]);
		// renormalize ...
		if(radius>1.) {length /= radius; radius=1.;}
		// draw a jet
		gluCylinder(q, 0., radius, length, 30, 1);
		// realign to z-axis
		glRotatef(-acos(cth)*57.2957795131,jet[3],-jet[2],0.0f);
		break;
	    }
	default:
	    {
		// no default action
		break;
	    }
	}
    }
    glTranslatef(0.0f,0.0f,-1.0f);
    glEndList();
    updateGL();
    return;
}

void GLevent::SetViewAngle_x(int teta)
{
    xRot = (GLfloat)(teta % 360);
    updateGL();
}

void GLevent::SetViewAngle_y(int teta)
{
    yRot = (GLfloat)(teta % 360);
    updateGL();
}

void GLevent::SetViewAngle_z(int teta)
{
    zRot = (GLfloat)(teta % 360);
    updateGL();
}

void GLevent::SetScale(int scle)
{
    scale = (GLfloat)(scle)/10;
    updateGL();
}

void GLevent::SetPos_x(int l)
{
    xPos = (GLfloat)(l/25.)-2;
    updateGL();
}

void GLevent::SetPos_y(int l)
{
    yPos = (GLfloat)(l/25.)-2;
    updateGL();
}

void GLevent::SetPos_z(int l)
{
    zPos = (GLfloat)(l/10.)-5.;
    updateGL();
}
