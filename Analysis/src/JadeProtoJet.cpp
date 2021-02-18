//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS : JadeProtoJet
// Object used to compute jets with Jade
//
// Written by J.P. Wellisch, 25. Jan 1999
// adapted to Alpha++ by C.Delaere
//
///////////////////////////////////////////////////////////

#include "JadeProtoJet.h"
#include "QvecBase.h"
#include <float.h>
#include <fstream>

extern ofstream fout;

// Constructor (from QvecBase)
JadeProtoJet::
JadeProtoJet(const QvecBase & alobj)
{
  if (alobj.A4V().E()==0)
    {
      fout << "Error: bad Eflw: E=0" << endl;
      exit(1);
    }
  theFourMomentum = alobj.A4V();
  theConstituants.push_back(&alobj);
}

// Operator += (depends on the scheme)
JadeProtoJet & JadeProtoJet::
operator+=(const JadeProtoJet & aJet)
{
  if (Scheme)
    {
      // recombination according to E-Scheme.
      theFourMomentum += aJet.get4Momentum();
    }
  else
    {
      // recombination according to E0-Scheme.
      double e = theFourMomentum.E() + aJet.get4Momentum().E();
      double p2i = (theFourMomentum + aJet.get4Momentum()).Vect().Mag();
      if (p2i <= pow(10.,-14.))
	{
	  fout << " Error: Division by zero! " << endl;
	  exit(1);
	}
      theFourMomentum.SetVect(e/p2i*(theFourMomentum.Vect()+aJet.get4Momentum().Vect()));
      theFourMomentum.SetE(e);
    }

  vector<const QvecBase *> aConstituantList;
  aConstituantList = aJet.getConstituants();
  vector<const QvecBase *>::iterator constitIter;
  for(constitIter=aConstituantList.begin(); 
      constitIter!=aConstituantList.end(); 
      constitIter++)
  {
    theConstituants.push_back(*constitIter);
  }
  
  return *this;
}  

// the Metric
double JadeProtoJet::
getYTimesE2(const JadeProtoJet * aJet)
{
  double result;
  double e1 = theFourMomentum.E();
  double e2 = aJet->get4Momentum().E();
  double costh = theFourMomentum.Vect() * aJet->get4Momentum().Vect();
  costh /= theFourMomentum.Vect().Mag();
  costh /= aJet->get4Momentum().Vect().Mag();
  result = 2.*e1*e2*(1-costh);
  return result;
}

// find the Next Neighbour
vector<JadeProtoJet>::const_iterator JadeProtoJet::
findNextNeighbour(const vector<JadeProtoJet> & theProtoJets)
{
  vector<JadeProtoJet>::const_iterator i = theProtoJets.begin();
  double minDist = DBL_MAX;
  vector<JadeProtoJet>::const_iterator theNextNeighbour = theProtoJets.end();
  for (i = theProtoJets.begin(); i != theProtoJets.end(); i++)
  {
    if(&(*i)!=this)
    {
      double distance = getYTimesE2(&(*i));
      if(distance<minDist)
      {
        minDist = distance;
        theNextNeighbour = i;
      }
    }
  }
  return theNextNeighbour;
}

// the scheme (set by the algo, used by operator+=)
int JadeProtoJet::Scheme=1;

