//////////////////////////////////////////////////////////
//
// File which containes classes needed to construct
// the interface to the ALEPH BOS banks
// 
// Author : R. Cavanaugh
//
// C. Delaere : added event, run and vertex banks
// C. Delaere : added ROOT inheritence
//
//////////////////////////////////////////////////////////

 
#ifndef _ALPHACLASSES_H_
#define _ALPHACLASSES_H_

#include <vector>
#include "BankPatterns.h"
#include <TObject.h>
using namespace std;

/*----------------------------------------------------------------------------*/
class QLIN : public TObject
{
public:
     QLIN();
     ~QLIN(); 
     unsigned short    I;     
ClassDef(QLIN,1) // class QLIN
};
         
class QMTL : public TObject
{
public:
     QMTL();
     ~QMTL(); 
     unsigned short    I;     
ClassDef(QMTL,1) // class QMTL
};
         
class QMTS : public TObject
{
public:
     QMTS();
     ~QMTS(); 
     unsigned short    I;     
ClassDef(QMTS,1) // class QMTS
};
         
class FRFT : public TObject
{
public:
     FRFT();
     ~FRFT();    
     void Assign( FRFT_PATTERN* );
     float  IR;    
     float  TL;    
     float  P0;    
     float  D0;    
     float  Z0;    
     float  AL;    
     float  EM[20];
     float  C2;    
     unsigned short    DF;    
     unsigned short    NO;    
ClassDef(FRFT,1) // class FRFT
};
         
class FRTL : public TObject
{
public:
     FRTL();
     ~FRTL(); 
     void Assign( FRTL_PATTERN* );
     unsigned short   IV;     
     unsigned short   NV;     
     unsigned short   II;     
     unsigned short   NI;     
     unsigned short   NE;     
     unsigned short   IT;     
     unsigned short   NT;     
     unsigned short   NR;     
ClassDef(FRTL,1) // class FRTL
};
         
class TEXS : public TObject
{
public:
     TEXS();
     ~TEXS(); 
     void Assign( TEXS_PATTERN* );
     unsigned short   SI;     
     float TM;     
     float TL;     
     unsigned short   NS;     
     float AD;     
     unsigned short   TN;     
     unsigned short   SF;     
ClassDef(TEXS,1) // class TEXS
};
         
class HMAD : public TObject
{
public:
     HMAD();
     ~HMAD();  
     void Assign( HMAD_PATTERN* );
     unsigned short NplaFired;
     unsigned short NplaExp;  
     unsigned short NplaLast; 
     unsigned short MultHits; 
     short IGeomflag;
     float EnerDep;
     float ChiSquare;
     short NumbDeg;  
     int IExpbmap; 
     int ITruebmap;
     short IdenFlag; 
     unsigned short TrackNo;  
ClassDef(HMAD,1) // class HMAD
};
         
class MCAD : public TObject
{
public:
     MCAD();
     ~MCAD();  
     void Assign( MCAD_PATTERN* );
     unsigned short   NH[2];  
     float DH[2];  
     float DC[2];  
     float AM;     
     float AC;     
     unsigned short   TN;     
ClassDef(MCAD,1) // class MCAD
};
         
class PECO : public TObject
{
public:
     PECO();
     ~PECO();  
     void Assign( PECO_PATTERN* );
     float ER;     
     float E1;     
     float E2;     
     float TH;     
     float PH;     
     float EC;     
     unsigned short   KD;     
     unsigned short   CC;     
     unsigned short   RB;     
     unsigned short   PC;     
ClassDef(PECO,1) // class PECO
};
         
class EIDT : public TObject
{
public:
     EIDT();
     ~EIDT();  
     void Assign( EIDT_PATTERN* );
     unsigned short   IF;     
     float R1;     
     float R2;     
     float R3;     
     float R4;     
     float R5;     
     float R6;
     float R7;
     float EC;     
     unsigned short   IP;     
     float E1;     
     float E2;     
     float E3;     
     unsigned short   FR;     
     int   PE;     
ClassDef(EIDT,1) // class EIDT
};
         
class PHCO : public TObject
{
public:
     PHCO();
     ~PHCO();  
     void Assign( PHCO_PATTERN* );
     float ER;     
     float TH;     
     float PH;     
     float EC;     
     unsigned short   KD;     
     unsigned short   CC;     
     unsigned short   RB;     
     unsigned short   NF;     
     unsigned short   PC;     
ClassDef(PHCO,1) // class PHCO
};
         
