//////////////////////////////////////////////////////////
//
// CLASS AlElec:
// Concrete class for AlElec Objects, inherits from "QvecBase"
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
///////////////////////////////////////////////////////////
 

#ifndef _ALELEC_H_
#define _ALELEC_H_

#include "QvecBase.h"
class AlEflw;
class AlTrack;

//! Alpha Electrons (candidates)
class AlElec : public QvecBase {

public:
  
  //! constructor
  AlElec();

  //! copy constructor
  AlElec(const AlElec&);

  //! get the type
  ALEPHTYPE TYPE() const {return ELEC;}

// * Overwrite of general QvecBase Methods

  //! lock the e
  void Lock(bool recurse = 0);
  //! unlock the e
  void unLock(bool recurse = 0);

// * AlElec related methods

  //! set the pointer to the assoc. Eflw
  void setEflw(AlEflw* theEflw);

  //! get the pointer to the assoc. Eflw
  AlEflw* getEflw()const;

  //! set the pointer to the assoc. Track
  void setTrack(AlTrack* theTrack);

  //! get the pointer to the assoc. Track
  AlTrack* getTrack()const;

  // copy of ALPHA functions for EIDT
  //! Quality Flag for ID 0=OK, 1=crack, 2=overlap
  int   IF()const;
  //! R1 = (E_cluster-P_track)/reso(E,P); estimator(energy balance)
  float R1()const;
  //! R2 = (X-X0)/sigma(X); estimator(compactness) 
  float R2()const;
  //! R3 = (a-a0)/sigma(a); estimator(longitud. profile) 
  float R3()const;
  //! R4 = (b-b0)/sigma(b); estimator(longitud. profile)
  float R4()const;
  //! R5 = I-I0/SIGMA(I);   estimator(de/dx)
  float R5()const;
  float R6()const;
  float R7()const;
  //! corrected energy with elec. hyp.
  float EC()const;
  //! R2 > -3. && -2.4 < R3 < 3. --> IP=0 if "non electron", IP=1 if electron
  int   IP()const;
  //!  raw energy in centered storeys stack 1 
  float E1()const;
  //! raw energy in centered storeys stack 2
  float E2()const;
  //! raw energy in centered storeys stack 3 
  float E3()const;
  //! Row index in FRFT of the fitted track
  int   FR()const;
  //! Row index in PECO of the electromagnetic calobject
  int   PE()const;

private:
  // pointer to associated Eflw
  AlEflw* _theAssocEflw;
  // pointer to associated Track
  AlTrack* _theAssocTrack;
};

#endif


