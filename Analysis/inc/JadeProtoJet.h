#ifndef JadeProtoJet_h
#define JadeProtoJet_h

//////////////////////////////////////////////////////////
//
// CLASS : JadeProtoJet
// Object used to compute jets with Jade
//
// Written by J.P. Wellisch, 25. Jan 1999
// adapted to Alpha++ by C.Delaere
//
///////////////////////////////////////////////////////////

#include <vector>
#include "TLorentzVector.h"
using namespace std;
class QvecBase;

//! Object internaly used to compute jets with Jade
class JadeProtoJet
{
  public:
  //! Constructor (from QvecBase)
  JadeProtoJet(const QvecBase & alobj);
  //! Operator += (depends on the scheme)
  JadeProtoJet & operator+=(const JadeProtoJet & aJet);
  //! the Metric
  double getYTimesE2(const JadeProtoJet * aJet);
  //! find the Next Neighbour
  vector<JadeProtoJet>::const_iterator findNextNeighbour(const vector<JadeProtoJet> & theProtoJets);
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