class PEPT : public TObject
{
public:
     PEPT();
     ~PEPT();  
     void Assign( PEPT_PATTERN* );
     float T1;     
     float P1;     
     float T3;     
     float P3;     
ClassDef(PEPT,1) // class PEPT
};
         
class FRID : public TObject
{
public:
     FRID();
     ~FRID();  
     void Assign( FRID_PATTERN* );
     int   BP;     
     int   DZ;     
     int   BC;     
     int   DC;     
     float PE;     
     float PM;     
     float PI;     
     float PK;     
     float PP;     
     float NK;     
     int   QF;     
ClassDef(FRID,1) // class FRID
};
         
class EFOL : public TObject
{
public:
     EFOL();
     ~EFOL();  
     void Assign( EFOL_PATTERN* );
     void Assign( DENF_PATTERN* );
     void Assign( DENW_PATTERN* );
     float PX;     
     float PY;     
     float PZ;     
     float EW;     
     float WE;     
     unsigned short   TY;     
     short   LE;     
     short   LT;     
     short   LH;     
     short   LC;     
     short   LJ;      
ClassDef(EFOL,1) // class EFOL
};
         
class PCQA : public TObject
{
public:
     PCQA();
     ~PCQA();  
     void Assign( PCQA_PATTERN* );
     unsigned short NA;       
     float PX;     
     float PY;     
     float PZ;     
     float EN;     
ClassDef(PCQA,1) // class PCQA
};
         
class EGPC : public TObject
{
public:
     EGPC();
     ~EGPC();  
     void Assign( EGPC_PATTERN* );
     float PX;     
     float PY;     
     float PZ;     
     float R1;     
     float R2;     
     float F4;     
     float DM;     
     int   ST;     
     unsigned short   QU;     
     unsigned short   PE;     
ClassDef(EGPC,1) // class EGPC
};
         
class MUID : public TObject
{
public:
     MUID();
     ~MUID();  
     void Assign( MUID_PATTERN* );
     short IF;       
     float SR;     
     float DM;     
     unsigned short   ST;     
     unsigned short   TN;     
ClassDef(MUID,1) // class MUID
};
         
class PGPC : public TObject
{
public:
     PGPC();
     ~PGPC();  
     void Assign( PGPC_PATTERN*  );
     float EC;     
     float TC;     
     float PC;     
     float R1;     
     float R2;     
     float F4;     
     float DM;     
     float ST;     
     unsigned short   QU;     
     float Q1;     
     float Q2;     
     float M1;     
     float M2;     
     float MA;     
     float ER;     
     float TR;     
     float PR;     
     unsigned short   PE;     
ClassDef(PGPC,1) // class PGPC
};
         
class PGAC : public TObject
{
public:
     PGAC();
     ~PGAC();  
     void Assign( PGAC_PATTERN*  );
     float EC;     
     float TC;     
     float PC;     
     float R1;     
     float R2;     
     float F4;     
     float DM;     
     int   ST;     
     unsigned short   QU;     
     float Q1;     
     float Q2;     
     float M1;     
     float M2;     
     float MA;     
     float ER;     
     float TR;     
     float PR;     
     float EF;     
     float GC;     
     float ZS;     
     float PL;     
     float PH;     
     unsigned short   PN;     
     unsigned short   FA;     
     unsigned short   PE;     
ClassDef(PGAC,1) // class PGAC
};
         
class PDLT : public TObject
{
public:
     PDLT();
     ~PDLT();  
     void Assign( PDLT_PATTERN*  );
     unsigned short   PA;     
     unsigned short   JT;     
     float PI;     
     float PE;     
     unsigned short   VP;     
     unsigned short   FR;     
ClassDef(PDLT,1) // class PDLT
};
         
class PMLT : public TObject
{
public:
     PMLT();
     ~PMLT();  
     void Assign( PMLT_PATTERN*  );
     unsigned short   FL;       
     unsigned short   PO;       
     unsigned short   CH;       
     unsigned short   SP;       
     unsigned short   LE;       
     short   ME;       
     unsigned short   KT;       
     unsigned short   FR;       
ClassDef(PMLT,1) // class PMLT
};
         
