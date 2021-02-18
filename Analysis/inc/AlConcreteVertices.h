//////////////////////////////////////////////////////////
//
// CLASS AlConcreteVertices:
// Concrete classes for Vertex Objects,  from QvrtBase
// AlVertex is the standard ALPHA vertex (from QVRT)
// AlUsrVertex is a user vertex, copied from QVRT or handmade
//
// Author :  C. Delaere
//
///////////////////////////////////////////////////////////
 

#ifndef _ALVERTEX_H_
#define _ALVERTEX_H_

#include "QvrtBase.h"

//! standard ALPHA vertex (from QVRT)
class AlVertex : public QvrtBase {

public:
  
  //! constructor
  AlVertex();

  //! copy constructor
  AlVertex ( const AlVertex& origin);

  //! destructor
  ~AlVertex();

  //! set the pointer to QVRT
  virtual void SetPointer(QVRT* pointer);

  //! get the type
  ALEPHTYPE TYPE() const {return VERTEX;}

  // ALPHA wrapping
  //! vertex number
  virtual int KVN() const;
  //! vertex type
  virtual int KVTYPE() const;
  //! \f$ \chi^2 \f$ of the vertex fit
  virtual double QVCHIF() const;
  //! covariance matrix
  virtual TMatrixDSym QVEM() const;
  //! covariance matrix element
  virtual float QVEM(int,int) const; 
  //! momentum of the parent track at the kink position (KINK only)
  virtual float PKINK() const;
  //! Pt of the outgoing track relative to parent (KINK only)
  virtual float PTOUT() const;
  //! Pl of the outgoing track relative to parent (KINK only)
  virtual float PLOUT() const;
  //! Hypothesis of mass cuts satisfied by this decay
  virtual int   IHYPK() const;
  //! time of flight
  virtual float TOF() const;
  //! vertex volume name
  virtual char* VertexVolumeName() const;
  //! vertex mechanisme
  virtual char* VertexMechanisme() const;
  
private:

  //! pointer to QVRT
  QVRT* qvrt;
  
};

#endif

#ifndef _ALUSRVERTEX_H_
#define _ALUSRVERTEX_H_

#include "QvrtBase.h"

//! user vertex, copied from QVRT or handmade
class AlUsrVertex : public QvrtBase {

public:

  //! constructor
  AlUsrVertex();

  //! copy constructor
  AlUsrVertex(const AlUsrVertex& origin);

  //! conversion constructor
  AlUsrVertex(const AlVertex& origin);

  //! destructor
  ~AlUsrVertex();
  
  //! get the type
  ALEPHTYPE TYPE() const {return VERTEX;}

  //! set private members
  virtual void setEM(const TMatrixDSym& matrix);
  virtual void setCHIF(const double chi2);
  
  // ALPHA wrapping
  //! vertex type
  virtual int KVNTYPE() const;
  //! \f$ \chi^2 \f$ of the vertex fit
  virtual double QVCHIF() const;
  //! covariance matrix
  virtual TMatrixDSym QVEM() const;
  //! covariance matrix element
  virtual float QVEM(int,int) const;

private:

  TMatrixDSym _EM;
  double _CHI2;
    
};

#endif
