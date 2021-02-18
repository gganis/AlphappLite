//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS QvecBase : is independent of Fortran memory 
//                  and serves as base for tracks,
//                  eflows etc.
//
// Author : G. Bagliesi
// modified by C. Delaere: - modified lock (recursive)
//                         - added operator < 
//                           with a variable SortCriterium
//
//////////////////////////////////////////////////////////

#include <vector>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include "QvecBase.h"
#include "TLorentzVector.h"
using namespace std;
extern ofstream fout;

int QvecBase::NERR=0;

// constructor
QvecBase::QvecBase()
{
  _locked = 0;
  setA4V(0.,0.,0.,0.);
  _qch    =  0;
  oVertex = NULL;
  eVertex = NULL;
}

//copy constructor
QvecBase::QvecBase(const QvecBase& origin)
{
 _A4V    = origin._A4V; 
 _locked = origin._locked;
 _qch    = origin._qch;
}

// compare 2 objects...
// the criterium is fixed by the static member [SortCriterium]
// [0,1,2,3] = [px,py,pz,e]
// 4 = Pt
// default is 3 = e
bool QvecBase::operator<(const QvecBase& other) const
  {
    if(SortCriterium>3)
      return ( QPT() < other.QPT());
    else
      return (_A4V[SortCriterium] < other._A4V[SortCriterium]);
  }

float QvecBase::sign(float k)const{return k/fabs(k);}

// return the Lorentz vector
TLorentzVector QvecBase::A4V()const{ return _A4V; }

// set the Lorentz vector
void QvecBase::setA4V(float x, float y, float z, float e)
 {
   _A4V.SetPx(x);
   _A4V.SetPy(y);
   _A4V.SetPz(z);
   _A4V.SetE(e);
 }


// add two objects
QvecBase QvecBase::operator+(const QvecBase j)const
 {
  TLorentzVector A4Temp = A4V() + j.A4V(); 
  QvecBase Temp;
  Temp.setA4V(A4Temp);
  Temp.setQCH(QCH() + j.QCH());  
  return Temp;
 }

// appreviations for standard ALPHA functions
float QvecBase::QCH()const{return _qch;}    
float QvecBase::QX() const{return A4V().Px();} 
float QvecBase::QY() const{return A4V().Py();}
float QvecBase::QZ() const{return A4V().Pz();}
float QvecBase::QP() const{return A4V().Rho();}
float QvecBase::QE() const{return A4V().E();}
float QvecBase::QM() const{return A4V().M();}
float QvecBase::QCT()const{ return A4V().CosTheta();}
float QvecBase::QPH()const{ return A4V().Phi(); }
float QvecBase::QPT()const{ return A4V().Perp();} 
float QvecBase::QBETA() const{ return A4V().Rho()/A4V().E();}        
float QvecBase::QGAMMA()const{ return 1./sqrt((1.-QBETA())*(1.+QBETA())); }


float QvecBase::QMSQ2(const QvecBase j) const
{ 
  TLorentzVector A4Temp = A4V() + j.A4V();
  return A4Temp.M2();
}

float QvecBase::QM2(const QvecBase j) const
{
  TLorentzVector A4Temp = A4V() + j.A4V();
  return A4Temp.M();
}

float QvecBase::QDMSQ(const QvecBase j) const
{ 
  TLorentzVector A4Temp = A4V() - j.A4V();
  return A4Temp.M2();  
}

float QvecBase::QPPAR(const QvecBase j) const{ return QDOT3(j)/j.A4V().Rho();}  
float QvecBase::QPPER(const QvecBase j) const{ return A4V().Perp(j.A4V().Vect()); }
float QvecBase::QDOT3(const QvecBase j) const{ return A4V().Vect().Dot(j.A4V().Vect());}
float QvecBase::QDOT4(const QvecBase j) const{ return A4V().Dot(j.A4V());}

float QvecBase::QCOSA(const QvecBase j) const
{ 
  return cos(A4V().Angle(j.A4V().Vect()));
}  

float QvecBase::QDECA2(const QvecBase j)const
  { 
    double P_1[4], P_2[4];
    P_1[0] = (double) A4V().Px();            
    P_1[1] = (double) A4V().Py();            
    P_1[2] = (double) A4V().Pz();            
    P_1[3] = (double) A4V().E();             
    double PMAG = sqrt(pow(P_1[0],2) + pow(P_1[1],2) + pow(P_1[2],2));
    P_2[0] = (double) j.A4V().Px();          
    P_2[1] = (double) j.A4V().Py();          
    P_2[2] = (double) j.A4V().Pz();          
    P_2[3] = (double) j.A4V().E();            
    double PP = sqrt( pow((P_1[0]+P_2[0]),2) + pow((P_1[1]+P_2[1]),2)
                                    + pow((P_1[2]+P_2[2]),2));
    double BETA = PP / ( P_1[3]+P_2[3] );
    double PPAR = ( P_1[0] *(P_1[0]+P_2[0]) + P_1[1] *(P_1[1]+P_2[1])
                                      + P_1[2] *(P_1[2]+P_2[2]) )/PP;
    PP = PPAR - BETA * P_1[3];
    return (float) (PP / sqrt(pow(PP,2.) + (PMAG-PPAR)*(PMAG+PPAR)*(1.-BETA)*(1.+BETA)));
  }  

double QvecBase::DECAY_ANG(const QvecBase j) const
 {
  QvecBase temp= (*this) + j;
  TLorentzVector v  = temp.A4V(); 
  TLorentzVector v1 = A4V();
  v1.Boost(-v.BoostVector());
  return cos(v.Angle(v1.Vect()));
 } 

float QvecBase::QDECAN(const QvecBase j) const
  {
    float PP =A4V().Rho();
    float BETA = PP / A4V().E();
    float PPAR = (A4V().Px() * j.A4V().Px() + A4V().Py() * j.A4V().Py() + A4V().Pz() * j.A4V().Pz()) / PP;
    PP = PPAR - BETA * j.A4V().E();
    float Q_DECAN = pow(PP,2) + (j.A4V().Rho() - PPAR) * (j.A4V().Rho() + PPAR) *
                                             (1. - BETA) * (1. + BETA); 
     if (Q_DECAN > 0.)  
      { return PP / sqrt (Q_DECAN); }
     else
       {NERR++;
	if (NERR <= 10)  
            { fout << endl << "_QDECAN_ 2nd particle is not a decay product of 1st" << endl; }
        return 1.;
       }
  }  

// the locking
void  QvecBase::Lock(bool recurse)     { _locked = 1 ; }
void  QvecBase::unLock(bool recurse)   { _locked = 0 ; }
int   QvecBase::isLocked()const{ return _locked; }

// default Sort Criterium
int   QvecBase::SortCriterium = 3;

