//////////////////////////////////////////////////////////
//
// CLASS AlTrack:
// Concrete class for Tracks, inherits from QvecBase
//
// Author :  G. Bagliesi
// modified by:  C. Delaere, V. Lemaitre, O. van der Aa :
//                - now inherit form QvecLink
//                - link to new banks: FRFT and TEXS
//                - fixed assignement operator
//
///////////////////////////////////////////////////////////
 

#ifndef _ALTRACK_H_
#define _ALTRACK_H_

#include "QvecLink.h"
class AlMCtruth;
class AlEflw;
template <class Type> class AlephCollection;

//! the Alpha Track object
class AlTrack : public QvecLink {

public:

  //! constructor
  AlTrack();

  //! copy constructor
  AlTrack(const AlTrack& oldAt);

  //! assignement operator
  AlTrack& operator=(const AlTrack& oldAt);
  
  //! destructor
  ~AlTrack();
 
  //! get the type
  ALEPHTYPE TYPE() const {return TRACK;}

  // copy of additionnal ALPHA functions from QVEC
  float SIG(int x)const; //!< Triangular covariance matrix
  float SIGEE() const;   //!< Error squared on the energy
  float SIGPP() const;   //!< Error squared on the momentum
  float SIGMM() const;   //!< Error squared on the mass
  
  // copy of ALPHA functions for FRTL
  int   NV()const; //!< offset in FVCL
  int   NI()const; //!< numb. coord. in Vdet
  int   NE()const; //!< offset in FICL
  int   NT()const; //!< numb. coord. in Itc
  int   NR()const; //!< numb. coord. in following spirals in ITC
  // copy of ALPHA functions for FRFT
  float IR()const; //!< Inverse radius of curvature in x-y projection
  float TL()const; //!< tangent of dip angle
  float P0()const; //!< Phi at closest point of approach to line x=y=0
  float D0()const; //!< Closest distance of approach to line in the x-y plane (impact parameter)
  float Z0()const; //!< Z-coordinate at D0
  float AL()const; //!< Multiple scattering angle between tpc and itc
  float EM(int x)const; //!< Triangular covariance matrix
  float C2()const; //!< Chisquare of helix fit
  int   DF()const; //!< Number of degr. of freedom
  int   NO()const; //!< nopt
  // copy of ALPHA functions for TEXS
  int   SI(int seg)const; //!< Sector slot number
  float TM(int seg)const; //!< Truncated mean of dE/dx measurements
  float TL2(int seg)const; //!< Useful length of track for dE/dx
  int   NS(int seg)const; //!< Number of samples used for dE/dx
  float AD(int seg)const; //!< Average drift length of samples
  int   TN(int seg)const; //!< Pointer to track entry in TGFT
  int   SF(int seg)const; //!< saturation flag
  float TMmean()const; //!< mean of TM on all segments
  float TL2sum()const; //!< sum of TL2 on all segments
  int   NSsum()const; //!< sum of NS on all segments
  float ADmean()const; //!< mean of AD on all segments

  //! set the vector of matching MC particles 
  void  setMatchingVector(AlephCollection<AlMCtruth*>&);
  //! get the vector of matching MC particles
  AlephCollection<AlMCtruth*>* getMatchingVector()const;

  //! get the associated energy flow
  AlEflw* getEflw() {return theEflw;}
  //! set the associated energy flow
  void setEflw(AlEflw* eft) { theEflw = eft;}
  
private:
  AlephCollection<AlMCtruth*>* Match;
  AlEflw* theEflw;
};

#endif
