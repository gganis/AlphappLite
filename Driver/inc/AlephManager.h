//////////////////////////////////////////////////////
//
//  Class AlephManager
//
//  The Base Class for an AlephManager (IO, DB, EXE,...)
//  no instances of this class can be created
//
//  Author : G. Dissertori  ,  02.11.98
//
//////////////////////////////////////////////////////


#ifndef ALEPHMANAGER_H
#define ALEPHMANAGER_H

#include <string>
#include "AlephSession.h"


// status info
enum AlephStatus { CREATED , INITIALIZED , RUNNING , 
		   TERMINATED ,  DELETED , UNKNOWN  };


//! the general Manager
class AlephManager {

public:

//
// first the purely virtual functions
//
//! the initialization step 
  virtual AlephRC initialize() = 0; 

//! the terminating step 
  virtual AlephRC terminate() = 0; 


//
// now  the non-purely virtual functions
//

//! destructor 
  virtual ~AlephManager() {};

//! do a setup (similar to a constructor)
  void AlephManagerSetup(const string& aManagerType);

//! do a shutdown (similar to a destructor)
  void AlephManagerShutDown();

//! get the pointer to the session
  virtual AlephSession* alephSession() const;


// monitoring
  //! get the manager type
  virtual string managerType() const;

  //! set the status
  virtual void setStatus(const AlephStatus& statusNow);

  //! get the status
  virtual AlephStatus status() const;


private:

// the character string describing the manager type
  string _thisManagerType;

// pointer to the session
  AlephSession* _theSession;


// monitoring
  AlephStatus _theStatus;

};





#endif
