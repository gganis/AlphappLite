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
 

#ifndef _ALEFLW_H_
#define _ALEFLW_H_

#include "QvecLink.h"
class AlTrack;

enum EFLWTYPE{ChargedTrack, Electron, Muon, V0Track, Electromagnetic, ECAL, HCAL, LCAL, SICAL };

//! Makes the link with the db for track-related objects
class AlEflw : public QvecLink {

public:
  
  //! constructor
  AlEflw();

  //! copy constructor
  AlEflw(const AlEflw&);

  //! get the type
  ALEPHTYPE TYPE() const {return EFLOW;}

  //! set the Eflow type
  void setEfType(const int& type);

  //! get the Eflow type
  EFLWTYPE  getEfType()const;

  //! set the pointer to the assoc. track
  void setTrack(AlTrack* theTrack);

  //! get the pointer to the assoc. track
  AlTrack* getTrack()const;

  //! lock the Eflw
  void Lock(bool recurse = 0);
  //! unlock the Eflw
  void unLock(bool recurse = 0);

private:

  // the Eflow type
  int _efType;
  // pointer to associated track if type <= 3
  AlTrack* _theAssocTrack;
};

#endif
