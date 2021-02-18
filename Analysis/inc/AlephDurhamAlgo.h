#include "DurhamProtoJet.h"
#include <float.h>

// From Orca 
// Written by J.P. Wellisch, 25. Jan 1999
// Adapted to Alpha++ by C. Delaere
//              Added : - DurhamYn
//                      - fixed number of jets

  //! Durham jet clustering (From Orca)
  /*!
    Routine to calculate number of jet and jet momenta for a given Ycut and
    a given AlephCollection of pointers to AlObjects
    Input:   
         -  float theYcut      :       Ycut value
         -  int Scheme         :       Recombination Scheme
	 
    Scheme = 0 : E0 - Scheme
    Scheme = 1 : E - Scheme
    Enter a negative valut of theYCut to obtain -theYCut jets

    Output: AlephCollection<AlJet> jets    Vector of Jets
  */
template <class Type>
AlephCollection<AlJet> AlephCollection<Type>::DurhamJet(float theYCut, int Scheme, float Qelep) const
{
  // update the static member of DurhamProtoJet: used to add 2 protojets
  DurhamProtoJet::Scheme = Scheme;
  // the result...
  AlephCollection<AlJet> result;
  // the temp vector to work
  vector<DurhamProtoJet> theProtoJets;
  typename AlephCollection<Type>::const_iterator i = begin();
  double totalEnergy = 0.;
  // make a copy of the original vector (as protojets) and compute Evis 
  for (i = begin(); i != end(); i++)
    if (!((*i)->isLocked()))
      {
	totalEnergy += (*i)->A4V().E() ;
	DurhamProtoJet aProtoJet(*(*i));
	theProtoJets.push_back(aProtoJet);
      }
  if(Qelep != 0.) totalEnergy=Qelep;
  int Np = theProtoJets.size();
  double totalE2 = totalEnergy*totalEnergy;

  // Check if # of particles is o.k.
  if (Np < 2)
    {
      result.resize(0);
      fout << 
	"there is only one particle, therefore Jet Algorithm cannot be performed" 
	   << endl;
      return result;
    }

  double minY = 0;
  int iYcut = (int) theYCut;
  // Main loop
  while(((minY<theYCut) && (theYCut >= 0.)) || 
	(((int)theProtoJets.size() > -iYcut) && (theYCut < 0.)))
  {
    minY = DBL_MAX;
    typename vector<DurhamProtoJet>::iterator aCandidate ;
    typename vector<DurhamProtoJet>::iterator aNextNeighbour ;
    typename vector<DurhamProtoJet>::iterator i1 = theProtoJets.begin();
    for(i1 = theProtoJets.begin(); i1!= theProtoJets.end(); i1++)
      {
	double y = DBL_MAX;
	typename vector<DurhamProtoJet>::const_iterator aNeighbour = i1->findNextNeighbour(theProtoJets);
	if(aNeighbour != theProtoJets.end()) y = i1->getYTimesE2(&(*aNeighbour))/totalE2;
	if(y<minY) 
	  {
	    minY = y;
	    aCandidate = i1;
	    aNextNeighbour = theProtoJets.begin() + (aNeighbour - theProtoJets.begin());
	  }
      }
    if(((minY<theYCut) && (theYCut >= 0.)) || 
       (((int)theProtoJets.size() > -iYcut) && (theYCut < 0.)))
      {
	*aCandidate += *aNextNeighbour;
	theProtoJets.erase(aNextNeighbour);
      }
  }
  
  // build the result from the protojets 
  // (uses the conversion constructor of AlJet)
  typename vector<DurhamProtoJet>::iterator aJetList;
  for(aJetList = theProtoJets.begin();
      aJetList != theProtoJets.end();
      aJetList++)
    result.push_back(*aJetList);
  // return an AlephCollection of AlJet
  return result;
}

  //! computes the set of Yn using the Durham metric
  /*!
    Routine to calculate number of jet and jet momenta for a given Ycut and
    a given AlephCollection of pointers to AlObjects
    Input:   int Scheme                Recombination Scheme
                         Scheme = 0 : E0 - Scheme
                         Scheme = 1 : E - Scheme

    Output: Vector<Real> Yn            Vector of critical Ycuts
  */
template <class Type>
vector<float> AlephCollection<Type>::DurhamYn(int Scheme, float Qelep) const
{
  // update the static member of DurhamProtoJet: used to add 2 protojets
  DurhamProtoJet::Scheme = Scheme;
  // the temp vector to work
  vector<DurhamProtoJet> theProtoJets;
  typename AlephCollection<Type>::const_iterator i = begin();
  double totalEnergy = 0.;
  // make a copy of the original vector (as protojets) and compute Evis 
  for (i = begin(); i != end(); i++)
    if (!((*i)->isLocked()))
      {
	totalEnergy += (*i)->A4V().E() ;
	DurhamProtoJet aProtoJet(*(*i));
	theProtoJets.push_back(aProtoJet);
      }
  if(Qelep != 0.) totalEnergy=Qelep;
  int Np = theProtoJets.size();
  // the result...
  vector<float> Yn(Np-1);
  double totalE2 = totalEnergy*totalEnergy;

  // Check if # of particles is o.k.
  if (Np < 2)
    {
      Yn.resize(0);
      fout << "there is only one particle, therefore AJetJn cannot be performed" << endl;
      return Yn;
    }

  double minY = 0;
  // Main loop
  while( theProtoJets.size() != 1)
  {
    minY = DBL_MAX;
    typename vector<DurhamProtoJet>::iterator aCandidate;
    typename vector<DurhamProtoJet>::iterator aNextNeighbour;
    typename vector<DurhamProtoJet>::iterator i1 = theProtoJets.begin();
    for(i1 = theProtoJets.begin(); i1!= theProtoJets.end(); i1++)
      {
	double y = DBL_MAX;
	typename vector<DurhamProtoJet>::const_iterator aNeighbour = i1->findNextNeighbour(theProtoJets);
	if(aNeighbour != theProtoJets.end()) y = i1->getYTimesE2(&(*aNeighbour))/totalE2;
	if(y<minY) 
	  {
	    minY = y;
	    aCandidate = i1;
            aNextNeighbour = theProtoJets.begin() + (aNeighbour - theProtoJets.begin());
	  }
      }
	*aCandidate += *aNextNeighbour;
	theProtoJets.erase(aNextNeighbour);
	Yn[theProtoJets.size()-1]=minY;
  }
  // return a vector of float
  return Yn;
}


