//////////////////////////////////////////////////////////
//
// File which containes classes needed to construct
// the interface to the ALEPH BOS banks
// 
// Author : R. Cavanaugh
//
//////////////////////////////////////////////////////////

 
#ifndef _ALEPHBOSBANKS_H_
#define _ALEPHBOSBANKS_H_

/*----------------------------------------------------------------------------*/
class YV0V_PATTERN // V0 vertex fit List
{
public:
      int   K1;    // K1               [1,*]
                   // Number of the positive track coming from V0 in the frft bank
      int   K2;    // K2               [1,*]
                   // Number of the negative track coming from V0 in the frft bank
      float VX;    // VXcoordin        [-180.0,180.0]
                   // Fitted V0 x coordinate
      float VY;    // VYcoordin        [-180.0,180.0]
                   // Fitted V0 y coordinate
      float VZ;    // VZcoordin        [-220.0,220.0]
                   // Fitted V0 z coordinate
      float VM[6]; // VerrMat          [*,*]
                   // Triangular covariance matrix of V0s coordinates stored in the order
                   // 1 2 4
                   // - 3 5
                   // - - 6
      float PX;    // PXmomentum       [*,*]
                   // Fitted V0 momentum px
      float PY;    // PYmomentum       [*,*]
                   // Fitted V0 momentum py
      float PZ;    // PZmomentum       [*,*]
                   // Fitted V0 mometum pz
      float PM[6]; // PerrMat          [*,*]
                   // Triangular covariance matrix of V0s momentum stored in the order
                   // 1 2 4
                   // - 3 5
                   // - - 6
      float X1;    // X1consmass       [*,*]
                   // First constraint of mass r on the aleph note
      float X2;    // X2consmass       [*,*]
                   // Second constraint of mass b on the aleph note
      float XM[3]; // XerrMat          [*,*]
                   // Triangular covariance matrix of V0s constraint stored in the order
                   // 1 2
                   // - 3
      float C2;    // C2chisquare      [0.0,*]
                   // Chisquare of V0 vertex fit
      int   IC;    // ICodevo          [-22,22]
                   // (Fit hypothesis*10+abs(IND))*sign.
                   // IND in range -2 to 2 (see YV0 package write-up).
                   // IND=-2 or -1 if tracks do not intersect in xy.
                   // IND=0 - intersect at one point.
                   // IND=1 or 2 - intersect twice.
                   // Sign is positive if IND is positive. Fit hyp.=1 if tracks
                   // not parallel at vertex (ie. IND=1 or diff. in tan(dip) not small).
                   // Fit hyp=2 if tracks approx parallel at vertex
                   // (ie. IND.NE.1 and diff.in tan(dip) is small).
      float P1[3]; // P1               [*,*]
                   // Momentum of positive charged particle coming from V0 candidate
      float P2[3]; // P2               [*,*]
                   // Momentum of negative charged particle coming from V0 candidate
      float EP[21];// EP               [*,*]
                   // Coovariance matrix of P1 P2  stored in the order
                   // 1  2  4  7  11 16
                   // -  3  5  8  12 17
                   // -  -  6  9  13 18
                   // -  -  -  10 14 19
                   // -  -  -  -  15 20
                   // -  -  -  -  -  21
      float DM;    // DM               [*,*]
                   // Minimum distance between helices (see aleph note)
      float S1;    // S1               [*,*]
                   // Psi angle for positive charged particle coming from V0
      float S2;    // S2               [*,*]
                   // Psi angle for negative charged particle coming from V0
};
/*----------------------------------------------------------------------------*/
class FVER_PATTERN // Fxxx monte carlo VERtex bank.
{
public:
      float VX;    // VX               [*,*]
                   // Vertex X position
      float VY;    // VY               [*,*]
                   // Vertex Y position
      float VZ;    // VZ               [*,*]
                   // Vertex Z position
      float TO;    // TOf              [*,*]
                   // Time of flight
      int   IP;    // IPrim            [0,*]
                   // FKIN track which produced this vertex
      int   IS;    // ISec             [0,*]
                   // Offset to first FKIN outgoing track
      int   NS;    // NSec             [0,*]
                   // no. of outgoing tracks
      char  VN[4]; // VolNam
                   // vertex volume name
      char  VM[4]; // VertexMechanism
                   // vertex mechanism name
};
/*----------------------------------------------------------------------------*/
class FKIN_PATTERN // Fxxx monte carlo track bank.
{
public:
      float PX;    // PX               [*,*]
                   // Px
      float PY;    // PY               [*,*]
                   // Py
      float PZ;    // PZ               [*,*]
                   // Pz
      float MA;    // MAss             [0.0,*]
                   // mass
      int   PA;    // PArt             [0,*]
                   // ALEPH particle code
      int   OV;    // OVrt             [0,*]
                   // (FVER) Origin vertex no.
      int   EV;    // EVrt             [0,*]
                   // (FVER) End vertex no.
      int   HC;    // HCode            [0,*]
                   // History code (generator dependant)
};
/*----------------------------------------------------------------------------*/
class QVEC_PATTERN //   TRACKS (BOS)
{
public:

//   Basic attributes
     float QX;
     float QY;
     float QZ;
     float QE;
     float QM;
     float QP;
     float QCH;

//   flags  
     int   TN;     // JULIA / GALEPH Track Number
     int   SC;     // stability code
     int   KS;     // LUND status code
     int   CL;     // track CLass
     int   PA;     // ALEPH particle code
     int   QD;     // offset for corresponding row in QDET (NOT the row number!)
  
     int   NP;     // pointer to Next Particle / same particle code / same class
     int   SP;     // Same Particle, different hypothesis or Lorentz frame
     int   OV;     // Origin Vertex no
     int   EV;     // End Vertex no
  
     int   ND;     // Number of Decay particles
     int   DL;     // offset of 1st daughter in particle List QLIN
     int   NO;     // Number of mother particles
     int   OL;     // offset of 1st mother in particle List QLIN
     int   NM;     // Number of Matches
     int   ML;     // Match list = row offset in banks QMTL and QMTS
  
     int   BM[14]; // Lock Bit masks ( up to 448 tracks allowed )
     int   LK;     // QLITK flag
  
     float DB;     // Distance of closest approach to beam axis
     float ZB;     // Z coordinate of point where DB is measured.
     float SD;     // Error**2 on DB
     float SZ;     // Error**2 on DZ
     float CB;     // Chi**2 corresponding do DB and DZ.
  
//   Error Matrix  
     float EM[10]; // triangular covariance matrix
  
     float CF;     // chi**2 from last kinematical fit
     float EW;     // weight from energy flow analysis
  
     float US[18]; // User space
};
/*----------------------------------------------------------------------------*/
class QDET_PATTERN //  DETECTOR INFORMATION
{
public:

     // ALPHA flags  
     int   AF;     //  offset for corresponding row in bank FRFT 
                   //                          (NOT row number !)
     int   AL;     //  offset for corresponding row in bank FRTL
     int   NT;     //  number of segments in bank TEXS
     int   AT[4];  //  offset for corresponding rows in bank TEXS (MAX : 5)
     int   LT;     //  last allowed AT address
  
     int   AE;     //  offset for corresponding row in bank EIDT
     int   AH;     //  offset for corresponding row in bank HMAD
     int   AM;     //  offset for corresponding row in bank MCAD

     int   CF;     //  calorimeter flag 
                   //    (<0 : ass, > 0 : isol, abs=1 : ECAL; =2 : HCAL)
     int   EC;     //  offset for corresponding row in bank PECO
     int   HC;     //  offset for corresponding row in bank PHCO
     int   ET;     //  offset for corresponding row in bank PEPT
     int   FI;     //  offset for corresponding row in bank FRID
     int   NF;     //  number of associated charged tracks
     int   FL;     //  offset of 1st ass. ch. track in list QLIN
     int   NE;     //  number of associated ECAL objects
     int   EL;     //  offset of 1st ass. ECAL object in list QLIN
     int   NH;     //  number of associated HCAL objects
     int   HL;     //  offset of 1st ass. HCAL object in list QLIN
     int   LH;     //  overlap - associated
     int   EF;     //  offset for corresponding row in bank EFOL
     int   PC;     //  offset for corresponding row in bank PCQA
     int   EG;     //  offset for corresponding row in bank EGPC
     int   MU;     //  offset for corresponding row in bank MUID
     int   DX;     //  offset for corresponding row in bank
     int   PG;     //  offset for corresponding row in bank PGPC
     int   PD;     //  offset for corresponding row in bank PDLT
     int   PM;     //  offset for corresponding row in bank PMLT
};
/*----------------------------------------------------------------------------*/
class QVRT_PATTERN //  VERTICIES
{
public:
     float VX;     //   XPosition
     float VY;     //   YPosition
     float VZ;     //   ZPosition
     int   VN;     //   JULIA /GALEPH Vertex number
     int   TY;     //   vertex TYpe
  
     int   IP;     //   track number of Incoming Particle
     int   ND;     //   Number of Decay particles
     int   DL;     //   offset for decay particle list
     int   AY;     //   offset for corresponding row in YV0V
     int   AF;     //   offset for corresponding row in FVER
  
     float EM[6];  //   triangular error matrix
  
