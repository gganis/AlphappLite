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

#ifndef USERFUNCTION_H
#define USERFUNCTION_H

#include <qstring.h>
#include <qvaluevector.h>
#include <qpair.h>

class userFunction
{
    public:
    userFunction() {}
    virtual ~userFunction() {}
    void setName(QString functionName) { name = functionName; }
    void setCode(int functionCode) { code = functionCode; }
    QString getName() const { return name; }
    int getCode() const { return code; }
    QValueVector< QPair<QString, float> > getOptions() const { return options; }
    void addOption(QString optionName, float defaultValue) 
    { 
	QPair<QString, float> tmp; 
	tmp.first = optionName; tmp.second = defaultValue;
	options.push_back(tmp); 
    }
    private:
    QString name;
    int code;
    QValueVector< QPair<QString, float> > options;
};

#endif
