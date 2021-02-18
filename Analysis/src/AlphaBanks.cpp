/*-----------------------------------------------------------------------------*/
/* Define methods for the Event class and create objects from the FORTRAN      */
/* BOS memory.                                                                 */
/* Author: R. Cavanaugh                                                        */
/*-----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string> 
#include <stdlib.h>
#include "AlphaBanks.h"
#include "AlephCollection.h"
#include "TLorentzVector.h"
#include "TClass.h"

extern ofstream fout;

ClassImp(AlphaBanks)

///////////////////////////////////////////////////////////
//  Constructor
///////////////////////////////////////////////////////////
AlphaBanks::AlphaBanks(DataSource src) 
{
     if(src==BOS) LoadFromBos();
     _Valid = true;
}

void AlphaBanks::LoadFromBos()
{
     fout << "ERROR : AlphaBanks::LoadFromBos() unavailble in this ROOT-only version" << endl;
}
///////////////////////////////////////////////////////////
//  Destructor
///////////////////////////////////////////////////////////
/*-----------------------------------------------------------------------------*/
template <class AlphaObject>
void Detach( AlphaObject*& Object )
{
     delete Object;     
     Object = (AlphaObject*) NULL;     
}
/*-----------------------------------------------------------------------------*/
AlphaBanks::~AlphaBanks() 
{
     for( int Row = 0; (uint) Row < qvec.size(); Row++ ) 
     {
          if( qvec[Row].QD != (QDET*) NULL)  
	  {
               if( qvec[Row].QD -> AF != (FRFT*) NULL )   Detach( qvec[Row].QD -> AF );
               if( qvec[Row].QD -> AL != (FRTL*) NULL )   Detach( qvec[Row].QD -> AL );
               for( int i = 0; i < 4; i++)
                    if( qvec[Row].QD -> AT[i] != (TEXS*) NULL ) Detach( qvec[Row].QD -> AT[i] );
               if( qvec[Row].QD -> LT != (TEXS*) NULL )   Detach( qvec[Row].QD -> LT );
               if( qvec[Row].QD -> AE != (EIDT*) NULL )   Detach( qvec[Row].QD -> AE );
               if( qvec[Row].QD -> AH != (HMAD*) NULL )   Detach( qvec[Row].QD -> AH );
               if( qvec[Row].QD -> AM != (MCAD*) NULL )   Detach( qvec[Row].QD -> AM );
               if( qvec[Row].QD -> EC != (PECO*) NULL )   Detach( qvec[Row].QD -> EC );
               if( qvec[Row].QD -> HC != (PHCO*) NULL )   Detach( qvec[Row].QD -> HC );
               if( qvec[Row].QD -> ET != (PEPT*) NULL )   Detach( qvec[Row].QD -> ET );
               if( qvec[Row].QD -> FI != (FRID*) NULL )   Detach( qvec[Row].QD -> FI );
               if( qvec[Row].QD -> EF != (EFOL*) NULL )   Detach( qvec[Row].QD -> EF );
               if( qvec[Row].QD -> PC != (PCQA*) NULL )   Detach( qvec[Row].QD -> PC );
               if( qvec[Row].QD -> EG != (EGPC*) NULL )   Detach( qvec[Row].QD -> EG );
               if( qvec[Row].QD -> MU != (MUID*) NULL )   Detach( qvec[Row].QD -> MU );
               if( qvec[Row].QD -> PG != (PGAC*) NULL )   Detach( qvec[Row].QD -> PG );
               if( qvec[Row].QD -> PD != (PDLT*) NULL )   Detach( qvec[Row].QD -> PD );
               if( qvec[Row].QD -> PM != (PMLT*) NULL )   Detach( qvec[Row].QD -> PM );                    
               Detach( qvec[Row].QD );
	  }
     }
     qvec.resize( 0 );
     for( int Row = 0; (uint) Row < qvrt.size(); Row++ )
     {
          if( qvrt[Row].AY != (YV0V*) NULL) 
		  Detach( qvrt[Row].AY );
	  if( qvrt[Row].AF != (FVER*) NULL)
	  {
	       Detach( qvrt[Row].AF );
	  }
     }
     qvrt.resize( 0 );
     if( qext.LP != (RLEP*) NULL )  Detach( qext.LP );
     
     if( qhac.EH != (EVEH*) NULL )  Detach( qhac.EH );
     if( qhac.RH != (RUNH*) NULL )  Detach( qhac.RH );
     if( qhac.KE != (KEVH*) NULL )  Detach( qhac.KE );
     if( qhac.RE != (REVH*) NULL )  Detach( qhac.RE );
     if( qhac.BO != (BOMB*) NULL )  Detach( qhac.BO );
     if( qhac.AS != (ASIM*) NULL )  Detach( qhac.AS );
     if( qhac.AD != (ADBR*) NULL )  Detach( qhac.AD );
     if( qhac.CN != (XTCN*) NULL )  Detach( qhac.CN );
     if( qhac.OP != (XTOP*) NULL )  Detach( qhac.OP );
     if( qhac.LP != (LUPA*) NULL )  Detach( qhac.LP );
     if( qhac.SI != (SILH*) NULL )  Detach( qhac.SI );
     if( qhac.EB != (XTEB*) NULL )  Detach( qhac.EB );
     if( qhac.RB != (XTRB*) NULL )  Detach( qhac.RB );
     if( qhac.BP != (DTBP*) NULL )  Detach( qhac.BP );
     if( qhac.X2 != (SIX2*) NULL )  Detach( qhac.X2 );
     if( qhac.TC != (SITC*) NULL )  Detach( qhac.TC );
     if( qhac.EX != (EAUX*) NULL )  Detach( qhac.EX );
     for (unsigned int row=0;row<qhac.LO.size();row++)
        if( qhac.LO[row] != (LOLE*) NULL )  Detach( qhac.LO[row] );
     for (unsigned int row=0;row<qhac.X1.size();row++)
        if( qhac.X1[row] != (X1RG*) NULL )  Detach( qhac.X1[row] );
     for (unsigned int row=0;row<qhac.BN.size();row++)
        if( qhac.BN[row] != (XTBN*) NULL )  Detach( qhac.BN[row] );
     for (unsigned int row=0;row<qhac.HV.size();row++)
        if( qhac.HV[row] != (XHVB*) NULL )  Detach( qhac.HV[row] );
     for (unsigned int row=0;row<qhac.TV.size();row++)
        if( qhac.TV[row] != (X1TV*) NULL )  Detach( qhac.TV[row] );
     for (unsigned int row=0;row<qhac.KW.size();row++)
        if( qhac.KW[row] != (KWGT*) NULL )  Detach( qhac.KW[row] );
     for (unsigned int row=0;row<qhac.IP.size();row++)
        if( qhac.IP[row] != (X1IP*) NULL )  Detach( qhac.IP[row] );
     for (unsigned int row=0;row<qhac.XA.size();row++)
        if( qhac.XA[row] != (SIXA*) NULL )  Detach( qhac.XA[row] );
     for (unsigned int row=0;row<qhac.CO.size();row++)
        if( qhac.CO[row] != (SRCO*) NULL )  Detach( qhac.CO[row] );
     for (unsigned int row=0;row<qhac.BV.size();row++)
        if( qhac.BV[row] != (VHBV*) NULL )  Detach( qhac.BV[row] );
     for (unsigned int row=0;row<qhac.PV.size();row++)
        if( qhac.PV[row] != (VHPV*) NULL )  Detach( qhac.PV[row] );
     for (unsigned int row=0;row<qhac.TH.size();row++)
        if( qhac.TH[row] != (X1TH*) NULL )  Detach( qhac.TH[row] );
     for (unsigned int row=0;row<qhac.XD.size();row++)
        if( qhac.XD[row] != (X1AD*) NULL )  Detach( qhac.XD[row] );
}

