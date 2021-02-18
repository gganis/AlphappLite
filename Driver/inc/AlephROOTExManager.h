//////////////////////////////////////////////////////
//
//  Class AlephROOTExManager
//
//  The specific execution manager in case we use ROOT files
//  It inherits from AlephExManager
//  It is a singleton.
//
//  Author : C. Delaere  ,  15.08.2002
//
//////////////////////////////////////////////////////

#ifndef ALEPHROOTEXMANAGER_H
#define ALEPHROOTEXMANAGER_H

///////////////////////////////////////////////////////////
// the includes
///////////////////////////////////////////////////////////
#include "AlephExManager.h"
#include "AlephDbManager.h"

//! the execution manager used when running on ROOT input

class AlephROOTExManager : public AlephExManager 
{
public:

// declare the AlephExManager base class also as friend.
// Then the constructor can stay protected which avoids multiple
// creation from a client 
  friend class AlephExManager;
//! the initialization step 
  virtual AlephRC initialize(); 
//! the running step
  virtual AlephRC run();
//! the terminating step 
  virtual AlephRC terminate(); 
protected:

// constructor and destructor
  AlephROOTExManager();
  virtual ~AlephROOTExManager();
// some execution routines
  // if in batch mode
  // loop over databases, runs and events, actually calls next two routines
  virtual AlephRC loopAll();   
  // reading loop
  virtual AlephRC loopAllRead();
  // writing loop
  virtual AlephRC loopAllWrite();
  // if in interactive mode
  // loop over databases, runs and events, actually calls next two routines
  virtual AlephRC loopInter();   
  // reading loop
  virtual AlephRC loopInterRead();
  // writing loop
  virtual AlephRC loopInterWrite();
};

#endif
