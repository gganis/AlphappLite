//////////////////////////////////////////////////////
//
//  Implementation of class AlephSession
//
//  The Base Class for an AlephSession.
//  It is a Singleton
//
//  Author : G. Dissertori  ,  30.10.98
//  Modified: C. Delaere    ,  16.08.02 renewed timing
//
//////////////////////////////////////////////////////

#include <fstream>
#include "AlephSession.h"
#include "AlephIoManager.h"
#include "AlephDbManager.h"
#include "AlephExManager.h"

extern ofstream fout;

//
// set the global instance variable
//
AlephSession* AlephSession::_theAlephSession=0;

//
// implementation of the instance member
//
AlephSession* AlephSession::TheAlephSession()
{
  if (_theAlephSession == 0) 
  {
    _theAlephSession = new AlephSession;
  } 
  return _theAlephSession;

}

//
// the constructor sets the default sessionType and initializes other
// private members 
//
AlephSession::AlephSession()
{
  // set the default session type
  _thisSessionType = "BATCH";
  _startTime = 0;
  _endTime   = 0;
  _theAlephIoManager=0;
  _theAlephDbManager=0;
  _theAlephExManager=0;
}

//
// the destructor clears the memory
//
AlephSession::~AlephSession()
{
  //  call the destructor of the managers
  //  _theAlephIoManager->~AlephIoManager();
  //  _theAlephDbManager->~AlephDbManager();
  //  _theAlephExManager->~AlephExManager();
}

//
// the setSessiontype Method
//
void AlephSession::setSessionType(const string& theType)
{
  // analyze the character string, just the first 5 characters 
  string theTypeShort;
  theTypeShort.resize(5);
  int i;
  for (i=0 ; i<5 ; i++)
  {
    theTypeShort[i] = toupper(theType[i]);
  }
  if (!theTypeShort.compare("BATCH"))
  {
    _thisSessionType = "BATCH";
  }
  else
  if (!theTypeShort.compare("INTER"))
  {
    _thisSessionType = "INTER";
  }
  fout << " The session is set to type " << _thisSessionType << endl;
}

//
// get the sessiontype Method
//
string AlephSession::sessionType() const
{
  return _thisSessionType;
}

//
// get the pointer to a specific manager, defined by the input string
//
AlephManager* AlephSession::aAlephManager(const string& aManager) const
{
  // compare the string
  if (!aManager.compare("IoManager"))
      return _theAlephIoManager;
  else
  if (!aManager.compare("DbManager"))
      return _theAlephDbManager;
  else
  if (!aManager.compare("ExManager"))
      return _theAlephExManager;
  else
  {
    fout << "AlephSession : there is no manager of type " << aManager 
         << " !  Warning : returning NULL pointer " << endl;
    return 0;
  }
}

//
// monitoring :  grap the starting time
//
void AlephSession::startTimer(bool precision)
{
  if(precision)
  	_startClock = clock();
  else
  	_startTime = time(0);
}

//
// monitoring :  grap the ending time
//
void AlephSession::stopTimer(bool precision)
{
  if(precision)
  	_endClock = clock();
  else
        _endTime = time(0);
}

//
// debug level setting and getting
//
void AlephSession::setDebugLevel(const int& aLevel)
{
  _debugLevel = aLevel;
}

int AlephSession::debugLevel() const
{
  return _debugLevel;
}

//
// the initialization step
//
AlephRC AlephSession::initialize()
{
  AlephRC rc;
  // start the timer
  startTimer();
  startTimer(true);
  // print out some stuff
  const  time_t aStartTime = _startTime; 
  struct tm* aTimePointer = gmtime(&aStartTime);
  char* aTimeCharA = asctime(aTimePointer);
  // need this manipulation to cut out the newline character created by asctime
  char* aTimeCharB = new char[strlen(aTimeCharA)];
  strncpy(aTimeCharB,aTimeCharA,strlen(aTimeCharA)-1);

  fout << "**************************************************" << endl;
  fout << "*                                                *" << endl;
  fout << "*                  ALEPHSESSION                  *" << endl;
  fout.setf(ios::showpoint);
  fout.precision(2);
  fout << "*                  Version  " << AlephSessionVersion 
       << "                  *" << endl;
  fout << "*                                                *" << endl;
  fout << "*     The session has been initialized at:       *" << endl;
  fout << "*           " << aTimeCharB <<     "             *" << endl;
  fout << "*                                                *" << endl;
  fout << "**************************************************" << endl;

  fout.precision(6);
  delete[] aTimeCharB;

  cout << "    **************************************************" << endl;
  cout << "    *                                                *" << endl;
  cout << "    *                     ALPHA++                    *" << endl;
  cout << "    *                                                *" << endl;
  cout << "    *    You can find more outputs in the file       *" << endl;
  cout << "    *    defined with the APPL_OUT env. variable.    *" << endl;
  cout << "    *                                                *" << endl;
  cout << "    **************************************************" << endl;

  cout << endl << endl << "Initialisation of ALPHA++ managers..." << endl;
  // create and init the various managers
  // the IO manager
  _theAlephIoManager = AlephIoManager::TheAlephIoManager();
  rc = _theAlephIoManager->initialize();
  // the DB manager
  _theAlephDbManager = AlephDbManager::TheAlephDbManager();
  rc = _theAlephDbManager->initialize();
  // the Ex manager
  _theAlephExManager = AlephExManager::TheAlephExManager();
  rc = _theAlephExManager->initialize();
  // precise time report for the initialisation
  stopTimer(true);
  init_time = ( _endClock - _startClock)/(CLOCKS_PER_SEC / (double) 1000.0);
  fout << endl << "Session initialized in " << init_time << " miliseconds" << endl;
  return rc;
}

