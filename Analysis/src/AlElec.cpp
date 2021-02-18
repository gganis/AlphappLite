//////////////////////////////////////////////////////////
//
// CLASS AlElec:
// Concrete class for AlElec Objects, inherits from "QvecBase"
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
///////////////////////////////////////////////////////////


#include "AlElec.h"
#include "AlEflw.h"
#include "AlTrack.h"
#include "BankClasses.h"

// default constructor 
AlElec::AlElec()
{  
  _theAssocEflw = NULL;
  _theAssocTrack= NULL;
}

// copy constructor
AlElec::AlElec(const AlElec& oldEl):QvecBase(oldEl) 
{ 
  _theAssocEflw = oldEl._theAssocEflw;
  _theAssocTrack = oldEl._theAssocTrack;
}

// *Normal QvecBase methods (overwritten here)

// specialised lock

void AlElec::Lock(bool recurse)
{
  if (recurse && (_theAssocEflw != NULL) ) _theAssocEflw->Lock(1);
  if (recurse && (_theAssocTrack != NULL) ) _theAssocTrack->Lock(1);
  _locked = 1;
}
void AlElec::unLock(bool recurse)
{
  if (recurse && (_theAssocEflw != NULL) ) _theAssocEflw->unLock(1);
  if (recurse && (_theAssocTrack != NULL) ) _theAssocTrack->unLock(1);
  _locked = 0;
}

// *Special methods for the AlElec objects only

// set the assoc. Eflw
// Since there may be no associated Eflw,
// it is beter to set the track before.
void AlElec::setEflw(AlEflw* theEflw)
{
 _theAssocEflw = theEflw;
 if ( _theAssocEflw != NULL ) 
   {
     //_A4V    = _theAssocEflw->A4V();
     //_qch    = _theAssocEflw->QCH();
   }
}

// get the assoc. Eflw
AlEflw* AlElec::getEflw() const
{
  return _theAssocEflw;
}

// set the assoc. Track
// the associated track should always be != NULL
void AlElec::setTrack(AlTrack* theTrack)
{
  _theAssocTrack = theTrack;
  if ( _theAssocTrack != NULL )
   {
     _A4V    = _theAssocTrack->A4V();
     _qch    = _theAssocTrack->QCH();
   }
}

// get the assoc. Track
AlTrack* AlElec::getTrack() const
{
  return _theAssocTrack;
}

int   AlElec::IF() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> IF;
                      else
                        return -1; }
float AlElec::R1() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> R1;
                     else
                        return -1; }
float AlElec::R2() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> R2;
                     else
                        return -1; }
float AlElec::R3() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> R3;
                     else
                        return -1; }
float AlElec::R4() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> R4;
                     else
                        return -1; }
float AlElec::R5() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> R5;
                     else
                        return -1; }
float AlElec::R6() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> R6;
                     else
                        return -1; }
float AlElec::R7() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> R7;
                     else
                        return -1; }
float AlElec::EC() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> EC;
                     else
                        return -1; }
int   AlElec::IP() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> IP;
                     else
                        return -1; }
float AlElec::E1() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> E1;
                     else
                        return -1; }
float AlElec::E2() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> E2;
                     else
                        return -1; }
float AlElec::E3() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> E3;
                     else
                        return -1; }
int   AlElec::FR() const{ if ( _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> FR;
                     else
                        return -1; }
int AlElec::PE() const{ if (  _theAssocTrack -> Qvec() -> QD != NULL && _theAssocTrack -> Qvec() -> QD -> AE != NULL )
                        return _theAssocTrack -> Qvec() -> QD -> AE -> PE;
                     else
                        return -1; }

