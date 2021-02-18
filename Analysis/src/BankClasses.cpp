/*-----------------------------------------------------------------------------*/
/* Define methods for the Event class and create objects from the FORTRAN      */
/* BOS memory.                                                                 */
/* Author: R. Cavanaugh                                                        */
/*-----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string> 
#include <stdlib.h>

#include <vector>
#include <TObject.h>

#include "BankClasses.h"
#include "BankPatterns.h"                                                  

extern ofstream fout;
/*-----------------------------------------------------------------------------*/
void YV0V::Assign( YV0V_PATTERN *Bank )
{
     K1  =  Bank -> K1;
     K2  =  Bank -> K2;
     VX  =  Bank -> VX;
     VY  =  Bank -> VY;
     VZ  =  Bank -> VZ;
     for(int i = 0; i < 6; i++)
     {
     	VM[i]  =  Bank -> VM[i];
        PM[i]  =  Bank -> PM[i];
     }
     PX  =  Bank -> PX;
     PY  =  Bank -> PY;
     PZ  =  Bank -> PZ;
     X1  =  Bank -> X1;
     X2  =  Bank -> X2;
     for(int i = 0; i < 3; i++)
     {
        XM[i]  =  Bank -> XM[i];
        P1[i]  =  Bank -> P1[i];
	P2[i]  =  Bank -> P2[i];
     }
     for(int i = 0; i < 3; i++)
	EP[i]  =  Bank -> EP[i];
     DM  =  Bank -> DM;
     S1  =  Bank -> S1;
     S2  =  Bank -> S2;
}
/*-----------------------------------------------------------------------------*/
void FKIN::Assign( FKIN_PATTERN *Bank )
{
     PX  =  Bank -> PX;
     PY  =  Bank -> PY;
     PZ  =  Bank -> PZ;
     MA  =  Bank -> MA;
     PA  =  Bank -> PA;
     OV  =  Bank -> OV;
     EV  =  Bank -> EV;
     HC  =  Bank -> HC;
}
/*-----------------------------------------------------------------------------*/
void FVER::Assign( FVER_PATTERN *Bank )
{
     VX  =  Bank -> VX;
     VY  =  Bank -> VY;
     VZ  =  Bank -> VZ;
     TO  =  Bank -> TO;
     NS  =  Bank -> NS;
     for(int i = 0; i < 4; i++)
     {
        VN[i]  =  Bank -> VN[i];
        VM[i]  =  Bank -> VM[i];
     }
}
/*-----------------------------------------------------------------------------*/
void QVRT::Assign( QVRT_PATTERN *Bank )
{
     VX  =  Bank -> VX;
     VY  =  Bank -> VY;
     VZ  =  Bank -> VZ;
     VN  =  Bank -> VN;
     TY  =  Bank -> TY;
     IP  =  Bank -> IP;
     ND  =  Bank -> ND;
     CF  =  Bank -> CF;
     for(int i = 0; i < 6; i++)
        EM[i]  =  Bank -> EM[i];
     for(int i = 0; i < 7; i++)
        ET[i]  =  Bank -> ET[i];
     if(Bank -> TY == 5)
     {
     	US  = Bank -> US;
     	PK  = Bank -> PK;
     	PT  = Bank -> PT;
     	PL  = Bank -> PL;
     	HY  = Bank -> HY;
     }
     else
     {
        US  = -1;
        PK  = -1;
        PT  = -1;
        PL  = -1;
        HY  = -1;
     }
}
/*-----------------------------------------------------------------------------*/
void QVEC::Assign( QVEC_PATTERN *Bank )
{
     QX  =  Bank -> QX;
     QY  =  Bank -> QY;
     QZ  =  Bank -> QZ;
     QE  =  Bank -> QE;
     QM  =  Bank -> QM;
     QP  =  Bank -> QP;
     QCH =  Bank -> QCH;
     TN  =  Bank -> TN;
     SC  =  Bank -> SC;
     KS  =  Bank -> KS;
     CL  =  Bank -> CL;
     PA  =  Bank -> PA;
     OV  =  Bank -> OV;
     EV  =  Bank -> EV;
     ND  =  Bank -> ND;
     NO  =  Bank -> NO;
     NM  =  Bank -> NM;     
     for(int i = 0; i < 14; i++)
          BM[i]  =  Bank -> BM[i];
     LK  =  Bank -> LK;
     DB  =  Bank -> DB;
     ZB  =  Bank -> ZB;
     SD  =  Bank -> SD;
     SZ  =  Bank -> SZ;
     CB  =  Bank -> CB;
     for(int i = 0; i < 10; i++)
          EM[i]  =  Bank -> EM[i];
     CF  =  Bank -> CF;
     EW  =  Bank -> EW;
     for(int i = 0; i < 18; i++)
          US[i]  =  Bank -> US[i];
}
/*-----------------------------------------------------------------------------*/
void QDET::Assign( QDET_PATTERN *Bank ) 
{
     NT  =  Bank -> NT; 
     CF  =  Bank -> CF; 
     NF  =  Bank -> NF; 
     NE  =  Bank -> NE; 
     NH  =  Bank -> NH; 
     LH  =  Bank -> LH; 
     DX  =  Bank -> DX;
}
/*-----------------------------------------------------------------------------*/
void FRFT::Assign( FRFT_PATTERN *Bank ) 
{
     IR  =  Bank -> IR; 
     TL  =  Bank -> TL; 
     P0  =  Bank -> P0; 
     D0  =  Bank -> D0; 
     Z0  =  Bank -> Z0; 
     AL  =  Bank -> AL;
     for( int i = 0; i < 20; i++ ) 
          EM[i]  =  Bank -> EM[i]; 
     C2  =  Bank -> C2; 
     DF  =  Bank -> DF; 
     NO  =  Bank -> NO; 
}
/*-----------------------------------------------------------------------------*/
void FRTL::Assign( FRTL_PATTERN *Bank )
{
     IV  =  Bank -> IV; 
     NV  =  Bank -> NV; 
     II  =  Bank -> II; 
     NI  =  Bank -> NI; 
     NE  =  Bank -> NE; 
     IT  =  Bank -> IT; 
     NT  =  Bank -> NT; 
     NR  =  Bank -> NR; 
}
/*-----------------------------------------------------------------------------*/
void TEXS::Assign( TEXS_PATTERN *Bank )
{
     SI  =  Bank -> SI; 
     TM  =  Bank -> TM; 
     TL  =  Bank -> TL; 
     NS  =  Bank -> NS; 
     AD  =  Bank -> AD; 
     TN  =  Bank -> TN; 
     SF  =  Bank -> SF; 
}
/*-----------------------------------------------------------------------------*/
void HMAD::Assign( HMAD_PATTERN *Bank )
{
     NplaFired   =  Bank -> NplaFired; 
     NplaExp     =  Bank -> NplaExp; 
     NplaLast    =  Bank -> NplaLast; 
     MultHits    =  Bank -> MultHits; 
     IGeomflag   =  Bank -> IGeomflag; 
     EnerDep     =  Bank -> EnerDep; 
     ChiSquare   =  Bank -> ChiSquare; 
     NumbDeg     =  Bank -> NumbDeg; 
     IExpbmap    =  Bank -> IExpbmap;
     ITruebmap   =  Bank -> ITruebmap;
     IdenFlag    =  Bank -> IdenFlag; 
     TrackNo     =  Bank -> TrackNo; 
     NumbDeg     =  Bank -> NumbDeg; 
}
/*-----------------------------------------------------------------------------*/
void MCAD::Assign( MCAD_PATTERN *Bank )
{
     for( int i = 0; i < 2; i++ ) 
          NH[i]  =  Bank -> NH[i]; 
     for( int i = 0; i < 2; i++ ) 
          DH[i]  =  Bank -> DH[i]; 
     for( int i = 0; i < 2; i++ ) 
          DC[i]  =  Bank -> DC[i]; 
     AM  =  Bank -> AM; 
     AC  =  Bank -> AC; 
     TN  =  Bank -> TN; 
}
/*-----------------------------------------------------------------------------*/
void PECO::Assign( PECO_PATTERN *Bank )
{
     ER  =  Bank -> ER; 
     E1  =  Bank -> E1; 
     E2  =  Bank -> E2; 
     TH  =  Bank -> TH; 
     PH  =  Bank -> PH; 
     EC  =  Bank -> EC; 
     KD  =  Bank -> KD; 
     CC  =  Bank -> CC; 
     RB  =  Bank -> RB; 
     PC  =  Bank -> PC; 
}
/*-----------------------------------------------------------------------------*/
void EIDT::Assign( EIDT_PATTERN *Bank )
{
     IF  =  Bank -> IF; 
     R1  =  Bank -> R1; 
     R2  =  Bank -> R2; 
     R3  =  Bank -> R3; 
     R4  =  Bank -> R4; 
     R5  =  Bank -> R5; 
     R6  =  Bank -> R6; 
     R7  =  Bank -> R7; 
     EC  =  Bank -> EC; 
     IP  =  Bank -> IP; 
     E1  =  Bank -> E1; 
     E2  =  Bank -> E2; 
     E3  =  Bank -> E3;
     FR  =  Bank -> FR;
     PE  =  Bank -> PE; 
}
/*-----------------------------------------------------------------------------*/
void PHCO::Assign( PHCO_PATTERN *Bank )
{
     ER  =  Bank -> ER; 
     TH  =  Bank -> TH; 
     PH  =  Bank -> PH; 
     EC  =  Bank -> EC; 
     KD  =  Bank -> KD; 
     CC  =  Bank -> CC; 
     RB  =  Bank -> RB; 
     NF  =  Bank -> NF; 
     PC  =  Bank -> PC; 
}
/*-----------------------------------------------------------------------------*/
void PEPT::Assign( PEPT_PATTERN *Bank )
{
     T1  =  Bank -> T1; 
     P1  =  Bank -> P1; 
     T3  =  Bank -> T3; 
     P3  =  Bank -> P3; 
}
/*-----------------------------------------------------------------------------*/
void FRID::Assign( FRID_PATTERN *Bank )
{
     BP  =  Bank -> BP; 
     DZ  =  Bank -> DZ; 
     BC  =  Bank -> BC; 
     DC  =  Bank -> DC; 
     PE  =  Bank -> PE; 
     PM  =  Bank -> PM; 
     PI  =  Bank -> PI; 
     PK  =  Bank -> PK; 
     PP  =  Bank -> PP; 
     NK  =  Bank -> NK; 
     QF  =  Bank -> QF; 
}
/*-----------------------------------------------------------------------------*/
void EFOL::Assign( EFOL_PATTERN *Bank )
{
     PX  =  Bank -> PX; 
     PY  =  Bank -> PY; 
     PZ  =  Bank -> PZ; 
     EW  =  Bank -> EW; 
     WE  =  Bank -> WE; 
     TY  =  Bank -> TY; 
     LE  =  Bank -> LE; 
     LT  =  Bank -> LT; 
     LH  =  Bank -> LH; 
     LC  =  Bank -> LC; 
     LJ  =  Bank -> LJ; 
}
/*-----------------------------------------------------------------------------*/
void EFOL::Assign( DENF_PATTERN *Bank )
{
     PX  =  Bank -> PX; 
     PY  =  Bank -> PY; 
     PZ  =  Bank -> PZ; 
     EW  =  Bank -> EW; 
     WE  =  Bank -> WE; 
     TY  =  Bank -> TY; 
     LE  =  -1; 
     LT  =  Bank -> DT; 
     LH  =  -1; 
     LC  =  -1; 
     LJ  =  Bank -> DJ; 
}
/*-----------------------------------------------------------------------------*/
void EFOL::Assign( DENW_PATTERN *Bank )
{
     LC  =  Bank -> LC; 
}
/*-----------------------------------------------------------------------------*/
void PCQA::Assign( PCQA_PATTERN *Bank )
{
     NA  =  Bank -> NA; 
     PX  =  Bank -> PX; 
     PY  =  Bank -> PY; 
     PZ  =  Bank -> PZ; 
     EN  =  Bank -> EN; 
}
/*-----------------------------------------------------------------------------*/
void EGPC::Assign( EGPC_PATTERN *Bank )
{
     PX  =  Bank -> PX; 
     PY  =  Bank -> PY; 
     PZ  =  Bank -> PZ; 
     R1  =  Bank -> R1; 
     R2  =  Bank -> R2; 
     F4  =  Bank -> F4; 
     DM  =  Bank -> DM; 
     ST  =  Bank -> ST; 
     QU  =  Bank -> QU; 
}
/*-----------------------------------------------------------------------------*/
void MUID::Assign( MUID_PATTERN *Bank )
{
     IF  =  Bank -> IF; 
     SR  =  Bank -> SR; 
     DM  =  Bank -> DM; 
     ST  =  Bank -> ST; 
     TN  =  Bank -> TN; 
}
/*-----------------------------------------------------------------------------*/
void PGPC::Assign( PGPC_PATTERN *Bank )
{
     EC  =  Bank -> EC; 
     TC  =  Bank -> TC; 
     PC  =  Bank -> PC; 
     R1  =  Bank -> R1; 
     R2  =  Bank -> R2; 
     F4  =  Bank -> F4; 
     DM  =  Bank -> DM; 
     ST  =  Bank -> ST; 
     QU  =  Bank -> QU; 
     Q1  =  Bank -> Q1; 
     Q2  =  Bank -> Q2; 
     M1  =  Bank -> M1; 
     M2  =  Bank -> M2; 
     MA  =  Bank -> MA; 
     ER  =  Bank -> ER; 
     TR  =  Bank -> TR; 
     PR  =  Bank -> PR; 
}
/*-----------------------------------------------------------------------------*/
void PGAC::Assign( PGAC_PATTERN *Bank )
{
     EC  =  Bank -> EC; 
     TC  =  Bank -> TC; 
     PC  =  Bank -> PC; 
     R1  =  Bank -> R1; 
     R2  =  Bank -> R2; 
     F4  =  Bank -> F4; 
     DM  =  Bank -> DM; 
     ST  =  Bank -> ST; 
     QU  =  Bank -> QU; 
     Q1  =  Bank -> Q1; 
     Q2  =  Bank -> Q2; 
     M1  =  Bank -> M1; 
     M2  =  Bank -> M2; 
     MA  =  Bank -> MA; 
     ER  =  Bank -> ER; 
     TR  =  Bank -> TR; 
     PR  =  Bank -> PR; 
     EF  =  Bank -> EF; 
     GC  =  Bank -> GC; 
     ZS  =  Bank -> ZS; 
     PL  =  Bank -> PL; 
     PN  =  Bank -> PN;
     FA  =  Bank -> FA; 
     PE  =  Bank -> PE; 
}
/*-----------------------------------------------------------------------------*/
void PDLT::Assign( PDLT_PATTERN *Bank )
{
     PA  =  Bank -> PA; 
     JT  =  Bank -> JT; 
     PI  =  Bank -> PI; 
     PE  =  Bank -> PE; 
     VP  =  Bank -> VP; 
     FR  =  Bank -> FR; 
}
/*-----------------------------------------------------------------------------*/
void PMLT::Assign( PMLT_PATTERN *Bank )
{
     FL  =  Bank -> FL; 
     PO  =  Bank -> PO; 
     CH  =  Bank -> CH; 
     SP  =  Bank -> SP; 
     LE  =  Bank -> LE; 
     ME  =  Bank -> ME; 
     KT  =  Bank -> KT; 
}
/*-----------------------------------------------------------------------------*/
void ALPB::Assign( ALPB_PATTERN *Bank )
{
     FE  =  Bank -> FE; 
     XP  =  Bank -> XP; 
     XE  =  Bank -> XE; 
     YP  =  Bank -> YP; 
     YE  =  Bank -> YE; 
}
/*-----------------------------------------------------------------------------*/
void ALRP::Assign( ALRP_PATTERN *Bank )
{
     PN  =  Bank -> PN; 
     WE  =  Bank -> WE; 
     ER  =  Bank -> ER; 
     XS  =  Bank -> XS; 
     YS  =  Bank -> YS; 
     ZS  =  Bank -> ZS; 
     XR  =  Bank -> XR; 
     YR  =  Bank -> YR; 
     F1  =  Bank -> F1; 
     M1  =  Bank -> M1; 
     S1  =  Bank -> S1; 
     M2  =  Bank -> M2; 
     S2  =  Bank -> S2; 
}
/*-----------------------------------------------------------------------------*/
void RNL2::Assign( RNL2_PATTERN *Bank )
{
     DA  =  Bank -> DA; 
     TI  =  Bank -> TI; 
     EN  =  Bank -> EN;  
}
/*-----------------------------------------------------------------------------*/
void RNF2::Assign( RNF2_PATTERN *Bank )
{
     FN  =  Bank -> FN; 
     DS  =  Bank -> DS; 
     TS  =  Bank -> TS; 
     DE  =  Bank -> DE; 
     TE  =  Bank -> TE; 
     FS  =  Bank -> FS; 
     LS  =  Bank -> LS; 
}
/*-----------------------------------------------------------------------------*/
void RNR2::Assign( RNR2_PATTERN *Bank )
{
     RN  =  Bank -> RN; 
     EN  =  Bank -> EN; 
}
/*-----------------------------------------------------------------------------*/
void RLEP::Assign( RLEP_PATTERN *Bank )
{
     LE  =  Bank -> LE; 
     for(int i=0;i<4;i++)
       LB[i]  =  Bank -> LB[i]; 
     LD  =  Bank -> LD; 
     LF  =  Bank -> LF; 
     LP  =  Bank -> LP; 
}
/*-----------------------------------------------------------------------------*/
void LFIL::Assign( LFIL_PATTERN *Bank )
{
     LF  =  Bank -> LF; 
     FR  =  Bank -> FR; 
     LR  =  Bank -> LR; 
     NV  =  Bank -> NV; 
     LE  =  Bank -> LE; 
     BX  =  Bank -> BX; 
     BY  =  Bank -> BY; 
     BZ  =  Bank -> BZ; 
     EX  =  Bank -> EX; 
     EY  =  Bank -> EY; 
     EZ  =  Bank -> EZ; 
     OF  =  Bank -> OF; 
}
/*-----------------------------------------------------------------------------*/
void EVEH::Assign( EVEH_PATTERN *Bank )
{
     EN  =  Bank -> EN; 
     RN  =  Bank -> RN; 
     RT  =  Bank -> RT; 
     DA  =  Bank -> DA; 
     TI  =  Bank -> TI; 
     EV  =  Bank -> EV; 
     M1  =  Bank -> M1; 
     M2  =  Bank -> M2; 
     M3  =  Bank -> M3; 
     M4  =  Bank -> M4; 
     TY  =  Bank -> TY; 
     ES  =  Bank -> ES; 
     TE  =  Bank -> TE; 
}
/*-----------------------------------------------------------------------------*/
void KEVH::Assign( KEVH_PATTERN *Bank )
{
     RN  =  Bank -> RN; 
     NT  =  Bank -> NT; 
     NV  =  Bank -> NV; 
     PI  =  Bank -> PI; 
     WT  =  Bank -> WT; 
     SR  =  Bank -> SR; 
     TR  =  Bank -> TR; 
}
/*-----------------------------------------------------------------------------*/
void KWGT::Assign( KWGT_PATTERN *Bank )
{
     WN  =  Bank -> WN;
     WV  =  Bank -> WV;
}
/*-----------------------------------------------------------------------------*/
void REVH::Assign( REVH_PATTERN *Bank )
{
     DS  =  Bank -> DS; 
     SB  =  Bank -> SB; 
     TI  =  Bank -> TI; 
     EC  =  Bank -> EC; 
     for (int i=0;i<2;i++)
     {
	     FE[i]  =  Bank -> FE[i];
	     NE[i]  =  Bank -> NE[i];
	     RB[i]  =  Bank -> RB[i];
     }
}
/*-----------------------------------------------------------------------------*/
void LOLE::Assign( LOLE_PATTERN *Bank )
{
     SP  =  Bank -> SP; 
     TO  =  Bank -> TO; 
     HV  =  Bank -> HV; 
     ER  =  Bank -> ER;
     for (int i=0;i<4;i++) 
     {
	     FB[i]  =  Bank -> FB[i];
	     MA[i]  =  Bank -> MA[i];
     }
}
/*-----------------------------------------------------------------------------*/
void X1RG::Assign( X1RG_PATTERN *Bank )
{
     for (int i=0;i<4;i++)
        NA[i]  =  Bank -> NA[i]; 
     for (int i=0;i<3;i++)
        CO[i]  =  Bank -> CO[i]; 
}
/*-----------------------------------------------------------------------------*/
void BOMB::Assign( BOMB_PATTERN *Bank )
{
     XX  =  Bank -> XX; 
     YY  =  Bank -> YY; 
     EE  =  Bank -> EE; 
}
/*-----------------------------------------------------------------------------*/
void RUNH::Assign( RUNH_PATTERN *Bank )
{
     EN  =  Bank -> EN; 
     RN  =  Bank -> RN; 
     RT  =  Bank -> RT; 
     SD  =  Bank -> SD; 
     ST  =  Bank -> ST;
     for (int i=0;i<8;i++)
     { 
     	TT[i]  =  Bank -> TT[i]; 
     	RC[i]  =  Bank -> RC[i];
     }	
}
/*-----------------------------------------------------------------------------*/
void ASIM::Assign( ASIM_PATTERN *Bank )
{
     YM  =  Bank -> YM; 
}
/*-----------------------------------------------------------------------------*/
void ADBR::Assign( ADBR_PATTERN *Bank )
{
     PN  =  Bank -> PN; 
     FR  =  Bank -> FR; 
     BP  =  Bank -> BP; 
     VD  =  Bank -> VD; 
     IT  =  Bank -> IT; 
     TP  =  Bank -> TP; 
     EC  =  Bank -> EC; 
     LC  =  Bank -> LC; 
     SA  =  Bank -> SA; 
     HC  =  Bank -> HC; 
     MU  =  Bank -> MU; 
     TR  =  Bank -> TR; 
     GE  =  Bank -> GE; 
     DB  =  Bank -> DB; 
     SI  =  Bank -> SI; 
     BE  =  Bank -> BE; 
}
/*-----------------------------------------------------------------------------*/
void XTBN::Assign( XTBN_PATTERN *Bank )
{
     ID  =  Bank -> ID; 
     TN  =  Bank -> TN; 
     TB  =  Bank -> TB; 
     L1  =  Bank -> L1; 
     L2  =  Bank -> L2;
     for (int i=0;i<2;i++)
	     VR[i]  =  Bank -> VR[i];
     for (int i=0;i<8;i++)
	     BM[i]  =  Bank -> BM[i];
     for (int i=0;i<40;i++)
	     BN[i]  =  Bank -> BN[i];
     for (int i=0;i<20;i++)
	     AD[i]  =  Bank -> AD[i];
}
/*-----------------------------------------------------------------------------*/
void XTCN::Assign( XTCN_PATTERN *Bank )
{
     for (int i=0;i<2;i++)
       TT[i]  =  Bank -> TT[i]; 
     GC  =  Bank -> GC; 
     LL  =  Bank -> LL; 
     BN  =  Bank -> BN; 
     CL  =  Bank -> CL; 
     for (int i=0;i<10;i++)
       TR[i]  =  Bank -> TR[i]; 
}
/*-----------------------------------------------------------------------------*/
void XTOP::Assign( XTOP_PATTERN *Bank )
{
     ID  =  Bank -> ID;
     for (int i=0;i<2;i++)
     {
       VR[i]  =  Bank -> VR[i]; 
       NA[i]  =  Bank -> NA[i]; 
     }
     TR  =  Bank -> TR; 
     GS  =  Bank -> GS; 
     for (int i=0;i<8;i++)
       DS[i]  =  Bank -> DS[i]; 
     TT  =  Bank -> TT; 
}
/*-----------------------------------------------------------------------------*/
void LUPA::Assign( LUPA_PATTERN *Bank )
{
     GB  =  Bank -> GB; 
     HV  =  Bank -> HV; 
     T1  =  Bank -> T1; 
     L2  =  Bank -> L2; 
     TE  =  Bank -> TE; 
     LO  =  Bank -> LO; 
     AM  =  Bank -> AM; 
     MD  =  Bank -> MD; 
     EF  =  Bank -> EF;
     for (int i=0;i<2;i++) 
     {
     EC[i]  =  Bank -> EC[i]; 
     EW[i]  =  Bank -> EW[i]; 
     XC[i]  =  Bank -> XC[i]; 
     YC[i]  =  Bank -> YC[i]; 
     TC[i]  =  Bank -> TC[i]; 
     PC[i]  =  Bank -> PC[i]; 
     AX[i]  =  Bank -> AX[i]; 
     AY[i]  =  Bank -> AY[i]; 
     XX[i]  =  Bank -> XX[i]; 
     YY[i]  =  Bank -> YY[i]; 
     XY[i]  =  Bank -> XY[i]; 
     XA[i]  =  Bank -> XA[i]; 
     YA[i]  =  Bank -> YA[i]; 
     XD[i]  =  Bank -> XD[i]; 
     YD[i]  =  Bank -> YD[i]; 
     AD[i]  =  Bank -> AD[i]; 
     IT[i]  =  Bank -> IT[i]; 
     CT[i]  =  Bank -> CT[i]; 
     TT[i]  =  Bank -> TT[i]; 
     PT[i]  =  Bank -> PT[i]; 
     XT[i]  =  Bank -> XT[i]; 
     YT[i]  =  Bank -> YT[i]; 
     E1[i]  =  Bank -> E1[i]; 
     E2[i]  =  Bank -> E2[i]; 
     XL[i]  =  Bank -> XL[i]; 
     YL[i]  =  Bank -> YL[i]; 
     AI[i]  =  Bank -> AI[i]; 
     ES[i]  =  Bank -> ES[i]; 
     XS[i]  =  Bank -> XS[i]; 
     YS[i]  =  Bank -> YS[i]; 
     AS[i]  =  Bank -> AS[i]; 
     }
}
/*-----------------------------------------------------------------------------*/
void SILH::Assign( SILH_PATTERN *Bank )
{
     GB  =  Bank -> GB; 
     HV  =  Bank -> HV; 
     T1  =  Bank -> T1; 
     T2  =  Bank -> T2; 
     TE  =  Bank -> TE; 
     LO  =  Bank -> LO; 
     S2  =  Bank -> S2; 
     for (int i=0;i<3;i++)
     {
     DW[i]  =  Bank -> DW[i]; 
     SC[i]  =  Bank -> SC[i]; 
     }
     AM  =  Bank -> AM; 
     WI  =  Bank -> WI; 
}
/*-----------------------------------------------------------------------------*/
void XHVB::Assign( XHVB_PATTERN *Bank )
{
     RU  =  Bank -> RU; 
     FE  =  Bank -> FE; 
     LE  =  Bank -> LE; 
     HV  =  Bank -> HV; 
     DE  =  Bank -> DE; 
}
/*-----------------------------------------------------------------------------*/
void XTEB::Assign( XTEB_PATTERN *Bank )
{
     T1  =  Bank -> T1; 
     T2  =  Bank -> T2; 
     L2  =  Bank -> L2; 
     for (int i=0;i<12;i++)
     {
       HT[i]  =  Bank -> HT[i]; 
       HW[i]  =  Bank -> HW[i]; 
       LW[i]  =  Bank -> LW[i]; 
       EW[i]  =  Bank -> EW[i]; 
     }
     for (int i=0;i<4;i++)
       LT[i]  =  Bank -> LT[i]; 
     for (int i=0;i<2;i++)
       TE[i]  =  Bank -> TE[i];
     for (int i=0;i<4;i++)
       IT[i]  =  Bank -> IT[i]; 
     for (int i=0;i<4;i++)
       TP[i]  =  Bank -> TP[i]; 
}
/*-----------------------------------------------------------------------------*/
void XTRB::Assign( XTRB_PATTERN *Bank )
{
     for (int i=0;i<3;i++)
       RP[i]  =  Bank -> RP[i]; 
     RN  =  Bank -> RN; 
}
/*-----------------------------------------------------------------------------*/
void DTBP::Assign( DTBP_PATTERN *Bank )
{
     T1  =  Bank -> T1; 
     T2  =  Bank -> T2; 
     L2  =  Bank -> L2; 
}
/*-----------------------------------------------------------------------------*/
void VHBV::Assign( VHBV_PATTERN *Bank )
{
     BN  =  Bank -> BN; 
     FR  =  Bank -> FR; 
     LR  =  Bank -> LR; 
}
/*-----------------------------------------------------------------------------*/
void VHPV::Assign( VHPV_PATTERN *Bank )
{
     FR  =  Bank -> FR; 
     LR  =  Bank -> LR; 
}
/*-----------------------------------------------------------------------------*/
void EAUX::Assign( EAUX_PATTERN *Bank )
{
     TR  =  Bank -> TR; 
     CA  =  Bank -> CA; 
     HV  =  Bank -> HV; 
     HE  =  Bank -> HE; 
     HK  =  Bank -> HK; 
     E2  =  Bank -> E2; 
}
/*-----------------------------------------------------------------------------*/
void SIX2::Assign( SIX2_PATTERN *Bank )
{
     TW  =  Bank -> TW; 
}
/*-----------------------------------------------------------------------------*/
void X1TV::Assign( X1TV_PATTERN *Bank )
{
     for (int i=0;i<4;i++)
     {
       TT[i]  =  Bank -> TT[i]; 
       TV[i]  =  Bank -> TV[i]; 
     }
}
/*-----------------------------------------------------------------------------*/
void X1IP::Assign( X1IP_PATTERN *Bank )
{
     for (int i=0;i<4;i++)
       IT[i]  =  Bank -> IT[i];
     for (int i=0;i<36;i++) 
       CO[i]  =  Bank -> CO[i];
}
/*-----------------------------------------------------------------------------*/
void SIXA::Assign( SIXA_PATTERN *Bank )
{
     AO  =  Bank -> AO; 
     AE  =  Bank -> AE; 
}
/*-----------------------------------------------------------------------------*/
void SITC::Assign( SITC_PATTERN *Bank )
{
     TT  =  Bank -> TT; 
     DO  =  Bank -> DO; 
     DE  =  Bank -> DE; 
}
/*-----------------------------------------------------------------------------*/
void SRCO::Assign( SRCO_PATTERN *Bank )
{
     for (int i=0;i<4;i++)
       NA[i]  =  Bank -> NA[i]; 
     VA  =  Bank -> VA; 
}
/*-----------------------------------------------------------------------------*/
void X1TH::Assign( X1TH_PATTERN *Bank )
{
     ID  =  Bank -> ID;
     for (int i=0;i<2;i++)
       VR[i]  =  Bank -> VR[i];
     for (int i=0;i<4;i++) 
     {
       TT[i]  =  Bank -> TT[i]; 
       TV[i]  =  Bank -> TV[i];
     }
}
/*-----------------------------------------------------------------------------*/
void X1AD::Assign( X1AD_PATTERN *Bank )
{
     for (int i=0;i<4;i++)
       IT[i]  =  Bank -> IT[i];
     for (int i=0;i<36;i++) 
       AV[i]  =  Bank -> AV[i]; 
}
ClassImp(QLIN)

