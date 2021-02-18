
//////////////////////////////////////////////////////////
//
// CLASS AlMCtruth:
// Concrete class for Monte Carlo Truth Tracks, inherits from QvecBase
//
// Author :  R. Cavanaugh
//
///////////////////////////////////////////////////////////
 

#ifndef _ALMCTRUTH_H_
#define _ALMCTRUTH_H_

#include "QvecLink.h"
#include "AlephCollection.h"
#include "BankClasses.h"

/*--------------------------------------------------------------------------*/

//! Concrete class for Monte Carlo Truth Tracks
class AlMCtruth : public QvecLink
{
public:

  //! constructor
  AlMCtruth();
  //! copy constructor
  AlMCtruth(const AlMCtruth&);
  //! destructor
  ~AlMCtruth();
  //! get the type
  ALEPHTYPE TYPE() const {return MCTRUTH;}

  //! set pointer to relational. track
  void setMotherVector(   AlephCollection<AlMCtruth*> );
  //! set vector of pointers to all daughters
  void setDaughterVector( AlephCollection<AlMCtruth*> );

  //! get pointer to relational. track
  AlephCollection<AlMCtruth*> getMotherVector()const;
  //! get vector of pointers to all daughters
  AlephCollection<AlMCtruth*> getDaughterVector()const;

  //! ALEPH particle code
  int PA() const{ if (qvec) return qvec -> PA; else return -1; }
  //! Number of mother particles
  int NO() const{ if (qvec) return qvec -> NO; else return -1; }
  //! number of decay particles
  int ND() const{ if (qvec) return qvec -> ND; else return -1; }
  char* name() const;                             //!< char string for the name of particle 

private:

  AlephCollection<AlMCtruth*> Mother;                 // pointer to mother
  AlephCollection<AlMCtruth*> Daughter;               // vector of pointers to daughters

};

/*--------------------------------------------------------------------------*/

#endif
