//////////////////////////////////////////////////////////
//
// CLASS AlTau
// Concrete class for Tau Objects, inherits from QvecBase
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
/////////////////////////////////////////////////////////// 
 

#ifndef _ALTAU_H_
#define _ALTAU_H_

#include "AlJet.h"
class AlEflw;

//! Alpha Taus (candidates)
class AlTau: public AlJet 
{
 public: 

  //! default constructor
  AlTau();

  //! copy constructor
  AlTau(const AlTau& oldAt);

  //! copy constructor
  AlTau(const AlJet& oldAt);

  //! get the object type 
  ALEPHTYPE TYPE() const {return ALTAU;}
   
  //! set the number of charged tracks
  void  setNch(int nch);
  
  //! get the number of charged tracks
  int   getNch()const;

  //! set the energy of charged tracks
  void  setEch(float ech);
 
  //! get the energy of charged tracks
  float getEch()const;

  //! set the pointer to the assoc. Eflw
  void setEflw(AlEflw* theEflw);

  //! get the pointer to the assoc. Eflw
  AlEflw* getEflw()const;

 private:
  // number of charged particules
  int _nch;
  // sum of charged tracks energies
  float _ech;  
  // the associated Eflw
  AlEflw* _theAssocEflw;
 };

#endif

