////////////////////////////////////////////////////////////////////
//
// Implementation of class QvrtBase
//
// Author : C. Delaere
//
////////////////////////////////////////////////////////////////////


#include <vector>
#include <stdlib.h>
#include <math.h>
#include "QvrtBase.h"

int QvrtBase::NERR=0;

// constructor
QvrtBase::QvrtBase()
{
	_locked = 0;
	setA4V(0.,0.,0.,0.);
}

// copy constructor
QvrtBase::QvrtBase(const QvrtBase& origin)
{
	_locked = origin._locked;
	_A4V = origin._A4V;
}

// destructor
QvrtBase::~QvrtBase() {}

// compare 2 objects
// the criterium is the distance to the origin.
bool QvrtBase::operator<(const QvrtBase& other) const
{
	return (A4V().Rho()<other.A4V().Rho());
}

// set the Lorentz vector
void QvrtBase::setA4V(float x, float y, float z, float e)
{
	_A4V.SetX(x);
	_A4V.SetY(y);
	_A4V.SetZ(z);
	_A4V.SetT(e);
}

// return the Lorentz vector
TLorentzVector QvrtBase::A4V() const {return _A4V; }

// standard ALPHA functions
float QvrtBase::QX() const { return _A4V.X();}
float QvrtBase::QY() const { return _A4V.Y();} 
float QvrtBase::QZ() const { return _A4V.Z();}
float QvrtBase::QP() const { return 0;}
float QvrtBase::QR() const { return _A4V.Rho();}
float QvrtBase::QE() const { return 0;}
float QvrtBase::QM() const { return 0;}
float QvrtBase::QCT() const { return _A4V.CosTheta();}
float QvrtBase::QCH() const { return 0;}
float QvrtBase::QPH() const { return _A4V.Phi();}
int   QvrtBase::KVN() const { return -1;} 
/*!
 * vertex types are the alpha ones:
 *  - =1 for main vertex
 *  - =0 for std V0s
 *  - =2 for vertices reconstructed with KVFIT
 *  - =3 for "long V0s"
 *  - =4 for nuclear interactions
 *  - =5 for kink vertex
 */
int   QvrtBase::KVTYPE() const { return -1;} 
double QvrtBase::QVCHIF() const { return -1;}
TMatrixDSym QvrtBase::QVEM() const { return TMatrixDSym(3);}
float QvrtBase::QVEM(int i,int j) const { return -1;}
// functions for a kink vertex only
float QvrtBase::PKINK() const { return -1;}
float QvrtBase::PTOUT() const { return -1;}
/*! Hypothesis of mass cut atisfied by this decay:
 * - =1  \f$ \pi \to \mu\nu \f$
 * - =2  \f$ K \to \mu\nu \f$
 * - =3  \f$ K \to \pi\pi^0 \f$
 * - =4  \f$ \Sigma^+ \to p \pi^0 \f$
 * - =5  \f$ \Sigma^+ \to n\pi^+ \f$
 * - =6  \f$ \Sigma^- \to n\pi^- \f$
 * - =7  \f$ \Xi^- \to \lambda\pi^- \f$
 * - =8  \f$ \Omega^- \to \lambda K^- \f$
 * - =9  \f$ \Omega^- \to \Xi^0 \pi^- \f$
 * - =10 \f$ \Omega^- \to \Xi^- \pi^0 \f$
 * - =0  none of the above is satisfied
 */
float QvrtBase::PLOUT() const { return -1;}
int   QvrtBase::IHYPK() const { return -1;}
// functions defined for MC vertices only
float QvrtBase::TOF() const { return -1;}
char* QvrtBase::VertexVolumeName() const { return "none";}
char* QvrtBase::VertexMechanisme() const { return "none";}
                 
// the locking
void QvrtBase::Lock(bool recurse) { _locked=1;}
void QvrtBase::unLock(bool recurse) { _locked=0;}
int QvrtBase::isLocked() const { return _locked;}

