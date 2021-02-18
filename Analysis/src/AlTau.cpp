//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS AlTau
// Concrete class for Tau Objects, inherits from QvecBase
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
/////////////////////////////////////////////////////////// 

#include "AlTau.h"

// default constructor : has to do something,
// since it is not created out of qvec

AlTau::AlTau()
{
  _theAssocEflw = NULL;
  _ech = 0.;
  _nch = 0;
} 

// copy constructor : NOTE: THE VECTOR OF POINTERS
// TO ITS OBJECTS IS JUST COPIED!! COULD BE DANGEROUS...

AlTau::AlTau(const AlTau& oldAt):AlJet(oldAt)
{
  _theAssocEflw = oldAt._theAssocEflw;
  _ech = oldAt._ech;
  _nch = oldAt._nch;
}

AlTau::AlTau(const AlJet& oldAt):AlJet(oldAt)
{
  _theAssocEflw = NULL;
  _ech = 0.;
  _nch = 0;
}

void AlTau::setNch(int nch) 
{ _nch = nch; }
int  AlTau::getNch() const
{ return _nch; }

void AlTau::setEch(float ech)
{ _ech = ech; }
float  AlTau::getEch() const
{ return _ech; }

// set the assoc. Eflw
void AlTau::setEflw(AlEflw* theEflw)
{
  _theAssocEflw = theEflw;
}

// get the assoc. Eflw
AlEflw* AlTau::getEflw()const
{
  return _theAssocEflw;
}



