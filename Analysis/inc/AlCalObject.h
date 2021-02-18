//////////////////////////////////////////////////////////
//
// CLASS AlCalObject:
// Concrete class for ECAL and HCAL objects, 
// inherits from QvecBase
//
// Author :  C. Delaere
//
///////////////////////////////////////////////////////////
 

#ifndef _ALCALOBJECT_H_
#define _ALCALOBJECT_H_

#include "QvecLink.h"
#include <vector>

using namespace std;

//! the Alpha CalObject object
class AlCalObject : public QvecLink {

public:

  //! constructor
  AlCalObject() {}

  //! copy constructor
  AlCalObject(const AlCalObject& oldAt);

  //! assignement operator
  AlCalObject& operator=(const AlCalObject& oldAt);
  
  //! destructor
  ~AlCalObject();
 
  //! get the type
  ALEPHTYPE TYPE() const; 

  // copy of ALPHA functions for PECO and PHCO
  
  //! Returns the raw Energy.
  /** Element 0 is always the total aw Energy.
   *  for ECAL objects, elements 1 and 2 are portion 
   *  of raw energy in the corresponding stack 
   **/
  vector<float> GetRawEnergy();
  int GetRegionCode(); //!< Region code ; see note ALEPH # 88-134
  //! Correction code for the cluster analysis method;
  /** 0 : Standard
   *  1 : Crack between modules
   *  2 : Overlap between detectors
   *  3 : Dead storey
   *  (not filled in JULIA 224 for HCAL)
   **/
  int GetCorrectionCode();
  //! Relation bits
  /** 0 : no relations
   *  1 : charged track relation
   *  2 : ECAL/HCAL relation
   *  3 : Both ch tk and EC/HC relation
   **/
  int GetRelationBits();
  //! Is this flagged as an "isolated" object ?
  inline bool IsIsolated() { return _isolated; }
  //! Is this flagged as an "isolated" object ?
  inline void SetIsolation(bool isol) { _isolated = isol; }

private:
  bool _isolated;
  
};

#endif
