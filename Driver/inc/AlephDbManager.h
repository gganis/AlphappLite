//////////////////////////////////////////////////////
//
//  Class AlephDbManager
//
//  The class responsible for the database handling
//  It inherits from AlephManager.
//  It is a singleton
//
//  Author : G. Dissertori  ,  02.11.98
//
//////////////////////////////////////////////////////

#ifndef ALEPHDBMANAGER_H
#define ALEPHDBMANAGER_H

#include <string>
#include <vector>
#include "AlephManager.h"

class AlphaBanks;

// transaction info
enum AlephTransaction { HALTED , READING , UPDATE };

//! The DataBase manager
class AlephDbManager : public AlephManager 
{
public:

//! the instance function of the  Singleton
  static AlephManager* TheAlephDbManager(); 
//! the initialization step 
  virtual AlephRC initialize(); 
//! the terminating step 
  virtual AlephRC terminate(); 
//! get the current transaction type
  virtual AlephTransaction transactionType() const;
//! set the current transaction type
  virtual void setTransactionType(const AlephTransaction& transType);
//! start a transaction, transType = READING or UPDATE
  virtual AlephRC startTransaction(const AlephTransaction& transType);
//! stop the current transaction, sets transType to HALTED
  virtual AlephRC stopTransaction();
//! do a commit and hold
  virtual AlephRC commitAndHoldTransaction();
//! open an existing database 
  virtual AlephRC openExistingDb(const vector<string>& aDbName, const string& mode = "TRANSTY");
//! open a new database 
  virtual AlephRC openNewDb(const string& aDbName);
//! return the name of the current database 
  virtual string dbName() const;
//! set the name of the current database 
  virtual void setDbName(const string& aDbName);
//! store an event
  virtual AlephRC StoreEvent(AlphaBanks* event);
//! get the next event
  virtual AlephRC GetEvent(AlphaBanks*);
protected:

// constructor and destructor
  AlephDbManager();
  virtual ~AlephDbManager();

private:

  // the pointer to the single static instance
  static AlephManager* _theAlephDbManager;
  // the current database name
  string _dbName;                       
  // the transaction type
  AlephTransaction _theTransactionType;   // can be reading,update,halted
};





#endif
