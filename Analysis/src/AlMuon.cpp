//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS AlMuon:
// Concrete class for AlMuon Objects, inherits from "QvecBase"
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
///////////////////////////////////////////////////////////

#include "AlMuon.h"
#include "AlEflw.h"
#include "AlTrack.h"
#include "BankClasses.h"

// default constructor : does nothing
AlMuon::AlMuon()
{  
  _theAssocEflw = NULL;
  _theAssocTrack = NULL;
}

// copy constructor :
AlMuon::AlMuon(const AlMuon& oldMU):QvecBase(oldMU)
{ 
  _theAssocEflw = oldMU._theAssocEflw;
  _theAssocTrack = oldMU._theAssocTrack;
}

// *Normal QvecBase methods (overwritten here)

void AlMuon::Lock(bool recurse)
{
  if (recurse && (_theAssocEflw != NULL) )  _theAssocEflw->Lock(1);
  if (recurse && (_theAssocTrack != NULL) )  _theAssocTrack->Lock(1);
  _locked = 1;
}
void AlMuon::unLock(bool recurse)
{
  if (recurse && (_theAssocEflw != NULL) )  _theAssocEflw->unLock(1);
  if (recurse && (_theAssocTrack != NULL) )  _theAssocTrack->unLock(1);
  _locked = 0;
}

// *Special methods for the AlMuon objects only

// set the assoc. Eflw
// Since there may be no associated Eflw,
// it is beter to set the track before.
void AlMuon::setEflw(AlEflw* theEflw)
{
  _theAssocEflw = theEflw;
  if ( _theAssocEflw != NULL ) 
   {
     //_A4V    = _theAssocEflw->A4V();
     //_qch    = _theAssocEflw->QCH();
   }
}

// get the assoc. Eflw
AlEflw* AlMuon::getEflw() const
{
  return _theAssocEflw;
}

// set the assoc. Track
// the associated track should always be != NULL
void AlMuon::setTrack(AlTrack* theTrack)
{
  _theAssocTrack = theTrack;
  if ( _theAssocTrack != NULL )
   {
     _A4V    = _theAssocTrack->A4V();
     _qch    = _theAssocTrack->QCH();
   }
}

// get the assoc. Track
AlTrack* AlMuon::getTrack()const
{
  return _theAssocTrack;
}

/*!
 * - =1 if muon flagged only by HCAL
 * - =2 if muon flagged only by MUON
 * - =3 if muon flagged by both HCAL and MUON
 * - =10 is one hit in each layer of MUON but failing tight matching criteria
 * - =11 is good HCAL pattern
 * - =12 is one and only one MUON hit
 * - =13 is good HCAL + one and only one muon
 * - =14 is good HCAL + one hit in each layer
 * - =15 is one hit in each layer of MUON passing tight matching criteria
 * - =0 not a muon
 * - <0 as above but lost shadowing contest 
 */
int   AlMuon::IF() const{ if ( _theAssocTrack != NULL && 
			  _theAssocTrack -> Qvec() -> QD != NULL && 
			  _theAssocTrack -> Qvec() -> QD -> MU != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> MU -> IF;
                      else
                        return -1; }
float AlMuon::SR() const{ if ( _theAssocTrack != NULL &&
			  _theAssocTrack -> Qvec() -> QD != NULL && 
			  _theAssocTrack -> Qvec() -> QD -> MU != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> MU -> SR;
                      else
                        return -1; }
float AlMuon::DM() const{ if ( _theAssocTrack != NULL &&
			  _theAssocTrack -> Qvec() -> QD != NULL &&
			  _theAssocTrack -> Qvec() -> QD -> MU != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> MU -> DM;
                      else
                        return -1; }
int   AlMuon::ST() const{ if ( _theAssocTrack != NULL &&
			  _theAssocTrack -> Qvec() -> QD != NULL && 
			  _theAssocTrack -> Qvec() -> QD -> MU != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> MU -> ST;
                      else
                        return -1; }
int   AlMuon::TN() const{ if ( _theAssocTrack != NULL &&
			  _theAssocTrack -> Qvec() -> QD != NULL && 
			  _theAssocTrack -> Qvec() -> QD -> MU != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> MU -> TN;
                      else
                        return -1; }


