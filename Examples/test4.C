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

void AlephExManager::UserInit() {}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  User Event
///////////////////////////////////////////////////////////////////////
bool AlephExManager::UserEvent(AlphaBanks& EventInfo)
{
	// get the calo objects
	AlephCollection< AlCalObject*> ecal = EventInfo.ECalObjectPV();
	AlephCollection< AlCalObject*> hcal = EventInfo.HCalObjectPV();
	// loop and print
	AlephCollection< AlCalObject*>::iterator it;
	cout << "ECAL objects" << endl;
	for(it=ecal.begin();it<ecal.end();it++)
	{
		cout << (*it)->QE() << " " << (*it)->QX() << " " << (*it)->QY() << " " << (*it)->QZ()  << endl;
		cout << "     " << (*it)->GetRawEnergy()[0] << " " << (*it)->GetRawEnergy()[1] << " " <<(*it)->GetRawEnergy()[2] << endl;
		cout << "     CorrectionCode:" << (*it)->GetCorrectionCode() << " Relation bits:" << (*it)->GetRelationBits() << " Isolation:" << (*it)->IsIsolated() << endl;
	}
	cout << "HCAL objects" << endl;
	for(it=hcal.begin();it<hcal.end();it++)
	{
		cout << (*it)->QE() << " " << (*it)->QX() << " " << (*it)->QY() << " " << (*it)->QZ()  << endl;
		cout << "     " << (*it)->GetRawEnergy()[0] << endl;
		cout << "     CorrectionCode:" << (*it)->GetCorrectionCode() << " Relation bits:" << (*it)->GetRelationBits() << " Isolation:" << (*it)->IsIsolated() << endl;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  User Term
///////////////////////////////////////////////////////////////////////
void AlephExManager::UserTerm() {}