class QDET : public TObject
{
public:
     QDET();
     ~QDET(); 
     void Assign( QDET_PATTERN* );
     FRFT* AF;     
     FRTL* AL;     
     unsigned short   NT;     
     TEXS* AT[4];  
     TEXS* LT;     
     EIDT* AE;     
     HMAD* AH;     
     MCAD* AM;     //!
     short   CF;     
     PECO* EC;     
     PHCO* HC;     
     PEPT* ET;     
     FRID* FI;     //!
     unsigned short   NF;     
//     vector<QVEC*> FL;// vector of pointers to ass. ch. tracks in QVEC
     unsigned short   NE;     
//     vector<QVEC*> EL;// vector of pointers to ass. ECAL objects in QVEC
     unsigned short   NH;     
//     vector<QVEC*> HL;// vector of pointers to ass. HCAL objects in QVEC
     short   LH;     
     EFOL* EF;     
     PCQA* PC;     
     EGPC* EG;     
     MUID* MU;     
     unsigned short   DX;     
     PGAC* PG;     
     PDLT* PD;     //!
     PMLT* PM;     //!
ClassDef(QDET,1) // class QDET
};
         
class QVEC : public TObject
{
public:
     QVEC();
     ~QVEC(); 
     void Assign( QVEC_PATTERN* );
//   Basic attributes
     float QX;
     float QY;
     float QZ;
     float QE;
     float QM;
     float QP;
     float QCH;
//   flags  
     unsigned short   TN;     
     int   SC;     
     int   KS;     
     int   CL;     
     unsigned short   PA;     
     QDET* QD;     
     QVEC* NP;     
     QVEC* SP;     
     unsigned short   OV;     
     unsigned short   EV;     
     unsigned short   ND;     
     vector<unsigned short> DL;
     unsigned short   NO;     
     vector<unsigned short> OL;
     unsigned short   NM;     
     vector<unsigned short> ML;
     int   BM[14]; 
     int   LK;     
     float DB;     
     float ZB;     
     float SD;     
     float SZ;     
     float CB;     
     float EM[10]; 
     float CF;     
     float EW;     
     float US[18]; 
ClassDef(QVEC,1) // class QVEC
};
         
class YV0V : public TObject
{
public:
     YV0V();
     ~YV0V(); 
      void Assign( YV0V_PATTERN* );
      unsigned short   K1;    
      unsigned short   K2;    
      float VX;    
      float VY;    
      float VZ;    
      float VM[6]; 
      float PX;    
      float PY;    
      float PZ;    
      float PM[6]; 
      float X1;    
      float X2;    
      float XM[3]; 
      float C2;    
      short   IC;    
      float P1[3];
      float P2[3];
      float EP[21];
      float DM;
      float S1;
      float S2;
ClassDef(YV0V,1) // class YV0V
};
         
class FKIN : public TObject
{
public:
     FKIN();
     ~FKIN(); 
      void Assign( FKIN_PATTERN* );
      float PX;    
      float PY;    
      float PZ;    
      float MA;    
      unsigned short   PA;    
      unsigned short   OV;    
      unsigned short   EV;    
      int   HC;    
ClassDef(FKIN,1) // class FKIN
};
         
class FVER : public TObject
{
public:
     FVER();
     ~FVER(); 
      void Assign( FVER_PATTERN* );
      float VX;    
      float VY;    
      float VZ;    
      float TO;    
      FKIN* IP;    
      vector<FKIN*> IS;    
      unsigned short   NS;    
      char  VN[4]; 
      char  VM[4]; 
ClassDef(FVER,1) // class FVER
};
         
class QVRT : public TObject
{
public:
     QVRT();
     ~QVRT(); 
      void Assign( QVRT_PATTERN* );
     float VX;     
     float VY;     
     float VZ;     
     unsigned short   VN;     
     unsigned short   TY;     
     unsigned short   IP;     
     unsigned short   ND;     
     vector<unsigned short> DL; 
     YV0V* AY;     
     FVER* AF;     
     float EM[6];  
     float CF;     
     float ET[7];  
     float US;     
     float PK;     
     float PT;     
     float PL;     
     int   HY;     
ClassDef(QVRT,1) // class QVRT
};
         
class ALPB : public TObject
{
public:
     ALPB();
     ~ALPB(); 
     void Assign( ALPB_PATTERN* );
     int FE;       
     int XP;       
     int XE;       
     int YP;       
     int YE;       
ClassDef(ALPB,1) // class ALPB
};
         
class ALRP : public TObject
{
public:
     ALRP();
     ~ALRP(); 
     void Assign( ALRP_PATTERN* );
      int PN;      
      int WE;      
      unsigned short ER;      
      float XS;    
      float YS;    
      float ZS;    
      float XR;    
      float YR;    
      float F1;    
      float M1;    
      float S1;    
      float M2;    
      float S2;    
ClassDef(ALRP,1) // class ALRP
};
         
