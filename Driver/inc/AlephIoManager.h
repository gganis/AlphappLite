//////////////////////////////////////////////////////
//
//  Class AlephIoManager
//
//  The class which handles the Input/Ouput
//  It inherits from AlephManager
//  It is a singleton
//
//  Author : G. Dissertori  ,  02.11.98
//
//////////////////////////////////////////////////////


#ifndef ALEPHIOMANAGER_H
#define ALEPHIOMANAGER_H

#include "AlephManager.h"
#include "AlephCardsReader.h"
#include "AlephNtupleWriter.h"

//! the input-output manager
class AlephIoManager : public AlephManager 
{

public:

//! the instance function of the  Singleton
  static AlephManager* TheAlephIoManager();


//! the initialization step 
  virtual AlephRC initialize(); 


//! the running 
  AlephRC run(); 

//! the terminating step 
  virtual AlephRC terminate(); 

//! return the pointer to the Cards Reader
  virtual AlephCardsReader& theCardsReader();

//! return the pointer to the Ntuple Writer
  virtual AlephNtupleWriter& theNtupleWriter();

protected:

// constructor and destructor
  AlephIoManager();
  ~AlephIoManager();


private:

// the pointer to the single static instance
  static AlephManager* _theAlephIoManager;

// the Card Reader
  AlephCardsReader _theCardsReader;

// the Ntuple Writer
  AlephNtupleWriter _theNtupleWriter;

};

#endif