void AlphaBanks::addObject(AlObject* obj) { Objects.push_back(obj); }
AlephCollection< AlCalObject>& AlphaBanks::ECalObjectV()   {return ECalObject;             }
AlephCollection< AlCalObject*> AlphaBanks::ECalObjectPV()  {return ECalObject.Pointers();  }
AlephCollection< AlCalObject>& AlphaBanks::HCalObjectV()   {return HCalObject;             }
AlephCollection< AlCalObject*> AlphaBanks::HCalObjectPV()  {return HCalObject.Pointers();  }
AlephCollection< AlGamp     >& AlphaBanks::GampV()         {return Gamp;                   }
AlephCollection< AlGamp*    >  AlphaBanks::GampPV()        {return Gamp.Pointers();        }
AlephCollection< AlEflw     >& AlphaBanks::EflwV()         {return Eflw;                   }
AlephCollection< AlEflw*    >  AlphaBanks::EflwPV()        {return Eflw.Pointers();        }
AlephCollection< AlTrack    >& AlphaBanks::TrackV()        {return Track;                  }
AlephCollection< AlTrack*   >  AlphaBanks::TrackPV()       {return Track.Pointers();       }
AlephCollection< AlTrack    >& AlphaBanks::V0TrackV()      {return V0Track;                }
AlephCollection< AlTrack*   >  AlphaBanks::V0TrackPV()     {return V0Track.Pointers();     }
AlephCollection< AlTrack    >& AlphaBanks::StdV0V()        {return StdV0;                  }
AlephCollection< AlTrack*   >  AlphaBanks::StdV0PV()       {return StdV0.Pointers();       }
AlephCollection< AlTrack    >& AlphaBanks::LongV0V()       {return LongV0;                 }
AlephCollection< AlTrack*   >  AlphaBanks::LongV0PV()      {return LongV0.Pointers();      }
AlephCollection< AlMCtruth  >& AlphaBanks::MCtruthV()      {return MCtruth;                }
AlephCollection< AlMCtruth* >  AlphaBanks::MCtruthPV()     {return MCtruth.Pointers();     }
AlephCollection< AlMuon     >& AlphaBanks::MuonV()         {return Muon;                   }
AlephCollection< AlMuon*    >  AlphaBanks::MuonPV()        {return Muon.Pointers();        }
AlephCollection< AlElec     >& AlphaBanks::ElecV()         {return Elec;                   }
AlephCollection< AlElec*    >  AlphaBanks::ElecPV()        {return Elec.Pointers();        }
AlVertex&                      AlphaBanks::MainVertex()    {return _MainVertex;            }
AlVertex*                      AlphaBanks::MainVertexP()   {return &_MainVertex;           }
AlephCollection< AlVertex   >& AlphaBanks::SecVerticesV()  {return SecVertices;            }
AlephCollection< AlVertex*  >  AlphaBanks::SecVerticesPV() {return SecVertices.Pointers(); }
AlephCollection< AlVertex   >& AlphaBanks::MCverticesV()   {return MCvertices;             }
AlephCollection< AlVertex*  >  AlphaBanks::MCverticesPV()  {return MCvertices.Pointers();  }
AlephCollection< AlObject*  >  AlphaBanks::ObjectPV()      {return Objects;                }

