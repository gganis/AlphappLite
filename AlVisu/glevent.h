/***************************************************************************
                                  glevent.h 
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

#ifndef GLEVENT_H
#define GLEVENT_H

#include <qgl.h>
#include <qvaluevector.h>
#include <qcolor.h>

class GLevent : public QGLWidget
{
    Q_OBJECT

public:
    GLevent( QWidget* parent, const char* name );
    ~GLevent();
    
public slots:
	void setListNumber(int size);
	void configure(QColor c1, QColor c2,QColor c3,QColor c4,QColor c5,QColor c6,QColor c7,int r, int l, bool light, bool full=false);
	void reset();
	void makeDetector(int pattern);
             void makeTracks(QValueVector< float* > *tracklist,QColor pcolor, QColor mcolor, QColor ncolor);
	void makeLeptons(QValueVector< float* > *tracklist,QColor pColorEl,QColor mColorEl,
			 QColor pColorMu,QColor mColorMu,QColor pColorTau,QColor mColorTau);
	void makeJets(QValueVector< float* > *tracklist, QColor *jetcolor, int nJetcolor);
	void makeUserObjects(QValueVector< float* > *objectlist,int code, QColor *colors, int ncolors);
	void SetViewAngle_x(int teta);
	void SetViewAngle_y(int teta);
	void SetViewAngle_z(int teta);
	void SetPos_x(int l);
	void SetPos_y(int l);
	void SetPos_z(int l);
	void SetScale(int scle);
    
signals:
	void glViewChanged(int, int, int, int, int, int, int);
	
protected:
	void initializeGL();
	void paintGL();
	void resizeGL( int w, int h );
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

private:
	GLuint detector;
	GLuint tracks;
	GLuint leptons;
	GLuint jets;
	GLuint *userObjects;
	int listNumber;
	GLfloat xRot, yRot, zRot, scale;
	GLfloat xPos, yPos, zPos;
	int onscreenXorigin, onscreenYorigin;
	GLfloat xPos0, yPos0, zPos0;
	GLfloat xRot0, yRot0, zRot0;
	QTimer* timer;
	QColor VDETcolor;
	QColor ITCcolor;
	QColor TPCcolor;
	QColor ECALcolor;
	QColor HCALcolor;
	QColor MUONcolor;
	QColor BACKcolor;
	int energyRadius, energyLength;
	bool light_on;
};

#endif
