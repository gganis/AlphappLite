//////////////////////////////////////////////////////////
//
// CLASS AlEvent 
// Concrete class for AlEvent Object 
//
///////////////////////////////////////////////////////////
 

#ifndef _ALEVENT_H_
#define _ALEVENT_H_

#include "BankClasses.h"
class TimeInfo;
class AlRun;

class AlEvent {

public:
  
  //! constructor
  AlEvent();

  //! copy constructor
  AlEvent(const AlEvent&);

  //! Time information
  TimeInfo Time() const;

  //! Event number
  int number() const;

  //! Event type
  int type()const;

  //! EDIR class
  int EdirClass()const;

  //! Error Status
  int ErrorStatus()const;

  //! Energy
  float Energy()const;

  //! E12 generator for MC.
  float gen_e12(float qelep)const;

  //! XLUMOK
  bool xlumok(float qelep, int mode = 0)const;

  //! DECTRG
  bool IsTrigger(bool MINI)const;

  //! ALTRIG
  int GetRawTrigger()const;

  //! set the pointer to QHAC
  void SETqhac(QHAC*);

  //! get the pointer to QHAC
  QHAC* GETqhac() {return qhac;}
  
  KEVH* GeneratorStatus()const;
  vector<KWGT*>* GeneratorWeights()const;
  float getGeneratorWeight(int Number=0)const;

private:
  // misc banks pointers
  EVEH* Header()const;
  REVH* ReconstructorHeader()const;
  vector<LOLE*>* LcalErrorFlags()const;
  vector<X1RG*>* Readout()const;
  BOMB* BeamPosition()const;
  vector<XTBN*>* TriggerBitNames()const;
  XTCN* TriggerLevelControl()const;
  XTOP* TriggerOptions()const;
  LUPA* LuminosityParameters()const;
  SILH* SicalLuminosityParameters()const;
  vector<XHVB*>* HVfixes()const;
  XTEB* TriggerLevelEventBitPattern()const;
  XTRB* TriggerLevelRegisterBitPattern()const;
  DTBP* TriggerBitPattern()const;
  vector<VHBV*>* VDETbit()const;
  vector<VHPV*>* NoHVbit()const;
  EAUX* ENFLWinfo()const;
  SIX2* SicalTriggerX2()const;
  vector<X1TV*>* Triggerlevel1Threshold()const;
  vector<X1IP*>* Triggerlevel1Input()const;
  vector<SIXA*>* SicalTriggerSectorsAdc()const;
  SITC* SicalTriggerConditions()const;
  vector<SRCO*>* SicalRunConditions()const;
  vector<X1TH*>* TriggerOldlevel1Threshold()const;
  vector<X1AD*>* Triggerlevel1Adc()const;
  // pointers to the banks
  QHAC* qhac;
  // functions internally used for e12 calculation
  float e12_produce(double thr, double c1, double c2, double c3, float qelep, float (AlEvent::*fp)(float x1) const)const;
  float r183_e12(float x1)const;
  float r189_e12(float x1)const;
  float r192_e12(float x1)const;
  float r196_e12(float x1)const;
  float r200_e12(float x1)const;
  float r202_e12(float x1)const;
  float r205_e12(float x1)const;
  float r207_e12(float x1)const;
  // functions internally used for xlumok calculation
  bool EnergyStability(float qelep)const;
  int EnabledTriggers()const;
  vector<bool> HVStatus()const;
  bool TimeSynchronization()const;
  bool LaserEvent()const;
  bool VDETstatus()const;
  // functions internally used for dectrg calculation
  void RedoTrigger()const;
  void RedoOldTrigger()const;
  void SimulateTrigger(int*,int*,int*,int*,int*)const;
  void SimulateOldTrigger(int*,int*,int*,int*,int*,int*,int*,int*,int*)const;
  void SimulateSicalTrigger()const;
  void ApplyTrigger(int*,int*,int*,int,int)const;
  void ApplyOldTrigger(int*,int*,int*BIT,int*,int*,int*,int)const;
  // STATIC members
  // SIsetup has to be static because it is defined only for the first event of the run
  static int SIsetup;
  // masks obtained from XTBN have to be static for the same reason.
  static int mask1, mask2, mask3, tmask;
};

#endif