QLIN::QLIN() {}
QLIN::~QLIN(){}


ClassImp(QMTL)

QMTL::QMTL() {}
QMTL::~QMTL(){}


ClassImp(QMTS)

QMTS::QMTS() {}
QMTS::~QMTS(){}


ClassImp(FRFT)

FRFT::FRFT() {}
FRFT::~FRFT(){}


ClassImp(FRTL)

FRTL::FRTL() {}
FRTL::~FRTL(){}


ClassImp(TEXS)

TEXS::TEXS() {}
TEXS::~TEXS(){}


ClassImp(HMAD)

HMAD::HMAD() {}
HMAD::~HMAD(){}


ClassImp(MCAD)

MCAD::MCAD() {}
MCAD::~MCAD(){}


ClassImp(PECO)

PECO::PECO() {}
PECO::~PECO(){}


ClassImp(EIDT)

EIDT::EIDT() {}
EIDT::~EIDT(){}


ClassImp(PHCO)

PHCO::PHCO() {}
PHCO::~PHCO(){}


ClassImp(PEPT)

PEPT::PEPT() {}
PEPT::~PEPT(){}


ClassImp(FRID)

FRID::FRID() {}
FRID::~FRID(){}


ClassImp(EFOL)

EFOL::EFOL() {}
EFOL::~EFOL(){}