class RNL2 : public TObject
{
public:
     RNL2();
     ~RNL2(); 
     void Assign( RNL2_PATTERN* );
      int DA;      
      int TI;      
      float EN;    
ClassDef(RNL2,1) // class RNL2
};
         
class RNF2 : public TObject
{
public:
     RNF2();
     ~RNF2(); 
     void Assign( RNF2_PATTERN* );
      int FN;      
      int DS;      
      int TS;      
      int DE;      
      int TE;      
      int FS;      
      int LS;      
ClassDef(RNF2,1) // class RNF2
};
         
class RNR2 : public TObject
{
public:
     RNR2();
     ~RNR2(); 
     void Assign( RNR2_PATTERN* );
      int RN;      
      float EN;    
ClassDef(RNR2,1) // class RNR2
};
         
class RLEP : public TObject
{
public:
     RLEP();
     ~RLEP(); 
     void Assign( RLEP_PATTERN* );
      int LE;      
      char LB[4];  
      int LD;      
      int LF;      
      int LP;      
ClassDef(RLEP,1) // class RLEP
};
         
class LFIL : public TObject
{
public:
     LFIL();
     ~LFIL(); 
     void Assign( LFIL_PATTERN* );
      int LF;      
      int FR;      
      int LR;      
      int NV;      
      float LE;    
      float BX;    
      float BY;    
      float BZ;    
      float EX;    
      float EY;    
      float EZ;    
      float OF;    
ClassDef(LFIL,1) // class LFIL
};
         
class EVEH : public TObject
{
public:
     EVEH();
     ~EVEH(); 
     void Assign( EVEH_PATTERN* );
      unsigned short EN;      
      int RN;      
      int RT;      
      int DA;      
      int TI;      
      int EV;      
      int M1;      
      int M2;      
      int M3;      
      int M4;      
      int TY;      
      int ES;      
      int TE;      
ClassDef(EVEH,1) // class EVEH
};
         
class KEVH : public TObject
{
public:
     KEVH();
     ~KEVH(); 
     void Assign( KEVH_PATTERN* );
      int RN;      
      unsigned short NT;      
      unsigned short NV;      
      int PI;      
      float WT;    
      int SR;      
      int TR;      
ClassDef(KEVH,1) // class KEVH
};
         
class REVH : public TObject
{
public:
     REVH();
     ~REVH(); 
     void Assign( REVH_PATTERN* );
      int DS;      
      int FE[2];   
      int NE[2];   
      int SB;      
      float TI;    
      int RB[2];   
      int EC;      
ClassDef(REVH,1) // class REVH
};
         
class LOLE : public TObject
{
public:
     LOLE();
     ~LOLE(); 
     void Assign( LOLE_PATTERN* );
      int FB[4];   
      int SP;      
      int TO;      
      int MA[4];   
      int HV;      
      int ER;      
ClassDef(LOLE,1) // class LOLE
};
         
class X1RG : public TObject
{
public:
     X1RG();
     ~X1RG(); 
     void Assign( X1RG_PATTERN* );
      char NA[4];  
      int CO[3];   
ClassDef(X1RG,1) // class X1RG
};
         
class BOMB : public TObject
{
public:
     BOMB();
     ~BOMB(); 
     void Assign( BOMB_PATTERN* );
      float XX;    
      float YY;    
      int EE;      
ClassDef(BOMB,1) // class BOMB
};
         
class RUNH : public TObject
{
public:
     RUNH();
     ~RUNH(); 
     void Assign( RUNH_PATTERN* );
      unsigned short EN;      
      int RN;      
      int RT;      
      int SD;      
      int ST;      
      char TT[8];  
      char RC[8];  
ClassDef(RUNH,1) // class RUNH
};
         
class ASIM : public TObject
{
public:
     ASIM();
     ~ASIM(); 
     void Assign( ASIM_PATTERN* );
      int YM;      
ClassDef(ASIM,1) // class ASIM
};
         
class ADBR : public TObject
{
public:
     ADBR();
     ~ADBR(); 
     void Assign( ADBR_PATTERN* );
      unsigned short PN;      
      int FR;      
      unsigned short BP;      
      unsigned short VD;      
      unsigned short IT;      
      unsigned short TP;      
      unsigned short EC;      
      unsigned short LC;      
      unsigned short SA;      
      unsigned short HC;      
      unsigned short MU;      
      unsigned short TR;      
      unsigned short GE;      
      unsigned short DB;      
      unsigned short SI;      
      unsigned short BE;      
ClassDef(ADBR,1) // class ADBR
};
         
