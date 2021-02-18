//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS : DurhamProtoJet
// Object used to compute jets with Durham
//
// Written by J.P. Wellisch, 25. Jan 1999
// adapted to Alpha++ by C.Delaere
//
///////////////////////////////////////////////////////////

#include "DurhamProtoJet.h"
#include "QvecBase.h"
#include <float.h>
#include <fstream>
extern ofstream fout;

// Constructor (from QvecBase)
DurhamProtoJet::
DurhamProtoJet(const QvecBase & alobj)
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
DurhamProtoJet & DurhamProtoJet::
operator+=(const DurhamProtoJet & aJet)
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
double DurhamProtoJet::
getYTimesE2(const DurhamProtoJet * aJet)
{
  double result;
  double e1 = theFourMomentum.E();
  double e2 = aJet->get4Momentum().E();
  double costh = theFourMomentum.Vect() * aJet->get4Momentum().Vect();
  costh /= theFourMomentum.Vect().Mag();
  costh /= aJet->get4Momentum().Vect().Mag();
  result = e1;
  if(e1>e2) result = e2;
  result *= result;
  result *= 2.*(1-costh);
  return result;
}

// find the Next Neighbour
vector<DurhamProtoJet>::const_iterator DurhamProtoJet::
findNextNeighbour(const vector<DurhamProtoJet> & theProtoJets)
{
  vector<DurhamProtoJet>::const_iterator i = theProtoJets.begin();
  double minDist = DBL_MAX;
  vector<DurhamProtoJet>::const_iterator theNextNeighbour = theProtoJets.end();
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
int DurhamProtoJet::Scheme=1;