     float CF;     //   chi**2 for vertex fit -- filled by KVFITN, KVFITV
     float ET[8];  //   track-vertex error matrix
     float US;     //         User space
     float PK;     //   momentum of parent track at the kink position
     float PT;     //   Pt of outgoing ch part relative to parent
     float PL;     //   Pl of outgoing ch part relative to parent
     int   HY;     //   Hypothesis of mass cuts satisfied
};
/*----------------------------------------------------------------------------*/
class QLIN_PATTERN //  ONE - TO MANY PARTICLE RELATIONS
{
public:
     int    I;     //  ALPHA track number    
};
/*----------------------------------------------------------------------------*/
class QMTL_PATTERN //  MATCH LIST
{
public:
     int    I;     //  ALPHA track number
};
/*----------------------------------------------------------------------------*/
class QMTS_PATTERN //  NUMBER OF SHARED HITS IN MATCH LIST
{
public:
     int    I;     //  Number of shared hits
};
/*----------------------------------------------------------------------------*/
class FRFT_PATTERN // Global Geometrical track Fit
{
public:   
     float  IR;    //  InverseRadi      [*,*]   
                   //    Inverse radius of curvature in x-y  
                   //    projection            
                   //    signed +ve if track bends           
                   //    counterclockwise      
                   //    -ve if tracks bends clockwise       
     float  TL;    //  TanLambda        [*,*]   
                   //    tangent of dip angle  
     float  P0;    //  Phi0             [0.0,6.3]             
                   //    Phi at closest point of approach to 
                   //    line x=y=0            
     float  D0;    //  D0               [-180.,180.]          
                   //    Closest distance of approach to line
                   //    x=y=0                 
                   //    in the x-y plane (impact parameter) 
                   //    (signed +ve if particle has a positive
                   //    angular momemtum around the origin, -ve     
                   //    otherwise)            
     float  Z0;    //  Z0               [-220.,220.]          
                   //    Z-coordinate at D0    
     float  AL;    //  Alpha            [-3.15,3.15]          
                   //    Multiple scattering angle between tpc 
                   //    and itc               
     float  EM[20];//  EcovarM          [*,*]   
                   //    Triangular covariance matrix stored in
                   //    the order:            
                   //    1 
                   //    2 3                   
                   //    4 5 6                 
                   //    7 8 9 10              
                   //    11 12 13 14 15        
                   //    16 17 18 19 20 21     
     float  C2;    //  Chis2            [0.0,*] 
                   //    Chisquare of helix fit
     int    DF;    //  numDegFree       [0,63]  
                   //    Numer of degr. of freedom           
     int    NO;    //  nopt             [0,149] 
                   //    nopt=nmult*100+iopt*10+ierr         
                   //    IOPT=1 Circle+line fit with UFITMS  
                   //    IOPT=2 3-D iteration with UFITMS    
                   //    IOPT=3 M.S. A*(R-R0)/R with UFITMS  
                   //    IOPT=4 M.S. I-DD0(A) I-PH0(A) with UFITMS
                   //    IOPT=9 Kalman filter fit UFTKAL     
                   //    NMULT=1 Increased TPC errors for M.S. in UFITMS 
                   //    NMULT=0 TPC errors left alone       
                   //    IERR=1 Circle+line fit failed in UFITMS                
                   //    IERR=2 Cannot invert cov matrix from UFITMS
                   //    IERR=3 Cov. matrix from UFITMS not pos. def.
                   //    IERR=4 Kalman filter fit was tried but       
                   //           failed; The old fit from UFITMS was 
                   //           retained              
};
/*----------------------------------------------------------------------------*/
class FRTL_PATTERN //   Tpc+Itc+Vdet Geometry Track point List. 
                   //            Rows correspond with rows in FRFT bank. 
{
public:
     int   IV;     //  IoffV  [0,10000] offset in FVCL        
     int   NV;     //  NarcV  [0,4]     numb. coord. in Vdet  
     int   II;     //  IoffI  [0,10000] offset in FICL        
     int   NI;     //  NarcI  [0,8]     numb. coord. in Itc   
     int   NE;     //  NrEsti [0,1000]  numb. coord. in following spirals in ITC
     int   IT;     //  IoffT  [0,10000] offset in FTCL        
     int   NT;     //  NarcT  [0,21]    numb. coord. in first arc in Tpc    
     int   NR;     //  NRestt [0,1000]  numb. coord. in following spirals,in Tpc
};
/*----------------------------------------------------------------------------*/
class TEXS_PATTERN // Tpc dE/dX Segment (NR=0) 
                   //        One track segment per sector crossed 
{
public:
     int   SI;     // SegmentId      [1,*]       Sector slot number    
     float TM;     // TruncatedMean  [0.0,*]     Truncated mean of dE/dx 
                   //                               measurements
     float TL;     // TrackLength    [0.0,500.0] Useful length of track for 
                   //                               dE/dx    
     int   NS;     // NumberSamples  [1,500]     Number of samples used for 
                   //                               dE/dx    
     float AD;     // AverageDrift   [0.0,220.0] Average drift length of samples
     int   TN;     // TrackNumber    [1,*]       Pointer to track entry in TGFT 
     int   SF;     // SatFlag        [0,1]   
                   //    1= >40% saturated hits.             
                   //    0= <40% saturated hits     
};
/*----------------------------------------------------------------------------*/
class EIDT_PATTERN // Electron IDenTification          
{            
public:     
     int   IF;     // Quality Flag for ID 0=OK, 1=crack, 2=overlap 
     float R1;     // R1 = (E_cluster-P_track)/reso(E,P); 
                   //       estimator(energy balance)    
     float R2;     // R2 = (X-X0)/sigma(X); estimator(compactness) 
     float R3;     // R3 = (a-a0)/sigma(a); estimator(longitud. profile)   
     float R4;     // R4 = (b-b0)/sigma(b); estimator(longitud. profile)   
     float R5;     // R5 = I-I0/SIGMA(I);   estimator(de/dx)       
     float R6;     //            
     float R7;     //            
     float EC;     // corrected energy with elec. hyp.             
     int   IP;     // R2 > -3. && -2.4 < R3 < 3. --> 
                   //        IP=0 if "non electron", IP=1 if electron
     float E1;     // raw energy in centered storeys stack 1       
     float E2;     // raw energy in centered storeys stack 2       
     float E3;     // raw energy in centered storeys stack 3       
     int   FR;     // Row index in FRFT of the fitted track        
     int   PE;     // Row index in PECO of the electromagnetic calobject 
};     
/*----------------------------------------------------------------------------*/
class HMAD_PATTERN // Hcal Muon tracks Association
{
public: 
     int NplaFired;//  [0,23]        : number of fired planes
     int NplaExp;  //  [0,23]        : number of expected fired planes
     int NplaLast; //  [0,10]        : number of fired planes in last 10
     int MultHits; //  [0,30]        : number of clusters in last ten planes
     int IGeomflag;//  [-1,8]        : geometry flag :
                   //             -1 : error condition
                   //              0 : track in active zone
                   //              1 : dead zone between two barrel modules
                   //              2 : dead zone between two endcap modules
                   //              3 : barrel module notch
                   //              4 : spacer in endcap module
                   //              5 : not active zone of tube
                   //              6 : first plane in thin endcap
                   //              7 : masked digital chain
                   //              8 : masked HV channel 
     float EnerDep;//  [0.0,100.]  : energy deposit in corresponding Hcal storey
     float ChiSquare;// [0.00,200.00] : chisquare for hits inside the Hcal road
                   //                  - not filled in jul222
     int NumbDeg;  //  [0,23]        : degrees of freedom -not filled in jul222
     int IExpbmap; //  [0,11000000]  : expected bit map for Hcal planes
     int ITruebmap;//  [0,11000000]  : observed bit map for Hcal planes 
                   //                    Note: bit# = plane# only for barrel 
                   //                    regions away from endcap-overlap 
     int IdenFlag; //  [-1,1]        : preliminary identification flag 
                   //             -1 : hadron
                   //              0 : not classified (track near dead zone)
                   //              1 : muon candidate
     int TrackNo;  //  [1,999]       : associated track # 
};
/*----------------------------------------------------------------------------*/
class MCAD_PATTERN // Muon Chambers Association 
{
 public:
     int   NH[2];  //NassHit  [0,99]         number of associated hits          
                   //                          1,2 -> Int/Ext chambers     
     float DH[2];  //DistHit  [0.0,1000.00]  minimum distance hit-track  
     float DC[2];  //DistCut  [0.0,1000.00]  cutoff on hit-track distance
     float AM;     //AngMin   [0.0,*]        minimum angle between extrap
                   //                          and measured (in muon ch) track
     float AC;     //AngCut   [0.0,*]        cutoff on mimimum angle            
     int   TN;     //TrackNo  [1,999]        associated track #         
};
/*----------------------------------------------------------------------------*/
class PECO_PATTERN // Electromagnetic Calorimeter
{
public:
     float ER;     //  ERaw             [0.0,300.000] 
                   //       Raw Energy (Gev)      
     float E1;     //  Esta1            [0.0,1.00]           
                   //       Proportion of raw energy in stack 1       
                   //       "Stack 1" is defined properly for the            
                   //       overlap region according to the tower number      
     float E2;     //  Esta2            [0.0,1.00]           
                   //       Proportion of raw energy in stack 2       
                   //       "Stack 2" is defined properly for the            
                   //       overlap region according to the tower number      
     float TH;     //  THeta            [0.0,3.1416]                
                   //       Theta. The theta, phi of stacks 1 - 3            
                   //       are weighted by the stack energy                 
     float PH;     //  PHi              [0.0,6.2833]                
                   //       Phi. The theta, phi of stacks 1 - 3 are   
                   //       weighted by the stack energy              
     float EC;     //  ECorr            [0.0,300.000]               
                   //       Energy (Gev) corrected for geometrical    
                   //       effects (cracks, detector                 
                   //       overlap, dead storeys)
                   //       Set to ERaw in JULIA 224                  
     int   KD;     //  KDrg             [0,255] 
                   //       Region code ; see note ALEPH # 88-134            
                   //       for a detailed description of this code          
     int   CC;     //  CCode            [0,255] 
                   //        Correction code for the cluster                  
                   //        analysis method;      
                   //        CCode =               
                   //        0 : Standard          
                   //        1 : Crack between modules                        
                   //        2 : Overlap between detectors                    
                   //        3 : Dead storey       
     int   RB;     //  RBits            [0,255] 
                   //       Relation bits         
                   //       RBITS =               
                   //       0 : no relations      
                   //       1 : charged track relation                       
                   //       2 : HCAL relation     
                   //       3 : Both ch tk and HC relation                   
     int   PC;     //  PCOB                     
                   //       CalObject number           
};
/*----------------------------------------------------------------------------*/
class PHCO_PATTERN //  Hadron Calorimeter Object
{
public:

     float ER;     //  ERaw             [0.0,300.00]   Raw Energy (Gev)      
     float TH;     //  THeta            [0.0,3.142]    Theta          
     float PH;     //  PHi              [0.0,6.284]    Phi            
     float EC;     //  ECorr            [0.0,300.00]                       
                   //     Energy (Gev) corrected for geometrical           
                   //     losses ( cracks , spacers and coil )             
     int   KD;     //  KDrg             [0,255] 
                   //     Region code = 1 in overlap region                 
                   //                 = 0 otherwise         
     int   CC;     //  CCode            [0,255] 
                   //     Correction code (not filled in JULIA 224)          
     int   RB;     //  RBits            [0,255]        Relation bits         
                   //     RBITS =               
                   //        0 : no relations      
                   //        1 : charged track relation                       
                   //        2 : ECAL relation     
                   //        3 : Both ch tk and EC relation                   
     int   NF;     //  NoiseFlag        [0,64]  
                   //     Noise Flag from Topological Analysis             
                   //     and Digital Pattern matching                     
                   //     bits 0-4 Top. An. (0=OK,1=Noise)                 
                   //     bit 5 Dig. Matching (0=OK,1=Noise)               
     int   PC;     //  PCOB  CalObject number           
};
/*----------------------------------------------------------------------------*/
class PEPT_PATTERN // Electromagnetic calorimeter object Phi and Theta values
{
public:
     float T1;     //  Testa12          [0.0,3.142]    Theta in stacks 1 and 2
     float P1;     //  Phi12            [0.0,6.284]    Phi in stacks 1 and 2 
     float T3;     //  Testa3           [0.0,3.142]    Theta in stack 3      
     float P3;     //  Phi3             [0.0,6.284]    Phi in stack 3      
};
/*----------------------------------------------------------------------------*/
class FRID_PATTERN // Particle identification bank for charged tracks.
{
public:
     int   BP;     // BitPat           [*,*]   
                   //       Bit Patter for traking devices.                  
                   //       Bits correspont to layers on tracking            
                   //       devices, 1 means that the layer has              
                   //       been used in the fit of this track, 0            
                   //       not used. The first Bit corresponds to           
                   //       the information about the inner layer            
                   //       of VDET (2 layers in VDET, 8 in ITC and          
                   //       21 in TPC)            
     int   DZ;     //  DeadZone         [*,*]   
                   //       Dead Zone Patter for tracking devices.           
                   //       Bits correspont to layers on tracking            
                   //       devices, 1 means that this track cross           
                   //       a sensitive zone, 0 dead zone. The               
                   //       first Bit corresponds to the    
                   //       information about the inner layer of         
                   //       VDET (2 layers in VDET, 8 in ITC and 21      
                   //       in TPC)               
     int   BC;     //  BitpatC          [*,*]   
                   //       Bit Patter for calorimeters.                 
                   //       Bits correspont to layers on                 
                   //       calorimeters, 1 means that the layer         
                   //       has been associated to the track, 0 not 
                   //       associated. The first Bit corresponds        
                   //       to the information about the inner           
                   //       layer of ECAL (3 layers in ECAL, 23 in       
                   //       HCAL and 4 in MUON Chambers)                 
     int   DC;     //  DeadzoneC        [*,*]   
                   //       Dead Zone Patter for calorimeters.           
                   //       Bits correspont to layers on                 
                   //       calorimeters 1 means the extrapolated        
                   //       track cross a sensitive zone, 0 cross a    
                   //        dead zone. The first Bit corresponds to      
                   //        the information about the inner layer        
                   //       of ECAL (3 layers in ECAL, 23 in HCAL        
                   //       and 4 in MUON Chambers)                      
     float PE;     //  ProbElec         [0.0,*] 
                   //       Probability density that a electron          
                   //       give what             
                   //       has been observed in TPC , Ecal and          
                   //       Hcal and Muon chambers
     float PM;     //  ProbMuon         [0.0,*]   muon probability      
     float PI;     //  ProbpIon         [0.0,*]   pion probability      
     float PK;     //  ProbKaon         [0.0,*]   kaon probability      
     float PP;     //  ProbProton       [0.0,*]   proton probability    
     float NK;     //  NoKinkprob       [0.0,1.]  probability of having no kink 
     int   QF;     //  QualityFlag      [*,*]     Track Quality Flag from UFITQL
};
/*----------------------------------------------------------------------------*/
class EFOL_PATTERN //  Energy FlOw eLements
{
public:
     float PX;     //  PX        [-999.,999.] Weighted component x  
     float PY;     //  PY        [-999.,999.] Weighted component y  
     float PZ;     //  PZ        [-999.,999.] Weighted component z  
     float EW;     //  EnergyW   [-999.,999.] Element weighted by E-Flow 
                   //                            coefficients                 
     float WE;     //  WEight    [0.0,99.]    Weight applied to E-Flow element  
     int   TY;     //  TYpe             [0,10]  
                   //       Object type           
                   //       0 = Track             
                   //       1 = Electron          
                   //       2 = Muon              
                   //       3 = Track from V0     
                   //       4 = Electromagnetic   
                   //       5 = Ecal hadron/residu
                   //       6 = Hcal element      
                   //       7 = Lcal element      
     int   LE;     //  LinkEcal  [0,999]        Peco # associated     
     int   LT;     //  LinkTrak  [0,999]        Track # associated    
     int   LH;     //  LinkHcal  [0,999]        Phco # associated     
     int   LC;     //  LinkCalo  [0,999]        Calobject # associated
     int   LJ;     //  LinkJet   [0,100]        Jet # associated           
};
/*----------------------------------------------------------------------------*/
class DENF_PATTERN //  Energy FlOw eLements
{
public:
     float PX;     //  PX        [-999.,999.] Weighted component x  
     float PY;     //  PY        [-999.,999.] Weighted component y  
     float PZ;     //  PZ        [-999.,999.] Weighted component z  
     float EW;     //  EnergyW   [-999.,999.] Element weighted by E-Flow 
                   //                            coefficients                 
     float WE;     //  WEight    [0.0,99.]    Weight applied to E-Flow element  
     int   TY;     //  TYpe             [0,10]  
                   //       Object type           
                   //       0 = Track             
                   //       1 = Electron          
                   //       2 = Muon              
                   //       3 = Track from V0     
                   //       4 = Electromagnetic   
                   //       5 = Ecal hadron/residu
                   //       6 = Hcal element      
                   //       7 = Lcal element      
     int   DT;     //  LinkTrak  [0,999]        Track # associated    
     int   DJ;     //  LinkJet   [0,100]        Jet # associated           
};
/*----------------------------------------------------------------------------*/
class DENW_PATTERN //  Energy FlOw eLements
{
public:
     int   LC;     //  LinkCalo  [0,999]        Calobject # associated
};
/*----------------------------------------------------------------------------*/
class PCQA_PATTERN //  Calobject neutral particle for alpha Qvector from pcpA
{
public:
     