class XTBN : public TObject
{
public:
     XTBN();
     ~XTBN(); 
     void Assign( XTBN_PATTERN* );
      int ID;      
      int VR[2];   
      unsigned short TN;      
      unsigned short TB;      
      char BM[8];  
      char BN[40]; 
      char AD[20]; 
      int L1;      
      int L2;      
ClassDef(XTBN,1) // class XTBN
};
         
class XTCN : public TObject
{
public:
     XTCN();
     ~XTCN(); 
     void Assign( XTCN_PATTERN* );
      int TT[2];   
      int GC;      
      int LL;      
      int BN;      
      int CL;      
      int TR[10];  
ClassDef(XTCN,1) // class XTCN
};
         
class XTOP : public TObject
{
public:
     XTOP();
     ~XTOP(); 
     void Assign( XTOP_PATTERN* );
      int ID;      
      int VR[2];   
      int NA[2];   
      int TR;      
      int GS;      
      int DS[8];   
      unsigned short TT;      
ClassDef(XTOP,1) // class XTOP
};
         
class LUPA : public TObject
{
public:
     LUPA();
     ~LUPA(); 
     void Assign( LUPA_PATTERN* );
      int GB;      
      int HV;      
      int T1;      
      int L2;      
      int TE;      
      int LO;      
      int AM;      
      int MD;      
      float EF;    
      float EC[2]; 
      float EW[2]; 
      float XC[2]; 
      float YC[2]; 
      float TC[2]; 
      float PC[2]; 
      float AX[2]; 
      float AY[2]; 
      float XX[2]; 
      float YY[2]; 
      float XY[2]; 
      float XA[2]; 
      float YA[2]; 
      float XD[2]; 
      float YD[2]; 
      unsigned short AD[2];   
      int IT[2];   
      float CT[2]; 
      float TT[2]; 
      float PT[2]; 
      float XT[2]; 
      float YT[2]; 
      float E1[2]; 
      float E2[2]; 
      float XL[2]; 
      float YL[2]; 
      unsigned short AI[2];   
      float ES[2]; 
      float XS[2]; 
      float YS[2]; 
      unsigned short AS[2];   
ClassDef(LUPA,1) // class LUPA
};
         
class SILH : public TObject
{
public:
     SILH();
     ~SILH(); 
     void Assign( SILH_PATTERN* );
      int GB;      
      int HV;      
      int T1;      
      int T2;      
      int TE;      
      int LO;      
      int S2;      
      int DW[3];   
      int SC[3];   
      int AM;      
      int WI;      
ClassDef(SILH,1) // class SILH
};
         
class XHVB : public TObject
{
public:
     XHVB();
     ~XHVB(); 
     void Assign( XHVB_PATTERN* );
      int RU;      
      int FE;      
      int LE;      
      unsigned short HV;      
      unsigned short DE;      
ClassDef(XHVB,1) // class XHVB
};
         
class XTEB : public TObject
{
public:
     XTEB();
     ~XTEB(); 
     void Assign( XTEB_PATTERN* );
      int T1;      
      int T2;      
      int L2;      
      int HT[12];  
      int HW[12];  
      int LW[12];  
      int EW[12];  
      int LT[4];   
      int TE[2];   
      int IT[4];   
      int TP[4];   
ClassDef(XTEB,1) // class XTEB
};
         
class XTRB : public TObject
{
public:
     XTRB();
     ~XTRB(); 
     void Assign( XTRB_PATTERN* );
      int RP[3];    
      int RN;       
ClassDef(XTRB,1) // class XTRB
};
         
class DTBP : public TObject
{
public:
     DTBP();
     ~DTBP(); 
     void Assign( DTBP_PATTERN* );
      int T1;      
      int T2;      
      int L2;      
ClassDef(DTBP,1) // class DTBP
};
         
class VHBV : public TObject
{
public:
     VHBV();
     ~VHBV(); 
     void Assign( VHBV_PATTERN* );
      unsigned short BN;      
      int FR;      
      int LR;      
ClassDef(VHBV,1) // class VHBV
};
         
class VHPV : public TObject
{
public:
     VHPV();
     ~VHPV(); 
     void Assign( VHPV_PATTERN* );
      int FR;      
      int LR;      
ClassDef(VHPV,1) // class VHPV
};
         
