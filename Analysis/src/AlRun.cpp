////////////////////////////////////////////////////////////////////
//
// Implementation of class AlRun
//
//
////////////////////////////////////////////////////////////////////


#include "AlRun.h"

// default constructor : does nothing
AlRun::AlRun()  {}  

// copy constructor :
AlRun::AlRun(const AlRun& oldRun) 
{ 
   qhac = oldRun.qhac;
   qext = oldRun.qext;
}

// Energy
/*!
 * The best energy (QELEP) is provided by the event energy.
 * Here, only run energy, as provided by Lep
 */
int AlRun::Energy() const
{
  if ((qext->LP) != (RLEP*) NULL) 
     return qext->LP->LE;
  else
     return -1;
};

// Experiment number
int AlRun::ExperimentNumber() const
{
  if ((qhac->EH) != (EVEH*) NULL) 
     return qhac->EH->EN;
  else
     return -1;
};

// run number
int AlRun::number() const
{
  if ((qhac->EH) != (EVEH*) NULL) 
     return qhac->EH->RN;
  else
     return -1;
};

// run type
int AlRun::type() const
{
  if ((qhac->EH) != (EVEH*) NULL) 
     return qhac->EH->RT;
  else
     return -1;
};

