////////////////////////////////////////////////////////////////////
//
// Implementation of class AlEvent
//
//
////////////////////////////////////////////////////////////////////


#include "AlEvent.h"
#include "TimeInfo.h"
#include <math.h>
#include <string.h> 
#include "TRandom3.h"


// default constructor : do nothing
AlEvent::AlEvent()  {}

// copy constructor :
AlEvent::AlEvent(const AlEvent& oldEvent) { 
   qhac = oldEvent.qhac;
}

// Static values
int AlEvent::SIsetup=-1;
int AlEvent::mask1 = 0;
int AlEvent::mask2 = 0;
int AlEvent::mask3 = 0;
int AlEvent::tmask = 0;

EVEH* AlEvent::Header()const{return qhac->EH;}
KEVH* AlEvent::GeneratorStatus() const{return qhac->KE;}
REVH* AlEvent::ReconstructorHeader() const{return qhac->RE;}
vector<LOLE*>* AlEvent::LcalErrorFlags() const{return &(qhac->LO);}
vector<X1RG*>* AlEvent::Readout() const{return &(qhac->X1);}
BOMB* AlEvent::BeamPosition() const{return qhac->BO;}
vector<XTBN*>* AlEvent::TriggerBitNames() const{return &(qhac->BN);}
XTCN* AlEvent::TriggerLevelControl() const{return qhac->CN;}
XTOP* AlEvent::TriggerOptions()const{return qhac->OP;}
LUPA* AlEvent::LuminosityParameters()const{return qhac->LP;}
SILH* AlEvent::SicalLuminosityParameters()const{return qhac->SI;}
vector<XHVB*>* AlEvent::HVfixes()const{return &(qhac->HV);}
XTEB* AlEvent::TriggerLevelEventBitPattern()const{return qhac->EB;}
XTRB* AlEvent::TriggerLevelRegisterBitPattern()const{return qhac->RB;}
DTBP* AlEvent::TriggerBitPattern()const{return qhac->BP;}
vector<VHBV*>* AlEvent::VDETbit()const{return &(qhac->BV);}
vector<VHPV*>* AlEvent::NoHVbit()const{return &(qhac->PV);}
EAUX* AlEvent::ENFLWinfo()const{return qhac->EX;}
SIX2* AlEvent::SicalTriggerX2()const{return qhac->X2;}
vector<X1TV*>* AlEvent::Triggerlevel1Threshold()const{return &(qhac->TV);}
vector<KWGT*>* AlEvent::GeneratorWeights() const{return &(qhac->KW);}
vector<X1IP*>* AlEvent::Triggerlevel1Input()const{return &(qhac->IP);}
vector<SIXA*>* AlEvent::SicalTriggerSectorsAdc()const{return &(qhac->XA);}
SITC* AlEvent::SicalTriggerConditions()const{return qhac->TC;}
vector<SRCO*>* AlEvent::SicalRunConditions()const{return &(qhac->CO);}
vector<X1TH*>* AlEvent::TriggerOldlevel1Threshold()const{return &(qhac->TH);}
vector<X1AD*>* AlEvent::Triggerlevel1Adc()const{return &(qhac->XD);}
      
void AlEvent::SETqhac(QHAC* bank) {qhac = bank;}

// Time Information
TimeInfo AlEvent::Time()const
{
  if (qhac->EH != (EVEH*) NULL)
    {
       TimeInfo summary(qhac->EH->DA,qhac->EH->TI);
       return summary;
    }
  else
    {
      TimeInfo summary;
      summary.sec   = -1;
      summary.min   = -1;
      summary.hour  = -1;
      summary.day   = -1;
      summary.month = -1;
      summary.year  = -1;
      return summary;
    }
}

// Event number
int AlEvent::number()const
{
  if (qhac->EH != (EVEH*) NULL) 
     return qhac->EH->EV;
  else
     return -1;
}

// Event type
int AlEvent::type()const
{
  if (qhac->EH != (EVEH*) NULL) 
     return qhac->EH->TY;
  else
     return -1;
}

// EDIR class
int AlEvent::EdirClass()const
{
  if (qhac->RE != (REVH*) NULL)
     return qhac->RE->EC;
  else
     return 0;
}
	  
// Error Status
int AlEvent::ErrorStatus()const
{
  if (qhac->EH != (EVEH*) NULL) 
     return qhac->EH->ES;
  else
     return -1;
}

// Energy
float AlEvent::Energy()const
{
  if (qhac->EH != (EVEH*) NULL) 
     return (float(qhac->EH->TE))/1000000.;
  else
     return -1;
/*
  float value = 0;
  QELEP_ALPHA(value);
  return value;
*/
}

// E12 generator for MC.
float AlEvent::gen_e12(float qelep)const
{
  float e12;
  if (qelep<180)
	e12=0;
  else if (qelep<185)
	  if (gRandom->Rndm()>0.046) e12=0;
       	  else {float y; do { e12=gRandom->Rndm()*70; y=gRandom->Rndm()*700;} 
	       while (y > r183_e12(e12));}	  
  else if (qelep<190)
	  e12=e12_produce(0.08736,3.,3.3,1200.,qelep,&AlEvent::r189_e12);
  else if (qelep<194)
	  e12=e12_produce(0.08761,3.,3.35,300.,qelep,&AlEvent::r192_e12);
  else if (qelep<198)
	  e12=e12_produce(0.09738,3.,3.35,600.,qelep,&AlEvent::r196_e12);
  else if (qelep<201)
	  e12=e12_produce(0.08761,3.,3.35,600.,qelep,&AlEvent::r200_e12);
  else if (qelep<203)
	  e12=e12_produce(0.07973,3.,3.35,300.,qelep,&AlEvent::r202_e12);
  else if (qelep<206)
	  e12=e12_produce(0.09497,3.,3.35,700,qelep,&AlEvent::r205_e12);
  else    e12=e12_produce(0.08784,3.,3.35,1000,qelep,&AlEvent::r207_e12);
  return e12;
}

// XLUMOK
// Energy is wanted as input so that the user uses the best known value.
// May be put (later) directly in the routine using AlEvent::Energy();
// mode:
//   0: standard (like alpha's xlumok)
//   1: allow miniramps (like alpha's xlum2k)
//   2: select only miniramps
bool AlEvent::xlumok(float qelep, int mode)const
{
  // the last run proceeded is kept for faster use
  static int lastrun = 0;
  static int xtgenb = 0;
  if (qhac->AD != (ADBR*)NULL) SIsetup = qhac->AD->SI;
  if (SIsetup < 0) return false;
  int runnum;
  if ((qhac->EH) != (EVEH*) NULL)
     runnum = qhac->EH->RN;
  else  return false; // no run number: bad
  // MC
  if (runnum < 2001) return ( (SIsetup >= 0) && VDETstatus() );
  // data
  if (runnum != lastrun) {lastrun=runnum; xtgenb = EnabledTriggers();} // only if run changed
  else if (xtgenb < 4) xtgenb = EnabledTriggers();   // if 1st event reject
  // exclude laser events
  if (LaserEvent()) return false;
  // get and combine HV info
  vector<bool> XHV = HVStatus();
  bool XHVTR = XHV[15] && XHV[5];
  bool XHVE  = XHV[0]  && XHV[1]  && XHV[2];
  bool XHVH  = XHV[7]  && XHV[8]  && XHV[9];
  bool XHVTG = XHV[13] && XHV[14];
  bool XHVOK = XHVTR   && XHVE    && XHVH    && XHVTG;
  bool XHVL  = XHV[3];
  bool XHVS  = XHV[10];
  // get t0 sync info
  bool XT0 = TimeSynchronization();
  // combine info collected
  bool LL = (SIsetup>=6) && XHVOK && XHVL && XT0;
  bool SL = ((SIsetup==5)||(SIsetup==7)) && XHVOK && XHVS && XT0;
  if ((runnum>20000)&&(runnum<40000)) LL = (SIsetup>=4) && XHVOK && XHVL && XT0;
  if (runnum>40000) SL = (SIsetup>=4) && XHVOK && XHVS && XT0;
  bool XL = LL && ( SL || (SIsetup==0));
  if (runnum > 45000) XL = ( XL && VDETstatus() );
  if (mode == 0)      // mode 0 : standard
    return (XL && EnergyStability(qelep));
  else if (mode == 1) // mode 1 : include miniramps
    return XL;
  else if (mode == 2) // mode 2 : select only miniramps
    return (XL && !EnergyStability(qelep));
  else return 0;      // should never be here...
}

// Trigger decoding
// input: MINI=1 if mini proceeded, else 0
// output: true if trigger ok (fine event)
bool AlEvent::IsTrigger(bool MINI)const
{
  int pattern=0;
  int runnum;
  if ((qhac->EH) != (EVEH*) NULL)
      runnum = qhac->EH->RN;
  else
      runnum = -1;		    
  if( MINI && (ENFLWinfo() != NULL)) pattern = ENFLWinfo()->TR;
  else 
    {
      if (runnum < 4000) 
        {
          if (Readout() != NULL) RedoTrigger();
          else RedoOldTrigger();
        }
      pattern = GetRawTrigger();
    }
  // build triggers
  // itrg1: Energy based triggers
  // first: ECAL Barrel Total Energy and ECAL endcap coincidence
  int itrg1 = 8*((pattern>>17)&1) + ((pattern>>20)&1);
  // then Endcaps total energy
  itrg1 += 2*((pattern>>(((runnum<6000)&&(Readout()->size()==0))?24:18))&1);
  itrg1 += 4*((pattern>>(((runnum<6000)&&(Readout()->size()==0))?25:19))&1);
  // itrg2: muons triggers
  int itrg2 = ((pattern>>8)&1) + 2*((pattern>>9)&1);
  // return result
  return ((itrg1!=0)||(itrg2!=0));     
}

