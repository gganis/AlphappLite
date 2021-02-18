//////////////////////////////////////////////////////////
// implementation of the AlThrust class methods
// 
// Author :  M. Hoerndl
//
///////////////////////////////////////////////////////////


#include "AlThrust.h"

// default constructor : has to do something,
// since it is not created out of qvec
AlThrust::AlThrust() {}

// copy constructor :Everything is set by the QvecBase copy constructor
AlThrust::AlThrust(const AlThrust& oldT):QvecBase(oldT) {}

TVector3 AlThrust::getThrustDirection() const
{ return A4V().Vect(); }

float AlThrust::getThrustValue() const
{ return A4V().E(); }

 
