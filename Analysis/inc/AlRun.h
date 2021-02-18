//////////////////////////////////////////////////////////
//
// CLASS AlRun 
// Concrete class for AlRun Object 
//
//
///////////////////////////////////////////////////////////
 

#ifndef _ALRUN_H_
#define _ALRUN_H_

#include "BankClasses.h"

//! Concrete class for Run Object
/*!
 gives acces to general run-related information
*/
class AlRun {

public:
  
  //! constructor
  AlRun();

  //! copy constructor
  AlRun(const AlRun&);

  //! Energy
  int Energy() const;

  //! Experiment number
  int ExperimentNumber() const;

  //! run number
  int number() const;

  //! run type
  int type() const;

  //! set the pointer to QHAC
  void SETqhac(QHAC* bank) {qhac = bank;}
  //! set the pointer to QEXT
  void SETqext(QEXT* bank) {qext = bank;}

  //! get the pointer to QHAC
  QHAC* GETqhac() {return qhac;}
  //! get the pointer to QEXT
  QEXT* GETqext() {return qext;}
  
private:
  // direct acces to the banks
  EVEH* EventHeader() const {return qhac->EH;}
  RLEP* LepHeader()   const {return qext->LP;}
  RUNH* RunHeader()   const {return qhac->RH;}
  ASIM* MCdate()      const {return qhac->AS;} 
  // pointer to associated bank of interest 
  QHAC* qhac;
  QEXT* qext;
};

#endif


