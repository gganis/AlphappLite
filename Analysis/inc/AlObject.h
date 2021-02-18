//////////////////////////////////////////////////////////
//
// CLASS AlObject:
// Abstract interface to the Aleph Objects
//
// Author :  G. Bagliesi
//
///////////////////////////////////////////////////////////
 

#ifndef _ALEPHOBJECT_H_
#define _ALEPHOBJECT_H_ 

#include "TLorentzVector.h"

//! list all possible object types
enum ALEPHTYPE {OBJECT,ALPHA_QVEC,ALPHA_QVRT,TRACK,EFLOW,ECALE,HCALE,GAMPEC,VERTEX,ALJET,ALTHRUST,MUON,ELEC,ALTAU,MCTRUTH,USERTRACK}; 

//! Abstract interface to the Aleph Objects (tracks and vertices)
class AlObject {

 public:

  virtual float QP() const = 0;     
  virtual float QX() const = 0;
  virtual float QY() const = 0;
  virtual float QZ() const = 0;
  virtual float QE() const = 0;
  virtual float QM() const = 0;
  virtual TLorentzVector A4V() const = 0;  
  virtual void setA4V(float x, float y, float z, float e) = 0;
  virtual void setA4V(TLorentzVector vec) = 0;
  virtual float QCH() const = 0;
  virtual int  isLocked() const = 0;
  virtual void Lock(bool) = 0;
  virtual void unLock(bool) = 0;
  virtual ALEPHTYPE TYPE() const {return OBJECT;}       

  virtual ~AlObject();

};

#endif