bool AlphaBanks::isValid() const
{
	return _Valid;
}
void AlphaBanks::InitObjectStructure()
{
     try{
     // it may be an error in some very rare cases.
     // sometimes, there is an lepton without any track
     // (missing qvec), etc. 
     MCtruth.resize( KNMCT );
     if(KNMCT)
     {
     if ((unsigned int)KLMCT>qvec.size()) throw 0;
     for( int i = KFMCT - 1; i < KLMCT; i++ ) 
     {
         MCtruth[ i - (KFMCT - 1) ].SetPointer( &qvec[i] );

         AlephCollection<AlMCtruth*> MotherVector( qvec[i].NO );
         for( int j = 0; j < qvec[i].NO; j++)  MotherVector[j] = &MCtruth[ qvec[i].OL[j] - OKFMCT ];
         MCtruth[ i - (KFMCT - 1) ].setMotherVector( MotherVector );

         AlephCollection<AlMCtruth*> DaughterVector( qvec[i].ND );
         for( int j = 0; j < qvec[i].ND; j++)  DaughterVector[j] = &MCtruth[ qvec[i].DL[j] - OKFMCT ];
         MCtruth[ i - (KFMCT - 1) ].setDaughterVector( DaughterVector );
     }
     for( AlephCollection<AlMCtruth>::iterator imc = MCtruthV().begin(); imc < MCtruthV().end(); imc++ )
     {
          addObject(&(*imc));
     }
     }
     Track.resize( KNCHT ); 
     if(KNCHT)
     {
     if ((unsigned int)KLCHT>qvec.size()) throw 1;
     for( int i = KFCHT - 1; i < KLCHT; i++ ) 
     {
          Track[ i - (KFCHT - 1) ].SetPointer( &qvec[i] );
	  AlephCollection<AlMCtruth*> MatchingVector( qvec[i].NM );
	  for( int j = 0; j < qvec[i].NM; j++) 
	  {
		  if ((unsigned int)(qvec[i].ML[j] - OKFMCT)>=MCtruth.size()) throw 2;
		  MatchingVector[j] = &MCtruth[ qvec[i].ML[j] - OKFMCT ];
	  }
          Track[ i - (KFCHT - 1) ].setMatchingVector( MatchingVector );
     }
     for( AlephCollection<AlTrack>::iterator ich = TrackV().begin(); ich < TrackV().end(); ich++ )
     {
          addObject(&(*ich));
     }
     }
     if(KNCOT)
     {
     if ((unsigned int)KLCOT>qvec.size()) throw 1;
     int nECAL=0;
     int nHCAL=0;
     for( int i = KFCOT - 1; i < KLCOT; i++ )
	     if(qvec[i].QD)
	     {
		     if(qvec[i].QD->EC) nECAL++;
		     if(qvec[i].QD->HC) nHCAL++;
	     }
     ECalObject.resize( nECAL );
     HCalObject.resize( nHCAL );
     nECAL=0;
     nHCAL=0;
     for( int i = KFCOT - 1; i < KLCOT; i++ )
	     if(qvec[i].QD)
	     {
		     if(qvec[i].QD->EC)
		     {
			     ECalObject[ nECAL ].SetPointer( &qvec[i] );
			     ECalObject[ nECAL++ ].SetIsolation((i>=KFIST)&&(i<KLIST));
		     }
		     if(qvec[i].QD->HC)
		     {
			     HCalObject[ nHCAL ].SetPointer( &qvec[i] );
			     HCalObject[ nHCAL++ ].SetIsolation((i>=KFIST)&&(i<KLIST));
		     }
             }
     for( AlephCollection<AlCalObject>::iterator ical = ECalObjectV().begin(); ical < ECalObjectV().end(); ical++ )
     {
          addObject(&(*ical));
     }
     for( AlephCollection<AlCalObject>::iterator ical = HCalObjectV().begin(); ical < HCalObjectV().end(); ical++ )
     {
          addObject(&(*ical));
     }
     }
     V0Track.resize( KNDCT ); 
     if(KNDCT)
     {
     if ((unsigned int)KLDCT>qvec.size()) throw 11;
     for( int i = KFDCT - 1; i < KLDCT; i++ ) 
     {
          V0Track[ i - (KFDCT - 1) ].SetPointer( &qvec[i] );
	  AlephCollection<AlMCtruth*> MatchingVector( qvec[i].NM );
	  for( int j = 0; j < qvec[i].NM; j++)
	  {
		  if ((unsigned int)(qvec[i].ML[j] - OKFMCT)>=MCtruth.size()) throw 2;
		  MatchingVector[j] = &MCtruth[ qvec[i].ML[j] - OKFMCT ];
	  }
          V0Track[ i - (KFDCT - 1) ].setMatchingVector( MatchingVector );
     }
     for( AlephCollection<AlTrack>::iterator ich = V0TrackV().begin(); ich < V0TrackV().end(); ich++ )
     {
          addObject(&(*ich));
     }
     }
     StdV0.resize( KNV0T ); 
     if(KNV0T)
     {
     if ((unsigned int)KLV0T>qvec.size()) throw 12;
     for( int i = KFV0T - 1; i < KLV0T; i++ ) 
     {
          StdV0[ i - (KFV0T - 1) ].SetPointer( &qvec[i] );
	  AlephCollection<AlMCtruth*> MatchingVector( qvec[i].NM );
	  for( int j = 0; j < qvec[i].NM; j++) 
	  {
		  if ((unsigned int)(qvec[i].ML[j] - OKFMCT)>=MCtruth.size()) throw 2;
		  MatchingVector[j] = &MCtruth[ qvec[i].ML[j] - OKFMCT ];
	  }
          StdV0[ i - (KFV0T - 1) ].setMatchingVector( MatchingVector );
     }
     for( AlephCollection<AlTrack>::iterator ich = StdV0V().begin(); ich < StdV0V().end(); ich++ )
     {
          addObject(&(*ich));
     }
     }
     LongV0.resize( KNLVT ); 
     if(KNLVT)
     {
     if ((unsigned int)KLLVT>qvec.size()) throw 13;
     for( int i = KFLVT - 1; i < KLLVT; i++ ) 
     {
          LongV0[ i - (KFLVT - 1) ].SetPointer( &qvec[i] );
	  AlephCollection<AlMCtruth*> MatchingVector( qvec[i].NM );
	  for( int j = 0; j < qvec[i].NM; j++) 
	  {
		  if ((unsigned int)(qvec[i].ML[j] - OKFMCT)>=MCtruth.size()) throw 2;
		  MatchingVector[j] = &MCtruth[ qvec[i].ML[j] - OKFMCT ];
	  }
          LongV0[ i - (KFLVT - 1) ].setMatchingVector( MatchingVector );
     }
     for( AlephCollection<AlTrack>::iterator ich = LongV0V().begin(); ich < LongV0V().end(); ich++ )
     {
          addObject(&(*ich));
     }
     }
     Eflw.resize( KNEFT );
     if(KNEFT)
     {
     if ((unsigned int)KLEFT>qvec.size()) throw 3; 
     for( int i = KFEFT - 1; i < KLEFT; i++ ) 
     {
          Eflw[ i - (KFEFT - 1) ].SetPointer( &qvec[i] );
	  Eflw[ i - (KFEFT - 1) ].setEfType(Eflw[ i - (KFEFT - 1) ].Qvec()->QD->EF->TY);
	  AlTrack* theAssoctrack;
	  int itr = Eflw[ i - (KFEFT - 1) ].Qvec()->QD->EF->LT;
	  if (itr>(int)Track.size()) throw 5;
	  if (itr==0)
		  theAssoctrack = NULL;
	  else
	  {
		  theAssoctrack = &Track[itr-1];
		  theAssoctrack->setEflw(&Eflw[ i - (KFEFT - 1) ]);
	  }
	  Eflw[ i - (KFEFT - 1) ].setTrack(theAssoctrack);
	  TEmap[ theAssoctrack  ] = (i - (KFEFT - 1));
     }
     for( AlephCollection<AlEflw>::iterator ift = EflwV().begin(); ift < EflwV().end(); ift++ )
     {
          addObject(&(*ift));
     }
     }
     for( AlephCollection<AlTrack>::iterator itr = TrackV().begin(); itr < TrackV().end(); itr++)
     {
	     if(itr->Qvec()->QD->MU)
	     {
		     AlTrack* theAssocTrack = &(*itr);
		     AlMuon tmpmuon;
		     tmpmuon.setTrack( theAssocTrack );
		     AlEflw* theAssocEflw;
		     if (TEmap.find(theAssocTrack) == TEmap.end())
			     theAssocEflw = NULL;
		     else
			     theAssocEflw = &Eflw[TEmap.find(theAssocTrack)->second];
		     tmpmuon.setEflw( theAssocEflw );
		     Muon.push_back(tmpmuon);
	     }
     }
     for( AlephCollection<AlMuon>::iterator imu = MuonV().begin(); imu < MuonV().end(); imu++ )
     {
          addObject(&(*imu));
     }
     for( AlephCollection<AlTrack>::iterator itr = TrackV().begin(); itr < TrackV().end(); itr++)
     {
	     if(itr->Qvec()->QD->AE)
	     {
		     AlTrack* theAssocTrack = &(*itr);
		     AlElec tmpelec;
		     tmpelec.setTrack( theAssocTrack );
		     AlEflw* theAssocEflw;
		     if (TEmap.find(theAssocTrack) == TEmap.end())
			     theAssocEflw = NULL;
		     else
			     theAssocEflw = &Eflw[TEmap.find(theAssocTrack)->second];
		     tmpelec.setEflw( theAssocEflw );
		     Elec.push_back(tmpelec);
	     }
     }
     for( AlephCollection<AlElec>::iterator iel = ElecV().begin(); iel < ElecV().end(); iel++ )
       {
          addObject(&(*iel));
       }
     Gamp.resize( KNGAT );
     if(KNGAT)
     {
     if ((unsigned int)KLGAT > qvec.size()) throw 8;
     for( int i = KFGAT - 1; i < KLGAT; i++ ) 
     {
          Gamp[ i - (KFGAT - 1) ].SetPointer( &qvec[i] );
	  if((Gamp[ i - (KFGAT - 1) ].Qvec()!=NULL)&&(Gamp[ i - (KFGAT - 1) ].Qvec()->QD!=NULL)&&(Gamp[ i - (KFGAT - 1) ].Qvec()->QD->PG!=NULL))
		if((Gamp[ i - (KFGAT - 1) ].Qvec()->QD->PG->PN>0)&&(Gamp[ i - (KFGAT - 1) ].Qvec()->QD->PG->PN<=(KLGAT-KFGAT+1)))
      			Gamp[ i - (KFGAT - 1) ].SetFake(&Gamp[ i + (Gamp[ i - (KFGAT - 1) ].Qvec()->QD->PG->PN) - (KFGAT - 1)]);
     }
     for( AlephCollection<AlGamp>::iterator ift = GampV().begin(); ift < GampV().end(); ift++ )
     {
          addObject(&(*ift));
     }
     }
     if(KNREV>0)               // it may be no vertex at all
     {
     if ((unsigned int)KLREV > qvrt.size()) throw 9;
     	if(qvrt[KFREV-1].TY == 1) // it may be no main vertex
     	{
	     _MainVertex.SetPointer(&qvrt[KFREV-1]);
	     _MainVertex.SetIncomingTrack(NULL);
	     for (vector<unsigned short>::iterator ii=qvrt[KFREV-1].DL.begin();ii<qvrt[KFREV-1].DL.end();ii++)
	     {
		     AlTrack* theaddr = NULL;
		     if(((*ii)>=OKFCHT)&&((*ii)<(OKFCHT+KNCHT))) theaddr = &Track[(*ii)-KFCHT];
		     if(((*ii)>=OKFDCT)&&((*ii)<(OKFDCT+KNDCT))) theaddr = &V0Track[(*ii)-KFDCT];
		     _MainVertex.AddOutgoingTrack(theaddr);
	     }
	     SecVertices.resize(KNREV-1); 
	     for(int i = KFREV; i<KLREV; i++)
	     {
		     SecVertices[i-KFREV].SetPointer(&qvrt[i]);
		     AlTrack* theaddr = NULL;
		     if((qvrt[i].IP>=OKFV0T)&&(qvrt[i].IP<(OKFV0T+KNV0T))) theaddr = &StdV0[qvrt[i].IP-OKFV0T];
		     if((qvrt[i].IP>=OKFLVT)&&(qvrt[i].IP<(OKFLVT+KNLVT))) theaddr = &LongV0[qvrt[i].IP-OKFLVT];
		     if((qvrt[i].IP>=OKFCHT)&&(qvrt[i].IP<(OKFCHT+KNCHT))) theaddr = &Track[qvrt[i].IP-OKFCHT];
		     SecVertices[i-KFREV].SetIncomingTrack(theaddr);
		     for (vector<unsigned short>::iterator ii=qvrt[i].DL.begin();ii<qvrt[i].DL.end();ii++)
		     {
			     AlTrack* theaddr = NULL;
			     if(((*ii)>=OKFCHT)&&((*ii)<(OKFCHT+KNCHT))) theaddr = &Track[(*ii)-OKFCHT];
			     if(((*ii)>=OKFDCT)&&((*ii)<(OKFDCT+KNDCT))) theaddr = &V0Track[(*ii)-OKFDCT];
			     SecVertices[i-KFREV].AddOutgoingTrack(theaddr);
		     }
	     }
     	}
     	else
     	{
	     SecVertices.resize(KNREV);
	     for(int i = KFREV-1; i<KLREV; i++)
	     {
		     SecVertices[i-KFREV+1].SetPointer(&qvrt[i]);
		     AlTrack* theaddr = NULL;
		     if((qvrt[i].IP>=OKFV0T)&&(qvrt[i].IP<(OKFV0T+KNV0T))) theaddr = &StdV0[qvrt[i].IP-OKFV0T];
		     if((qvrt[i].IP>=OKFLVT)&&(qvrt[i].IP<(OKFLVT+KNLVT))) theaddr = &LongV0[qvrt[i].IP-OKFLVT];
		     SecVertices[i-KFREV+1].SetIncomingTrack(theaddr);
		     for (vector<unsigned short>::iterator ii=qvrt[i].DL.begin();ii<qvrt[i].DL.end();ii++)
		     {
			     AlTrack* theaddr = NULL;
			     if(((*ii)>=OKFCHT)&&((*ii)<(OKFCHT+KNCHT))) theaddr = &Track[(*ii)-OKFCHT];
			     if(((*ii)>=OKFDCT)&&((*ii)<(OKFDCT+KNDCT))) theaddr = &V0Track[(*ii)-OKFDCT];
			     SecVertices[i-KFREV+1].AddOutgoingTrack(theaddr);
		     }
	     }
     	}
     }
     MCvertices.resize(KNMCV);
     if(KNMCV)
     {
     if ((unsigned int)KLMCV > qvrt.size()) throw 10;
     for(int i = KFMCV-1; i<KLMCV; i++)
     {
	     MCvertices[i-KFMCV+1].SetPointer(&qvrt[i]);
	     AlMCtruth* theaddr = NULL;
	     if((qvrt[i].IP>=OKFMCT)&&(qvrt[i].IP<(OKFMCT+KNMCT))) theaddr = &MCtruth[qvrt[i].IP-OKFMCT];
	     MCvertices[i-KFMCV+1].SetIncomingTrack(theaddr);
	     for (vector<unsigned short>::iterator ii=qvrt[i].DL.begin();ii<qvrt[i].DL.end();ii++)
	     {
		     AlMCtruth* theaddr = NULL;
		     if(((*ii)>=OKFMCT)&&((*ii)<(OKFMCT+KNMCT))) theaddr = &MCtruth[(*ii)-OKFMCT];
		     MCvertices[i-KFMCV+1].AddOutgoingTrack(theaddr);
	     }
     }
     }
     if(KNCHT)
     for( int i = KFCHT - 1; i < KLCHT; i++ ) 
     {
	  int ismain = KNREV ? ((qvrt[KFREV-1].TY == 1) ? 1 : 0) : 0;
	  if (((qvec[i].OV!=0)&&((qvec[i].OV-(OKFREV-1)-ismain)<-1) ) ||((qvec[i].OV-OKFREV-ismain)>=(int)SecVertices.size())) throw 14;
	  if (((qvec[i].EV!=0)&&((qvec[i].EV-(OKFREV-1)-ismain)<-1) ) ||((qvec[i].EV-OKFREV-ismain)>=(int)SecVertices.size())) throw 15;
	  QvrtBase*  origin;
	  if ((qvec[i].OV==0)||(qvec[i].OV==OKFREV))
	  {
		  if (ismain==1)
			  origin = &_MainVertex;
		  else    origin = NULL;
	  }
	  else origin = &SecVertices[qvec[i].OV-OKFREV-ismain];
	  QvrtBase*  end = &SecVertices[qvec[i].EV-OKFREV-ismain];
	  if (qvec[i].EV==0) end = NULL;
	  Track[ i - (KFCHT - 1) ].setOriginVertex(origin);
	  Track[ i - (KFCHT - 1) ].setEndVertex(end);
     }
     if(KNDCT)
     for( int i = KFDCT - 1; i < KLDCT; i++ ) 
     {
	  int ismain = KNREV ? ((qvrt[KFREV-1].TY == 1) ? 1 : 0) : 0 ;
	  if (((qvec[i].OV!=0)&&((qvec[i].OV-(OKFREV-1)-ismain)<-1) ) ||((qvec[i].OV-OKFREV-ismain)>=(int)SecVertices.size())) throw 14;
	  if (((qvec[i].EV!=0)&&((qvec[i].EV-(OKFREV-1)-ismain)<-1) ) ||((qvec[i].EV-OKFREV-ismain)>=(int)SecVertices.size())) throw 15;
	  QvrtBase*  origin;
	  if ((qvec[i].OV==0)||(qvec[i].OV==OKFREV))
	  {
		  if (ismain==1)
			  origin = &_MainVertex;
		  else    origin = NULL;
	  }
	  else origin = &SecVertices[qvec[i].OV-OKFREV-ismain];
	  QvrtBase*  end = &SecVertices[qvec[i].EV-OKFREV-ismain];
	  if (qvec[i].EV==0) end = NULL;
	  V0Track[ i - (KFDCT - 1) ].setOriginVertex(origin);
	  V0Track[ i - (KFDCT - 1) ].setEndVertex(end);
     }
     if(KNV0T)
     for( int i = KFV0T - 1; i < KLV0T; i++ ) 
     {
	  int ismain = KNREV ? ((qvrt[KFREV-1].TY == 1) ? 1 : 0) : 0 ;
	  if (((qvec[i].OV!=0)&&((qvec[i].OV-(OKFREV-1)-ismain)<-1) ) ||((qvec[i].OV-OKFREV-ismain)>=(int)SecVertices.size())) throw 14;
	  if (((qvec[i].EV!=0)&&((qvec[i].EV-(OKFREV-1)-ismain)<-1) ) ||((qvec[i].EV-OKFREV-ismain)>=(int)SecVertices.size())) throw 15;
	  QvrtBase*  origin;
	  if ((qvec[i].OV==0)||(qvec[i].OV==OKFREV))
	  {
		  if (ismain==1)
			  origin = &_MainVertex;
		  else    origin = NULL;
	  }
	  else origin = &SecVertices[qvec[i].OV-OKFREV-ismain];
	  QvrtBase*  end = &SecVertices[qvec[i].EV-OKFREV-ismain];
	  if (qvec[i].EV==0) end = NULL;
	  StdV0[ i - (KFV0T - 1) ].setOriginVertex(origin);
	  StdV0[ i - (KFV0T - 1) ].setEndVertex(end);
     }
     if(KNLVT)
     for( int i = KFLVT - 1; i < KLLVT; i++ ) 
     {
	  int ismain = KNREV ? ((qvrt[KFREV-1].TY == 1) ? 1 : 0) : 0 ;
	  if (((qvec[i].OV!=0)&&((qvec[i].OV-(OKFREV-1)-ismain)<-1) ) ||((qvec[i].OV-OKFREV-ismain)>=(int)SecVertices.size())) throw 14;
	  if (((qvec[i].EV!=0)&&((qvec[i].EV-(OKFREV-1)-ismain)<-1) ) ||((qvec[i].EV-OKFREV-ismain)>=(int)SecVertices.size())) throw 15;
	  QvrtBase*  origin;
	  if ((qvec[i].OV==0)||(qvec[i].OV==OKFREV))
	  {
		  if (ismain==1)
			  origin = &_MainVertex;
		  else    origin = NULL;
	  }
	  else origin = &SecVertices[qvec[i].OV-OKFREV-ismain];
	  QvrtBase*  end = &SecVertices[qvec[i].EV-OKFREV-ismain];
	  if (qvec[i].EV==0) end = NULL;
	  LongV0[ i - (KFLVT - 1) ].setOriginVertex(origin);
	  LongV0[ i - (KFLVT - 1) ].setEndVertex(end);
     }
     if(KNMCT)
     for( int i = KFMCT - 1; i < KLMCT; i++ ) 
     {
        MCtruth[ i - (KFMCT - 1) ].SetPointer( &qvec[i] );
	if ((((qvec[i].OV-OKFMCV)<0)&&(qvec[i].OV!=0))||((qvec[i].OV-OKFMCV)>=(int)MCvertices.size())) throw 14;
	if ((((qvec[i].EV-OKFMCV)<0)&&(qvec[i].EV!=0))||((qvec[i].EV-OKFMCV)>=(int)MCvertices.size())) throw 15;
	QvrtBase*  origin = &MCvertices[qvec[i].OV-OKFMCV];
	QvrtBase*  end    = &MCvertices[qvec[i].EV-OKFMCV];
	if (qvec[i].EV==0) end = NULL;
	if (qvec[i].OV==0) origin = NULL;
	MCtruth[ i - (KFMCT - 1) ].setOriginVertex(origin);
	MCtruth[ i - (KFMCT - 1) ].setEndVertex(end);
     }
     }
     catch (int a) {  cerr << "Event invalid: " << a << endl; _Valid = false;} 
     _Event.SETqhac(&qhac);
     _Run.SETqhac(&qhac);
     _Run.SETqext(&qext);
}
