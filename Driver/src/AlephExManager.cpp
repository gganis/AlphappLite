//////////////////////////////////////////////////////
//
//  Implementation of class AlephExManager
//
//  Author : G. Dissertori  ,  10.8.99
//                             31.8.2000
//
//////////////////////////////////////////////////////


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "AlephSession.h"
#include "AlephIoManager.h"
#include "AlephExManager.h"
#include "AlephROOTExManager.h"
#include "TRandom3.h"

extern ofstream fout;

//
// set the global instance variable
//
AlephManager* AlephExManager::_theAlephExManager=0;

//
// the instance function of the  Singleton
//
AlephManager* AlephExManager::TheAlephExManager()
{
  if (_theAlephExManager == 0) 
    {

      // check which type of database we want

      string databaseType;
      // first check is the IoManager is there and has a card DBTY
      AlephManager* ioManager = (AlephSession::TheAlephSession())->aAlephManager("IoManager");
      if (ioManager != NULL) 
	{
	  AlephStatus ioManStatus = ioManager->status();
	  if (ioManStatus == INITIALIZED) 
	    {
	      // get the DBTY card
	      databaseType = (((AlephIoManager*)ioManager)->theCardsReader()).getDbType();
	    }
	}
      // else look for an environment variable
      else
	{
	  databaseType = getenv("DATABASETYPE");
	}
      
      if (databaseType != "root")
	{
	  fout << " AlephExManager Warning : env variable DATABASETYPE " 
	       << databaseType << " is not a valid db type " << endl;
	  fout << " Therefore creating a default database manager..." << endl;
	  _theAlephExManager = new AlephExManager;
	}
      else
	{
	  _theAlephExManager = new AlephROOTExManager;
	}  
    }
  return _theAlephExManager;
} 

//
// the constructor
//
AlephExManager::AlephExManager()
{
  // call the constructor of the base class
  AlephManagerSetup("ExManager");

  // set the pointer to the database manager
  _theDbManager = (AlephDbManager*)(alephSession()->aAlephManager("DbManager"));

  // set current run and event numbers
  _currentRun = 0;
  _currentEvt = 0;
}

//
// the destructor
//
AlephExManager::~AlephExManager() 
{
  AlephManagerShutDown();
  delete [] _theAlephExManager;
}

//
// the initialization step
//
AlephRC AlephExManager::initialize()
{
  // say something
  fout << " AlephExManager :  initializing .... " << endl;
  fout << " AlephExManager :  Setting random generator seed to ";
  // first check is the IoManager is there 
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
  fout << " AlephExManager :  calling the user initialization " << endl;
  // call the user init
  UserInit();
  // set the status
  setStatus(INITIALIZED); 
  return AlephOK;
}

//
// the running step
//
AlephRC AlephExManager::run()
{
  // set the status
  setStatus(RUNNING); 
  // say something
  fout << " AlephExManager :  start running .... " << endl;
  fout << " AlephExManager :  calling the user event routine " << endl;
  // call the user event : note : in the default version bb may be null!!
  AlphaBanks bb(AlphaBanks::BOS);
  bb.InitObjectStructure();
  if (!bb.isValid())
  	fout << " AlephExManager :  inconsistency in Event. Skipped " << endl;
  else
  	UserEvent(bb);
  return AlephOK;
}

//
// the termination step
//
AlephRC AlephExManager::terminate()
{
  // say something
  fout << " AlephExManager :  terminating .... " << endl;
  fout << " AlephExManager :  calling the user termination " << endl;
  // call the user term and clear Ntuple Image
  UserTerm();
  // set the status
  setStatus(TERMINATED); 
  return AlephOK;
}

//
// set current run and event number
//
void AlephExManager::setCurrentRunEvt(const long& CurrentRun,
                                      const long& CurrentEvt)
{
  _currentRun = CurrentRun;
  _currentEvt = CurrentEvt;
}

//
// get current Run number
//
long AlephExManager::getCurrentRun() const
{
  return _currentRun;
}

//
// get current Evt number
//
long AlephExManager::getCurrentEvt() const
{
  return _currentEvt;
}

//
// get the event counter
//
long AlephExManager::getEventCount() const
{
  return EventCount;
}

//
// give pointers to managers, NtupleWriter, cardsreader, ...
//
AlephSession* AlephExManager::theSession() const
{
  return AlephSession::TheAlephSession();
}

AlephDbManager* AlephExManager::theDbm() const
{
  return (AlephDbManager*)AlephSession::TheAlephSession()->aAlephManager("DbManager");
}

AlephIoManager* AlephExManager::theIom() const
{
  return (AlephIoManager*)theSession()->aAlephManager("IoManager");
}

AlephCardsReader* AlephExManager::theCardsReader() const
{
  AlephIoManager* iom = theIom();
  if (iom == NULL) 
    {
      fout << " AlephExManager::theCardsReader : WARNING!! " << endl;
      fout << "       no IoManager has been created!! " << endl;
      fout << "       therefore returning NULL pointer !! " << endl;
      return NULL;     
    }
  else
    return &(iom->theCardsReader());
}

AlephNtupleWriter* AlephExManager::theNtupleWriter() const
{
  AlephIoManager* iom = theIom();
  if (iom == NULL)
    {
      fout << " AlephExManager::theCardsReader : WARNING!! " << endl;
      fout << "       no IoManager has been created!! " << endl;
      fout << "       therefore returning NULL pointer !! " << endl;
      return NULL;
    }
  else
   return &(iom->theNtupleWriter());
}

