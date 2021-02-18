//////////////////////////////////////////////////////////
// Class AlephROOTDbManager:
// Give access to general methods to write events to files
// The AlphaBanks is stored as is in a TTree
// 
// Author : C.Delaere
//
///////////////////////////////////////////////////////////

#include "AlephROOTDbManager.h"
#include "AlphaBanks.h"
#include "AlephCardsReader.h"
#include "AlephIoManager.h"
#include "AlephExManager.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

extern ofstream fout;

AlephROOTDbManager::AlephROOTDbManager()
{
	ROOTDbFile = NULL;
	ROOTDbTree = NULL;
	entry = -1;
        classbitpattern = 0;
}

AlephROOTDbManager::~AlephROOTDbManager() 
{
	// the TTree is deleted when closing the file.
	if(ROOTDbTree) delete ROOTDbTree;
	if(ROOTDbFile) delete ROOTDbFile;
}

AlephRC AlephROOTDbManager::initialize()
{
	fout << " AlephROOTDbManager :  initializing .... " << endl;
	AlephManager* ioManager = (AlephSession::TheAlephSession())->aAlephManager("IoManager");
	if (ioManager != NULL)
	  {
	    AlephStatus ioManStatus = ioManager->status();
	    if (ioManStatus == INITIALIZED)
	      {
	        // optimisation of the ROOTfile
		AlphaBanks::Class()->IgnoreTObjectStreamer();
		QLIN::Class()->IgnoreTObjectStreamer();
		QMTL::Class()->IgnoreTObjectStreamer();
		QMTS::Class()->IgnoreTObjectStreamer();
		FRFT::Class()->IgnoreTObjectStreamer();
		FRTL::Class()->IgnoreTObjectStreamer();
		TEXS::Class()->IgnoreTObjectStreamer();
		HMAD::Class()->IgnoreTObjectStreamer();
		MCAD::Class()->IgnoreTObjectStreamer();
		PECO::Class()->IgnoreTObjectStreamer();
		EIDT::Class()->IgnoreTObjectStreamer();
		PHCO::Class()->IgnoreTObjectStreamer();
		PEPT::Class()->IgnoreTObjectStreamer();
		FRID::Class()->IgnoreTObjectStreamer();
		EFOL::Class()->IgnoreTObjectStreamer();
		PCQA::Class()->IgnoreTObjectStreamer();
		EGPC::Class()->IgnoreTObjectStreamer();
		MUID::Class()->IgnoreTObjectStreamer();
		PGPC::Class()->IgnoreTObjectStreamer();
		PGAC::Class()->IgnoreTObjectStreamer();
		PDLT::Class()->IgnoreTObjectStreamer();
		PMLT::Class()->IgnoreTObjectStreamer();
		QDET::Class()->IgnoreTObjectStreamer();
		QVEC::Class()->IgnoreTObjectStreamer();
		YV0V::Class()->IgnoreTObjectStreamer();
		FKIN::Class()->IgnoreTObjectStreamer();
		FVER::Class()->IgnoreTObjectStreamer();
		QVRT::Class()->IgnoreTObjectStreamer();
		ALPB::Class()->IgnoreTObjectStreamer();
		ALRP::Class()->IgnoreTObjectStreamer();
		RNL2::Class()->IgnoreTObjectStreamer();
		RNF2::Class()->IgnoreTObjectStreamer();
		RNR2::Class()->IgnoreTObjectStreamer();
		RLEP::Class()->IgnoreTObjectStreamer();
		LFIL::Class()->IgnoreTObjectStreamer();
		EVEH::Class()->IgnoreTObjectStreamer();
		KEVH::Class()->IgnoreTObjectStreamer();
		REVH::Class()->IgnoreTObjectStreamer();
		LOLE::Class()->IgnoreTObjectStreamer();
		X1RG::Class()->IgnoreTObjectStreamer();
		BOMB::Class()->IgnoreTObjectStreamer();
		RUNH::Class()->IgnoreTObjectStreamer();
		ASIM::Class()->IgnoreTObjectStreamer();
		ADBR::Class()->IgnoreTObjectStreamer();
		XTBN::Class()->IgnoreTObjectStreamer();
		XTCN::Class()->IgnoreTObjectStreamer();
		XTOP::Class()->IgnoreTObjectStreamer();
		LUPA::Class()->IgnoreTObjectStreamer();
		SILH::Class()->IgnoreTObjectStreamer();
		XHVB::Class()->IgnoreTObjectStreamer();
		XTEB::Class()->IgnoreTObjectStreamer();
		XTRB::Class()->IgnoreTObjectStreamer();
		DTBP::Class()->IgnoreTObjectStreamer();
		VHBV::Class()->IgnoreTObjectStreamer();
		VHPV::Class()->IgnoreTObjectStreamer();
		EAUX::Class()->IgnoreTObjectStreamer();
		SIX2::Class()->IgnoreTObjectStreamer();
		X1TV::Class()->IgnoreTObjectStreamer();
		KWGT::Class()->IgnoreTObjectStreamer();
		X1IP::Class()->IgnoreTObjectStreamer();
		SIXA::Class()->IgnoreTObjectStreamer();
		SITC::Class()->IgnoreTObjectStreamer();
		SRCO::Class()->IgnoreTObjectStreamer();
		X1TH::Class()->IgnoreTObjectStreamer();
		X1AD::Class()->IgnoreTObjectStreamer();
		QEXT::Class()->IgnoreTObjectStreamer();
		QHAC::Class()->IgnoreTObjectStreamer();
	        AlephIoManager* IoManager = (AlephIoManager*)ioManager;
		AlephCardsReader& cardsReader = IoManager->theCardsReader();
		// get the ASRU and CLAS cards
		vector<int> edirclass = cardsReader.getClass();
		vector<long> asrucard = cardsReader.getAlphaSrun();
		// build the class bit pattern
		classbitpattern = 0;
		for(vector<int>::iterator theclass = edirclass.begin();theclass<edirclass.end();theclass++)
			classbitpattern |= (1<<((*theclass)-1));
		// build a fast look-up table with the selected runs (if some)
		asrucardlist.clear();
		for(vector<long>::iterator thecard = asrucard.begin();thecard<asrucard.end();thecard++)
			asrucardlist.push_back(*thecard);
		switch(cardsReader.getTaType()=="write")
		{
			case true:
			{	
				openNewDb(cardsReader.getAlphaFilo());
				break;
			}
			case false:
			{
				openExistingDb(cardsReader.getAlphaFili());
				// get the NEVT card
				vector<long> nevtcard = cardsReader.getNevt();
				// get the total number of available events in the TChain
				if (ROOTDbTree == 0) 
					{
						fout << "AlephROOTDbManager::Initialize ERROR: ROOTDbTree not initialized!" << endl; 
						return AlephERROR;
					}
				int nentries = int(((TChain*)ROOTDbTree)->GetEntries());
				// build the interval requested
				if(nevtcard.size()==1)
					{
						lowentry  = 0;
						highentry = nevtcard[0]<nentries ? nevtcard[0] : nentries;
					}
				else if (nevtcard.size()==2)
					{
						lowentry = nevtcard[0];
						highentry = nevtcard[1]<nentries ? nevtcard[1] : nentries;
					}
				else
					{
						fout << "AlephROOTDbManager::Initialize WARNING: bad NEVT format. Ignored" << endl;
						lowentry = 0;
						highentry = nentries;
					}
				entry = lowentry-1;
				break;
			}
	        }
	      }
	    else
	      {
	        fout << "AlephDbManager Warning : AlephIoManager not initialized... can't start" << endl;
		exit(1);
	      }
	  }
	else
	  {
	    fout << "AlephDbManager Warning : AlephIoManager not persent... can't start" << endl;
	    exit(1);
	  }
	setStatus(INITIALIZED);
	return AlephOK;
}