//
// the running step
//
AlephRC AlephSession::run()
{
  AlephRC rc;
  // Say Hello...
  fout << " AlephSession starts running ... " << endl;
  cout << "AlephSession starts running ... " << endl<< endl<< endl;
  // run the execution manager
  startTimer(true);
  rc = ((AlephExManager*)_theAlephExManager)->run();
  stopTimer(true);
  run_time = ( _endClock - _startClock)/(CLOCKS_PER_SEC / (double) 1000.0)/(double) 1000.0;
  // Say Goodbye...
  cout << endl << endl << endl << "AlephSession stops running ... " << endl;
  fout << " AlephSession stops running ... " << endl;
  return rc;
}

//
// the terminating step
//
AlephRC AlephSession::terminate()
{
  AlephRC rc;
  // start the timer
  startTimer(true);
  // a last comment...
  cout <<  "Termination of ALPHA++ managers..." << endl << endl;
  // send the terminate to the various managers
  // order is important : it is the inverse order of initialization
  // the Ex manager
  long EventCount = ((AlephExManager*)_theAlephExManager)->getEventCount();
  rc = _theAlephExManager->terminate();
  // the DB manager
  rc = _theAlephDbManager->terminate();
  // the IO manager
  rc = _theAlephIoManager->terminate();
  // stop the timer
  stopTimer();
  stopTimer(true);
  // compute finally elapsed time
  run_time = difftime(_endTime,_startTime) > 900 ? difftime(_endTime,_startTime) : run_time;
  // print out some stuff
  const  time_t aEndTime = _endTime; 
  struct tm* aTimePointer = gmtime(&aEndTime);
  char* aTimeCharA = asctime(aTimePointer);
  // need this manipulation to cut out the newline character created by asctime
  char* aTimeCharB = new char[strlen(aTimeCharA)];
  strncpy(aTimeCharB,aTimeCharA,strlen(aTimeCharA)-1);
  
  term_time = ( _endClock - _startClock)/(CLOCKS_PER_SEC / (double) 1000.0);
  fout << "Session terminated in " << term_time << " miliseconds" << endl << endl;

  fout << "**************************************************" << endl;
  fout << "*                                                *" << endl;
  fout << "*                  ALEPHSESSION                  *" << endl;
  fout.setf(ios::showpoint);
  fout.precision(2);
  fout << "*                  Version  " << AlephSessionVersion 
       << "                  *" << endl;
  fout << "*                                                *" << endl;
  fout << "*        The session has terminated at:          *" << endl;
  fout << "*           " << aTimeCharB <<      "            *" << endl;
  fout << "*                                                *" << endl;
  fout.precision(10);
  fout << "*   Elapsed time in seconds = " << run_time << 
          "        *" << endl;
  fout << "**************************************************" << endl;

  fout.precision(6);
  delete[] aTimeCharB;

  cout << " ------------ " << endl;
  cout << " Time Report: " << endl;
  cout << " ------------ " << endl;
  cout << "    Initialisation : " << init_time << " miliseconds" << endl;
  cout << "    Running : " << endl;
  cout << "         " << EventCount << " events : " << run_time << " seconds" << endl;
  cout << "         " << "1 event : " << ( EventCount > 0 ? (run_time/EventCount)*1000 : 0. ) << " miliseconds" << endl;
  cout << "    Termination : " << term_time << " miliseconds" << endl;
  cout << " ------------ " << endl << endl;

  cout << "    **************************************************" << endl;
  cout << "    *                                                *" << endl;
  cout << "    *                     ALPHA++                    *" << endl;
  cout << "    *                                                *" << endl;
  cout << "    *      The session has terminated normaly        *" << endl;
  cout << "    *              Have a nice Day ;-)               *" << endl;
  cout << "    *                                                *" << endl;
  cout << "    **************************************************" << endl << endl;
  
  return AlephOK;
}
