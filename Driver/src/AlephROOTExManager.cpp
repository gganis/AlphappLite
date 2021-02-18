//////////////////////////////////////////////////////
//
//  Implementation of class AlephROOTExManager
//
//  Author : G. Dissertori  ,  15.08.2002
//
//////////////////////////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "AlephExManager.h"
#include "AlephROOTExManager.h"
#include "AlephDbManager.h"
#include "AlephIoManager.h"
#include "AlephCardsReader.h"
#include "AlephInteractiveHandler.h"
#include "DefaultInteractiveActions.h"
#include "AlephRegisteredAction.h"
#include "TRandom3.h"


extern ofstream fout;

//
// the constructor
//
AlephROOTExManager::AlephROOTExManager()
{
  // call the constructor of the base class
  AlephManagerSetup("ROOTExManager");
  fout << " An AlephROOTExManager has been created " << endl;
}

//
// the destructor
//
AlephROOTExManager::~AlephROOTExManager() {}

//
// the initialization step
//
AlephRC AlephROOTExManager::initialize()
{
  // get debug level
  int debug = (AlephSession::TheAlephSession())->debugLevel();
  // say something
  fout << " AlephROOTExManager :  initializing .... " << endl << endl;;
  // first check is the IoManager is there 
  fout << " AlephROOTExManager :  Setting random generator seed to ";
  AlephManager* ioManager = (AlephSession::TheAlephSession())->aAlephManager("IoManager");
  unsigned long theseed = 1;
  if (ioManager != NULL)
    {
      AlephStatus ioManStatus = ioManager->status();
      if (ioManStatus == INITIALIZED)
       {
        // get the SEED card (if not, there is an unknown value)
        theseed = (((AlephIoManager*)ioManager)->theCardsReader()).getSeed();
       }
    }
  fout << theseed << endl;
  gRandom = new TRandom3(theseed);
  // initialisation of default interactive functions
  AlephRegisteredAction<GeneralEventInfo> code100;
  AlephRegisteredAction<CollectTracks> code200;
  AlephRegisteredAction<CollectLeptons> code300;
  AlephRegisteredAction<CollectJets> code400;
  // User Initialization
  fout << " AlephROOTExManager :  calling user init " << endl;
  UserInit();
  return AlephOK;
}

//
// the termination step
//
AlephRC AlephROOTExManager::terminate()
{
  // say something
  fout << " AlephROOTExManager :  terminating .... " << endl;
  fout << " AlephROOTExManager :  calling user term " << endl;
  UserTerm();
  // set the status
  setStatus(TERMINATED); 
  return AlephOK;
}

//
// the running step
//
AlephRC AlephROOTExManager::run()
{
  // check first if the database manager is up
  AlephManager* dbManager = (AlephSession::TheAlephSession())->aAlephManager("DbManager");
  if (dbManager == NULL)
    {
      fout << " FATAL : AlephROOTExManager : there is NO DbManager !! " << endl;
      return AlephERROR;
    }
  else
    {
      // check if it is initialized
      AlephStatus dbManStatus = dbManager->status();
      if (dbManStatus != INITIALIZED) dbManager->initialize(); 
      // check the session type
      string sessionTy = (AlephSession::TheAlephSession())->sessionType();
      // if it is batch, call the loop function
      fout << " The session type is " << sessionTy << endl;
      if (sessionTy == "BATCH") 
	{
	  AlephRC  loopRC = loopAll();
	  return loopRC;
	}
      else // else do interactive stuff
      if (sessionTy  == "INTER")
	{
	  // call next user request
	  AlephRC  loopRC = loopInter();
	  return loopRC;
	}
      else  // do nothing
 	{
	  fout << "  FATAL : AlephROOTExManager : do not know this session Type !! " << endl;
	  return AlephERROR;
	}
    }
}

//////////
// batch loop
//////////
AlephRC AlephROOTExManager::loopAll()
{
  // check if user wants a reading or writing transaction
  // get it from the cards
  // first check if the IoManager is there
  AlephManager* ioManager = (AlephSession::TheAlephSession())->aAlephManager("IoManager");
  if (ioManager == NULL) 
    {
      fout << "  FATAL : AlephROOTExManager : there is no IoManager !! " << endl;
      return AlephERROR;
    }
  else
    {
      AlephStatus ioManStatus = ioManager->status();	
      if (ioManStatus != INITIALIZED) ioManager->initialize();
      // get the TATY card
      string transType = (((AlephIoManager*)ioManager)->theCardsReader()).getTaType();
      if (transType == "write")
	{	  
	  return loopAllWrite();
	}
      else
	{
	  return loopAllRead();
	}
    }
}