AlephRC AlephROOTDbManager::openExistingDb(const vector<string>& aDbName,const string& mode)
{
	ROOTDbTree = new TChain("AlephDbTree","AlephEvents");
	for(vector<string>::const_iterator filename=aDbName.begin();filename<aDbName.end();filename++)
	{
		((TChain*)ROOTDbTree)->Add(filename->c_str());
	}
	setDbName("TChain");
	return AlephOK;
}

AlephRC AlephROOTDbManager::openNewDb(const string& aDbName)
{
	ROOTDbFile = new TFile(aDbName.c_str(),"RECREATE");
	//ROOTDbFile->SetCompressionLevel(9);
	ROOTDbTree = new TTree("AlephDbTree","AlephEvents");
	ROOTDbTree->Branch("AlphaBanks","AlphaBanks", &mylocalevent,1600,0);
	ROOTDbTree->Branch("Event_number",&eventnumber,"Event_number/I");
	ROOTDbTree->Branch("Run_number",&runnumber,"Run_number/I");
	ROOTDbTree->Branch("EDIR_class",&edirclass,"EDIR_class/I");
	setDbName(aDbName);
	return AlephOK;
}

AlephRC AlephROOTDbManager::StoreEvent(AlphaBanks* event)
{
        mylocalevent = event;
	eventnumber = event->Event().number();
	runnumber = event->Run().number();
	edirclass = event->Event().EdirClass();
	ROOTDbFile->cd();
	ROOTDbTree->Fill();
	return AlephOK;
}

AlephRC AlephROOTDbManager::GetEvent(AlphaBanks* theoutput)
{
	AlephExManager* exManager = (AlephExManager*)(AlephSession::TheAlephSession())->aAlephManager("ExManager");
        // check if there is a next event to deliver...
	for(entry++;entry<highentry;entry++)
	{
		if(entry>=highentry) return AlephERROR;
		// open the right TTree
		Int_t ientry = ((TChain*)ROOTDbTree)->LoadTree(entry);
		// first read Run_number and EDIR_class branches
		// to check if the event has to be selected
		TBranch* bRun_number   = ((TChain*)ROOTDbTree)->GetBranch("Run_number");
		TBranch* bEDIR_class   = ((TChain*)ROOTDbTree)->GetBranch("EDIR_class");
		TBranch* bEvent_number = ((TChain*)ROOTDbTree)->GetBranch("Event_number");
		TBranch* bAlphaBanks   = ((TChain*)ROOTDbTree)->GetBranch("AlphaBanks");
		bRun_number->SetAddress(&runnumber);
		bEDIR_class->SetAddress(&edirclass);
		bEvent_number->SetAddress(&eventnumber);
		bAlphaBanks->SetAddress(&theoutput);
		bEDIR_class->GetEntry(ientry);
		bRun_number->GetEntry(ientry);
		//check the class
		if((classbitpattern)&&(!(edirclass&classbitpattern))) continue;
		//chech the run
		if((asrucardlist.size())&&(find(asrucardlist.begin(),asrucardlist.end(),runnumber)==asrucardlist.end())) continue;
		//load the full event
		((TChain*)ROOTDbTree)->GetEntry(ientry);
		exManager->setCurrentRunEvt(runnumber,eventnumber);
		return AlephOK;
	}
	return AlephERROR;
}

AlephRC AlephROOTDbManager::terminate()
{
	if(ROOTDbFile)
	{
		ROOTDbFile->cd();
		ROOTDbFile->Write();
		ROOTDbFile->Close();
		setDbName("");
		ROOTDbTree = NULL;
	}
	setStatus(TERMINATED);
	return AlephOK;
}

