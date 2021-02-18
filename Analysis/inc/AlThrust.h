//////////////////////////////////////////////////////////
//
// CLASS AlThrust
// Concrete class for Thrust Objects, inherits from QvecBase
//
// Author :  M. Hoerndl
// modified by C. Delaere: fixed assignement operator
//
///////////////////////////////////////////////////////////


#ifndef _ALTHRUST_H_
#define _ALTHRUST_H_

#include "QvecBase.h"
#include "TVector3.h"

//! Thrust Objects 
class AlThrust: public QvecBase {
 
 public:
  
  //! default constructor
  AlThrust();
  
  //! copy constructor
  AlThrust(const AlThrust&);

  //! get the object type
  ALEPHTYPE TYPE() const {return ALTHRUST;}
  
  //! get the thrust direction
  TVector3 getThrustDirection()const;
  
  //! get the thrust value
  float getThrustValue()const;  
};

#endif 