// Altrig (first word only)
int AlEvent::GetRawTrigger()const
{
  int pattern;
      if(Readout()->size() != 0)
        {
          for(vector<X1RG*>::iterator iter=Readout()->begin();iter<Readout()->end();iter++)
           {
             char tmp[5];
             strncpy(tmp,(*iter)->NA,4); // copy the bank word
             tmp[4] = '\0';
             if ((strcasecmp(tmp, "TPR ") == 0 )|| (strcasecmp(tmp, " RPT") == 0 ))
                 pattern = ((*iter)->CO[0]);
           }
        }
      else if(TriggerLevelRegisterBitPattern() != NULL)
               pattern = TriggerLevelRegisterBitPattern()->RP[0];
      else if(TriggerLevelEventBitPattern() != NULL)
	       pattern = TriggerLevelEventBitPattern()->T1;
      else if(TriggerBitPattern() != NULL)
               pattern = TriggerBitPattern()->T1;
      else if(LuminosityParameters() != NULL)
	       pattern = LuminosityParameters()->T1;
      else if(SicalLuminosityParameters() != NULL)
               pattern = SicalLuminosityParameters()->T1;
      else pattern = 0; // no trigger bank !!!
return pattern;
}

// functions internally used for e12 calculation

float AlEvent::e12_produce(double thr, double c1, double c2, double c3, float qelep, float (AlEvent::*fp)(float x1)const)const
{
        float x1,y;
        y=gRandom->Rndm();
	if (y>thr) return 0;
	do
	{
		x1=gRandom->Rndm()*c1-c2;
		y=gRandom->Rndm()*c3;
	}
	while (y > (this->*fp)(x1));
	return pow(10,x1)*qelep;
}


/*------------------------------------------------------------------------
 Distribution of E12 for 183 GeV random triggers. E12 /= 0 in 4.6% of
 random events. The distribution of E12 with a 100MeV binning between 0
 and 70 GeV is given by this function (max entry in a bin = 700 evts)
------------------------------------------------------------------------*/
float AlEvent::r183_e12(float x1)const
{
  float r183;
  if      ( x1 < 0.4 ) r183 = 605.*exp(-pow((x1-0.34),2)/0.03);
  else if ( x1 < 3. )  r183 = 997.*(1.-exp(-5.*x1))*exp(-1.18*x1);
  else if ( x1 < 70. ) r183 = 270.*exp(-0.73*x1)+2.4-0.02*x1 ;
  else                 r183 = -999.;
  return r183;
}

/*------------------------------------------------------------------------
 Distribution of E12 for 189 GeV random triggers. E12 > 0 in 8.736% of
 random events. The distribution of xl=log10(E12/Elep) with a 0.05 binning 
 between -3.3 and -0.3 is given by this function (max entry in a bin=1200)
------------------------------------------------------------------------*/
float AlEvent::r189_e12(float xl)const
{
  float r189;
  r189 = exp(-70.6-22.74*xl);
  r189 += 416.*exp(-0.5*pow(((xl+2.696)/0.1617),2));
  r189 += 1119.*exp(-0.5*pow(((xl+2.254)/0.3535),2));
  r189 += 188.*exp(-0.5*pow(((xl+1.030)/0.2688),2));
  r189 += 397.*exp(-0.5*pow(((xl+0.526)/0.0552),2));
  return r189;
}

/*------------------------------------------------------------------------
 Distribution of E12 for 192 GeV random triggers. E12 > 0 in 8.76 % of
 random events. The distribution of xl=log10(E12/Elep) with a 0.05 binning 
 between -3.35 and -0.35 is given by this function (max entry in a bin=300)
------------------------------------------------------------------------*/
float AlEvent::r192_e12(float xl)const
{
  float r192;
  r192 = exp(-324.-98.*xl);
  r192 += 51.*exp(-0.5*pow(((xl+2.699)/0.1000),2));
  r192 += 213.*exp(-0.5*pow(((xl+2.354)/0.3502),2));
  r192 += 15.*exp(-0.5*pow(((xl+1.085)/0.3289),2));
  r192 += 89.*exp(-0.5*pow(((xl+0.513)/0.0460),2));
  return r192;
}

/*------------------------------------------------------------------------
 Distribution of E12 for 196 GeV random triggers. E12 > 0 in 9.74% of
 random events. The distribution of xl=log10(E12/Elep) with a 0.05 binning 
 between -3.35 and -0.35 is given by this function (max entry in a bin=600)
------------------------------------------------------------------------*/
float AlEvent::r196_e12(float xl)const
{
  float r196;
  r196 = exp(-323.-98.*xl);
  r196 += 81.*exp(-0.5*pow(((xl+2.757)/0.0816),2));
  r196 += 480.*exp(-0.5*pow(((xl+2.354)/0.3451),2));
  r196 += 16.*exp(-0.5*pow(((xl+1.027)/0.3257),2));
  r196 += 101.*exp(-0.5*pow(((xl+0.518)/0.0483),2));
  return r196;
}

/*------------------------------------------------------------------------
 Distribution of E12 for 200 GeV random triggers. E12 > 0 in 8.76% of
 random events. The distribution of xl=log10(E12/Elep) with a 0.05 binning 
 between -3.35 and -0.35 is given by this function (max entry in a bin=600)
------------------------------------------------------------------------*/
float AlEvent::r200_e12(float xl)const
{
  float r200;
  r200 = exp(-322.-98.*xl);
  r200 += 73.*exp(-0.5*pow(((xl+2.732)/0.0833),2));
  r200 += 519.*exp(-0.5*pow(((xl+2.362)/0.3446),2));
  r200 += 14.*exp(-0.5*pow(((xl+0.538)/0.8125),2));
  r200 += 106.*exp(-0.5*pow(((xl+0.492)/0.0554),2));
  return r200;
}

/*------------------------------------------------------------------------
 Distribution of E12 for 202 GeV random triggers. E12 > 0 in 7.97% of
 random events. The distribution of xl=log10(E12/Elep) with a 0.05 binning 
 between -3.35 and -0.35 is given by this function (max entry in a bin=300)
------------------------------------------------------------------------*/
float AlEvent::r202_e12(float xl)const
{
  float r202;
  r202 = exp(-322.-98.*xl);
  r202 += 41.*exp(-0.5*pow(((xl+2.794)/0.1261),2));
  r202 += 231.*exp(-0.5*pow(((xl+2.359)/0.3320),2));
  r202 += 3.*exp(-0.5*pow(((xl+1.507)/3.4067),2));
  r202 += 36.*exp(-0.5*pow(((xl+0.493)/0.0465),2));
  return r202;
}

/*------------------------------------------------------------------------
 Distribution of E12 for 205 GeV random triggers. E12 > 0 in 9.497% of
 random events. The distribution of xl=log10(E12/Elep) with a 0.05 binning
 between -3.35 and -0.35 is given by this function (max entry in a bin=700)
------------------------------------------------------------------------*/
float AlEvent::r205_e12(float xl)const
{
  float r205;
  r205 = exp(-323.-98.*xl);
  r205 += 351.*exp(-0.5*pow(((xl+2.735)/0.1053),2));
  r205 += 535.*exp(-0.5*pow(((xl+2.337)/0.3496),2));
  r205 += 39.*exp(-0.5*pow(((xl+1.019)/0.2566),2));
  r205 += 156.*exp(-0.5*pow(((xl+0.483)/0.0390),2));
  return r205;
}

/*------------------------------------------------------------------------
 Distribution of E12 for 207 GeV random triggers. E12 > 0 in 8.784% of
 random events. The distribution of xl=log10(E12/Elep) with a 0.05 binning 
 between -3.35 and -0.35 is given by this function (max entry in a bin=1000)
------------------------------------------------------------------------*/
float AlEvent::r207_e12(float xl)const
{
  float r207;
  r207 = exp(-322.-98.*xl);
  r207 += 553.*exp(-0.5*pow(((xl+2.739)/0.1078),2));
  r207 += 819.*exp(-0.5*pow(((xl+2.345)/0.3472),2));
  r207 += 60.*exp(-0.5*pow(((xl+1.026)/0.2712),2));
  r207 += 205.*exp(-0.5*pow(((xl+0.487)/0.0395),2));
  return r207;
}

// functions internally used for xlumok calculation

// xestab.  Not implemented: MRMP card and bank FRMP use
bool AlEvent::EnergyStability(float qelep)const
{
  int run2k=53000;
  int runnumber;
  if ((qhac->EH) != (EVEH*) NULL) 
    runnumber = qhac->EH->RN;
  else
    runnumber = -1;
  if (runnumber<run2k) return true;
  if (qelep<110) return true;
  if (Readout()->size()>1)
    { if ((*Readout())[1] != NULL) return (((*Readout())[1]->CO[2])>>17)&1; 
      else if (TriggerLevelControl() != NULL) return ((TriggerLevelControl()->TR[0])>>17)&1;
      else if (ReconstructorHeader() != NULL) return ((ReconstructorHeader()->DS)>>17)&1;
      else if (LuminosityParameters() != NULL) return ((LuminosityParameters()->HV)>>17)&1;
      else if (SicalLuminosityParameters() != NULL) return ((SicalLuminosityParameters()->HV)>>17)&1;
      else return false;
    }
  else if (TriggerLevelControl() != NULL) return ((TriggerLevelControl()->TR[0])>>17)&1;
  else if (ReconstructorHeader() != NULL) return ((ReconstructorHeader()->DS)>>17)&1;
  else if (LuminosityParameters() != NULL) return ((LuminosityParameters()->HV)>>17)&1;
  else if (SicalLuminosityParameters() != NULL) return ((SicalLuminosityParameters()->HV)>>17)&1;
  else return false;
}