ClassImp(PCQA)

PCQA::PCQA() {}
PCQA::~PCQA(){}


ClassImp(EGPC)

EGPC::EGPC() {}
EGPC::~EGPC(){}


ClassImp(MUID)

MUID::MUID() {}
MUID::~MUID(){}


ClassImp(PGPC)

PGPC::PGPC() {}
PGPC::~PGPC(){}


ClassImp(PGAC)

PGAC::PGAC() {}
PGAC::~PGAC(){}


ClassImp(PDLT)

PDLT::PDLT() {}
PDLT::~PDLT(){}


ClassImp(PMLT)

PMLT::PMLT() {}
PMLT::~PMLT(){}


ClassImp(QDET)

QDET::QDET() 
{ 
AF = NULL;
AL = NULL;
AT[0] = NULL;
AT[1] = NULL;
AT[2] = NULL;
AT[3] = NULL;
LT = NULL;
AE = NULL;
AH = NULL;
AM = NULL;
EC = NULL;
HC = NULL;
ET = NULL;
FI = NULL;
EF = NULL;
PC = NULL;
EG = NULL;
MU = NULL;
PG = NULL;
PD = NULL;
PM = NULL;
}
QDET::~QDET(){}


ClassImp(QVEC)

QVEC::QVEC() 
{
QD = NULL;
NP = NULL;
SP = NULL;
}
QVEC::~QVEC(){}