//////////
// batch reading loop
//////////
AlephRC AlephROOTExManager::loopAllRead()
{
  // get the db manager
  AlephDbManager* rootMan = theDbm();
  // start a read transaction if not already done
  rootMan->startTransaction(READING);
  // get the debug level
  int debug = (AlephSession::TheAlephSession())->debugLevel();
///////////////////
// main event loop
//////////////////
  int ier1;
  EventCount = 0;
  do {
    AlphaBanks *bb = new AlphaBanks(AlphaBanks::ROOT);
    ier1 = rootMan->GetEvent(bb)-1;
    if (ier1 != 0) { delete bb; break; }
    EventCount++;
    if (debug >= 2) 
    {
      fout << endl;
      fout << "*************************************************" << endl;
      fout << "** Run # " << getCurrentRun() << " , Evt # " << getCurrentEvt() << "  --> " << endl;
      fout << "*************************************************" << endl;
    }
    // prepare AlphaBanks for analysis
    bb->InitObjectStructure();
    if(!bb->isValid())
	    fout << " AlephROOTExManager : inconsistency in event. Skipped " << endl;
    else
            UserEvent(*bb);
    // some status report
    if (! (EventCount % 1000))
      {
	fout << endl;
	fout << "******* " << EventCount << " events read " << endl;
        fout << "******* current Run # = " << getCurrentRun() << endl;
        fout << "******* current Evt # = " << getCurrentEvt() << endl;
        fout << endl;
      }
    delete bb;
///////////////////
// end main event loop
////////////////// 
  } while (ier1 == 0);
  fout << endl;
  fout << " *** " << EventCount << " Events have been read" << endl;
  fout << endl;
  // stop the transaction
  AlephRC stopRC = rootMan->stopTransaction();
  if (debug >= 0)
  {
    fout << endl;
    fout << " ****** AlephROOTExManager::loopAllRead : transaction stopped ****** " << endl;
    fout << endl;
  }
  return stopRC;
}
 
//////////
// batch writing loop
//////////
AlephRC AlephROOTExManager::loopAllWrite()
{
  fout << " in loopInterWrite : doing nothing for the moment ... " << endl;
  return AlephOK;
}

//////////
// interactive loop
//////////
AlephRC AlephROOTExManager::loopInter()
{
  // check if user wants a reading or writing transaction
  // get it from the cards
  // first check if the IoManager is there
  AlephManager* ioManager = (AlephSession::TheAlephSession())->aAlephManager("IoManager");
  if (ioManager == NULL) 
    {
      fout << "  FATAL : AlephROOTExManager : there is no IoManager !! " << endl;
      return AlephERROR;
    }
  else
    {
      AlephStatus ioManStatus = ioManager->status();	
      if (ioManStatus != INITIALIZED) ioManager->initialize(); 
      // get the TATY card
      string transType = (((AlephIoManager*)ioManager)->theCardsReader()).getTaType();
      if (transType == "write")
	{	  
	  return loopInterWrite();
	}
      else
	{
	  return loopInterRead();
	}
    }
}

//////////
// interactive reading loop
//////////
AlephRC AlephROOTExManager::loopInterRead()
{
  // get the db manager
  AlephDbManager* rootMan = theDbm();
  // start a read transaction if not already done
  rootMan->startTransaction(READING);
  // get the debug level
  int debug = (AlephSession::TheAlephSession())->debugLevel();
  // instanciate the AlephInteractiveHandler
  AlephInteractiveHandler* Handler = AlephInteractiveHandler::TheAlephInteractiveHandler();
  int ier1=0;
  Handler->InitiateConnection(ier1);
///////////////////
// main event loop
//////////////////
  EventCount = 0;
  while(!ier1)
  {
    AlphaBanks *bb = new AlphaBanks(AlphaBanks::ROOT);
    ier1 = rootMan->GetEvent(bb)-1;
    if (ier1 != 0) { delete bb; break; }
    EventCount++;
    if (debug >= 2) {
      fout << endl;
      fout << "*************************************************" << endl;
      fout << "** Run # " << getCurrentRun() << " , Evt # " << getCurrentEvt() << "  --> " << endl;
      fout << "*************************************************" << endl;
    }
    // prepare AlphaBanks for analysis
    bb->InitObjectStructure();
    if(!bb->isValid())
	    fout << " AlephROOTExManager : inconsistency in event. Skipped " << endl;
    else
            if(UserEvent(*bb)||Handler->KeepAllEvents()) 
	    {
		    ier1 = Handler->HandleEvent(*bb);
	    }
    // some status report
    if (! (EventCount % 1000))
      {
	fout << endl;
	fout << "******* " << EventCount << 
                " events read " << endl;
        fout << "******* current Run # = " << getCurrentRun() << endl;
        fout << "******* current Evt # = " << getCurrentEvt() << endl;
        fout << endl;
      }
    delete bb;
///////////////////
// end main event loop
////////////////// 
  };
  Handler->CloseConnection();
  fout << endl;
  fout << " *** " << EventCount << " Events have been read" << endl;
  fout << endl;
// stop the transaction
  AlephRC stopRC = rootMan->stopTransaction();
  if (debug >= 0)
  {
    fout << endl;
    fout << " ****** AlephROOTExManager::loopInterRead : transaction stopped ****** " << endl;
    fout << endl;
  }
  return stopRC;
}
 
//////////
// interactive writing loop
//////////
AlephRC AlephROOTExManager::loopInterWrite()
{
  fout << " in loopInterWrite : doing nothing for the moment ... " << endl;
  return AlephOK;
}

