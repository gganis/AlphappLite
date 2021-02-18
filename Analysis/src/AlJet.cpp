//////////////////////////////////////////////////////////
//
// Implementation of
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

#include "AlJet.h"
#include "DurhamProtoJet.h"
#include "JadeProtoJet.h"
#include "AlephCollection.h"

// default constructor : has to do something,
// since it is not created out of qvec
AlJet::AlJet()
{
  _objects = new AlephCollection<AlObject*>;
  _scheme = 0;
  _metric = 0;
} 

AlJet::~AlJet()
{
  delete _objects;
}

AlJet::AlJet(const AlJet& oldAl):QvecBase(oldAl)
{
  _objects = new AlephCollection<AlObject*>;
  *_objects = *(oldAl._objects);
  _scheme = oldAl._scheme;
  _metric = oldAl._metric;
}

AlJet::AlJet(const DurhamProtoJet& protojet)
{
  float charge=0;
  setA4V(protojet.get4Momentum());
  setScheme(DurhamProtoJet::Scheme);
  setMetric(0);
  vector<const QvecBase *> aCandConstituants = protojet.getConstituants();
  vector<const QvecBase *>::iterator aCandIter;
  //loop on constituants to fill Objects vector of AlJet
  _objects = new AlephCollection<AlObject*>;
  for(aCandIter=aCandConstituants.begin();
      aCandIter!=aCandConstituants.end();
      aCandIter++)
    {
      charge += (*aCandIter)->QCH();
      addObject(*aCandIter);
    }
  setQCH(charge);
}

AlJet::AlJet(const JadeProtoJet& protojet)
{
  float charge=0;
  setA4V(protojet.get4Momentum());
  setScheme(JadeProtoJet::Scheme);
  setMetric(1);
  const vector<const QvecBase *> aCandConstituants = protojet.getConstituants();
  vector<const QvecBase *>::const_iterator aCandIter;
  //loop on constituants to fill Objects vector of AlJet
  _objects = new AlephCollection<AlObject*>;
  for(aCandIter=aCandConstituants.begin();
      aCandIter!=aCandConstituants.end();
      aCandIter++)
    {
      charge += (*aCandIter)->QCH();
      addObject(*aCandIter);
    }
  setQCH(charge);
}

AlJet& AlJet::operator=(const AlJet& oldAl)
{
 *_objects = *(oldAl._objects);
 _scheme   = oldAl._scheme;
 _metric   = oldAl._metric;
 _A4V      = oldAl._A4V;
 oVertex   = oldAl.oVertex;
 eVertex   = oldAl.eVertex;
 _locked   = oldAl._locked;
 _qch      = oldAl._qch;
 return *this;
}


// specialised lock
void AlJet::Lock(bool recurse)
{
  if (recurse)
    for (vector<AlObject*>::iterator i = _objects->begin();i<_objects->end();i++)
      (*i)->Lock(1);
  _locked = 1;
}
void AlJet::unLock(bool recurse)
{
  if (recurse)
    for (vector<AlObject*>::iterator i = _objects->begin();i<_objects->end();i++)
      (*i)->unLock(1);
  _locked = 0;
}

AlephCollection<AlObject*>& AlJet::getObjects() const
{ return (AlephCollection<AlObject*>&)(*_objects); }

void AlJet::addObject(const AlObject* a) 
{ 
	_objects->push_back((AlObject*)a); 
}

void AlJet::clearObjects() 
{ _objects->clear(); }

void AlJet::setScheme(int s) 
{ _scheme = s; }

int AlJet::getScheme() const
{ return _scheme; }

void AlJet::setMetric(int m) 
{ _metric = m; }

int AlJet::getMetric() const
{ return _metric; }

