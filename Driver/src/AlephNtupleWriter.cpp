#include "AlephNtupleWriter.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

//constructor
AlephNtupleWriter::AlephNtupleWriter()
{
cards = NULL;
type = 0;
}

// destructor
AlephNtupleWriter::~AlephNtupleWriter() {}

// initialize
void AlephNtupleWriter::Initialize(AlephCardsReader* thecards, int mode)
{
	cards = thecards;
	// mode: 1 = ROOT
	type = mode;
	switch (type)
	{
		case 1 :
			ROOTfile = new TFile(cards->getHist().c_str(),"RECREATE");
			ROOTtree = new TTree("analysis","alpha++ analysis");
			break;
		default :
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);
	}
}

// fill
void AlephNtupleWriter::Fill()
{
	switch (type)
	{
		case 1 :
			ROOTfile->cd();
			ROOTtree->Fill();
			break;
		default :
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);		
	}
}

// terminate
void AlephNtupleWriter::Terminate()
{
	switch (type)
	{
		case 1 :
			ROOTfile->cd();
			ROOTtree->Write();
			ROOTfile->Close();
//   The program seems to hang at the end is the tree is deleted.
//			delete ROOTtree;
			delete ROOTfile;
			for(map<string,int*>::iterator mapel=SizeAddresses.begin();mapel != SizeAddresses.end();mapel++)
				delete mapel->second;
			for(vector<smart_void*>::iterator vecel=theObjects.begin();vecel < theObjects.end();vecel++)
				delete *vecel;
			break;
		default :
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);
	}	
}
