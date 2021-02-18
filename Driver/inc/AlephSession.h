//////////////////////////////////////////////////////
//
//  Class AlephSession
//
//  The Base Class for an AlephSession.
//  It is a Singleton
//
//  Author : G. Dissertori  ,  30.10.98
//  Modified: C. Delaere    ,  16.08.02 renewed timing
//
//////////////////////////////////////////////////////

#ifndef ALEPHSESSION_H
#define ALEPHSESSION_H

#include <string>
#include <time.h>
using namespace std;
// set the version
static float AlephSessionVersion = 1.1;
// enumeration of return values
enum AlephRC { AlephOK=1 , AlephERROR=0 };
// forward declaration of the AlephManager
class AlephManager;
//! Main Alpha++ object. Instanciated in alpha++_main
class AlephSession {
public:

//! the instance function of the  Singleton
  static AlephSession* TheAlephSession();
//! set the session type
  void setSessionType(const string& theType);
//! get the session type
  string sessionType() const;
//! the initialization step 
  AlephRC initialize(); 
//! the running step 
  AlephRC run(); 
//! the terminating step 
  AlephRC terminate(); 
//! get a pointer to a specific manager
  AlephManager* aAlephManager(const string& aManager) const;
// monitoring
  void startTimer(bool precision=false);
  void stopTimer(bool precision=false);
//! set the debug output level 
  void setDebugLevel(const int& aLevel);
//! get the debug output level
  int  debugLevel() const;

protected:

// the protected constructor
  AlephSession();
// the protected destructor
  ~AlephSession();

private:

// the pointer to the single static instance
  static AlephSession* _theAlephSession;
// the character string describing the session type
  string _thisSessionType;
// pointers to the various manager
  AlephManager* _theAlephDbManager;   // database manager
  AlephManager* _theAlephIoManager;   // IO manager
  AlephManager* _theAlephExManager;   // execution manager
// monitoring
  time_t  _startTime;     //starting time
  time_t  _endTime;       //ending time
  clock_t _startClock;
  clock_t _endClock;
  double init_time;
  double run_time;
  double term_time;
// debug output level
  int _debugLevel;
};





#endif
