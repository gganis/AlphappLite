//////////////////////////////////////////////////////////
//
// Implementation of CLASS AlBjet
// Concrete class for B-Jet, inherits from AlJet
//
// Author :  C. Delaere
//
/////////////////////////////////////////////////////////// 

#include "AlBjet.h"

// default constructor : has to do something,
// since it is not created out of qvec
AlBjet::AlBjet()
{
  Bproba  = 0;
} 

AlBjet::AlBjet(const AlBjet& oldAl):AlJet(oldAl)
{
  Bproba = oldAl.Bproba;
}

AlBjet::AlBjet(const AlJet& oldAl, float proba):AlJet(oldAl)
{
  Bproba = proba;
}

void AlBjet::setBprobability(float proba) 
{ Bproba = proba; }

float  AlBjet::getBprobability() const
{ return Bproba; }