ClassImp(YV0V)

YV0V::YV0V() {}
YV0V::~YV0V(){}


ClassImp(FKIN)

FKIN::FKIN() {}
FKIN::~FKIN(){}


ClassImp(FVER)

FVER::FVER() 
{
IP = NULL;
}
FVER::~FVER(){}


ClassImp(QVRT)

QVRT::QVRT() 
{
AY = NULL;
AF = NULL;
}
QVRT::~QVRT(){}


ClassImp(ALPB)

ALPB::ALPB() {}
ALPB::~ALPB(){}


ClassImp(ALRP)

ALRP::ALRP() {}
ALRP::~ALRP(){}


ClassImp(RNL2)

RNL2::RNL2() {}
RNL2::~RNL2(){}


ClassImp(RNF2)

RNF2::RNF2() {}
RNF2::~RNF2(){}


ClassImp(RNR2)

RNR2::RNR2() {}
RNR2::~RNR2(){}


ClassImp(RLEP)

RLEP::RLEP() {}
RLEP::~RLEP(){}


ClassImp(LFIL)

LFIL::LFIL() {}
LFIL::~LFIL(){}


ClassImp(EVEH)

EVEH::EVEH() {}
EVEH::~EVEH(){}


ClassImp(KEVH)

KEVH::KEVH() {}
KEVH::~KEVH(){}


