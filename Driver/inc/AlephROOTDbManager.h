//////////////////////////////////////////////////////
//
//  Class AlephROOTDbManager
//
//  The class responsible for the database handling
//  It inherits from AlephManager.
//  It is a singleton
//
//  Author : C. Delaere 14.08.02
//
//////////////////////////////////////////////////////

#ifndef ALEPHROOTDBMANAGER_H
#define ALEPHROOTDBMANAGER_H

#include "AlephDbManager.h"
#include <vector>
#include <list>

class TFile;
class TTree;
class AlphaBanks;

//! The ROOT DataBase manager
class AlephROOTDbManager : public AlephDbManager 
{
public:

 friend class AlephDbManager;

//! the initialization step 
  virtual AlephRC initialize(); 
//! the terminating step 
  virtual AlephRC terminate(); 
//! store the event
  virtual AlephRC StoreEvent(AlphaBanks*);
//! get the event back
  virtual AlephRC GetEvent(AlphaBanks*);
//! open an existing database 
  virtual AlephRC openExistingDb(const vector<string>& aDbName,
                                 const string& mode = "TRANSTY");
//! open a new database 
  virtual AlephRC openNewDb(const string& aDbName);
protected:

// constructor and destructor
  AlephROOTDbManager();
  virtual ~AlephROOTDbManager();
private:

// ROOT objects used to store / retrieve information
  TFile *ROOTDbFile;
  TTree *ROOTDbTree;
  AlphaBanks* mylocalevent;
  int eventnumber, runnumber, edirclass ;
  int entry;
  long classbitpattern;
  list<long> asrucardlist;
  long lowentry;
  long highentry;

};

#endif