// xtgenb.
// output: bit 1 : all essential large-angle triggers enabled
//         bit 2 : all essential LCAL triggers enabled
//         bit 3 : all essential SICAL triggers enabled
int AlEvent::EnabledTriggers()const
{
  // required triggers: large angle
  char TTREQ[7][6][9] = {{"SNG_MUON","SNG_C_EM","ETT_EWBA","ETT_EWE*","ETT_EWEB"},
	                 {"SNG_MUON","SNG_C_EM","ETT_EWBA","ETT_EWE*","ETT_EWEB"},
		         {"SNG_MUON","SNG_C_EM","ETT_EWBA","ETT_EWE*","ETT_EWEB"},
                         {"SNG_MUON","SNG_C_EM","ETT_EWBA","ETT_EWE*","ETT_EWEB"},
                         {"SNG_MUON","SNG_C_EM","ETT_EWBA","ETT_EWE*","ETT_EWEB"},
                         {"SNG_MUON","SNG_C_EM","ETT_EWBA","ETT_EWE*","ETT_EWEB"},
                         {"SNG_MUON","SNG_C_EM","ETT_EWBA","ETT_EWE*","ETT_EWEB"}};
  // required triggers: LCAL
  char TTREL[7][2][9] = {{"LC_HI_LO","LC_LO_HI"},
                         {"LC_HI_LO","LC_LO_HI"},
                         {"LT_HI_LO","LT_LO_HI"},
                         {"LW_ET_HI","        "},
                         {"LW_ET_HI","        "},
                         {"LW_ET_HI","        "},
                         {"LW_LO_HI","        "}};
  // required triggers: SICAL
  char TTRES[7][1][9] = {{"        "},
                         {"        "},
                         {"        "},
                         {"        "},
                         {"SICAL_ME"},
                         {"SICAL_ME"},
                         {"SICAL_ME"}};
  // required trigger mask (hardwired): large angle
  int MHDRQ[7] = {51512064, 51512064,  1966848,  1966848,  1966848, 1966848, 1966848};
  // required trigger mask (hardwired): LCAL
  int MHDRL[7] = {49152, 49152, 49152, 65536, 65536, 64, 32};
  // required trigger mask (hardwired): SICAL
  int MHDRS[7] = { 0, 0, 0, 0, 16, 16, 16};
  // Hardwired trigger enable masks (XTOP corrupted)
  int MXBRN[19] = { 4017, 4067, 4351, 4387, 4476, 4525, 4530, 5112, 5329, 5373, 5852, 
                    7240, 8419, 8420, 8423, 8424, 12528, 12536, 12718};
  int MXBMK[19] = { -2083339265,-2083339265,-2083339274,-2083339266,-2083339266,
                    -2083339266,-2083339266,-2095922177,-2095922177,-2095922177,
                     51569663  ,-2145393668,-2011175940,-2011175940,-2011175940,
                    -2011175940,-2009078786,-2009078786,-2009078786};
  int runnum;
  if ((qhac->EH) != (EVEH*) NULL)
    runnum = qhac->EH->RN;
  else
    return 0; // no run number: very bad
  // for MC, all triggers are always enabled.
  if (runnum < 2001) return 7; //111
  // find which period the run belong
  int period;
  if (runnum <= 4535)
	  period = 0; // sep89
  else if (runnum <= 5909)
	  period = 1; // fal89
  else if (runnum <= 14000)
	  period = 2; // mar90
  else if (runnum <= 16500)
	  period = 3; // mar92
  else if (runnum <= 20000)
	  period = 4; // sep92
  else if (runnum <= 40000)
	  period = 5; // may93
  else    period = 6; // nov95
  // scan the XTBN bank
  // the bank is defined for the first event of a run,
  // so the content is defined as static
  bool OK=true;
  if (TriggerBitNames()->size() > 0)
    {
      mask1=(mask2=(mask3=0));
      for (vector<XTBN*>::iterator iter=TriggerBitNames()->begin();iter<TriggerBitNames()->end();iter++)
          {
            int idef = (*iter)->TN; // Trigger defiNed flag
	    int inum = (*iter)->TB; // Number of trigger bit in the level 1/2
	    if ((inum<0) || (inum>31)) {break; OK=false;} // check if bank corrupted
	    if ((idef != 0) && (inum != 31))
              {
                char MNM[9];
	        strncpy(MNM,(*iter)->BM,8); // copy the bank word
		MNM[8] = '\0';
		if (strcasecmp(MNM, "        ") != 0 )
                  {
                    // compare with the trigger names
		    for(int i=0;i<6;i++)
                       if(strcasecmp(MNM,TTREQ[period][i]) == 0) mask1 |= (1<<inum);
                    for(int i=0;i<2;i++)
                       if(strcasecmp(MNM,TTREL[period][i]) == 0) mask2 |= (1<<inum);
                    for(int i=0;i<1;i++)
                       if(strcasecmp(MNM,TTRES[period][i]) == 0) mask3 |= (1<<inum);
		  }
	      }
	  }
    }
  if ((mask1 == 0)||(!OK)) mask1 = MHDRQ[period];
  if ((mask2 == 0)||(!OK)) mask2 = MHDRL[period];
  if ((mask3 == 0)||(!OK)) mask3 = MHDRS[period];
  // We have the required mask. Get the mask of enabled triggers now.
  int result = 0;
  int MKENB = 0;
  if (TriggerOptions() != NULL) MKENB = TriggerOptions()->TR;
  else if (Readout()->size() != 0) MKENB = ((*Readout())[0])->CO[2];
  else if (LuminosityParameters() != NULL) MKENB = LuminosityParameters()->TE;
  else if (SicalLuminosityParameters() != NULL) MKENB = SicalLuminosityParameters()->TE;
  for (int i=0;i<19;i++) if (runnum == MXBRN[i]) MKENB = MXBMK[i];
  // Compare required mask with enabled mask to find whether all 
  // required triggers are enabled.
  if (mask1 != 0) result |= (mask1 == (mask1 & MKENB));
  if (mask2 != 0) result |= ((mask2 == (mask2 & MKENB))<<1);
  if (mask3 != 0) result |= ((mask3 == (mask3 & MKENB))<<2);
  // Luminosity trigger patch for runs 13191-13199.
  // Here triggers LT_A+BVH and LT_LO_HI were disabled due to noisy towers
  // Subsequent analysis showed that LW_ET_HI found all Bhabhas, therefore
  // these runs are allowed to pass.
  if ((runnum >= 13191) && (runnum <= 13199)) result |= 2;
  return result;
}