class EAUX : public TObject
{
public:
     EAUX();
     ~EAUX(); 
     void Assign( EAUX_PATTERN* );
      int TR;      
      int CA;      
      unsigned short HV;      
      float HE;    
      float HK;    
      float E2;    
ClassDef(EAUX,1) // class EAUX
};
         
class SIX2 : public TObject
{
public:
     SIX2();
     ~SIX2(); 
     void Assign( SIX2_PATTERN* );
      int TW;      
ClassDef(SIX2,1) // class SIX2
};
         
class X1TV : public TObject
{
public:
     X1TV();
     ~X1TV(); 
     void Assign( X1TV_PATTERN* );
      char TT[4];  
      int TV[4];   
ClassDef(X1TV,1) // class X1TV
};
         
class KWGT : public TObject
{
public:
     KWGT();
     ~KWGT(); 

     void Assign( KWGT_PATTERN* );
      int WN;      
      float WV;    
ClassDef(KWGT,1) // class KWGT
};
         
class X1IP : public TObject
{
public:
     X1IP();
     ~X1IP(); 
     void Assign( X1IP_PATTERN* );
      char IT[4];  
      int CO[36];  
ClassDef(X1IP,1) // class X1IP
};
         
class SIXA : public TObject
{
public:
     SIXA();
     ~SIXA(); 
     void Assign( SIXA_PATTERN* );
      int AO;      
      int AE;      
ClassDef(SIXA,1) // class SIXA
};
         
class SITC : public TObject
{
public:
     SITC();
     ~SITC(); 
     void Assign( SITC_PATTERN* );
      int TT;      
      int DO;      
      int DE;      
ClassDef(SITC,1) // class SITC
};
         
class SRCO : public TObject
{
public:
     SRCO();
     ~SRCO(); 
     void Assign( SRCO_PATTERN* );
      char NA[4];  
      int VA;      
ClassDef(SRCO,1) // class SRCO
};
         
class X1TH : public TObject
{
public:
     X1TH();
     ~X1TH(); 
     void Assign( X1TH_PATTERN* );
      int ID;      
      int VR[2];   
      char TT[4];  
      int TV[4];   
ClassDef(X1TH,1) // class X1TH
};
         
class X1AD : public TObject
{
public:
     X1AD();
     ~X1AD(); 
     void Assign( X1AD_PATTERN* );
      char IT[4];  
      int AV[36];  
ClassDef(X1AD,1) // class X1AD
};
         
class QEXT : public TObject
{
public:
     QEXT();
     ~QEXT(); 
     // ALPHA flags
     // only RLEP is now used for first QELEP estimation
     // other banks require more work to determine the
     // interesting row in bank... 
     // it will be needed for a best energy calculation
     // and a beam spot determination.
     //ALPB* PB;     // offset for corresponding bank ALPB
     //ALRP* RP;     // offset for corresponding bank ALRP
     //RNL2* L2;     // offset for corresponding bank RNL2
     //RNF2* F2;     // offset for corresponding bank RNF2
     //RNR2* R2;     // offset for corresponding bank RNR2
     RLEP* LP;     
     //LFIL* FL;     // offset for corresponding bank LFIL
ClassDef(QEXT,1) // class QEXT
};
         
class QHAC : public TObject
{
public:
     QHAC();
     ~QHAC(); 
     EVEH* EH;
     RUNH* RH;
     ASIM* AS;
     KEVH* KE;
     REVH* RE;
     vector<LOLE*> LO; //!
     vector<X1RG*> X1; //!
     ADBR* AD;
     BOMB* BO;
     vector<XTBN*> BN; //!
     XTCN* CN; //!
     XTOP* OP; //!
     LUPA* LP; //!
     SILH* SI; //!
     vector<XHVB*> HV; //!
     XTEB* EB; //!
     XTRB* RB; //!
     DTBP* BP; //!
     vector<VHPV*> PV; //!
     vector<VHBV*> BV; //!
     EAUX* EX;
     SIX2* X2; //!
     vector<X1TV*> TV; //!
     vector<KWGT*> KW; 
     vector<X1IP*> IP; //!
     vector<SIXA*> XA; //!
     SITC* TC; //!
     vector<SRCO*> CO; //!
     vector<X1TH*> TH; //!
     vector<X1AD*> XD; //!
ClassDef(QHAC,1) // class QHAC
};
#endif