ClassImp(REVH)

REVH::REVH() {}
REVH::~REVH(){}


ClassImp(LOLE)

LOLE::LOLE() {}
LOLE::~LOLE(){}


ClassImp(X1RG)

X1RG::X1RG() {}
X1RG::~X1RG(){}


ClassImp(BOMB)

BOMB::BOMB() {}
BOMB::~BOMB(){}


ClassImp(RUNH)

RUNH::RUNH() {}
RUNH::~RUNH(){}


ClassImp(ASIM)

ASIM::ASIM() {}
ASIM::~ASIM(){}


ClassImp(ADBR)

ADBR::ADBR() {}
ADBR::~ADBR(){}


ClassImp(XTBN)

XTBN::XTBN() {}
XTBN::~XTBN(){}


ClassImp(XTCN)

XTCN::XTCN() {}
XTCN::~XTCN(){}


ClassImp(XTOP)

XTOP::XTOP() {}
XTOP::~XTOP(){}


ClassImp(LUPA)

LUPA::LUPA() {}
LUPA::~LUPA(){}


ClassImp(SILH)

SILH::SILH() {}
SILH::~SILH(){}


ClassImp(XHVB)

XHVB::XHVB() {}
XHVB::~XHVB(){}


ClassImp(XTEB)

XTEB::XTEB() {}
XTEB::~XTEB(){}


