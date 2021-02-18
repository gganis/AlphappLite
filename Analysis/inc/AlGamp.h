//////////////////////////////////////////////////////////
//
// CLASS AlGamp:
// Concrete class for Gampec Objects, inherits from QvecBase
//
// Author :  G. Bagliesi
// modified by C. Delaere: now derive from QvecLink
//                         fixed assignement operator
//             C. Delaere: now access full PGAC info
//
///////////////////////////////////////////////////////////
 

#ifndef _ALGAMP_H_
#define _ALGAMP_H_

#include "QvecLink.h"
#include "TLorentzVector.h"

//! Gampec (photons) objects 
class AlGamp: public QvecLink {

public:
  
  //! constructor
  AlGamp();
  
  //! copy constructor
  AlGamp(const AlGamp&);

  //! get the type
  ALEPHTYPE TYPE() const {return GAMPEC;}

  //! set the fake parent
  void SetFake(AlGamp*);

  // select the information used for the Q routines
  //! use corrected Lorentz vector from Gampeck
  void UseCorrectedA4V();
  //! use standard Lorentz vector from QVEC
  void UseStandardA4V();
  //! use raw Lorentz vector (from raw Gampeck info)
  void UseRawA4V();

  // return the Lorentz vector
  //! return corrected Lorentz vector from Gampeck
  TLorentzVector GetCorrectedA4V() const;
  //! return standard Lorentz vector from QVEC
  TLorentzVector GetStandardA4V() const;
  //! return raw Lorentz vector (from raw Gampeck info)
  TLorentzVector GetRawA4V() const;
  
  // standard quality factors
  //! Energy fraction in stack 1 or 2
  float EnergyFractionInStack(const int) const;
  //! Energy fraction in the 4 central towers
  float EnergyFractionInCentralTowers() const;
  //! Distance to the closest track (cm)
  float Isolation() const;
  //! Storey flag
  int StoreyFlag() const;
  //! Quality flag
  int QualityFlag() const;

  // advanced quality factors
  //! Quality estimator (1 or 2) for photon
  float QualityEstimator(const int) const;
  //! moment (1 or 2) from CLMONS analysis
  float Moment(const int) const;
  //! Pi0 mass estmated from clmoms
  float Pi0Mass() const;
  //! Expected fraction in 4 towers
  float ExpectedEnergyFractionInCentralTowers() const;
  //! Geometrical correction
  float GeometricalCorrection() const;
  //! Zero supression correction from Coradoc
  float ZeroSupression() const;
  //! Probability to be a fake photon from Electromagnetic origine
  float FakeEcalProbability() const;
  //! Probability to be a fake photon from Hadronic origine
  float FakeHcalProbability() const;
  //! Pointer to the PGAC parent giving a fake photon
  AlGamp* ParentGivingFake() const;
  //! Flag for fake determination
  int FakeEquality() const;
  //! pointeur to PECO bank
  int PecoObject() const;
  
private:

  AlGamp* fake;

};

#endif
