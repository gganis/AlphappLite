/////////////////////////////////////////////////////////////////////
// 
// Vertex package test routines
//
// Author : C. Delaere
//
// Date: 2001-08-08
//
//
/////////////////////////////////////////////////////////////////////

#include <fstream>
#include "AlephExManager.h"
#include "AlephCollection.h"
#include <vector>
#include "AlBjet.h"

extern ofstream fout;

///////////////////////////////////////////////////////////////////////
//  User Init
///////////////////////////////////////////////////////////////////////

static float mZ = 91.1882; // RPP2000

void AlephExManager::UserInit()
{
	int i;
	float f;
	theNtupleWriter()->AddOutput(f,"x");
	theNtupleWriter()->AddOutput(f,"y");
	theNtupleWriter()->AddOutput(f,"z");
        theNtupleWriter()->AddOutput(f,"MCx");
	theNtupleWriter()->AddOutput(f,"MCy");
	theNtupleWriter()->AddOutput(f,"MCz");
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  User Event
///////////////////////////////////////////////////////////////////////
bool AlephExManager::UserEvent(AlphaBanks& EventInfo)
{
  cerr << ".";
// get pointers to the objects used in the analysis
  // Collection of pointers the the MC vertices
  AlephCollection<AlVertex *> alMCvtp=EventInfo.MCverticesPV();
  // The reconstructed main vertex
  AlVertex* alMainV=EventInfo.MainVertexP();
// keep the values (in the output ntuple)
  theNtupleWriter()->Keep("x", alMainV->QX());
  theNtupleWriter()->Keep("y", alMainV->QY());
  theNtupleWriter()->Keep("z", alMainV->QZ());
  theNtupleWriter()->Keep("MCx",alMCvtp[0]->QX());
  theNtupleWriter()->Keep("MCy",alMCvtp[0]->QY());
  theNtupleWriter()->Keep("MCz",alMCvtp[0]->QZ());
  theNtupleWriter()->Fill();
  return true;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  User Term
///////////////////////////////////////////////////////////////////////
void AlephExManager::UserTerm() {}