// XHVSTA
vector<bool> AlEvent::HVStatus()const
{
  int MTPHV[7] = {4316,4328,4350,4351,4357,4367,4371};
  int MTFEV[7] = {   1, 154,1320,   1, 121, 372,   1};
  int MTLEV[7] = {2080, 804,1576,9999,9999,9999, 251};
  vector<bool> result(24,true);
  vector<bool> verybad(24,false);
  int runnum;
  if ((qhac->EH) != (EVEH*) NULL)
        runnum = qhac->EH->RN;
  else  return verybad; // no run number: very bad
  if (runnum < 2001) return result; // MC: all subdetectors are on
  int tmp = 0;
  if (Readout()->size()>1) 
    { if ((*Readout())[1] != NULL) tmp = (*Readout())[1]->CO[2]; 
      else if (TriggerLevelControl() != NULL) tmp = TriggerLevelControl()->TR[0];
      else if (ReconstructorHeader() != NULL) tmp = ReconstructorHeader()->DS;
      else if (LuminosityParameters() != NULL) tmp = LuminosityParameters()->HV;
      else if (SicalLuminosityParameters() != NULL) tmp = SicalLuminosityParameters()->HV;
    }
  else if (TriggerLevelControl() != NULL) tmp = TriggerLevelControl()->TR[0];
  else if (ReconstructorHeader() != NULL) tmp = ReconstructorHeader()->DS;
  else if (LuminosityParameters() != NULL) tmp = LuminosityParameters()->HV;
  else if (SicalLuminosityParameters() != NULL) tmp = SicalLuminosityParameters()->HV;
  for (int i = 0; i<24;i++) result[i]= (tmp & (1<<i));
  // Now detector-specific, run-specific repair to HV bits
  //
  // Vertex Detector
  //
  // ITC
  // Message by Bill Cameron 11-Jun-1993: All events in run 20600 after event
  // 2787 should be discarded.
  if ((runnum == 20600) && (number()>=2787)) result[5] = false;
  // TPC
  // 1) Both TPC logicals are identically set for Sept 89 runs.
  // 2) Sept `89: 7 runs had TPC HV bits which should be ignored
  //    and are turned HV on here for the proper events.
  if (runnum <= 4800)
   {
     for(int i=0;i<7;i++)
        if (runnum == MTPHV[i])
          {
            result[4] = false;
	    if ((number()>=MTFEV[i]) && (number()<=MTLEV[i]))
              {
                result[4] = true;
		break;
	      }
	   }
     result[15] = result[4];
   }
  // ECAL
  //
  // HCAL
  // 1) Turn on the HCAL for Sept.89 (before HV bit existed)
  if (runnum <= 4800) result[7]=(result[8]=(result[9]=true));
  // 2) Run 20639: endcaps not at nominal voltage at the beginning of the
  //    run -> lower efficiency
  if ((runnum == 20639)&&(number()<690)) result[7]=(result[8]=false);
  // Run 23276: HCAL not operational for part of the run
  if ((runnum == 23276)&&(number()>11459)) result[7]=(result[8]=(result[9]=false));
  // Muon chambers
  //
  // LCAL
  // Check the LOLE (or LUPA) bank for errors also
  //  1) Completely ignore LOLE bank for run 4107
  //  2) Completely ignore REVH bit for run 4530
  //  3) Two Oct.`89 runs with erroneous LOLE banks
  int LOLEWD = 1;
  if (LuminosityParameters() != NULL) LOLEWD = LuminosityParameters()->LO;
  else if (LcalErrorFlags()->size() != 0) LOLEWD = ((*LcalErrorFlags())[0])->ER;
  else if (SicalLuminosityParameters() != NULL) LOLEWD = SicalLuminosityParameters()->LO;
  if (runnum == 4107) LOLEWD = 0;
  if (runnum == 4530) result[3] = true;
  if ((runnum == 4981)||(runnum == 4982)) LOLEWD = 0;
  if ((runnum >=10606)&&(runnum <= 10611)) LOLEWD = 0;
  // SICAL
  //  1) Fill 1451 (15/16-Nov-1992) had two amplexes which went bad. Take
  //     that into account by resetting the HV bit.
  if ((runnum >= 17766)&&(runnum <= 17781)) result[10] = false;
  // 2) Fill 1533 (18    May-1993) had some low voltage problem|
  //    Fill 1574 (30    May-1993) had some low voltage problem| part of
  //    Fill 1577 (31    May-1993) had some low voltage problem| some run
  if ((runnum == 20170)&&(number()>=3700)) result[10] = false;
  if ((runnum == 20592)&&(number()<=1500)) result[10] = false;
  if ((runnum == 20619)&&(number()>=7200)) result[10] = false;
  if ((runnum == 20621)&&(number()<= 500)) result[10] = false;
  if (runnum == 20620)                     result[10] = false;
  // SATR
  //
  // BCAL
  //
  // Trigger
  // 1) Turn on the trigger analog/CAMAC crate low voltages for Sept.89
  //    (before HV bit existed)
  if (runnum <= 4800) result[13]=(result[14]=true);
  for(vector<XHVB*>::iterator iter=HVfixes()->begin();iter<HVfixes()->end();iter++)
    if ((runnum == (*iter)->RU)&&(number() >= (*iter)->FE)&&(number() <= (*iter)->LE))
      result[(*iter)->DE-1]=(*iter)->HV;
return result;
}
// XT0SYN
bool AlEvent::TimeSynchronization()const
{
  int runnum;
  tmask = 0;
  if ((qhac->EH) != (EVEH*) NULL)
     runnum = qhac->EH->RN;
  else  return false; // no run number: bad
  if (runnum < 2001) return true; // MC: always true
  bool OK=true;
  if (TriggerBitNames()->size() > 0)
    {
      tmask = 0;
      for (vector<XTBN*>::iterator iter=TriggerBitNames()->begin();iter<TriggerBitNames()->end();iter++)
          {
            int idef = (*iter)->TN; // Trigger defiNed flag
	    int inum = (*iter)->TB; // Number of trigger bit in the level 1/2
	    if ((inum<0) || (inum>31)) {break; OK=false;} // check if bank corrupted
	    if ((idef != 0) && (inum != 31))
              {
                char MNM[9];
	        strncpy(MNM,(*iter)->BM,8); // copy the bank word
		MNM[8] = '\0';
		if (strcasecmp(MNM, "        ") != 0 )
                  {
                    // compare with the required trigger names
		    for(int i=0;i<6;i++)
                       if(strcasecmp(MNM,"T0_SYNCH") == 0) tmask |= (1<<inum);
		  }
	      }
	  }
    }
  if ((tmask == 0)||(!OK))
    {
      if (runnum > 17061) tmask = 2; // for runs after first run with t0 bit worked
      if (runnum > 20000) tmask = 268435456; // for runs after 93
    }
  // Caution! The meaning of the bit changed.
  // In 1992: Bit on = synchronization of trigger with GBX is okay
  // In 1993: Bit on = synchronization of trigger with GBX is BAD!
  if (tmask != 0)
    {
      if(Readout()->size() != 0)
        {
          for(vector<X1RG*>::iterator iter=Readout()->begin();iter<Readout()->end();iter++)
           {
             char tmp[5];
             strncpy(tmp,(*iter)->NA,4); // copy the bank word
	     tmp[4] = '\0';
             if ((strcasecmp(tmp, "TPR ") == 0 )|| (strcasecmp(tmp, " RPT") == 0 ))
                 if (runnum<20000) return (( tmask & ((*iter)->CO[0]) ) == tmask );
                 else              return (( tmask & ((*iter)->CO[0]) ) == 0 );
           }
	}
      else if(TriggerLevelRegisterBitPattern() != NULL) 
               if (runnum<20000) return (( tmask & (TriggerLevelRegisterBitPattern()->RP[0]) ) == tmask );
               else              return (( tmask & (TriggerLevelRegisterBitPattern()->RP[0]) ) == 0 );
      else if(TriggerLevelEventBitPattern() != NULL)
               if (runnum<20000) return (( tmask & (TriggerLevelEventBitPattern()->T1) ) == tmask );
               else              return (( tmask & (TriggerLevelEventBitPattern()->T1) ) == 0 );
      else if(TriggerBitPattern() != NULL)
               if (runnum<20000) return (( tmask & (TriggerBitPattern()->T1) ) == tmask );
               else              return (( tmask & (TriggerBitPattern()->T1) ) == 0 );
      else if(LuminosityParameters() != NULL)
               if (runnum<20000) return (( tmask & (LuminosityParameters()->T1) ) == tmask );
               else              return (( tmask & (LuminosityParameters()->T1) ) == 0 );
      else if(SicalLuminosityParameters() != NULL)
               if (runnum<20000) return (( tmask & (SicalLuminosityParameters()->T1) ) == tmask );
               else              return (( tmask & (SicalLuminosityParameters()->T1) ) == 0 );
    }
  return true;
}
// XRE133 and XRE94
// logic inverted: return true if laser event
bool AlEvent::LaserEvent()const
{
  // first laser events taken during LEP1.5 data
  const int runs[13]={40307,40316,40334,40345,40395,40395,
                      40396,40396,40418,40441,40471,40483,
                      40512};
  const int events[13]={7214, 3398, 1542, 5064, 7511,13615,
                        1993, 8630, 3126, 6159, 2751, 1596,
                        1391};
  int runnum;
  if ((qhac->EH) != (EVEH*) NULL)
     runnum = qhac->EH->RN;
  else  return false; 
  if (((runnum < 40000) || (runnum > 40550))&& ((runnum < 25520) || (runnum > 25530)))  return false;
  for(int i=0;i<13;i++)
    if ( (runnum == runs[i])&&(number() == events[i])) return true;  
  if(Header() != NULL) 
    return ((Header()->M1) == (1<<23));
  return false;
}
// XVDEOK
bool AlEvent::VDETstatus()const
{
  int runnum;
  if ((qhac->EH) != (EVEH*) NULL)
     runnum = qhac->EH->RN;
  else  return false;
  if (runnum < 2001) return true;
  // look if we are in a bad period
  bool badperiod = false;
  if (NoHVbit()->size() != 0)
  {
    for (vector<VHPV*>::iterator iter = NoHVbit()->begin(); iter < NoHVbit()->end();iter++)
      if ((runnum >= (*iter)->FR) && (runnum <= (*iter)->LR)) badperiod = true;
  }
  else return false; 
  if (badperiod == false) return true;
  // look which bit is the VDET bit
  int bit;
  if (VDETbit()->size() != 0)
    {
      for (vector<VHBV*>::iterator iter = VDETbit()->begin(); iter < VDETbit()->end();iter++)
        if ((runnum >= (*iter)->FR) && (runnum <= (*iter)->LR)) bit = (*iter)->BN;
    }
  else return false;
  // Check the bit
  if (Readout()->size()>1) 
    { if ((*Readout())[1] != NULL) return (((*Readout())[1]->CO[2])>>bit)&1; 
      else if (TriggerLevelControl() != NULL) return ((TriggerLevelControl()->TR[0])>>bit)&1;
      else if (ReconstructorHeader() != NULL) return ((ReconstructorHeader()->DS)>>bit)&1;
      else if (LuminosityParameters() != NULL) return ((LuminosityParameters()->HV)>>bit)&1;
      else if (SicalLuminosityParameters() != NULL) return ((SicalLuminosityParameters()->HV)>>bit)&1;
      else return false;
    }
  else if (TriggerLevelControl() != NULL) return ((TriggerLevelControl()->TR[0])>>bit)&1;
  else if (ReconstructorHeader() != NULL) return ((ReconstructorHeader()->DS)>>bit)&1;
  else if (LuminosityParameters() != NULL) return ((LuminosityParameters()->HV)>>bit)&1;
  else if (SicalLuminosityParameters() != NULL) return ((SicalLuminosityParameters()->HV)>>bit)&1;
  else return false;
}

