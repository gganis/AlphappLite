//////////////////////////////////////////////////////
//
//  Implementation of class AlephIoManager
//
//  Author : G. Dissertori  ,  02.11.98
//
//////////////////////////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "AlephIoManager.h"

extern ofstream fout;

//
// set the global instance variable
//
AlephManager* AlephIoManager::_theAlephIoManager=0;

//
// the instance function of the  Singleton
//
AlephManager* AlephIoManager::TheAlephIoManager()
{
// check out which manager has to be produced
  if (_theAlephIoManager == 0) 
  {
    // here also the cards reader is created and starts its constructor
    _theAlephIoManager = new AlephIoManager;
  }
  return _theAlephIoManager;
} 


//
// the constructor
//
AlephIoManager::AlephIoManager()
{
  // call the constructor of the base class
  AlephManagerSetup("IoManager");
}


//
// the destructor
//
AlephIoManager::~AlephIoManager()
{
  AlephManagerShutDown();
}

//
// the initialization step
//
AlephRC AlephIoManager::initialize()
{
  
  // say something
  fout << " AlephIoManager :  initializing .... " << endl;

  // initialize the members
  int mode;
  if ((strrchr(_theCardsReader.getHist().c_str(),'.') == NULL)||(strcmp(strrchr(_theCardsReader.getHist().c_str(),'.'),".root"))) mode = 2; 
  else mode = 1;
  _theNtupleWriter.Initialize(&_theCardsReader, mode);

  // set the status
  setStatus(INITIALIZED); 

  return AlephOK;
}


//
// the running step
//
AlephRC AlephIoManager::run()
{
  
  // say something
  fout << " AlephIoManager :  running .... " << endl;


  // set the status
  setStatus(RUNNING); 

  return AlephOK;
}


//
// the termination step
//
AlephRC AlephIoManager::terminate()
{
  
  // say something
  fout << " AlephIoManager :  terminating .... " << endl;

  // terminate the members
  _theNtupleWriter.Terminate();

  // set the status
  setStatus(TERMINATED); 

  return AlephOK;
}

// return the pointer to the cards reader
AlephCardsReader& AlephIoManager::theCardsReader()
{
  return _theCardsReader;
}

// return the pointer to the ntuple writer
AlephNtupleWriter& AlephIoManager::theNtupleWriter()
{
  return _theNtupleWriter;
}

