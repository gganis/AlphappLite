//////////////////////////////////////////////////////////
//
// CLASS AlBjet
// Concrete class for B-Jets, inherits from AlJet
//
// Author :  C. Delaere
//
/////////////////////////////////////////////////////////// 
 

#ifndef _ALBJET_H_
#define _ALBJET_H_

#include "AlJet.h"

//! the B-Jet object class
class AlBjet: public AlJet
{
 public: 

  //! default costructor
  AlBjet();

  //! copy constructor
  AlBjet(const AlBjet& oldAj);

  //! conversion constructor 
  AlBjet(const AlJet& ojet, float proba = 0);

  //! set the B probability
  void setBprobability(float);

  //! get the B probability
  float getBprobability() const;

 private:
  
  //! the B probability
  float Bproba;
};

#endif