ClassImp(XTRB)

XTRB::XTRB() {}
XTRB::~XTRB(){}


ClassImp(DTBP)

DTBP::DTBP() {}
DTBP::~DTBP(){}


ClassImp(VHBV)

VHBV::VHBV() {}
VHBV::~VHBV(){}


ClassImp(VHPV)

VHPV::VHPV() {}
VHPV::~VHPV(){}


ClassImp(EAUX)

EAUX::EAUX() {}
EAUX::~EAUX(){}


ClassImp(SIX2)

SIX2::SIX2() {}
SIX2::~SIX2(){}


ClassImp(X1TV)

X1TV::X1TV() {}
X1TV::~X1TV(){}


ClassImp(KWGT)

KWGT::KWGT() {}
KWGT::~KWGT(){}


ClassImp(X1IP)

X1IP::X1IP() {}
X1IP::~X1IP(){}


ClassImp(SIXA)

SIXA::SIXA() {}
SIXA::~SIXA(){}


ClassImp(SITC)

SITC::SITC() {}
SITC::~SITC(){}


ClassImp(SRCO)

SRCO::SRCO() {}
SRCO::~SRCO(){}


ClassImp(X1TH)

X1TH::X1TH() {}
X1TH::~X1TH(){}


ClassImp(X1AD)

X1AD::X1AD() {}
X1AD::~X1AD(){}


ClassImp(QEXT)

QEXT::QEXT() 
{
LP = NULL;
}
QEXT::~QEXT(){}


ClassImp(QHAC)

QHAC::QHAC() 
{
EH = NULL;
RH = NULL;
AS = NULL;
KE = NULL;
RE = NULL;
AD = NULL;
BO = NULL;
CN = NULL;
OP = NULL;
LP = NULL;
SI = NULL;
EB = NULL;
RB = NULL;
BP = NULL;
EX = NULL;
X2 = NULL;
TC = NULL;
}
QHAC::~QHAC(){}