// functions internally used for IsTrigger calculation
// X1REDO
void AlEvent::RedoTrigger()const
{
  if(Readout()->size() == 0) return;
  if(Triggerlevel1Threshold()->size() == 0) return;
  if(Triggerlevel1Input()->size() == 0) return;
  int IHWSUM[72];
  int IEWSUM[72];
  int ILWSUM[8];
  int IECWTE[8];
  int IITSUM[4];
  for(vector<X1IP*>::iterator iter=Triggerlevel1Input()->begin();iter<Triggerlevel1Input()->end();iter++)
    {
      char name[5];
      strncpy(name,(*iter)->IT,4); // copy the bank word
      name[4] = '\0';
      if ((strcasecmp(name, "HCW ") == 0 ))
        for(int j=0;j<72;j+=2)
          {
           IHWSUM[j]   = (((*iter)->CO[j])/65536);
	   IHWSUM[j+1] = (((*iter)->CO[j])%65536);
	  }
      else if((strcasecmp(name, "ECW ") == 0 ))
        for(int j=0;j<72;j+=2)
          {
           IEWSUM[j]   = ((((*iter)->CO[j])/65536)-200);
	   IEWSUM[j+1] = ((((*iter)->CO[j])%65536)-200);
	  }
      else if((strcasecmp(name, "MISC") == 0 ))
        {
          for(int j=0;j<8;j++) ILWSUM[j] = (*iter)->CO[j];
          for(int j=0;j<8;j++) IECWTE[j] = (*iter)->CO[j];
          for(int j=0;j<4;j++) IITSUM[j] = (*iter)->CO[j];
        }
    }
  SimulateTrigger(IHWSUM,IEWSUM,ILWSUM,IECWTE,IITSUM);
}
//X1TRG
void AlEvent::RedoOldTrigger()const
{
  if(TriggerOldlevel1Threshold()->size() == 0) return;
  int IHTSUM[72];
  int IHWSUM[72];
  int IETSUM[72];
  int IEWSUM[72];
  int ILTSUM[24];
  int IITSUM[4] = {0};
  int IECTTE[4] = {0};
  int IHCTTE[4] = {0};
  int IECWTE[8] = {0};
  if((TriggerLevelEventBitPattern() == NULL)||(Triggerlevel1Adc()->size() == 0)) return;
  // fill different trigger sums
  for(vector<X1AD*>::iterator iter=Triggerlevel1Adc()->begin();iter<Triggerlevel1Adc()->end();iter++)
    {
      char name[5];
      strncpy(name,(*iter)->IT,4); // copy the bank word
      name[4] = '\0';
      // HC tower trigger
      if ((strcasecmp(name, "HCT ") == 0 ))
        {
          for(int i=0;i<72;i+=2)
           {
             IHTSUM[i]   = (5*((((*iter)->AV[i/2])/65536)-96));
             IHTSUM[i+1] = (5*((((*iter)->AV[i/2])%65536)-96));
	   }
        }
      // HC wire trigger
      else if ((strcasecmp(name, "HCW ") == 0 ))
        {
          for(int i=0;i<72;i+=2)
           {
             IHWSUM[i]   = (((((*iter)->AV[i/2])/65536)-96)/150);
             IHWSUM[i+1] = (((((*iter)->AV[i/2])%65536)-96)/150);
           }
        }
      // EC tower trigger
      else if ((strcasecmp(name, "ECT ") == 0 ))
        {
          for(int i=0;i<72;i+=2)
           {
             IETSUM[i]   = (5*((((*iter)->AV[i/2])/65536)-96));
             IETSUM[i+1] = (5*((((*iter)->AV[i/2])%65536)-96));
           }
        }
      // EC wire trigger
      else if ((strcasecmp(name, "ECW ") == 0 ))
        {
          for(int i=0;i<72;i+=2)
           {
             IEWSUM[i]   = (10*((((*iter)->AV[i/2])/65536)-96));
             IEWSUM[i+1] = (10*((((*iter)->AV[i/2])%65536)-96));
           }
        }
      // LC tower trigger
      else if ((strcasecmp(name, "LCT ") == 0 ))
        {
          for(int i=0;i<24;i+=2)
           {
             ILTSUM[i]   = (40*((((*iter)->AV[i/2])/65536)-96));
             ILTSUM[i+1] = (40*((((*iter)->AV[i/2])%65536)-96));
           }
        }
    }
  // TOTAL ENERGY (Endcap A, Endcap B, Barrel, Total)
  int KST;
  // HC tower trigger.
  for (int i=0;i<72;i++)
    {
      if (i<12) KST = 0;       // endcap A
      else if (i>=60) KST = 1; // endcap B
      else KST = 2;            // barrel
      IHCTTE[KST] += IHTSUM[i];
    }
  IHCTTE[3] = (IHCTTE[0] + IHCTTE[1] + IHCTTE[2]);
  // EC Tower Trigger
  for (int i=0;i<72;i++)
   {
     if (i<12) KST = 0;       // endcap A
     else if (i>=60) KST = 1; // endcap B
     else KST = 2;            // barrel
     IECTTE[KST] += IETSUM[i];
   }
  IECTTE[3] = (IECTTE[0] + IECTTE[1] + IECTTE[2]);
  // EC wire trigger
  for (int i=0;i<72;i+=2)
   {
     if (i<24) KST = 0;       // endcap A
     else if (i>=48) KST = 1; // endcap B
     else KST = 2;            // barrel
     IECWTE[KST] += IEWSUM[i];
     IECWTE[KST+4] += IEWSUM[i+1];
   }
  IECWTE[3] = (IECWTE[0] + IECWTE[1] + IECWTE[2]);
  IECWTE[7] = (IECWTE[4] + IECWTE[5] + IECWTE[6]);
  // fill ITC from XTEB
  if(TriggerLevelEventBitPattern() != NULL)
    for(int i=0;i<4;i++) IITSUM[i] = TriggerLevelEventBitPattern()->IT[i];
  // initialise XTEB
  if (TriggerLevelEventBitPattern() == NULL) qhac->EB = new XTEB;
  TriggerLevelEventBitPattern()->T1 = 0;
  TriggerLevelEventBitPattern()->T2 = 0;
  TriggerLevelEventBitPattern()->L2 = 0;
  for (int i=0;i<12;i++)
   {
     TriggerLevelEventBitPattern()->HT[i] = 0;
     TriggerLevelEventBitPattern()->HW[i] = 0;
     TriggerLevelEventBitPattern()->LW[i] = 0;
     TriggerLevelEventBitPattern()->EW[i] = 0;
     TriggerLevelEventBitPattern()->LT[i/3] = 0;
     TriggerLevelEventBitPattern()->TE[i/6] = 0;
     TriggerLevelEventBitPattern()->IT[i/3] = 0;
     TriggerLevelEventBitPattern()->TP[i/3] = 0;
   }
  // Simulate trigger
  SimulateOldTrigger(IHTSUM, IHWSUM, IETSUM, IEWSUM, ILTSUM, IITSUM, IECTTE, IHCTTE, IECWTE);
  
}
//X1DISN
void AlEvent::SimulateTrigger(int* IHWSUM, int* IEWSUM, int* ILWSUM, int* IECWTE, int* IITSUM)const
{
  int NHWBIT[8] = {0};
  int NEWBIT[8] = {0};
  int NITBIT[8] = {0};
  int NLWBIT = 0;
  int NTEBIT = 0;
  X1TV *HCWI,*ECEC,*ECBA,*ETEC,*ETBA,*LCEC;
  // get thresholds
  for(vector<X1TV*>::iterator iter=Triggerlevel1Threshold()->begin();iter<Triggerlevel1Threshold()->end();iter++)
    {
      char name[5];
      strncpy(name,(*iter)->TT,4); // copy the bank word
      name[4] = '\0';
      if ((strcasecmp(name, "HCWI") == 0 )) HCWI = (*iter);
      if ((strcasecmp(name, "ECEC") == 0 )) ECEC = (*iter);
      if ((strcasecmp(name, "ECBA") == 0 )) ECBA = (*iter);
      if ((strcasecmp(name, "ETEC") == 0 )) ETEC = (*iter);
      if ((strcasecmp(name, "ETBA") == 0 )) ETBA = (*iter);
      if ((strcasecmp(name, "LCEC") == 0 )) LCEC = (*iter);
    }
  // HCAL wire trigger sources
  for(int i=1;i<=4;i++)
    {
      int ibit=1;
      for(int j=1;j<=72;j++)
        {
          int jbit,k;
          if (ibit>32)
            {
              jbit = ibit - 32 - 1;
	      k = 2*i-1;
            }
	  else
            {
              jbit = ibit - 1;
              k = 2*i;
            }
          if (IHWSUM[j-1] >= HCWI->TV[i-1]) NHWBIT[k-1] |= (1<<jbit);
          ibit++;
          if(j == 36) ibit = 25;
        }
    }
  // ECAL wire trigger sources
  for(int i=1;i<=4;i++)
    {
      float KECEC = (ECEC->TV[i-1]/2.);
      float KECBA = (ECBA->TV[i-2]/2.);
      for(int j=1;j<=72;j+=2)
        {
          if(j<24)
            {
              // endcap A
              if((IEWSUM[j-1] <= KECEC) || (IEWSUM[j] <= KECEC)) continue;
              int jbit = ((j+3)/4 - 1);
              NEWBIT[2*i-1] |= (1<<jbit);
              NEWBIT[2*i-1] |= (1<<(jbit+6));
              jbit = ((j+23)/2);
              NEWBIT[2*i-1] |= (1<<jbit);
              if(jbit == 23) jbit = 11;
              NEWBIT[2*i-1] |= (1<<(jbit+1));
            }
          else if(j>48)
            {
              // endcap B
              if((IEWSUM[j-1] <= KECEC) || (IEWSUM[j] <= KECEC)) continue;
              int jbit = ((j+15)/4);
              NEWBIT[2*i-2] |= (1<<jbit);
              NEWBIT[2*i-2] |= (1<<(jbit+6));
              jbit = ((j-41)/2);
              NEWBIT[2*i-2] |= (1<<jbit);
              if(jbit == 15) jbit = 3;
              NEWBIT[2*i-2] |= (1<<(jbit+1));
            }
          else
            {
              // barrel
              if((IEWSUM[j-1] <= KECBA) || (IEWSUM[j] <= KECBA)) continue;
              int jbit = (j/2);
              NEWBIT[2*i-1] |= (1<<jbit);
              NEWBIT[2*i-2] |= (1<<(jbit-8));
              if(jbit<20)  NEWBIT[2*i-1] |= (1<<(jbit+12));
              else         NEWBIT[2*i-2] |= (1<<(jbit-20));
            }
        }
    }
  // LCAL wire trigger sources
  int LW_A = ( ILWSUM[0] + ILWSUM[1] + ILWSUM[2] + ILWSUM[3] );
  int LW_B = ( ILWSUM[5] + ILWSUM[6] + ILWSUM[7] + ILWSUM[8] );
  for(int i=0;i<4;i++)
    {
       if(i<3)
         {
           if (LW_A > LCEC->TV[i]) NLWBIT |= (1<<i);
           if (LW_B > LCEC->TV[i]) NLWBIT |= (1<<(i+4));
         }
       else
           if  ((LW_A+LW_B) > LCEC->TV[i]) NLWBIT |= (1<<i);
    }
  // SICAL trigger sources
  SimulateSicalTrigger();
  // ITC segment trigger bits
  int ibit = 1;
  for(int j=1;j<=72;j++)
    {
       int jbit,k,kk,kb;
       if(ibit > 32)
         {
           jbit = ibit - 32 - 1;
           k=0;
         }
       else
         {
           jbit = ibit - 1;
           k=1;
         }
       if(j<=32)
         {
           kk=0;
           kb=j-1;
         }
       else if(j>64)
         {
           kk=2;
           kb=j - 64 - 1;
         }
       else
         {
           kk=1;
           kb=j - 32 - 1;
         }
       if(((IITSUM[kk]>>kb)&1)) NITBIT[k] |= (1<<jbit);
       ibit++;
       if(j == 36) ibit = 25;
    }
  // Total energy
  for(int i=0;i<4;i++)
    {
      float KETEC = (ETEC->TV[i]/2.);
      float KETBA = (ETBA->TV[i]/2.);
      if((IECWTE[0]>=KETEC) && (IECWTE[4]>=KETEC)) NTEBIT |= (1<<(4*i));
      if((IECWTE[1]>=KETEC) && (IECWTE[5]>=KETEC)) NTEBIT |= (1<<(4*i+1));
      if((IECWTE[2]>=KETBA) && (IECWTE[6]>=KETBA)) NTEBIT |= (1<<(4*i+2));
    }
  // Apply Trigger
  ApplyTrigger(NHWBIT, NEWBIT, NITBIT, NLWBIT, NTEBIT);
}

