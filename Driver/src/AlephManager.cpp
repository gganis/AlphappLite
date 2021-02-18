//////////////////////////////////////////////////////
//
//  Implementation of class AlephManager
//
//  The Base Class for an AlephManager (IO, DB, EXE,...)
//
//  Author : G. Dissertori  ,  02.11.98
//
//////////////////////////////////////////////////////


#include <string>
#include <iostream>
#include <fstream>

#include "AlephManager.h"

extern ofstream fout;


//
// the "constructor" sets the managerType and initializes other
// private members 
//
void AlephManager::AlephManagerSetup(const string& aManagerType)
{

  // store the manager type
  _thisManagerType.assign(aManagerType);

  // set the pointer to the session
  _theSession = AlephSession::TheAlephSession();


  // set the status
  _theStatus = CREATED;
}

//
// the "destructor" frees the heap
//
void AlephManager::AlephManagerShutDown()
{
  _theStatus = DELETED;
}


//
// get the pointer to the session
//
AlephSession* AlephManager::alephSession() const
{
  return _theSession;
}



//
// get the managerType
//
string AlephManager::managerType() const
{
  return _thisManagerType;
}

 
//
// set the status
//
void AlephManager::setStatus(const AlephStatus& statusNow)
{
  _theStatus = statusNow;
}


//
// get the status
//
AlephStatus AlephManager::status() const
{
  return _theStatus;
}




