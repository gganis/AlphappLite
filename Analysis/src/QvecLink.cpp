//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS QvecLink : holds pointer to QVEC, is independent
//                  of Fortran memory and serves as base
//                  for tracks, eflows and gampecs.
//
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
//////////////////////////////////////////////////////////

#include "QvecLink.h"
#include "BankClasses.h"

// constructor
QvecLink::QvecLink()
{
  qvec = NULL;
}

//copy constructor
QvecLink::QvecLink(const QvecLink& origin):QvecBase(origin)
{
  qvec = origin.qvec;
}

// set the pointer to the memory
void  QvecLink::SetPointer(QVEC* pointer) 
{
  qvec = pointer;
  setA4V(qvec->QX, qvec->QY, qvec->QZ, qvec->QE);
  _qch = qvec->QCH;
}

float QvecLink::QDB() const   { return qvec->DB; }
float QvecLink::QZB() const   { return qvec->ZB; }
float QvecLink::QDBS2() const { return qvec->SD; }
float QvecLink::QZBS2() const { return qvec->SZ; }
float QvecLink::QBC2() const  { return qvec->CB; }
int   QvecLink::ITK()  const  { return qvec->TN; }