//SIX2MK
void AlEvent::SimulateSicalTrigger()const
{
  // Init the trigger constants for SICAL 
  float SIFOXA = 0.228;
  float SIDIFO = 0.00913;
  int Threshold[4]={9,12,22,41,};
  int Discri[2]={0};
  if (SicalRunConditions()->size() != 0)
    for(vector<SRCO*>::iterator iter=SicalRunConditions()->begin();iter<SicalRunConditions()->end();iter++)
      {
        char name[5];
        strncpy(name,(*iter)->NA,4); // copy the bank word
        name[4] = '\0';
        if ((strcasecmp(name, "SIXA") == 0 )) SIFOXA = ((*iter)->VA *.001);
        if ((strcasecmp(name, "SIFO") == 0 )) SIDIFO = ((*iter)->VA *.00001);
      }
  if (SicalTriggerConditions() != NULL)
    {
      for(int i=0;i<4;i++) Threshold[i]=(255 & (SicalTriggerConditions()->TT>>(8*i)));
      Discri[0] = SicalTriggerConditions()->DO;
      Discri[1] = SicalTriggerConditions()->DE;
    }					
  // Discriminate the sector and return a "Thermometer code"
  // for each end cap odd and each endcap even.
  int ThermometerCode[2][2]={{0,0},{0,0}};
  for(int endcap=0;endcap<2;endcap++)
    for(int parity=0;parity<2;parity++)
      // Loop over every sector and every road within this endcap and parity,
      // reading the energy deposit from the SIXA bank . If any sector has
      // an  energy deposit above threshold, then set a a bit in IPATT
      // C  corresponding to that threshold.
      if(SicalTriggerSectorsAdc()->size() != 0) 
        for(int road=0;road<2;road++)
          for(int sector=0;sector<8;sector++)
            {
              int IBT = 16*road + 8*endcap + sector;
              if (!((Discri[parity]>>IBT)&1))
                {
                 int IADC = 
                 (((parity?
                   (*SicalTriggerSectorsAdc())[endcap*8+sector]->AE:
                   (*SicalTriggerSectorsAdc())[endcap*8+sector]->AO )>>(16*road))&65535);
		 for(int i=0;i<4;i++)
                   if(IADC > Threshold[i]) ThermometerCode[endcap][parity] |= (1<<i);
		}
	    }
  // create and init the SIX2 bank
  if (SicalTriggerX2() == NULL) qhac->X2 = new SIX2;
  SicalTriggerX2()->TW = 0;
  // Make the six basic SICAL triggers and store them in the bank
  int endcapA = (ThermometerCode[0][0] | ThermometerCode[0][1]);
  int endcapB = (ThermometerCode[1][0] | ThermometerCode[1][1]);
  if((endcapA&4)&&(endcapB&2)) SicalTriggerX2()->TW |= 1;
  if((endcapA&2)&&(endcapB&4)) SicalTriggerX2()->TW |= 2;
  if (endcapA&8)               SicalTriggerX2()->TW |= 4;
  if (endcapB&8)               SicalTriggerX2()->TW |= 8;
  if (endcapA&1)               SicalTriggerX2()->TW |=16;
  if (endcapB&1)               SicalTriggerX2()->TW |=32;
  // Store the thermometer codes
  SicalTriggerX2()->TW |= ((ThermometerCode[0][0]&31)<<6);
  SicalTriggerX2()->TW |= ((ThermometerCode[0][1]&31)<<10);
  SicalTriggerX2()->TW |= ((ThermometerCode[1][0]&31)<<14);
  SicalTriggerX2()->TW |= ((ThermometerCode[1][1]&31)<<18);
}

