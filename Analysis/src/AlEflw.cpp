//////////////////////////////////////////////////////////
//
// CLASS AlEflw:
// Concrete class for Eflow Objects, inherits from QvecBase
//
// Author :  G. Bagliesi
// modified by C. Delaere: now derive from QvecLink
//                         added lock and unlock
//                         fixed assignement operator
//
///////////////////////////////////////////////////////////

#include "AlEflw.h"
#include "AlTrack.h"

// default constructor :
AlEflw::AlEflw()  {}

// copy constructor :
AlEflw::AlEflw(const AlEflw& oldE):QvecLink(oldE) 
{
   _efType = oldE._efType;
   _theAssocTrack = oldE._theAssocTrack;
}

// set the Eflow type
void AlEflw::setEfType(const int& type)
{
  _efType = type;
}


// get the Eflow type
/*!
 * Eflow types are:
 * - =0 charged track 
 * - =1 electron
 * - =2 muon
 * - =3 track from std V0
 * - =4 electromagnetic
 * - =5 ECAL hadron/residual
 * - =6 HCAL element
 * - =7 LCAL element
 * - =8 SICAL element
 */
EFLWTYPE AlEflw::getEfType() const
{
  return (EFLWTYPE)_efType;
}

// set the assoc. track
void AlEflw::setTrack(AlTrack* theTrack)
{
  _theAssocTrack = theTrack;
}

// get the assoc. track
AlTrack* AlEflw::getTrack() const
{
  return _theAssocTrack;
}

// specialised lock
void AlEflw::Lock(bool recurse)
{
  if (recurse && (_theAssocTrack != NULL) ) _theAssocTrack->Lock(1);
  _locked = 1;
}
void AlEflw::unLock(bool recurse)
{
  if (recurse && (_theAssocTrack != NULL) ) _theAssocTrack->unLock(1);
  _locked = 0;
}

