//////////////////////////////////////////////////////
//
//  Implementation of class AlephDbManager
//
//  Author : G. Dissertori  ,  02.11.98
//
//////////////////////////////////////////////////////


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "AlephIoManager.h"
#include "AlephDbManager.h"
#include "AlephROOTDbManager.h"

extern ofstream fout;

//
// set the global instance variable
//
AlephManager* AlephDbManager::_theAlephDbManager=0;

//
// the instance function of the  Singleton
//
AlephManager* AlephDbManager::TheAlephDbManager()
{
  if (_theAlephDbManager == 0) 
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
	    AlephIoManager* IoManager = (AlephIoManager*)ioManager;
	    // get the cards reader
	    AlephCardsReader& cardsReader = IoManager->theCardsReader();
	    // get the DBTY card
	    databaseType = cardsReader.getDbType();
	  }
      }
    // else look for an environment variable
    else
      {
	databaseType = getenv("DATABASETYPE");
      }
    
    if (databaseType == "")
      {
	    fout << "AlephDbManager Warning : env variable DATABASETYPE " 
		 << databaseType << " is not a valid db type " << endl;
	    fout << "Therefore creating a default database manager..." << endl;
	    _theAlephDbManager = new AlephDbManager;
      }
    else
      {
	    _theAlephDbManager = new AlephROOTDbManager;
      }  
  }
  return _theAlephDbManager;
} 

//
// the constructor
//
AlephDbManager::AlephDbManager()
{
  // call the constructor of the base class
  AlephManagerSetup("DbManager");
  // set the dbname to an empty string
  string _dbName = " ";
}

//
// the destructor
//
AlephDbManager::~AlephDbManager()
{
  AlephManagerShutDown();
  delete [] _theAlephDbManager;
}

//
// the initialization step
//
AlephRC AlephDbManager::initialize()
{
  // say something
  fout << " AlephDbManager :  initializing .... " << endl;
  // start reading transaction as default
  startTransaction(READING);
  // set the status
  setStatus(INITIALIZED); 
  return AlephOK;
}

//
// the termination step
//
AlephRC AlephDbManager::terminate()
{
  // say something
  fout << " AlephDbManager :  terminating .... " << endl;
  // stop any transaction
  stopTransaction();
  // set the status
  setStatus(TERMINATED); 
  return AlephOK;
}

//
// get the transaction type
//
AlephTransaction AlephDbManager::transactionType() const
{
  return _theTransactionType;
}

//
// set the transaction type
//
void AlephDbManager::setTransactionType(const AlephTransaction& transType)
{
  _theTransactionType = transType;
}

//
// start a transaction, transType = READING or UPDATE
//
AlephRC AlephDbManager::startTransaction(const AlephTransaction& transType)
{
  // set the transaction type
  setTransactionType(transType);
  // but to nothing else....
  return AlephOK;
}

//
// stop the current transaction, sets transType to HALTED
//
AlephRC  AlephDbManager::stopTransaction()
{
  // set the transaction type to HALTED
  setTransactionType(HALTED);
  // but to nothing else....
  return AlephOK;
}

//
// do commit and hold
//
AlephRC AlephDbManager::commitAndHoldTransaction()
{
  // do nothing
  return AlephOK;
}

//
// open an existing database 
//
AlephRC AlephDbManager::openExistingDb(const vector<string>& aDbName, 
                                       const string& mode)
{
  // do nothing
  return AlephOK;
}

//
// open a new database 
//
AlephRC AlephDbManager::openNewDb(const string& aDbName)
{
  // do nothing
  return AlephOK;
}

//
// return the name of the current database 
//
string AlephDbManager::dbName() const
{
  //return an empty string
  return _dbName;
} 

//
// set the name of the current database 
//
void AlephDbManager::setDbName(const string& aDbName)
{
  _dbName = aDbName;
}

//! store an event
AlephRC AlephDbManager::StoreEvent(AlphaBanks* event)
{
  return AlephOK;
}

//! get the next event
AlephRC AlephDbManager::GetEvent(AlphaBanks*)
{
  return AlephOK;
}

