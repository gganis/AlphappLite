//////////////////////////////////////////////////////////
//
// CLASS QvecLink : holds pointer to QVEC, is independent
//                  of Fortran memory and serves as base
//                  for tracks, eflows and gampecs.
//
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
//////////////////////////////////////////////////////////

 
#ifndef _QVECLINK_H_
#define _QVECLINK_H_

#include "QvecBase.h"
class QVEC;

//! holds pointer to QVEC
/*!
 * holds pointer to QVEC, is independent
 * of Fortran memory and serves as base
 * for tracks, eflows and gampecs.
 */
class QvecLink : public QvecBase  { 

public:

  //! constructor
  QvecLink();

  //! copy constructor
  QvecLink(const QvecLink & origin);
 
  //! destructor
  virtual ~QvecLink(){}

  //! set the pointer to the QVEC object
  virtual void SetPointer(QVEC* qvec);

  //! get  the pointer to the QVEC object
  virtual QVEC* Qvec() const {return qvec;}
  virtual float QDB()const;
  virtual float QZB()const;
  virtual float QDBS2()const;
  virtual float QZBS2()const;
  virtual float QBC2()const;
  virtual int   ITK()const;

protected:
  // pointer to QVEC
  QVEC* qvec;
};

#endif

