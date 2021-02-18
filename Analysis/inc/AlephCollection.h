////////////////////////////////////////////////////////
// AlephCollection.h
// Subclass of vector.h
//
// Author: Dan Wallin (with contributions from M. Hoerndl)
// modified by:  C. Delaere, V. Lemaitre, O. van der Aa :
//                 - added Pointers method
//                 - added Leptons filter algos
//                 - added GetSum and GetMiss
//                 - new Jet Algos (form Orca)
//
////////////////////////////////////////////////////////

#ifndef __AlephCollection__
#define __AlephCollection__

#include <iostream>
#include <vector>
#include <algorithm>
#include "AlObject.h"
#include "QvecBase.h"
#include "AlThrust.h"
#include "AlJet.h"
#include "AlBjet.h"
#include "AlTau.h"
#include "AlEflw.h"
#include "AlElec.h"
#include "AlMuon.h"

#include "TLorentzVector.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"

using namespace std;

// Prevents the compiler from generating several copies of 
// methods during the precompiling stage, which leads to longer
// compile time. 
#if defined(__GNUC__)
#pragma interface
#endif

// some additional possible naming
#define AlephSelection AlephCollection;

//! The main ALPHA++ tool...
/*!
 * derives from STL vector and owns the main algorithmes
 */
using namespace std;
template <class Type>
class AlephCollection: public vector<Type>{
  
public:  
  
  //! Default Constructor
  AlephCollection::AlephCollection():vector<Type>(){}
  
  //! Another Constructor
  AlephCollection::AlephCollection(int i):vector<Type>(i){}
  
  //! Add two vectors to each other
  void append(AlephCollection<Type>);
  
  //! Erase an element from the vector, should be used in loops
  void looperase(typename AlephCollection<Type>::iterator &it){
    typename AlephCollection::iterator tmp=it;
    it--;
    erase(tmp);
  }
  
  //! Create a vector of pointers from a vector of objects
  AlephCollection<Type *> Pointers()
    {
      AlephCollection<Type *> out;
      for (unsigned int i=0;i<size();i++) out.push_back(&((*this)[i]));
      return out;
    }

  // The Thrust algorithm
  AlThrust AThrust() const;

  // Sphericity, aplanarity and planarity
  float Sphericity() const;
  float Aplanarity() const;
  float Planarity()  const;
  
  // DurhamJet (jet clustering)
  AlephCollection<AlJet> DurhamJet(float theYcut, int Scheme=1, float Qelep=0.) const;
  // JadeJet (jet clustering)
  AlephCollection<AlJet> JadeJet(float theYcut, int Scheme=1, float Qelep=0.) const;
  // DurhamYn
  vector<float> DurhamYn(int, float Qelep=0.) const;

  // ATauJn (Tau candidates generator)
  AlephCollection<AlTau> ATauJn(vector<float> argus, float Qelep=0) const;

  // Filter Leptons
  void FilterMu(vector<float>);
  void FilterEl(const AlephCollection<AlMuon *>&, vector<float>);
  void FilterTau(vector<float>);

  // General methods
  QvecBase GetSum() const;
  QvecBase GetMiss(float QELEP=0.) const;

};

#if defined(__GNUC__)
#pragma implementation
#endif
// Implementations...

// Appends a vector of a certain kind to another vector
template <class Type>
void AlephCollection<Type>::append(AlephCollection<Type> cv)
{
  for(typename AlephCollection<Type>::iterator i=cv.begin();i<cv.end();i++) push_back(*i);
}

//! Sum all the elements
template <class Type> 
QvecBase AlephCollection<Type>::GetSum()  const
{
  QvecBase Psum;
  TLorentzVector P_4sum(0.,0.,0.,0.);
  float chtot=0.;
  typename AlephCollection<Type>::const_iterator it;
  for (it=begin();it<end();it++)
    if (!((*it)->isLocked()))
      { 
	if ((*it)->TYPE() == ALTHRUST ) 
	  { 
	    cout << "WARNING Type is AlThrust: type not supported !" << endl; 
	    exit(1);
	  }
	P_4sum += (*it)->A4V(); 
	chtot += (*it)->QCH();
      }
  Psum.setA4V(P_4sum);
  Psum.setQCH(chtot);
  return Psum;
}

//! Find the missing object
template <class Type> 
QvecBase AlephCollection<Type>::GetMiss(float QELEP) const
{
  if(QELEP==0.) cout << "WARNING, Pmiss calculated with QELEP=0 !" << endl;
  QvecBase Pmiss;
  TLorentzVector P_4miss(0.,0.,0.,QELEP);
  float chtot=0.;
  typename AlephCollection<Type>::const_iterator it;
  for (it=begin();it<end();it++) 
    if (!((*it)->isLocked()))
      { 
	if ((*it)->TYPE() == ALTHRUST ) 
	  { 
	    cout << "WARNING Type is AlThrust: type not supported !" << endl; 
	    exit(1);
	  }
	P_4miss -= (*it)->A4V(); 
	chtot -= (*it)->QCH();
      }
  P_4miss.SetE(max(P_4miss.E(),P_4miss.Rho()));
  Pmiss.setA4V(P_4miss);
  Pmiss.setQCH(chtot);
  return Pmiss;
}

// AlThrust algorithm
#include "AlephAlgoThrust.h"

// Jet clustering
#include "AlephDurhamAlgo.h"
#include "AlephJadeAlgo.h"

// Leptons algorithmes
#include "AlephAlgoLeptons.h"

#endif