     int NA;       //  NAtu      [0,255]    Nature of Neutral Particle  
                   //  Implemented for the moment being:                       
                   //    1 Isolated gamma      
                   //    2 Gamma from multi gammas neutral cluster  
                   //    3 Gamma from identified pi 0               
                   //    4 Gamma from electron bremstrhalung         
                   //    5 Gamma from electromagnetic charged cluster
                   //    10 Unresolved gamma-gamma                   
                   //    12 Residual electromagnetic energy from neutral cluster
                   //    13 Residual electromagnetic energy from charged cluster
                   //    17 Neutral hadron     
                   //    18 Residual hadronic energy from neutral calobject     
                   //    19 Residual hadronic energy from charged calobject 
                   //       with no hcal component 
                   //    20 Residual hadronic energy from charged calobject 
                   //       with hcal component                   
                   //    21 contibution from an ecal cluster for which 
                   //       EBNEUT was in error                               
                   //    22 contibution from an LcObject               
     float PX;     //  PXpa      [-300.00,300.00]    Momentum X component (Gev)
     float PY;     //  PYpa      [-300.00,300.00]    Momentum Y component (Gev)
     float PZ;     //  PZpa      [-300.00,300.00]    Momentum Z component (Gev)
     float EN;     //  ENpa      [-300.00,300.00]    Particle energy       
};
/*----------------------------------------------------------------------------*/
class EGPC_PATTERN // Photons from GAMPEC
{
public:
     float PX;     //  PX      [*,*]     Momentum along x axis (GeV/c)
     float PY;     //  PY      [*,*]     Momentum along y axis (GeV/c)
     float PZ;     //  PZ      [*,*]     Momentum along z axis (GeV/c)
     float R1;     //  R1      [0.0,1.]  Energy fraction in stack 1   
     float R2;     //  R2      [0.0,1.]  Energy fraction in stack 2   
     float F4;     //  F4      [0.0,1.]  Energy fraction in the 4 central towers
     float DM;     //  DMin    [0.0,*]   Distance to the closest track (cm) 
     int   ST;     //  SToreys          [0,*]   
                   //        NST1 + 100*NST2 + 10000*NST3  
                   //        NSTi = # storeys in stack i   
     int   QU;     //  QUality          [0,*]   
                   //        CRCK + 10*DST1 + 100*DST2 + 1000*DST3
                   //        DSTi = 1 if dead storey(s) in stack i 
                   //        CRCK = 1 if photon in crack region    
     int   PE;     //  PECO                     
                   //        pointeur to PECO bank      
};
/*----------------------------------------------------------------------------*/
class MUID_PATTERN //     
{            
public:     
     int IF;       // IdFlag           [-20,20]                      
                   //        Identification Flag: = 1 if muon            
                   //        flagged only by HCAL = 2 if muon           
                   //        flagged only by MUON = 3 if muon           
                   //        flagged by both HCAL and MUON [3 is the  
                   //        .AND. of 1 and 2] = 10 is one hit in     
                   //        each layer of MUON but failing tight     
                   //        matching criteria = 11 is good HCAL      
                   //        pattern = 12 is one and only one MUON    
                   //        hit = 13 is good HCAL + one and only     
                   //        one muon = 14 is good HCAL + one hit in  
                   //        each layer = 15 is one hit in each        
                   //        layer of MUON passing tight matching     
                   //        criteria = 0 not a muon -1 to -15 as 
                   //        above but lost shadowing contest 
     float SR;     // SumResid         [0.0,999.]
                   //        Sum of HCAL (hit -track) residuals
     float DM;     // DistMuch         [0.0,*]
                   //        distance between track and closest mu ch hit
     int   ST;     // ShadTrack        [0,*] 
                   //        track number of shaoowing track (FRFT)
     int   TN;     // TrackNumber      [0,*] 
                   //        track number (FRFT)
};            
/*----------------------------------------------------------------------------*/
class PGPC_PATTERN // Photon from GamPeC  
{
public:
     float EC;     //  EnergyCorrected    Energy corrected for photon hypothesis
     float TC;     //  ThetaCorrected     Theta corrected for photon hypothesis
     float PC;     //  PhiCorrected       Phi corrected for photon hypothesis  
     float R1;     //  fRactions1         Energy fraction in stack 1           
     float R2;     //  fRactions2         Energy fraction in stack 2           
     float F4;     //  Fraction4tower     Energy fraction in the 4 towers      
     float DM;     //  DMin               Distance to the closest track        
     float ST;     //  SToreys                  
                   //       NST1+100*NST2+10000*NST3                           
                   //       Nsti = number of storeys stack i                   
     int   QU;     //  QUalityflag              
                   //       CRCK + 10*DST1 + 100*DST2 +1000*DST3               
                   //       DSTi = 1 if dead storey stack i                    
                   //       CRCK = 1 if photon in crack region                 
     float Q1;     //  Quality1           Quality estimator 1 for photon       
     float Q2;     //  Quality2           Quality estimator 2 for photon       
     float M1;     //  Moment1            1st moment form CLMOMS analysis      
     float M2;     //  Moment2            2nd moment form CLMOMS analysis      
     float MA;     //  MAss               Pi0 mass estimated from CLMOMS       
     float ER;     //  EnergyRaw          Raw energy for photon 
     float TR;     //  ThetaRaw           Raw Theta for photon  
     float PR;     //  PhiRaw             Raw Phi for photon    
     int   PE;     //  PECO               pointeur to PECO bank      
};
/*----------------------------------------------------------------------------*/
class PGAC_PATTERN //!< Photon from GamPeCK  
{
public: 
     float EC;     //!<  EnergyCorrected    Energy corrected for photon hypothesis
     float TC;     //!<  ThetaCorrected     Theta corrected for photon hypothesis
     float PC;     //!<  PhiCorrected       Phi corrected for photon hypothesis  
     float R1;     //!<  fRactions1         Energy fraction in stack 1           
     float R2;     //!<  fRactions2         Energy fraction in stack 2           
     float F4;     //!<  Fraction4tower     Energy fraction in the 4 towers      
     float DM;     //!<  DMin               Distance to the closest track        
     int   ST;     //!<  SToreys                  
                   /*!<     NST1+100*NST2+10000*NST3                           
                         -  Nsti = number of storeys stack i                   */
     int   QU;     //!<  QUalityflag              
                   /*!<     CRCK + 10*DST1 + 100*DST2 +1000*DST3               
                         -  DSTi = 1 if dead storey stack i                    
                         -  CRCK = 1 if photon in crack region                 */
     float Q1;     //!<  Quality1           Quality estimator 1 for photon       
     float Q2;     //!<  Quality2           Quality estimator 2 for photon       
     float M1;     //!<  Moment1            1st moment form CLMOMS analysis      
     float M2;     //!<  Moment2            2nd moment form CLMOMS analysis      
     float MA;     //!<  MAss               Pi0 mass estimated from CLMOMS       
     float ER;     //!<  EnergyRaw          Raw energy for photon 
     float TR;     //!<  ThetaRaw           Raw Theta for photon  
     float PR;     //!<  PhiRaw             Raw Phi for photon    
     float EF;     //!<  ExpectedFraction   Expected fraction in 4 towers
     float GC;     //!<  GeometricalCorr    Geomtrical correction
     float ZS;     //!<  ZeroSupression     Zero suppresion correction from Coradoc
     float PL;     //!<  ProbafakeeLm       Probability to be a fake photon from Electromagnetic origine
     float PH;     //!<  ProbafakeHad       Probability to be a fake photon from Hadronic origine
     int   PN;     //!<  ParentNumber       Row number(PGAC) of parent giving a fake photon
     int   FA;     //!<  FAkequality        Flag for fake determination
     int   PE;     //!<  PECO               pointeur to PECO bank      
};
/*----------------------------------------------------------------------------*/
class PDLT_PATTERN // Reconstructed Tagged Lepton from Mini-DST
{
public:
     int   PA;     //  PArticletype     [2,23]  
                   //    Particle type :       
                   //         2 = e+                
                   //        12 = e+ in crack region                    
                   //        22 = e+ in overlap region                  
                   //         3 = e-                
                   //        13 = e- in crack region                   
                   //        23 = e- in overlap region                 
                   //         5 = mu+ QMUIDO IDF=14 
                   //        15 = mu+ QMUIDO IDF=13
                   //         6 = mu- QMUIDO IDF=14 
                   //        16 = mu- QMUIDO IDF=13
     int   JT;     //  JeTnumber        [1,*]   
                   //        Nearest jet number in 
                   //        jet section           
     float PI;     //  PtInclusif       [0.0,*] 
                   //        Transverse momentum   
                   //        respect to jet including                   
                   //        lepton                
     float PE;     //  PtExclusif       [0.0,*] 
                   //        Transverse momentum   
                   //        respect to jet lepton 
                   //        excluded              
     int   VP;     //  ValidityPt       [0,30]  
                   //        Flag giving validity of                   
                   //        Pt calculation        
                   //         0 = OK                
                   //        10 = No track E-flow track found 
                   //        20 = No valid jet      
                   //        30 = Not enough object in jet 
     int   FR;     //  FRFT                     
                   //        Pointer to Associated Track
};
/*----------------------------------------------------------------------------*/
class PMLT_PATTERN //  History of tagged Lepton for Mcarlo events from Mini-DST
{
public: 
     int FL;       //  FLavorofquark  [0,5]  Primary quark flavour from QTRUTH 
                   //         1 - 5 Primary quark flavour                
     int PO;       //  POppingflag    [0,5]  IPOP from QTRUTH      
                   //          0 = Direct production 
                   //         >0 = flavor of the popped qq                    
     int CH;       //  flagCHain      [1,4]  ICHAIN from QTRUTH    
     int SP;       //  flagSPlit      [1,10] ISPLIT from QTRUTH    
     int LE;       //  flagLEpton     [0,4]  LEPID from QTRUTH     
     int ME;       //  flagMEss       [-2,3] IBMES from QTRUTH     
     int KT;       //  KineTrack      [1,*]  FKIN track number     
     int FR;       //  FRFT                  Pointer to Associated Track      
};
/*----------------------------------------------------------------------------*/
class ALPB_PATTERN //  Aleph chunk-by-chunk beam position (NR=Run number)
{
public:
     int  FE;      //    FirstEvent       [0,*]
                   //    Event number of first event in chunk
     int XP;       //    XPoslumreg
                   //    X Position of luminous region centroid
                   //    in units of 0.5 micron
     int XE;       //    XposError        [0,*]
                   //    X position Error in units of 0.1 micron
     int YP;       //    YPoslumreg
                   //    Y Position of luminous region centroid
                   //    in units of 0.5 micron
     int YE;       //    YposError        [0,*]
                   //    Y position Error in units of 0.1 micron
};
/*----------------------------------------------------------------------------*/
class ALRP_PATTERN // Luminous Region Parameters 
{
public:
      int PN;      //    PeriodName       [0,*]
                   //    Run period/year name
      int WE;      //    WEight           [0,*]
                   //    Weight of this run period; for LEP1,
                   //    equals the number of qqbar events in
                   //    MAYB/PERF VD runs; for LEP2, equals
                   //    zero.
      int ER;      //    ERa              [0,*]
                   //    LEP era; equals 1 for LEP1, 2 otherwise
      float XS;    //    XSigma
                   //    Average rms size in the x direction
      float YS;    //    YSigma
                   //    Average rms size in the y direction
      float ZS;    //    ZSigma
                   //    Average rms size in the z direction
      float XR;    //    XRes
                   //    Position resolution in the x direction
      float YR;    //    YRes
                   //    Position resolution in the y direction
      float F1;    //    Frac1
                   //    Fraction of total area in first
                   //    Gaussian; the sigma_x distribution is
                   //    modeled as the sum of two Gaussians
      float M1;    //    Mean1
                   //    Mean of first Gaussian
      float S1;    //    Sigma1
                   //    Sigma of first Gaussian
      float M2;    //    Mean2
                   //    Mean of second Gaussian
      float S2;    //    Sigma2
                   //    Sigma of second Gaussian
};
/*----------------------------------------------------------------------------*/
class RNL2_PATTERN //    LEP2 instantaneous energy
{
public:
      int DA;      //    DAtestart        [0,*]
                   //    Date of start of 15 minutes time slice,
                   //    YYMMDD
      int TI;      //    TImestart        [0,*]
                   //    Time of start of 15 minutes time slice,
                   //    hhmmss
      float EN;    //    ENergy           [0.0,*]
                   //    Energy during the time slice, in GeV
};
/*----------------------------------------------------------------------------*/
class RNF2_PATTERN //    Description of fills for LEP2
{
public:
      int FN;      //    FillNumber       [0,*]
                   //    Fill number
      int DS;      //    DateStart        [0,*]
                   //    Date of start of fill, YYMMDD
      int TS;      //    TimeStart        [0,*]
                   //    Time of start of fill, hhmmss
      int DE;      //    DateEnd          [0,*]
                   //    Date of end of fill, YYMMDD
      int TE;      //    TimeEnd          [0,*]
                   //    Time of end of fill, hhmmss
      int FS;      //    FirstSlice       [0,*]
                   //    First row in RNL2 for time slice
                   //    informations for this fill
      int LS;      //    LastSlice        [0,*]
                   //    Last row in RNL2 for time slice
                   //    informations for this fill
};
/*----------------------------------------------------------------------------*/
class RNR2_PATTERN //    RUN averaged energy for LEP 2
{
public:
      int RN;      //    RunNumber        [0,*]
                   //    Run number
      float EN;    //    ENergy           [0.0,*]
                   //    Energy in GeV, average for this run
};
/*----------------------------------------------------------------------------*/
class RLEP_PATTERN //    Run Header for LEP parameters
{
public:
      int LE;      //    LepEnergy        [0,*]
                   //    Lep Energy in MeV
      char LB[4];  //    LepBeam          [NONE,NONE]...
                   //    Beam type
      int LD;      //    LepperioD        [0,*]
                   //    Number of Bunches for Lep operation
      int LF;      //    LepFill          [0,*]
                   //    Lep Fill number
      int LP;      //    LepPolar         [-1,1]
                   //    Code for polarization
};
/*----------------------------------------------------------------------------*/
class LFIL_PATTERN //    LEP Fill description
{
public:
      int LF;      //    LepFill          [0,*]
                   //    LEP Fill Number
      int FR;      //    FirstRun         [0,*]
                   //    First run to which these data belong
      int LR;      //    LastRun          [0,*]
                   //    Last Run to which these data belong
      int NV;      //    NumVer           [0,*]
                   //    Number of tracks used to compute BX, BY
      float LE;    //    LepEnergy        [0.0,250.000]
                   //    LEP center-of-mass energy, average for
                   //    this fill, in GeV
      float BX;    //    BeamX            [-1.0000,1.0000]
                   //    Mean x coordinate of beam crossing.
                   //    BeamX and BeamY are computed from the
                   //    distribution of d0 vs. phi for selected
                   //    tracks (the Toby Burnett Method).
      float BY;    //    BeamY            [-1.0000,1.0000]
                   //    Mean y coordinate of beam crossing
      float BZ;    //    BeamZ            [-1.0000,1.0000]
                   //    Mean z coordinate of beam crossing,
                   //    from vertices of Z0 -> Hadrons
      float EX;    //    ErroX            [0.0,1.0000]
                   //    Error on BeamX
      float EY;    //    ErroY            [0.0,1.0000]
                   //    Error on BeamY
      float EZ;    //    ErroZ            [0.0,10.0000]
                   //    Error on BeamZ
      float OF;    //   OFfset           [-1.0000,1.0000]
                   //    Average d0 (to account for possible
                   //    systematic offsets). The corrected d0
                   //    of a track, relative to the average
                   //    beam crossing is
                   //    d0beam = d0frft - BeamX*sin(phi0)
                   //    + BeamY*cos(phi0) - OFfset,
                   //    where d0frft is the d0 with respect to
                   //    the z-axis, and phi0 is the track phi
                   //    direction at closest approach to the
                   //    z-axis.
};
/*----------------------------------------------------------------------------*/
class EVEH_PATTERN //    EVEnt Header (NR = 0)
{
public:
      int EN;      //    ExpNumber
                   //    Experiment Number
                   //    Online = [0,1000]
                   //    MonteCarlo =1001
      int RN;      //    RunNumber        [1,*]
                   //    Unique run number
      int RT;      //    RunType
                   //    Monte Carlo run type
                   //    KINE "LUND" : [1000,1999]
                   //    "SJET" : [2000,2999]
                   //    "PART" : [3000,3999]
                   //    "USER" : [10000,99999]
                   //    undefined : 100000
      int DA;      //    DAte
                   //    event date : yymmdd
      int TI;      //    TIme
                   //    event time : hhmmss
      int EV;      //    EVentnumber
                   //    event number
      int M1;      //    Mask1
                   //    Trigger mask 1
      int M2;      //    Mask2
                   //    Trigger mask 2
      int M3;      //    Mask3
                   //    Trigger mask 3
      int M4;      //    Mask4
                   //    Trigger mask 4
      int TY;      //    TYpe
                   //    Event type
                   //    Real event = 1
      int ES;      //    ErrorStatus
                   //    Error status (OK = 1)
      int TE;      //    TotalEnergy
                   //    2*Beam energy (keV)
};
/*----------------------------------------------------------------------------*/
class KEVH_PATTERN //    Event generator status(NR=0)
{
public:
      int RN;      //    firstRandomNu
                   //    1st random number
      int NT;      //    NumberofTrac
                   //    # of tracks generated
      int NV;      //    NumberofVert
                   //    # of vertices generated
      int PI;      //    ProcessId
                   //    process identification
      float WT;    //    WeighT
                   //    weight
      int SR;      //    SeconRandomnu
                   //    2nd random number
      int TR;      //    ThirdRandomnu
                   //    3rd random number
};
/*----------------------------------------------------------------------------*/
class REVH_PATTERN //    Reconstructio EVent Header
{
public:
      int DS;      //    DetectorStatus   [*,*]
                   //    Detector status bits
      int FE[2];   //    FatalErr         [*,*]
                   //    Fatal error bits
      int NE[2];   //    NonfatalErr      [*,*]
                   //    Non-fatal error bits
      int SB;      //    SelectionBits    [*,*]
                   //    Selection bits
      float TI;    //    TIme             [0.0,*]
                   //    Time for reconstruction
      int RB[2];   //    ReadoutBits      [*,*]
                   //    Readout Bits, shows existence
                   //    of detector banks in raw data
                   //    bit 0 - VDET
                   //    bit 1 - ITC
                   //    bit 2 - TPC pad
                   //    bit 3 - TPC wire
                   //    bit 4 - ECAL pad
                   //    bit 5 - ECAL wire
                   //    bit 6 - HCAL pad
                   //    bit 7 - HCAL wire
                   //    bit 8 - MUON
                   //    bit 9 - SATR
                   //    bit 10- LCAL pad
                   //    bit 11- LCAL wire
                   //    bit 12- BCAL
                   //    bit 13- Trigger
                   //    bit 14- BOM
                   //    bit 15- SICAL
      int EC;      //    EdirClass        [0,*]
                   //    EDIR class word
};
/*----------------------------------------------------------------------------*/
class LOLE_PATTERN //    Lcal online error flags
{
public:
      int FB[4];   //    FastBus          [0,*]
                   //    Fastbus error bitpattern
      int SP;      //    Spark            [0,230]
                   //    plane + (module-1)*64
      int TO;      //    TimeOut          [0,1]
                   //    GBX timeout flag
      int MA[4];   //    Marker           [0,*]
                   //    Missing marker bitpattern
      int HV;      //    HVtrip           [0,15]
                   //    HV trip bitpat
      int ER;      //    ERrorflag        [-1,1]
                   //    Error flag
};
/*----------------------------------------------------------------------------*/
class X1RG_PATTERN //    XLV1: ReadOut: Registers and related stuff
{
public:
      char NA[4];  //    Name
                   //    Name of Entry
                   //    TIM 2*Time+TPR_EnabMask
                   //    TSR GBXcount,{L1Ys,BunchNum},HV_bits
                   //    TPR L1rslt,L2rslt,EvtMask
                   //    PLU One Byte/Sector; Four Sect/Word
                   //    ITC Bits {24-35}->{36-47}
                   //    TPC Bits {24-35}->{36-47}
                   //    LCW squeezed; 4*{2*4}Bits
                   //    ETT 3*12 Bits {ECW_o,ECW_e,LCW}
                   //    HCWn no manipulation wrt TSR
                   //    ECWn no manipulation wrt TSR
      int CO[3];   //    Cont
                   //    Data
};
/*----------------------------------------------------------------------------*/
class BOMB_PATTERN //    BOM beam position
{
public:
      float XX;    //    XX               [*,*]
                   //    X position
      float YY;    //    YY               [*,*]
                   //    Y position
      int EE;      //    EE               [*,*]
                   //    Error flag
};
/*----------------------------------------------------------------------------*/
class RUNH_PATTERN //    RUN Header
{
public:
      int EN;      //    ExpNumber
                   //    Experiment Number
                   //    Online = [0,1000]
                   //    MonteCarlo =1001
      int RN;      //    RunNumber        [1,*]
                   //    Unique run number
      int RT;      //    RunType
                   //    Monte Carlo run type
                   //    KINE "LUND" : [1000,1999]
                   //    "SJET" : [2000,2999]
                   //    "PART" : [3000,3999]
                   //    "USER" : [10000,99999]
                   //    undefined : 100000
      int SD;      //    StartDate
                   //    run start date : yymmdd
      int ST;      //    StartTime
                   //    run start time : hhmmss
      char TT[8];  //    TriggerType
                   //    trigger mask description
                   //    usually RUN_DFLT
      char RC[8];  //    RunCondition
                   //    general run conditions description
                   //    usually ALEPH
};
/*----------------------------------------------------------------------------*/
class ASIM_PATTERN //    Aleph Simulation date
{
public:
      int YM;      //    YearMonth        [8800,9912]
                   //    period number given as yymm
                   //    to be simulated
};
/*----------------------------------------------------------------------------*/
class ADBR_PATTERN //    first run of a period. (LTC)
{
public:
      int PN;      //    PeriodNumber     [8900,9912]
                   //    Period number is yy*100+mm
      int FR;      //    FirstRun         [2001,999999]
                   //    first run number of the period
      int BP;      //    BPipsetup        [1,20]
                   //    BPIP setup number
      int VD;      //    VDetsetup        [1,20]
                   //    VDET setup number
      int IT;      //    ITcsetup         [1,20]
                   //    ITC setup number
      int TP;      //    TPcsetup         [1,20]
                   //    TPC setup number
      int EC;      //    ECalsetup        [1,20]
                   //    ECAL setup number
      int LC;      //    LCalsetup        [1,20]
                   //    LCAL setup number
      int SA;      //    SAtrsetup        [1,20]
                   //    SATR setup number
      int HC;      //    HCalsetup        [1,20]
                   //    HCAL setup number
      int MU;      //    MUonsetup        [1,20]
                   //    MUON setup number
      int TR;      //    TRiggersetup     [1,20]
                   //    Trigger setup number
      int GE;      //    GEneralsetup     [1,20]
                   //    General setup number
      int DB;      //    DBasesetup       [1,20]
                   //    Dbase setup number
      int SI;      //    SIcalsetup       [1,20]
                   //    SICAL setup number
      int BE;      //    BEamperiod       [1,20]
                   //    Beam position and size period
};
/*----------------------------------------------------------------------------*/
class XTBN_PATTERN //    Trigger Bit Names of all 32 trigger bits (STC)
{
public:
      int ID;      //    ID
      int VR[2];   //    ValRng           [0,99999999]
                   //    Validity range
      int TN;      //    TrgdefiN         [0,32]
                   //    Trigger defiNed flag, if 0 the bit is
                   //    undefined and not used for triggering.
      int TB;      //    TrgBitnr         [0,31]
                   //    Number of trigger bit in the level 1/2
                   //    trigger bit mask.
      char BM[8];  //    BitMnem
                   //    Mnemonic name of this trigger bit
      char BN[40]; //    BitName
                   //    Full name of this trigger bit
      char AD[20]; //    ActDet           [HCAL,HCAL]...
                   //    Name of active subdetectors needed to
                   //    realize this trigger. This information
                   //    is deduced from the XTLF bank.
      int L1;      //    Lvl1trg
                   //    Links a trigger bit with corresponding
                   //    logical function
      int L2;      //    Lvl2trg
                   //    Links a trigger bit with corresponding
                   //    logical function for the level 2
                   //    decision of this trigger
};
/*----------------------------------------------------------------------------*/
class XTCN_PATTERN //    Trigger level 1/2 CoNtrol information
{
public:
      int TT[2];   //    TrgTime
                   //    Date and Time at readout of trigger
                   //    information
                   //    word 1 byte 1: day
                   //    word 1 byte 2: month
                   //    word 1 byte 3/4: year
                   //    word 2 byte 1: 1/100 second
                   //    word 2 byte 2: second
                   //    word 2 byte 3: minute
                   //    word 2 byte 4: hour
      int GC;      //    GbxCount         [0,16777215]
                   //    Number of GBX counted by the trigger
                   //    since last event readout
      int LL;      //    LvL1count        [0,16777215]
                   //    Number of level 1 YES since last event
                   //    readout
      int BN;      //    BunNum           [1,1]...
                   //    Bunch number of colliding e-beam only
                   //    one single bit must be set.
                   //    Bit 0: Bunch number 1;
                   //    Bit 1: Bunch number 1 + 1BX;
                   //    Bit 2: Bunch number 1 + 2BX;
                   //    Bit 3: Bunch number 1 + 3BX.
      int CL;      //    CntrlL1
                   //    Control flags from trigger Level 1
      int TR[10];  //    TrgRes           [0,*]
                   //    Reserved space for trigger info.
                   //    1 word : HV status bits, Bit 0: ECAL
                   //    Endcap A;
                   //    Bit 1: ECAL Endcap B;
                   //    Bit 2: ECAL Barrel;
                   //    Bit 3: LCAL;
                   //    Bit 4: TPC dE/dxA;
                   //    Bit 5: ITC ;
                   //    Bit 6: SATR ;
                   //    Bit 7: HCAL Endcap A;
                   //    Bit 8: HCAL Endcap B;
                   //    Bit 9: HCAL Barrel;
                   //    Bit 10: MUON chambers not conn. ;
                   //    Bit 11: BCAL not conn. ;
                   //    Bit 12: VDET not conn. ;
                   //    Bit 13: Trigger analog crates;
                   //    Bit 14: Trigger CAMAC crates;
                   //    Bit 15: TPC ;
                   //    Bit 16 - 22: not allocated;
                   //    Bit 23: Beam pick up.
                   //    Word 2: Current trigger mask used in
                   //    this event.
                   //    Word 3: number of fastbus errors during
                   //    readout.
                   //    Word 4: register error flags, a bit set
                   //    indicates a fastbus error caused by the
                   //    corresponding TSR.
                   //    Word 5: scaler error flags, same as
                   //    word 3 for TSS modules.
                   //    Word 6: ADC error flags. Word 7-10 empty
};
/*----------------------------------------------------------------------------*/
class XTOP_PATTERN //     List of Trigger OPtions which can be sel for a trigger
{
public:
      int ID;      //    ID
      int VR[2];   //    ValRng           [0,99999999]
                   //    Validity range
      int NA[2];   //    Name
                   //    Name of the trigger option
      int TR;      //    Trgmask          [-999999999,999999999]
                   //    Bit mask for level 1/2 trigger
      int GS;      //    GbxScale         [-16777215,16777215]
                   //    Used to define random trigger.
                   //    If negative the TMT signal is expected
                   //    to come from the TPC. A positive value
                   //    is taken as scale factor to downscale
                   //    GBX as random trigger.
      int DS[8];   //    DwnScale         [1,65535]
                   //    Scale factors for the trigger bits 1 - 8
      int TT;      //    TrgType          [0,10]
                   //    Number of links to XTYP
};
/*----------------------------------------------------------------------------*/
class LUPA_PATTERN //    Luminosity parameter bank;
{
public:
      int GB;      //    GBxcnt           [0,*]
                   //    GBX counter
      int HV;      //    HVolt            [*,*]
                   //    HV bit pattern
      int T1;      //    Trl1             [*,*]
                   //    Trigger level 1 bit pattern
      int L2;      //    L2bits           [*,*]
                   //    Trigger level 2 bit pattern after
                   //    appplication of the trigger mask
      int TE;      //    TrEna            [*,*]
                   //    Trigger enable bit pattern
      int LO;      //    LOle             [*,*]
                   //    Lole information word, if 0: LOLE okay
      int AM;      //    AccMet           [*,*]
                   //    Acceptance method bit pattern
      int MD;      //    MinDown          [1,*]
                   //    Minimum downscale factor
      float EF;    //    EFid             [0.0,300.00]
                   //    Total fiducial LCAL energy (GeV)
      float EC[2]; //    EC               [0.0,300.00]
                   //    Cluster energies of most energetic
                   //    cluster on either side (GeV); side 1 =
                   //    side with tight fiducial cut, 2 = other
                   //    side
      float EW[2]; //    EW               [0.0,300.00]
                   //    Total wire energies on either side (GeV)
      float XC[2]; //    XC               [-60.00,60.00]
                   //    Cluster x positions (cm)
      float YC[2]; //    YC               [-60.00,60.00]
                   //    Cluster y positions (cm)
      float TC[2]; //    TC               [-200.00,200.00]
                   //    Cluster thetas (mrad)
      float PC[2]; //    PC               [-180.00,180.00]
                   //    Cluster phis (deg)
      float AX[2]; //    AX               [-1.000,1.000]
                   //    Cluster x asymmetries
      float AY[2]; //    AY               [-1.000,1.000]
                   //    Cluster y asymmetries
      float XX[2]; //    XX               [0.0,25.50]
                   //    Shower width in x (cm)
      float YY[2]; //    YY               [0.0,25.50]
                   //    Shower width in y (cm)
      float XY[2]; //    XY               [-1.000,1.000]
                   //    Shower width correlation
      float XA[2]; //    XA               [-120.00,120.00]
                   //    Cluster x averages (cm)
                   //    (x[stack1]+x[stack3]-2*x[stack2])
      float YA[2]; //    YA               [-120.00,120.00]
                   //    Cluster y averages (cm)
                   //    (y[stack1]+y[stack3]-2*y[stack2])
      float XD[2]; //    XD               [-10.00,10.00]
                   //    Cluster x differences (cm)
                   //    (x[stack3]-x[stack1])
      float YD[2]; //    YD               [-10.00,10.00]
                   //    Cluster y differences (cm)
                   //    (y[stack3]-y[stack1])
      int AD[2];   //    AD               [0,3000]
                   //    Address of most energetic LCAL tower
      int IT[2];   //    IT               [0,*]
                   //    Track information words for either
                   //    side: bits 0,1 : Track quality; bits
                   //    2,3,4,5: NDF of fit; bits 6...15:
                   //    number of SATR coordinates on side
      float CT[2]; //    CT               [0.0,*]
                   //    Track fit chi squares
      float TT[2]; //    TT               [-100.00,100.00]
                   //    Track thetas (mrad)
      float PT[2]; //    PT               [-180.00,180.00]
                   //    Track phis (deg)
      float XT[2]; //    XT               [-10.00,10.00]
                   //    Track vertex x position at z=0 (cm)
      float YT[2]; //    YT               [-10.00,10.00]
                   //    Track vertex y position at z=0 (cm)
      float E1[2]; //    E1               [0.0,1.000]
                   //    Energy fraction in stack 1
      float E2[2]; //    E2               [0.0,1.000]
                   //    Energy fraction in stack 2
      float XL[2]; //    XL               [-60.00,60.00]
                   //    Cluster x local positions (cm)
      float YL[2]; //    YL               [-60.00,60.00]
                   //    Cluster y local positions (cm)
      int AI[2];   //    AI               [0,3000]
                   //    Address of LCAL intersection tower of
                   //    highest triplets
      float ES[2]; //    ES               [0.0,300.00]
                   //    Energies of second most energetic
                   //    cluster on either side (GeV); side 1 =
                   //    side with tight fiducial cut, 2 = other
                   //    side
      float XS[2]; //    XS               [-60.00,60.00]
                   //    Second highest cluster x local
                   //    positions (cm)
      float YS[2]; //    YS               [-60.00,60.00]
                   //    Second highest cluster y local
                   //    positions (cm)
      int AS[2];   //    AS               [0,3000]
                   //    Address of LCAL intersection tower of
                   //    highest triplets for second highest
                   //    cluster
};
/*----------------------------------------------------------------------------*/
class SILH_PATTERN //    Sical Luminosity parameter
{
public:
      int GB;      //    GBxcnt           [0,*]
                   //    GBX counter
      int HV;      //    HVolt            [*,*]
                   //    HV bit pattern
      int T1;      //    Trlvl1           [*,*]
                   //    Level 1 trigger bit pattern
      int T2;      //    Trlvl2           [*,*]
                   //    Level 2 trigger bit pattern
      int TE;      //    TEnabl           [*,*]
                   //    Trigger enable bit pattern
      int LO;      //    LOlewd           [*,*]
                   //    LOLE information word
      int S2;      //    Six2wd           [*,*]
                   //    SIX2 trigger word
      int DW[3];   //    DoWnsc           [*,*]
                   //    Down scale factors for the 3 triggers
      int SC[3];   //    SCaler           [0,*]
                   //    on line scalers for the 3 triggers
      int AM;      //    AccMeth          [*,*]
                   //    Acceptance Method bit pattern
      int WI;      //    WagonIdent       [0,*]
                   //    Wagon Identifier
};
/*----------------------------------------------------------------------------*/
class XHVB_PATTERN //    Modifications to HV bit status
{
public:
      int RU;      //    RUnnumber        [2001,*]
                   //    Run number affected
      int FE;      //    FirstEvt         [1,*]
                   //    First event affected
      int LE;      //    LastEvt          [1,*]
                   //    Last event affected
      int HV;      //    HVstatus         [0,1]
                   //    HV status to be set 1=ON,0=Off
      int DE;      //    DEtector         [1,24]
                   //    Detector/item affected
                   //    1= ECAL End A
                   //    2= ECAL End B
                   //    3= ECAL Barrel
                   //    4= LCAL
                   //    5= TPC dE/dx
                   //    6= ITC
                   //    7= SATR
                   //    8= HCAL End A
                   //    9= HCAL End B
                   //    10= HCAL Barrel
                   //    11= SCAL
                   //    12= BCAL
                   //    13= VDET
                   //    14= Trigger Analog Crates
                   //    15= Trigger Camac Crates
                   //    16= TPC
                   //    17-23= not attributed
                   //    24 = Beam pick up
};
/*----------------------------------------------------------------------------*/
class XTEB_PATTERN //     Trigger level 1 + 2 Event Bit pattern
{
public:
      int T1;      //    Tbitlvl1
                   //    Trigger bit pattern at time of level 1
                   //    decision
                   //    The assignment of the different trigger
                   //    bits may be subject to changes. The
                   //    actual definition can be found by
                   //    decoding bank XTBN in the start of run
                   //    records.
      int T2;      //    Tbitlvl2
                   //    Trigger bit pattern at time of level
                   //    two decision. The definition of the
                   //    bits is the same as for the Tbitlvl1
                   //    pattern.
      int L2;      //    Lvl2Bits
                   //    Level 2 trigger bit pattern after
                   //    application of the trigger mask. This
                   //    is the final trigger bit pattern which
                   //    is send to the trigger supervisor and
                   //    distributed on the level 2 broadcast.
                   //    The definition of the bits is the same
                   //    as above.
      int HT[12];  //    HcTrb
                   //    Fastbus register bit pattern from
                   //    discriminators on HCAL tower signals,
                   //    one bit for each of the 72 trigger
                   //    segments.
                   //    word 1- 3 bits (1:72) threshold 1
                   //    word 4- 6 bits (1:72) threshold 2
                   //    word 7- 9 bits (1:72) threshold 3
                   //    word 10-12 bits (1:72) threshold 4
      int HW[12];  //    HcWrb
                   //    Fastbus register bit pattern from
                   //    discriminators on HCAL wire signals.
                   //    Definition of the 12 words is the same
                   //    as for HcTrb.
      int LW[12];  //    LcWrb
                   //    Fastbus register bit pattern from
                   //    discriminators on LCAL wire signals
                   //    The first four words contain the bit
                   //    pattern from the LCW register. For each
                   //    threshold there are 8 bits for the
                   //    discriminated sum from the odd and even
                   //    planes of the four LCAL modules. The
                   //    fifth word contains the total energy
                   //    bits from the four thresholds. The
                   //    significance of the bits is : bit 0 :
                   //    Wire energy sum side A,
                   //    bit 1 : Wire energy sum side B,
                   //    bit 3 : unused,
                   //    bit 4 : Total wire energy sum.
                   //    This sequence is repeated for the four
                   //    the four thresholds. The remaining
                   //    words are empty, this is a temporary
                   //    measure, this bank will be revised in
                   //    the future.
      int EW[12];  //    EcWrb
                   //    Fastbus register bit pattern from
                   //    discriminators on ECAL wire signals
                   //    The 72 bits from the different
                   //    thresholds correspond to the 36 wire
                   //    modules, where each module is
                   //    discriminated on signals from odd and
                   //    even planes separately. The sequence is
                   //    odd,even,odd .... planes.
      int LT[4];   //    LcTrb
                   //    Fastbus register bit pattern from
                   //    discriminators on LCAL tower signals
                   //    4*24 bits from four different
                   //    thresholds one word for each threshold.
      int TE[2];   //    ToErb
                   //    Fastbus register bit pattern from
                   //    discriminators on total energy sums,
                   //    one 16 bit word for each total energy
                   //    signal type.
                   //    Bits 0 - 11: 3*4 bit for HCT endcap A,
                   //    endcap B, barrel, total ; thresholds
                   //    1-3.
                   //    Bits 16 - 27: 3*4 bit for LCW total sum
                   //    odd,
                   //    total sum even, empty, empty;
                   //    thresholds 1-3.
                   //    Bits 32 - 43: 3*4 bit for ECW odd
                   //    endcap A,
                   //    endcap B, barrel, total ; thresholds
                   //    1-3.
                   //    Bits 48 - 59: 3*4 bit for ECW even
                   //    endcap A,
                   //    endcap B, barrel, total ; thresholds
                   //    1-3.
                   //    Remark:
                   //    For the time beeing the 4. threshold is
                   //    not
                   //    available due to hardware reasons.
      int IT[4];   //    ITcrb
                   //    Fastbus register bit pattern from ITC
                   //    track mask and special bits. bytes 1-9:
                   //    track mask string of 72 contigous bits;
                   //    note that the ITC delivers only 60 bits
                   //    (central or already done), therefore
                   //    the bits 37-48 are dummy and are always
                   //    0;
                   //    Word 4: special bits.
                   //    Bits 0-7 : Veto Bits; Bits 8-12 : Track
                   //    count.
      int TP[4];   //    TPcrb
                   //    Fastbus register bit pattern from TPC
                   //    track mask and special bits. bytes 1-9:
                   //    track mask string of 72 contigous bits;
                   //    note that the TPC delivers only 60 bits
                   //    (central or already done), therefore
                   //    the bits 37-48 are dummy and are always
                   //    0;
                   //    Word 4: special bits.
                   //    Bits 0-3 : Track count inner sectors;
                   //    Bits 4-7 : Track count outer sectors.
};
/*----------------------------------------------------------------------------*/
class XTRB_PATTERN //    Trigger level 1 + 2 Register Bit pattern
{
public:
      int RP[3];    //   RegPat
                    //   Bit pattern of 72 contiguous bits from
                    //   the readout of one register. The
                    //   definition of the pattern depends on
                    //   the
                    //   trigger source. Bits set to 1 if
                    //   threshold in the corresponding trigger
                    //   segment is exceeded
      int RN;       //   RegNam           [TRB1,TRB1]...
                    //   Name of the bit pattern.
                    //   TRB1 = Trigger bits (trigger mask
                    //   register).
                    //   Word 1: Level 1 decision, Word 2: Level
                    //   2 decision, Word 3: final trigger
                    //   decision)
                    //   HCW1 = Hcal Wires threshold 1. 24
                    //   modules mapped to 72 trigger segments
                    //   HCW2,HCW3,HCW4 same as HCW1 but for
                    //   thresholds 2,3 and 4. ECW1 = Ecal Wires
                    //   information for threshold 1.
                    //   Bit pattern of the odd/even planes of
                    //   ECAL ECW2,ECW3,ECW4 same as ECW1 but
                    //   for threshold 2,3 and 4. LCT1 = LCAL
                    //   tower bit pattern of supersegments.
                    //   Word 1 bits 0-23 are filled
                    //   Word 2 and 3 are empty.
                    //   LCT2,LCT3,LCT4 same as LCT1 but for
                    //   thresholds 2,3 and 4., LCW1 = Lcal
                    //   Wires pattern for threshold 1. The
                    //   even/odd bits pairs 0/1,2/3,6/7,8/9
                    //   correspond to energy sum of odd/even
                    //   planes of modules 1,2,3,4
                    //   Word 2 and 3 are empty.
                    //   LCW2,LCW3,LCW4 same as LCW1 but for
                    //   thresholds 2,3 and 4. ETT1 = TOTAL
                    //   ENERGY: Bit 0-3 of word 1 correspond to
                    //   the total energies deposited in HCT
                    //   (Endcap A,endcap B,barrel,total).
                    //   Bit 16-19 of word 1 equivalent info for
                    //   ECT
                    //   Bit 0- 3 of word 2 equivalent info for
};
/*----------------------------------------------------------------------------*/
class DTBP_PATTERN //    Trigger Bit Pattern
{
public:
      int T1;      //    Trig1            [*,*]
                   //    Level 1 Bit Pattern - see XTEB
      int T2;      //    Trig2            [*,*]
                   //    Level 2 Bit Pattern - see XTEB
      int L2;      //    Level2           [*,*]
                   //    Level 2 Bit Pattern after mask - see
                   //    XTEB
};
/*----------------------------------------------------------------------------*/
class VHBV_PATTERN //    Bit number to use in different run ranges for VDET HV bit
{
public:
      int BN;      //    BitNumber        [0,31]
                   //    HV bit number to use
      int FR;      //    FirstR           [0,9999999]
                   //    First run of this bit
      int LR;      //    LastR            [0,9999999]
                   //    Last run of this bit
};
/*----------------------------------------------------------------------------*/
class VHPV_PATTERN //    Run periods when the HV bit was unreliable
{
public:
      int FR;      //    FirstRun         [0,9999999]
                   //    First run of unreliable period
      int LR;      //    LastRun          [0,9999999]
                   //    Last run of unreliable period
};
/*----------------------------------------------------------------------------*/
class EAUX_PATTERN //    Information from ENFLW
{
public:
      int TR;      //    TR               [0,*]
                   //    Trigger information
      int CA;      //    CA               [0,*]
                   //    Number of ECAL/HCAL objects
      int HV;      //    HV               [0,1]
                   //    HV status of the calorimeters
      float HE;    //    HE               [0.0,*]
                   //    HCAL energy validated by ENFLW
      float HK;    //    HK               [0.0,*]
                   //    HCAL fake energy, thus killed
      float E2;    //    E2               [0.0,*]
                   //    Energy measured below 12 degrees
};
/*----------------------------------------------------------------------------*/
class SIX2_PATTERN //    SIcal Trigger X2
{
public:
      int TW;      //    TriggerWord
                   //    Trigger Word
                   //    (bit 0 = A_high_B_low
                   //    bit 1 = A_low_B_high
                   //    bit 2 = A_very_high
                   //    bit 3 = B_very_high
                   //    bit 4 = A_very_low
                   //    bit 5 = B_very_low,
                   //    bit 6-9 = End-A odd thresh 1-4
                   //    bit 10-13 = End-A even thresh 1-4
                   //    bit 14-17 = End-B odd thresh 1-4
                   //    bit 18-21 = End-B even thresh 1-4
                   //    bit 22 = A_very_high_B_low
                   //    bit 23 = B_very_high_A_low
                   //    bits 24-31 reserved
};
/*----------------------------------------------------------------------------*/
class X1TV_PATTERN //    Trigger level 1 Threshold values
{
public:
      char TT[4];  //    ThrType
                   //    Threshold type name.
      int TV[4];   //    ThrVal           [0,*]
                   //    4 thresholds per threshold type HCWI :
                   //    Number of double planes ECEC :
                   //    Threshold (MeV) ECBA : Threshold (MeV)
                   //    ETEC : Threshold (MeV) ETBA : Threshold
                   //    (MeV) LCEC : Threshold (MeV)
};
/*----------------------------------------------------------------------------*/
class KWGT_PATTERN //    Kingal event partial WeiGhTs (NR=0)
{
public:

