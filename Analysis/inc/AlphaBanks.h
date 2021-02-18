//////////////////////////////////////////////////////////
// Class AlphaBanks
// acts as a container for the AlephObjects
//
// Author : R. Cavanaugh
//
// C. Delaere : added Event, Run and Vertices
// C. Delaere : converted it into a ROOT object
// 
//////////////////////////////////////////////////////////

#ifndef _ALPHABANKS_H_
#define _ALPHABANKS_H_

#include <vector>
#include <map>
#include <TObject.h>
#include "AlTrack.h"
#include "AlCalObject.h"
#include "AlMuon.h"
#include "AlEflw.h"
#include "AlGamp.h"
#include "AlMCtruth.h"
#include "AlElec.h"
#include "AlEvent.h"
#include "AlRun.h"
#include "AlConcreteVertices.h"
template <class T> class AlephCollection;
#include "BankClasses.h"
#include "BankPatterns.h"

class AlphaBanks : public TObject
{
public:
     enum DataSource { BOS, ROOT };
     AlphaBanks(DataSource src=ROOT);
     virtual ~AlphaBanks();                  
     void LoadFromBos();             
     void InitObjectStructure();     
     AlephCollection< AlCalObject>& ECalObjectV();
     AlephCollection< AlCalObject*> ECalObjectPV();
     AlephCollection< AlCalObject>& HCalObjectV();
     AlephCollection< AlCalObject*> HCalObjectPV();
     AlephCollection< AlGamp     >& GampV() ;
     AlephCollection< AlGamp*    >  GampPV() ;
     AlephCollection< AlEflw     >& EflwV() ;
     AlephCollection< AlEflw*    >  EflwPV() ;     
     AlephCollection< AlTrack    >& TrackV() ;
     AlephCollection< AlTrack*   >  TrackPV() ;
     AlephCollection< AlTrack    >& V0TrackV() ;
     AlephCollection< AlTrack*   >  V0TrackPV() ;
     AlephCollection< AlTrack    >& StdV0V() ;
     AlephCollection< AlTrack*   >  StdV0PV() ;
     AlephCollection< AlTrack    >& LongV0V() ;
     AlephCollection< AlTrack*   >  LongV0PV() ;
     AlephCollection< AlMCtruth  >& MCtruthV() ;
     AlephCollection< AlMCtruth* >  MCtruthPV() ;
     AlephCollection< AlMuon     >& MuonV() ;
     AlephCollection< AlMuon*    >  MuonPV() ;
     AlephCollection< AlElec     >& ElecV() ;
     AlephCollection< AlElec*    >  ElecPV() ;
     AlVertex& MainVertex();
     AlVertex* MainVertexP();
     AlephCollection< AlVertex   >& SecVerticesV() ;
     AlephCollection< AlVertex*  >  SecVerticesPV() ;
     AlephCollection< AlVertex   >& MCverticesV() ;
     AlephCollection< AlVertex*  >  MCverticesPV() ;
     AlephCollection< AlObject*  >  ObjectPV() ;
     AlEvent& Event()  {return _Event;}
     AlRun&   Run()  {return _Run;}
     void addObject(AlObject* obj);
     template <class T> void AlphaBanks::addObject(AlephCollection<T>);
     bool isValid() const;
private:
     vector<QVEC> qvec;        
     vector<QVRT> qvrt;        
     QEXT qext;                
     QHAC qhac;                
     int  KFCHT, KLCHT, KNCHT, OKFCHT,
          KFCOT, KLCOT, KNCOT, OKFCOT,
          KFIST, KLIST, KNIST, OKFIST,
          KFAST, KLAST, KNAST, OKFAST,
          KFRET, KLRET, KNRET, OKFRET,
          KFEFT, KLEFT, KNEFT, OKFEFT,
          KFNET, KLNET, KNNET, OKFNET,
          KFGAT, KLGAT, KNGAT, OKFGAT,
          KFJET, KLJET, KNJET, OKFJET,
          KFMCT, KLMCT, KNMCT, OKFMCT,
          KFV0T, KLV0T, KNV0T, OKFV0T,
          KFLVT, KLLVT, KNLVT, OKFLVT,
	  KFDCT, KLDCT, KNDCT, OKFDCT,
          KFREV, KLREV, KNREV, OKFREV,
	  KFMCV, KLMCV, KNMCV, OKFMCV;
     AlephCollection< AlCalObject> ECalObject;  //!
     AlephCollection< AlCalObject> HCalObject;  //!
     AlephCollection< AlGamp     > Gamp;        //!
     AlephCollection< AlEflw     > Eflw;        //!
     AlephCollection< AlTrack    > Track;       //!
     AlephCollection< AlTrack    > V0Track;     //!
     AlephCollection< AlTrack    > StdV0;       //!
     AlephCollection< AlTrack    > LongV0;      //!
     AlephCollection< AlMCtruth  > MCtruth;     //!
     AlephCollection< AlMuon     > Muon;        //!
     AlephCollection< AlElec     > Elec;        //!
     AlephCollection< AlVertex   > SecVertices; //!
     AlephCollection< AlVertex   > MCvertices;  //!
     AlVertex _MainVertex;                      //!
     AlephCollection< AlObject*  > Objects;     //!
     AlEvent _Event;                            //!
     AlRun   _Run;                              //!
     map<AlTrack*,int> TEmap;                   //!
     bool _Valid;                               //!
ClassDef(AlphaBanks,1) // The ALPHA++ BOS-wrapper
}; 
#endif

