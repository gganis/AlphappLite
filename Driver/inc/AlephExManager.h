
//
//  Class AlephExManager
//
//  The class responsible for the execution = run over data
//  It inherits from AlephManager.
//  It is a singleton
//
//  Author : G. Dissertori  ,  10.08.99
//
//////////////////////////////////////////////////////

#ifndef ALEPHEXMANAGER_H
#define ALEPHEXMANAGER_H

#include "AlObject.h"
#include "AlphaBanks.h"
#include "AlephManager.h"
#include "AlephDbManager.h"
#include "AlephIoManager.h"
#include "AlephCardsReader.h"
#include "AlephNtupleWriter.h"

// the AlephExManager class
class AlephExManager : public AlephManager {

public:

// the instance function of the  Singleton
  static AlephManager* TheAlephExManager(); 
// the initialization step 
  virtual AlephRC initialize(); 
// the user init
  void UserInit();
// the running 
  virtual AlephRC run(); 
// the user running
  bool UserEvent(AlphaBanks& );
// the terminating step 
  virtual AlephRC terminate(); 
// the user termination
  void UserTerm();
// some general utility 
  // set current run and event number
  void setCurrentRunEvt(const long& CurrentRun,
                        const long& CurrentEvt);
  // get current Run number
  long getCurrentRun() const;
  // get current Evt number
  long getCurrentEvt() const;
  // get the event counter
  long getEventCount() const;
  // give pointers to managers (nice for the user)
  AlephSession*       theSession() const;
  AlephDbManager*     theDbm()     const;
  AlephIoManager*     theIom()     const;
  AlephCardsReader*   theCardsReader() const;
  AlephNtupleWriter*  theNtupleWriter() const;
  
protected:

// constructor and destructor
  AlephExManager();
  virtual ~AlephExManager();
// the pointer to the database manager
  AlephDbManager* _theDbManager;
// event counter
  long EventCount;

 private:

// the pointer to the single static instance
  static AlephManager* _theAlephExManager;
// current run and event number
  long _currentRun;
  long _currentEvt;
};

#endif

