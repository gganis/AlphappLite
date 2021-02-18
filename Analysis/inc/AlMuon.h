//////////////////////////////////////////////////////////
//
// CLASS AlMuon:
// Concrete class for AlMuon Objects, inherits from "QvecBase"
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
///////////////////////////////////////////////////////////
 

#ifndef _ALMUON_H_
#define _ALMUON_H_

#include "QvecBase.h"
class AlEflw;
class AlTrack;

//! Alpha Muons (candidates)
class AlMuon : public QvecBase {

public:
  
  //! constructor
  AlMuon();

  //! copy constructor
  AlMuon(const AlMuon&);

  //! get the type
  ALEPHTYPE TYPE() const {return MUON;}

// * Overwrite of general QvecBase Methods

  void Lock(bool recurse = 0);     //!<  lock the muon
  void unLock(bool recurse = 0);     //!<  unlock the muon


// * AlMuon related methods

  //! set the pointer to the assoc. Eflw
  void setEflw(AlEflw* theEflw);

  //! get the pointer to the assoc. Eflw
  AlEflw* getEflw()const;

  //! set the pointer to the assoc. TRack
  void setTrack(AlTrack* theTrack);

  //! get the pointer to the assoc. Track
  AlTrack* getTrack()const;

  // copy of ALPHA functions for MUID
  int   IF()const; //!< Id Flag
  float SR()const; //!< Sum of HCAL (hit -track) residuals
  float DM()const; //!< distance between track and closest mu ch hit
  int   ST()const; //!< track number of shaoowing track (FRFT)
  int   TN()const; //!< TrackNumber

private:
  // pointer to associated Eflw
  AlEflw* _theAssocEflw;
  // pointer to associated Track
  AlTrack* _theAssocTrack;
};

#endif




