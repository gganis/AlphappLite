////////////////////////////////////////////////////////////////////
//
// Implementation of classes AlVertex and AlUsrVertex
//
// Author : C. Delaere
//
////////////////////////////////////////////////////////////////////

#include <vector>
#include <stdlib.h>
#include <math.h>
#include "AlConcreteVertices.h"
#include "TMatrixDSym.h"

////////////////////////////////////////////////////////////////////
//
// AlVertex
//
////////////////////////////////////////////////////////////////////

// constructor
AlVertex::AlVertex():QvrtBase()
{
	qvrt=NULL;
}

// copy constructor
AlVertex::AlVertex(const AlVertex& origin):QvrtBase(origin)
{
	qvrt = origin.qvrt;
}

// destructor
AlVertex::~AlVertex() {}

// set the pointer to QVRT
void AlVertex::SetPointer(QVRT* pointer)
{
	qvrt=pointer;
	setA4V(qvrt->VX,qvrt->VY,qvrt->VZ,0);
}

// ALPHA wrapping
int AlVertex::KVN() const {if(qvrt != NULL) return qvrt->VN; else return -1;}
/*!
 * vertex types are the alpha ones:
 *  - =1 for main vertex
 *  - =0 for std V0s
 *  - =2 for vertices reconstructed with KVFIT
 *  - =3 for "long V0s"
 *  - =4 for nuclear interactions
 *  - =5 for kink vertex
 */
int AlVertex::KVTYPE() const {if(qvrt != NULL) return qvrt->TY; else return -1;}
double AlVertex::QVCHIF() const {if(qvrt != NULL) return qvrt->CF; else return -1;}
TMatrixDSym AlVertex::QVEM() const
{
	TMatrixDSym tmpobj(3);
	if(qvrt != NULL)
	{				
		int cnt=0;
		for(unsigned int i=1;i<=3;i++)
			for(unsigned int j=1;j<=i;j++)
				tmpobj(i,j)=qvrt->EM[cnt++];
	}
	else
	{
		tmpobj-=1;
	}
	return tmpobj;
}
float AlVertex::QVEM(int i,int j) const
{
	if(qvrt == NULL) return -1;
	if(i*j==1) return qvrt->EM[1];
	if(i*j==2) return qvrt->EM[2];
	if(i*j==4) return qvrt->EM[3];
	if(i*j==3) return qvrt->EM[4];
	if(i*j==6) return qvrt->EM[5];
	if(i*j==9) return qvrt->EM[6];
	return -1;
}
float AlVertex::PKINK() const {if(qvrt != NULL) return qvrt->PK; else return -1;}
float AlVertex::PTOUT() const {if(qvrt != NULL) return qvrt->PT; else return -1;}
float AlVertex::PLOUT() const {if(qvrt != NULL) return qvrt->PL; else return -1;}
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
int   AlVertex::IHYPK() const {if(qvrt != NULL) return qvrt->HY; else return -1;}
float AlVertex::TOF()   const {if((qvrt != NULL)&&(qvrt->AF != NULL)) return qvrt->AF->TO; else return -1;}
char* AlVertex::VertexVolumeName() const 
{
	if((qvrt != NULL)&&(qvrt->AF != NULL))	
		return qvrt->AF->VN; 
	else 
		return "none";
}
char* AlVertex::VertexMechanisme() const
{
	if((qvrt != NULL)&&(qvrt->AF != NULL))
		return qvrt->AF->VM; 
	else 
		return "none";
}


////////////////////////////////////////////////////////////////////
//
// AlUsrVertex
//
////////////////////////////////////////////////////////////////////

// constructor
AlUsrVertex::AlUsrVertex():QvrtBase() 
{
	TMatrixDSym _tmp(3); 
        _EM = _tmp-1;
	_CHI2 = -1;
}

// copy constructor
AlUsrVertex::AlUsrVertex(const AlUsrVertex& origin):QvrtBase(origin)
{
	_EM = origin._EM;
	_CHI2 = origin._CHI2;
}

// conversion constructor
AlUsrVertex::AlUsrVertex(const AlVertex& origin):QvrtBase(origin)
{
	_EM = origin.QVEM();
	_CHI2 = origin.QVCHIF();
}

//destructor
AlUsrVertex::~AlUsrVertex() {}

// set private members
void AlUsrVertex::setEM(const TMatrixDSym& matrix)
{
	_EM = matrix;
}
void AlUsrVertex::setCHIF(const double chi2)
{
	_CHI2 = chi2;
}

// alpha wrapping
/*!
 * vertex types are the alpha ones:
 *  - =1 for main vertex
 *  - =0 for std V0s
 *  - =2 for vertices reconstructed with KVFIT
 *  - =3 for "long V0s"
 *  - =4 for nuclear interactions
 *  - =5 for kink vertex
 */
int AlUsrVertex::KVNTYPE() const {return 6;}
double AlUsrVertex::QVCHIF() const {return _CHI2;}
TMatrixDSym AlUsrVertex::QVEM() const {return _EM;}
float AlUsrVertex::QVEM(int i,int j) const {return _EM(i,j);}

