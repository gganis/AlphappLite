//////////////////////////////////////////////////////////
//
// CLASS QvrtBase : serves as base for vertices. 
//                  
//
// Author : C. Delaere
//
//////////////////////////////////////////////////////////

 
#ifndef _QVRTBASE_H_
#define _QVRTBASE_H_

#include "AlObject.h"
#include "AlephCollection.h"
#include "TMatrixDSym.h"
#include "BankClasses.h" 

class QvecBase;

//! base for vertices
class QvrtBase : public AlObject {

public:

  //! constructor
  QvrtBase();

  //! copy constructor
  QvrtBase(const QvrtBase&);

  //! destructor
  ~QvrtBase();

  //! compare 2 objects
  bool operator<(const QvrtBase& other) const;

  //! set the Lorentz vector
  virtual void setA4V (float x, float y, float z, float e);
  //! set the Lorentz vector
  virtual void setA4V (TLorentzVector vec) { _A4V = vec;}

  //! return the Lorentz vector
  virtual TLorentzVector A4V() const;
  
  //! get the type
  ALEPHTYPE TYPE() const {return OBJECT;}

  //! get the incoming track
  QvecBase* GetIncomingTrack() const { return inTrack; }
  //! get the outgoing tracks
  AlephCollection<QvecBase*> GetOutgoingTracks() const { return outTracks; }
  //! set the incoming track
  void SetIncomingTrack(QvecBase* trk) { inTrack = trk; }
  //! add an outgoing track
  void AddOutgoingTrack(QvecBase* trk) { outTracks.push_back(trk);}
  
  // copies of the ALPHA utility functions
  virtual float QX() const;
  virtual float QY() const;
  virtual float QZ() const;
  virtual float QP() const;
  virtual float QR() const;
  virtual float QE() const;
  virtual float QM() const;
  virtual float QCT() const;
  virtual float QCH() const;
  virtual float QPH() const;
  virtual int   KVN() const;         //!< vertex number
  virtual int   KVTYPE() const;      //!< vertex type
  virtual double QVCHIF() const;     //!< fit \f$ \chi^2 \f$
  virtual TMatrixDSym QVEM() const; //!< covariance matrix
  virtual float QVEM(int,int) const; //!< covariance matrix element
  // functions for a kink vertex only
  virtual float PKINK() const;
  virtual float PTOUT() const;
  virtual float PLOUT() const;
  virtual int   IHYPK() const;
  // functions defined for MC vertices only
  virtual float TOF() const;
  virtual char* VertexVolumeName() const;
  virtual char* VertexMechanisme() const;
  
  // the locking
  virtual void Lock(bool recurse = false); //!< lock the vertex
  virtual void unLock(bool recurse = false); //!< unlock the vertex
  virtual int isLocked() const; //!<  0 if not locked, else locked.
  
protected:

  TLorentzVector _A4V;
  int _locked;
  AlephCollection<QvecBase*> outTracks;
  QvecBase* inTrack;
  
private:
  static int NERR;
};

#endif
