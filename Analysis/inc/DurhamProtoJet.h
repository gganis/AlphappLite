#ifndef DurhamProtoJet_h
#define DurhamProtoJet_h

//////////////////////////////////////////////////////////
//
// CLASS : DurhamProtoJet
// Object used to compute jets with Durham
//
// Written by J.P. Wellisch, 25. Jan 1999
// adapted to Alpha++ by C.Delaere
//
///////////////////////////////////////////////////////////

#include <vector>
#include "TLorentzVector.h"
using namespace std;
class QvecBase;

//! Object internaly used to compute jets with Durham
class DurhamProtoJet
{
  public:
  //! Constructor (from QvecBase)
  DurhamProtoJet(const QvecBase & alobj);
  //! Operator += (depends on the scheme)
  DurhamProtoJet & operator+=(const DurhamProtoJet & aJet);
  //! the Metric
  double getYTimesE2(const DurhamProtoJet * aJet);
  //! find the Next Neighbour
  vector<DurhamProtoJet>::const_iterator findNextNeighbour(const vector<DurhamProtoJet> & theProtoJets);
  //! get constituants
  const vector<const QvecBase *> getConstituants() const {return theConstituants;}  
  //! the scheme (set by the algo, used by operator+=)
  static int Scheme;
  //! get four momentum vector
  const TLorentzVector & get4Momentum() const { return theFourMomentum;}
  
  private:
  TLorentzVector theFourMomentum;
  vector<const QvecBase *> theConstituants;

};

#endif




