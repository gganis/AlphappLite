//////////////////////////////////////////////////////////
//
// CLASS AlUserTrack:
// Class for user tracks, inherits from QvecBase
//
// Author :  K. Huettmann
//
///////////////////////////////////////////////////////////


#ifndef _ALUSERTRACK_H_
#define _ALUSERTRACK_H_

#include "AlephCollection.h"
#include "QvecBase.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"

class AlUserTrack: public QvecBase {
public:

  // default constructor
  AlUserTrack();

  //copy constructor
  AlUserTrack(const AlUserTrack& rhsAt);

  // defined in AlObject.h
  ALEPHTYPE TYPE() const {return USERTRACK;}

  AlephCollection<AlObject*>& getDaughters();
  void addDaughter(AlObject* d);

  // Various ways to access track helix covariance matrix
  float EM(int i) const;
  float EM(int m, int n) const;  
  TMatrixDSym& EM();
  void setEM(int i, float val);
  void setEM(const TMatrixDSym& em);

  // Various ways to access kinematic track covariance matrix
  float SIG(int i) const;            // Triangular covariance matrix. This one is compatible with AlTrack::SIG(int )
  float EM_kin(int m, int n) const;  
  TMatrixDSym& EM_kin();
  void setEM_kin(int i, float val);
  void setEM_kin(const TMatrixDSym& em);
  float SIGEE() const;   //!< Error squared on the energy
  float SIGPP() const;   //!< Error squared on the momentum
  float SIGMM() const;   //!< Error squared on the mass

  // Various ways to access track-vertex correlation matrix
  float corrMatrix(int m, int n) const;  
  TMatrixD& corrMatrix();
  void setCorrMatrix(int i, int j, float val);
  void setCorrMatrix(const TMatrixD& cm);

  virtual ~AlUserTrack(){}

private:
  // pointers to objects the track was built of
  AlephCollection<AlObject*> _daughters;
  // track helix covariance matrix (5 x 5: IR, TL, P0, D0, Z0)
  TMatrixDSym _EM;
  // Kinematic track covariance matrix (4 x 4, (E,p))
  TMatrixDSym _EM_kin;
  // Correlation matrix track-vertex
  TMatrixD _corr_track_vertex;

};
#endif
 