// X1APTN
void AlEvent::ApplyTrigger(int* NHWBIT, int* NEWBIT, int* NITBIT, int NLWBIT, int NTEBIT)const
{
  // init physics trigger counter
  int NPHYTR[9] = {0};
  // single muon trigger
  int NTRBIT = 0;
  int ITRG11 = ( NITBIT[1] & NHWBIT[5] );
  int ITRG12 = ( NITBIT[0] & NHWBIT[4] );
  int ITRI1  = ( ITRG11 | ITRG12 );
  if (ITRI1) { NTRBIT |= (1<<8); NPHYTR[0]++;}
  // Single Charged El.-mag. energy trigger (SNG_C_EM)
  int ITRG21 = ( NITBIT[1] & NEWBIT[1] );
  int ITRG22 = ( NITBIT[0] & NEWBIT[0] );
  int ITRI2 = ( ITRG21 | ITRG22 );
  if (ITRI2) {  NTRBIT |= (1<<9); NPHYTR[1]++;}
  // Single Neutral El.-mag. energy         (SNG_N_EL)
  int ITRG31 = NEWBIT[5] ;
  int ITRG32 = NEWBIT[4] ;
  int ITRI3 = ( ITRG31 | ITRG32 );
  if (ITRI3) {  NTRBIT |= (1<<2); NPHYTR[2]++;}
  // Total energy ECW barrel
  int ITRG42 = 0;
  int ITRG41 = 0;
  if (((NTEBIT>>2)&1)) ITRG41 |= 1;
  if (ITRG41) { NTRBIT |= (1<<17); NPHYTR[3]++;}
  // Total energy ECW Endcap_A
  int ITRG52 = 0;
  int ITRG51 = 0;
  if (((NTEBIT>>4)&1)) ITRG51 |= 1;
  if (ITRG51) { NTRBIT |= (1<<18); NPHYTR[4]++;}
  // Total energy ECW Endcap_B
  int ITRG62 = 0;
  int ITRG61 = 0;
  if (((NTEBIT>>5)&1)) ITRG61 |= 1;
  if (ITRG61) { NTRBIT |= (1<<19); NPHYTR[5]++;}
  // Total energy ECW Endcap_A*Endcap_B
  int ITRG72 = 0;
  int ITRG71 = 0;
  if ( ((NTEBIT>>0)&1) && ((NTEBIT>>1)&1) ) ITRG71 |= 1;
  if (ITRG71) { NTRBIT |= (1<<20); NPHYTR[6]++;}
  // LCAL Wires A*B*SUM (Bhabha)
  int ITRG82 = 0;
  int ITRG81 = 0;
  if ( ((NLWBIT>>1)&1) && ((NLWBIT>>5)&1) && ((NLWBIT>>3)&1) ) ITRG81 |= 1;
  if (ITRG81) { NTRBIT |= (1<<7); NPHYTR[7]++;}
  // Bhabha trigger  SICAL
  int ITRG92 = 0;
  int ITRG91 = 0;
  int MT2 = 0;
  int ITWORD = 0;
  if(SicalTriggerX2() != NULL)
    {
      ITWORD = SicalTriggerX2()->TW;
      if (ITWORD != 0)
        {
          //A VERY LOW    OR   B VERY LOW
          if (  ((ITWORD>>5)&1) || ((ITWORD>>4)&1)  ) MT2 |= 1;
          //A HIGH B LOW  OR   A LOW  B HIGH
          if (  ((ITWORD>>0)&1) || ((ITWORD>>1)&1)  ) MT2 |= 2;
          //A VERY HIGH   OR   B VERY HIGH
          if (  ((ITWORD>>2)&1) || ((ITWORD>>3)&1)  ) MT2 |= 4;
        }
    }
  ITRG91 = ITWORD;
  if (MT2) { NTRBIT |= (1<<4); NPHYTR[8]++;}
  // Fill Level1  Trigger Bit Word in bank X1RG
  // first check if there is an existing row with TPR as name
  bool exist = false;
  for(vector<X1RG*>::iterator iter=Readout()->begin();iter<Readout()->end();iter++)
    {
      char tmp[5];
      strncpy(tmp,(*iter)->NA,4); // copy the bank word
      tmp[4] = '\0';
      if ((strcasecmp(tmp, "TPR ") == 0 ))
        {
         // replace the content.
         ((*iter)->CO[0]) = NTRBIT;
         ((*iter)->CO[1]) = NTRBIT;
         ((*iter)->CO[2]) = NTRBIT;
         exist = true;
        }
    }
  // Otherwise, create a new row.
  if (!exist)
   {
     vector<X1RG*>::iterator pos=Readout()->begin();
     pos++; // TSR will be the second row
     X1RG* RowToAdd = new X1RG;
     Readout()->insert(pos,RowToAdd);
     pos=Readout()->begin();
     pos++; // go to the new row
     ((*pos)->CO[0]) = NTRBIT;
     ((*pos)->CO[1]) = NTRBIT;
     ((*pos)->CO[2]) = NTRBIT;
   } 
}
// X1DISC
void AlEvent::SimulateOldTrigger(int* IHTSUM, int* IHWSUM, int* IETSUM, int* IEWSUM, int* ILTSUM, int* IITSUM, int* IECTTE, int* IHCTTE, int* IECWTE)const
{
  int NHTBIT[8] = {0};
  int NHWBIT[8] = {0};
  int NETBIT[8] = {0};
  int NEWBIT[8] = {0};
  int NLTBIT[8] = {0};
  int NITBIT[8] = {0};
  int NTEBIT = 0;
  X1TH *ECTR,*ECWI,*HCTR,*HCWI,*LCTR,*ECTT,*ECTW,*HCTT;
  // get thresholds
  for(vector<X1TH*>::iterator iter=TriggerOldlevel1Threshold()->begin();iter<TriggerOldlevel1Threshold()->end();iter++)
   {
      char name[5];
      strncpy(name,(*iter)->TT,4); // copy the bank word
      name[4] = '\0';
      if ((strcasecmp(name, "ECTR") == 0 )) ECTR = (*iter);
      if ((strcasecmp(name, "ECWI") == 0 )) ECWI = (*iter);
      if ((strcasecmp(name, "HCTR") == 0 )) HCTR = (*iter);
      if ((strcasecmp(name, "HCWI") == 0 )) HCWI = (*iter);
      if ((strcasecmp(name, "LCTR") == 0 )) LCTR = (*iter);
      if ((strcasecmp(name, "ECTT") == 0 )) ECTT = (*iter);
      if ((strcasecmp(name, "ECTW") == 0 )) ECTW = (*iter);
      if ((strcasecmp(name, "HCTT") == 0 )) HCTT = (*iter);
   }
  // HCAL/ECAL trigger sources
  int KK=-1;
  for(int i=1;i<=4;i++)
    {
      int ibit=1;
      for(int j=1;j<=72;j++)
        {
          int jbit,kbit,k;
          if (ibit>32)
            {
              jbit = ibit - 32 - 1;
	      k = 2*i-1;
            }
	  else
            {
              jbit = ibit - 1;
              k = 2*i;
            }
          kbit = ((j-1)%32);
	  if (!kbit) KK++;
          if ((IHTSUM[j-1] > HCTR->TV[i-1])||(HCTR->TV[i-1] == 0)) 
            {
              NHTBIT[k-1] |= (1<<jbit);
	      TriggerLevelEventBitPattern()->HT[KK] |= (1<<kbit);
            }
          if (IHWSUM[j-1] >= HCWI->TV[i-1])
            {
              NHWBIT[k-1] |= (1<<jbit);
              TriggerLevelEventBitPattern()->HW[KK] |= (1<<kbit);
            }
          if ((IETSUM[j-1] > ECTR->TV[i-1])||(ECTR->TV[i-1] == 0))
            {
              NETBIT[k-1] |= (1<<jbit);
              TriggerLevelEventBitPattern()->LW[KK] |= (1<<kbit);
            }
          if (IEWSUM[j-1] >= ECWI->TV[i-1])
            TriggerLevelEventBitPattern()->EW[KK] |= (1<<kbit);
          ibit++;
          if(j == 36) ibit = 25;
        }
    }
  // ECAL wire trigger sources
  for(int i=1;i<=4;i++)
    {
      for(int j=1;j<=72;j+=2)
        {
          if((IEWSUM[j-1] <= ECWI->TV[i-1]) || (IEWSUM[j] <= ECWI->TV[i-1])) continue;
          if(j<24)
            {
              // endcap A
              int jbit = ((j+3)/4 - 1);
              NEWBIT[2*i-1] |= (1<<jbit);
              NEWBIT[2*i-1] |= (1<<(jbit+6));
              jbit = ((j+23)/2);
              NEWBIT[2*i-1] |= (1<<jbit);
              if(jbit == 23) jbit = 11;
              NEWBIT[2*i-1] |= (1<<(jbit+1));
            }
          else if(j>48)
            {
              // endcap B
              int jbit = ((j+15)/4);
              NEWBIT[2*i-2] |= (1<<jbit);
              NEWBIT[2*i-2] |= (1<<(jbit+6));
              jbit = ((j-41)/2);
              NEWBIT[2*i-2] |= (1<<jbit);
              if(jbit == 15) jbit = 3;
              NEWBIT[2*i-2] |= (1<<(jbit+1));
            }
          else
            {
              // barrel
              int jbit = (j/2);
              NEWBIT[2*i-1] |= (1<<jbit);
              NEWBIT[2*i-2] |= (1<<(jbit-8));
              if(jbit<20)  NEWBIT[2*i-1] |= (1<<(jbit+12));
              else         NEWBIT[2*i-2] |= (1<<(jbit-20));
            }
        }
    }
  // LCAL tower trigger sources
  for(int i=0;i<4;i++)
   {
     for(int j=0;j<24;j++)
      {
        if(ILTSUM[j] > LCTR->TV[i]) NLTBIT[i] |= (1<<j);
        if((j>12)&&(ILTSUM[j]>LCTR->TV[i])) NLTBIT[i+4] |= (1<<((j+6)%12));
      }
     TriggerLevelEventBitPattern()->LT[i] = NLTBIT[i];
   }
  // SICAL trigger sources
  SimulateSicalTrigger();
  // ITC segment trigger bits
  int ibit = 1;
  for(int j=1;j<=72;j++)
    {
       int jbit,k,kk,kb;
       if(ibit > 32)
         {
           jbit = ibit - 32 - 1;
           k=0;
         }
       else
         {
           jbit = ibit - 1;
           k=1;
         }
       if(j<=32)
         {
           kk=0;
           kb=j-1;
         }
       else if(j>64)
         {
           kk=2;
           kb=j - 64 - 1;
         }
       else
         {
           kk=1;
           kb=j - 32 - 1;
         }
       if(((IITSUM[kk]>>kb)&1)) NITBIT[k] |= (1<<jbit);
       ibit++;
       if(j == 36) ibit = 25;
    }
  TriggerLevelEventBitPattern()->IT[0] = NITBIT[1];
  TriggerLevelEventBitPattern()->IT[1] = ((((NITBIT[0]>>0)&15)<<0)|(((NITBIT[0]>>4)&65535)<<4));
  TriggerLevelEventBitPattern()->IT[2] = IITSUM[2];
  TriggerLevelEventBitPattern()->IT[3] = IITSUM[3];
  // Total energy
  int KECTW[4]={2300,2300,2800,3500};
  for(int i=0;i<4;i++)
    {
      if(IHCTTE[i]>HCTT->TV[i])   NTEBIT |= (1<<i);
      if(IECTTE[i]>ECTT->TV[i])   NTEBIT |= (1<<(i+4));
      if(IECWTE[i]>ECTW->TV[i])   NTEBIT |= (1<<(i+8));
      if(IECWTE[i+4]>ECTW->TV[i]) NTEBIT |= (1<<(i+12));
      if(IECWTE[i]>KECTW[i])      NTEBIT |= (1<<(i+24));
      if(IECWTE[i+4]>KECTW[i])    NTEBIT |= (1<<(i+28));
    }
  TriggerLevelEventBitPattern()->TE[0] = ((((NTEBIT>>0)&15)<<0)|(((NTEBIT>>4)&15)<<16));
  TriggerLevelEventBitPattern()->TE[1] = ((((NTEBIT>>8)&15)<<0)|(((NTEBIT>>24)&15)<<4)
                                         |(((NTEBIT>>12)&15)<<16)|(((NTEBIT>>28)&15)<<20));
  // Apply Trigger

  ApplyOldTrigger(NHTBIT, NHWBIT, NETBIT, NEWBIT, NLTBIT, NITBIT, NTEBIT);

  // Convert segment energies into ADC counts and fill them into the bank X1AD
  // First initialize the bank.
  // and if one exist: purge!
  for(vector<X1AD*>::iterator iter=Triggerlevel1Adc()->begin();iter<Triggerlevel1Adc()->end();iter++)
    delete (*iter);
  Triggerlevel1Adc()->resize(5);
  for(vector<X1AD*>::iterator iter=Triggerlevel1Adc()->begin();iter<Triggerlevel1Adc()->end();iter++)
    (*iter) = new X1AD;
  // now, fill members
  vector<X1AD*>::iterator x1ad = Triggerlevel1Adc()->begin();
  strncpy((*x1ad)->IT,"HCT ",4);
  for(int i=0;i<72;i+=2)
    (*x1ad)->AV[i/2] = (((((IHTSUM[i]/5)+96)<4096)?((IHTSUM[i]/5)+96):4096)*65536
                          + (((IHTSUM[i+1]/5)+96)<4096?((IHTSUM[i+1]/5)+96):4096));
  x1ad++;
  strncpy((*x1ad)->IT,"HCW ",4);
  for(int i=0;i<72;i+=2)
    (*x1ad)->AV[i/2] = (((((IHWSUM[i]*150)+96)<4096)?((IHWSUM[i]*150)+96):4096)*65536
                          + (((IHWSUM[i+1]*150)+96)<4096?((IHWSUM[i+1]*150)+96):4096));
  x1ad++;
  strncpy((*x1ad)->IT,"ECT ",4);
  for(int i=0;i<72;i+=2)
    {
      int num1 = ((((IETSUM[i]/5)+96)<4096)?((IETSUM[i]/5)+96):4096);
      int num2 = (((IETSUM[i+1]/5)+96)<4096?((IETSUM[i+1]/5)+96):4096);
      (*x1ad)->AV[i/2] = ((num1>0)?num1:0)*65536 + ((num2>0)?num2:0);
    }
  x1ad++;
  strncpy((*x1ad)->IT,"ECW ",4);
  for(int i=0;i<72;i+=2)
    (*x1ad)->AV[i/2] = (((((IEWSUM[i]/10)+96)<4096)?((IEWSUM[i]/10)+96):4096)*65536
                          + (((IEWSUM[i+1]/10)+96)<4096?((IEWSUM[i+1]/10)+96):4096));
  x1ad++;
  strncpy((*x1ad)->IT,"LCT ",4);
  for(int i=0;i<24;i+=2)
    (*x1ad)->AV[i/2] = (((((ILTSUM[i]/40)+96)<4096)?((ILTSUM[i]/40)+96):4096)*65536
                          + (((IEWSUM[i+1]/40)+96)<4096?((IEWSUM[i+1]/40)+96):4096));

}
// X1APTR
void AlEvent::ApplyOldTrigger(int* NHTBIT, int* NHWBIT, int* NETBIT, int* NEWBIT, int* NLTBIT, int* NITBIT, int NTEBIT)const
{
  // init physics trigger counter
  int NPHYTR[9] = {0};
  // single muon trigger
  int NTRBIT = 0;
  int ITRG11 = ( NITBIT[1] & NHWBIT[5] & NHTBIT[1]);
  int ITRG12 = ( NITBIT[0] & NHWBIT[4] & NHTBIT[0]);
  int ITRI1  = ( ITRG11 | ITRG12 );
  if (ITRI1) { NTRBIT |= (1<<0); NPHYTR[0]++;}
  // Single Charged El.-mag. energy trigger (SNG_C_EM)
  int ITRG21 = ( NITBIT[1] & NEWBIT[3] & NETBIT[5]);
  int ITRG22 = ( NITBIT[0] & NEWBIT[2] & NETBIT[4]);
  int ITRI2 = ( ITRG21 | ITRG22 );
  if (ITRI2) {  NTRBIT |= (1<<1); NPHYTR[1]++;}
  // Single Neutral El.-mag. energy         (SNG_N_EM)
  int ITRG31 = NEWBIT[7] & NETBIT[7];
  int ITRG32 = NEWBIT[6] & NETBIT[6] ;
  int ITRI3 = ( ITRG31 | ITRG32 );
  if (ITRI3) {  NTRBIT |= (1<<2); NPHYTR[2]++;}
  // Single Photon trigger
  // not implemented

  // Charged hadr. energy trigger           (SNG_C_HA)
  int ITRG51 = (NITBIT[1] & NHWBIT[1] & NHTBIT[3]);
  int ITRG52 = (NITBIT[0] & NHWBIT[0] & NHTBIT[2]);
  int ITRI5 = ( ITRG51 | ITRG52 );
  if (ITRG51) { NTRBIT |= (1<<4); NPHYTR[4]++;}
  // Neutral hadr. energy trigger           (SNG_N_HA)
  int ITRG61 = ( NHWBIT[3] & NHTBIT[5]);
  int ITRG62 = ( NHWBIT[2] & NHTBIT[4]);
  int ITRI6 = ( ITRG61 | ITRG62 );
  if (ITRG61) { NTRBIT |= (1<<5); NPHYTR[5]++;}
  // Total energy trigger
  int ITRG71 = 0;
  int ITRG72 = 0;
  if (((NTEBIT>>10)&1)&&((NTEBIT>>14)&1)) ITRG71 |= (1<<17);
  if (((NTEBIT>>12)&1)&&((NTEBIT>>13)&1)
      &&((NTEBIT>>8)&1)&&((NTEBIT>>9)&1)) ITRG71 |= (1<<20);
  if (((NTEBIT>>24)&1)&&((NTEBIT>>28)&1)) ITRG71 |= (1<<24);
  if (((NTEBIT>>25)&1)&&((NTEBIT>>29)&1)) ITRG71 |= (1<<25);
  if (ITRG71) { NTRBIT |= (1<<6); NPHYTR[6]++;}
  // Bhabha trigger  LCAL
  int ITRG81 = 0;
  int ITRG82 = 0;
  if (NLTBIT[1])                              ITRG81 |= (1<<0);
  if ((NLTBIT[2]&4095)&&(NLTBIT[2]&16773120)) ITRG81 |= (1<<3);
  if (NLTBIT[2]&4095)                         ITRG81 |= (1<<4);
  if (NLTBIT[2]&16773120)                     ITRG81 |= (1<<5);
  if (NLTBIT[3]&4095)                         ITRG81 |= (1<<6);
  if (NLTBIT[3]&16773120)                     ITRG81 |= (1<<7);
  if ((NLTBIT[2]&4095)&&(NLTBIT[3]&16773120)) ITRG81 |= (1<<14);
  if ((NLTBIT[3]&4095)&&(NLTBIT[2]&16773120)) ITRG81 |= (1<<15);
  if (ITRG81) { NTRBIT |= (1<<7); NPHYTR[7]++;}
  // Bhabha trigger  SICAL
  int ITRG92 = 0;
  int ITRG91 = 0;
  int MT2 = 0;
  int ITWORD = 0;
  if(SicalTriggerX2() != NULL)
    {
      ITWORD = SicalTriggerX2()->TW;
      if (ITWORD != 0)
        {
          //A VERY LOW    OR   B VERY LOW
          if (  ((ITWORD>>5)&1) || ((ITWORD>>4)&1)  ) MT2 |= 1;
          //A HIGH B LOW  OR   A LOW  B HIGH
          if (  ((ITWORD>>0)&1) || ((ITWORD>>1)&1)  ) MT2 |= 2;
          //A VERY HIGH   OR   B VERY HIGH
          if (  ((ITWORD>>2)&1) || ((ITWORD>>3)&1)  ) MT2 |= 4;
        }
    }
  ITRG91 = ITWORD;
  if (MT2) { NTRBIT |= (1<<8); NPHYTR[8]++;}
  // Fill Level1  Trigger Bit Word in bank XTEB
  TriggerLevelEventBitPattern()->T1 = (ITRG71|ITRG81|
                                       (((NTRBIT>>2)&1)<<2)|
                                       (((NTRBIT>>0)&3)<<8)|
                                       (((NTRBIT>>4)&3)<<11)); 
}
// Retrieve weight "number" from KWGT bank
float AlEvent::getGeneratorWeight(int number) const {

	if(GeneratorWeights()->size() == 0) return -1;
	for(vector<KWGT*>::iterator iter=GeneratorWeights()->begin();iter<GeneratorWeights()->end();iter++){
		if((*iter)->WN==number) {return (*iter)->WV;}
	}
	return -1;
}
