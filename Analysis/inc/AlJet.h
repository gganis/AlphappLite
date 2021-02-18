//////////////////////////////////////////////////////////
//
// CLASS AlJet
// Concrete class for Jet Objects, inherits from QvecBase
//
// Author :  M. Hoerndl
// modified by C. Delaere:
//          - added lock, unlock, clearObjects, sig2,
//            conversion constructors from protojets
//          - fixed assignement operator
//
/////////////////////////////////////////////////////////// 
 

#ifndef _ALJET_H_
#define _ALJET_H_

#include <vector>
#include "QvecBase.h"
class DurhamProtoJet;
class JadeProtoJet;
template <class T> class AlephCollection;

//! the Jet object class
class AlJet: public QvecBase {
 public: 

  //! default constructor
  AlJet();

  //! destructor
  ~AlJet();
  
  //! copy constructor
  AlJet(const AlJet& oldAj);

  //! conversion constructor used by Durham algo
  AlJet(const DurhamProtoJet& protojet);
  //! conversion constructor used by Jade algo
  AlJet(const JadeProtoJet&   protojet);

  AlJet& operator=(const AlJet& oldAj);
  
  //! object type
  ALEPHTYPE TYPE() const {return ALJET;}

  //! get the list of constituants
  AlephCollection<AlObject*>& getObjects()const;

  //! add a constituant
  void addObject(const AlObject* a);

  //! clear the list of constituants
  void clearObjects();
 
  //! set the scheme used for reconstruction
  void setScheme(int s);
 
  //! get the scheme used for reconstruction
  int getScheme() const;

  //! set the metric used for reconstruction
  void setMetric(int m);
 
  //! get the metric used for reconstruction
  int getMetric() const;

  //! lock the jet
  void Lock(bool recurse = 0);
  //! unlock the jet
  void unLock(bool recurse = 0);

 private:
  // objects of which jet was built
  AlephCollection<AlObject*>* _objects;
  // recombination scheme
  int _scheme;
  // metric for M
  int _metric;
 };

#endif