      int WN;      //    Weight number
      float WV;    //    Weight value
};
/*----------------------------------------------------------------------------*/
class X1IP_PATTERN //    Trigger level 1 Input for Physics triggers
{
public:
      char IT[4];  //    InpType          [HCW,HCW]...
                   //    Trigger input source name.
      int CO[36];  //    Cont
                   //    the content depends on the trigger
                   //    source. HCW : Number of double planes
                   //    (2 per word) ECW : Energy (MeV) (2 per
                   //    word) MISC: LC-Wires (8 words) + :
                   //    Ec-Wires total energy (8 words) + : ITC
                   //    bits (4 words)
};
/*----------------------------------------------------------------------------*/
class SIXA_PATTERN //    SIcal Trigger sectors Adc
{
public:
      int AO;      //    AdcOddlayers
                   //    Trigger ADC value, odd layers
                   //    bit 0-15 road 1, bit 16-31 road 2
      int AE;      //    AdcEvenlayers
                   //    Trigger ADC value, even layers
                   //    bit 0-15 road 1, bit 16-31 road 2
};
/*----------------------------------------------------------------------------*/
class SITC_PATTERN //    SIcal Trigger Conditions
{
public:
      int TT;      //    TrigThresh       [0,*]
                   //    Trigger threshhold word
                   //    bit 0-7 very low
                   //    bit 8-15 low
                   //    bit 16-23 high
                   //    bit 24-31 very high
      int DO;      //    DisabledOddsect  [0,*]
                   //    Disabled sector word odd layers
                   //    bit 0-15 =road 1
                   //    bit 16-31=road 2
      int DE;      //    DisabledEvensect [0,*]
                   //    Disabled sector word even layers
                   //    bit 0-15 =road 1
                   //    bit 16-31=road 2
};
/*----------------------------------------------------------------------------*/
class SRCO_PATTERN //    Sical Run COnditions
{
public:
      char NA[4];  //    conditionNAme
                   //    Condition key name
      int VA;      //    conditionVAlue   [*,*]
                   //    Value for key condition
};
/*----------------------------------------------------------------------------*/
class X1TH_PATTERN //    Trigger level 1 thresholds
{
public:
      int ID;      //    ID
      int VR[2];   //    ValRng           [0,99999999]
                   //    Validity range
      char TT[4];  //    ThrType
                   //    Type of threshold
                   //    ECTR = EcTowerEnergy
                   //    ECWI = EcWireEnergy
                   //    HCTR = HcTowerEnergy
                   //    HCWI = HcWire
                   //    LCTR = LcTowerEnergy
                   //    ECTT = EcTotalTowerEnergy
                   //    ECTW = EcTotalWireEnergy
                   //    HCTT = HcTotalTowerEnergy
      int TV[4];   //    ThrVal           [0,99999]
                   //    Threshold Values
};
/*----------------------------------------------------------------------------*/
class X1AD_PATTERN //    Trigger level 1 ADc values
{
public:
      char IT[4];  //    InpType          [HCT,HCT]...
                   //    Trigger input source name. The sequence
                   //    of the sources depends on the running
                   //    conditions.
      int AV[36];  //    AdcVal
                   //    72 ADC values from analog signal
                   //    digitizings. The mapping of the 72
                   //    signals is the same as for the
                   //    corresponding fastbus register bit
                   //    pattern (see desc. of XTRB). The values
                   //    of the ADC (12 bits) readings are
                   //    written into an array 16 bit words.
};
/*----------------------------------------------------------------------------*/
#endif
