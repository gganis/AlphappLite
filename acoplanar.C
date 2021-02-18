/////////////////////////////////////////////////////////////////////
// User analysis routines for acoplanar jets selection
// suited for inv. Higgs and single W selection
//
// Author : C. Delaere
//
// Date: 2000-09-10
// Updated 2001-14-03 : new Ntuple
// Updated 2001-14-08 : new alpha++ version (with vertexing and root)
//
/////////////////////////////////////////////////////////////////////


#include <fstream>
#include "AlephExManager.h"
#include "AlephCollection.h"
#include <vector>
#include <TLorentzVector.h>

extern ofstream fout;

float  max(float  i, float j)  { return i > j ? i : j; }
float  max(double i, float j)  { return i > j ? i : j; }
double max(double i, double j) { return i > j ? i : j; }
float  min(float  i, float j)  { return i < j ? i : j; }
float  min(double i, float j)  { return i < j ? i : j; }
double min(double i, double j) { return i < j ? i : j; }
float  max(float  i, double j) { return i > j ? i : j; }
float  min(float  i, double j) { return i < j ? i : j; }


///////////////////////////////////////////////////////////////////////
//  User Init
///////////////////////////////////////////////////////////////////////

static int Ngood = 0;
static int Ebeam = -1;
static int Nbad = 0;
static float mZ = 91.1882; // RPP2000

void AlephExManager::UserInit()
{
  // book an ntuple
  // this version using AddScalableOutput will not work properly with paw
	int i;
	float f;

	theNtupleWriter()->AddOutput(f,"echf");
	theNtupleWriter()->AddOutput(f,"e12f");
	theNtupleWriter()->AddOutput(f,"qelep");
	theNtupleWriter()->AddOutput(i,4, "run","event","trig","nch");
	theNtupleWriter()->AddOutput(f,2,"econef","ewedgef");
	theNtupleWriter()->AddOutput(f,15,"msumf","esumf","ptsumf","thrust",
					  "spher","plan","aplan",
					  "cthmiss","ptmiss","mmiss","minvis",
					  "acopl","acolin","y12","y23");
	theNtupleWriter()->AddOutput(i,3,"imutag","ieltag","itautag");
	theNtupleWriter()->AddScalableOutput("Pmumax",f,4);
	theNtupleWriter()->AddScalableOutput("Pelmax",f,4);
	theNtupleWriter()->AddScalableOutput("Ptaumax",f,4);
	theNtupleWriter()->AddScalableOutput("Pj1",f,4);
	theNtupleWriter()->AddScalableOutput("Pj2",f,4);
	theNtupleWriter()->AddScalableOutput("Pj1ww",f,4);
	theNtupleWriter()->AddScalableOutput("Pj2ww",f,4);
	theNtupleWriter()->AddOutput(f,8,"msumww","acoplww","acolww","pmaxf",
					 "intjets","mjets","pisol","Egamma");
        theNtupleWriter()->AddOutput(i,3,"nchtjet","lepton","presel");
        theNtupleWriter()->AddScalableOutput("MC_e",f,500);
	theNtupleWriter()->AddScalableOutput("MC_x",f,500);
	theNtupleWriter()->AddScalableOutput("MC_y",f,500);
	theNtupleWriter()->AddScalableOutput("MC_z",f,500);
	theNtupleWriter()->AddScalableOutput("MC_code",i,500);
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

//number of stable charged particles
int nchCount(AlMCtruth* particle) 
{
  int nch=0;
  AlephCollection<AlMCtruth*> daughters = particle->getDaughterVector();
  for(AlephCollection<AlMCtruth*>::iterator daughter = daughters.begin();
                                        daughter < daughters.end();daughter++)
   if( (*daughter)->getDaughterVector().size() != 0)
     nch += nchCount(*daughter);
   else
     nch += (int)fabs((*daughter)->QCH());
  return nch;
}
//number of stable charged particles
TLorentzVector A4VchCount(AlMCtruth* particle)
{
  TLorentzVector Ech;
  AlephCollection<AlMCtruth*> daughters = particle->getDaughterVector();
  for(AlephCollection<AlMCtruth*>::iterator daughter = daughters.begin();
                                        daughter < daughters.end();daughter++)
   if( (*daughter)->getDaughterVector().size() != 0)
     Ech += A4VchCount(*daughter);
   else
     Ech +=(*daughter)->A4V();
  return Ech;
}
// visible part of A4V
TLorentzVector visible(AlMCtruth* particle)
{
  TLorentzVector vis;
  AlephCollection<AlMCtruth*> daughters = particle->getDaughterVector();
  for(AlephCollection<AlMCtruth*>::iterator daughter = daughters.begin();
		                        daughter < daughters.end();daughter++)
   if( (*daughter)->getDaughterVector().size() != 0)
     vis += visible(*daughter);
   else
     if(!(((*daughter)->name()[0]=='n')&&((*daughter)->name()[1]=='u'))) 
      vis+=(*daughter)->A4V();
  return vis;
}
// the first generation of fermions
vector<pair<TLorentzVector, int > > FindFermions(AlephCollection<AlMCtruth*>::iterator obj , int thecode)
{
	vector<pair<TLorentzVector, int > > TheResult;
	if(((*obj)->PA()==41)||((*obj)->PA()==42)||((*obj)->PA()==43)||((*obj)->PA()==44)||((*obj)->PA()==54))
	{
		thecode = (*obj)->PA()*1000;
		AlephCollection<AlMCtruth*> daughters = (*obj)->getDaughterVector();
		for(AlephCollection<AlMCtruth*>::iterator MCpart=daughters.begin();
				MCpart<daughters.end();MCpart++)
		{
			int thenewcode= thecode+(*MCpart)->PA();
			vector<pair<TLorentzVector, int > > toappend = FindFermions(MCpart,thenewcode);
			for(vector<pair<TLorentzVector, int > >::iterator appender=toappend.begin();
					appender<toappend.end();appender++)
				TheResult.push_back(*appender);
		}
	}
	else 
	{
		pair<TLorentzVector, int > thisOne( (*obj)->A4V(), thecode);
		TheResult.push_back(thisOne);
	}
	return TheResult;
}
// a functor to sort collections of pointors
struct order
{
	bool operator()(QvecBase* a, QvecBase* b)
	{
		return ((*a) < (*b)) ;
	}
};
///////////////////////////////////////////////////////////////////////
//  User Event
///////////////////////////////////////////////////////////////////////
bool AlephExManager::UserEvent(AlphaBanks& EventInfo)
{
// some definitions
  typedef AlephCollection<AlObject *>::iterator ObI;
  typedef AlephCollection<AlTrack  *>::iterator TI;
  typedef AlephCollection<AlMuon   *>::iterator MuI;
  typedef AlephCollection<AlElec   *>::iterator ElI;
  typedef AlephCollection<AlEflw   *>::iterator FlI;
  typedef AlephCollection<AlTau    *>::iterator TauI;
  float QQRADP=180./M_PI;
  float QELEP;
  TI  Ich;
  MuI Imu;
  ElI Iel;
  FlI Ifl;
// initialize the run/event related quantities
  AlRun myrun = EventInfo.Run();
  AlEvent myevent = EventInfo.Event();
  QELEP = myevent.Energy();
  if (QELEP<=0)
    {
      cerr << "ERROR: QELEP <= 0" << endl;
      return false;
    }
// Select event according to class
  if (!((myevent.EdirClass())&(1<<15))) return false; // class 16
// Select event according to trigger/luminosity
  int rawtrigger = myevent.GetRawTrigger();
  if (!myevent.xlumok(QELEP)) 
    {
      cout << "Event " << myevent.number() << " : Bad Luminosity." << endl;
      return false;
    }
  int trig_opt = 1;
  typedef vector<double> Tvector;
  typedef pair<String,Tvector> element;
  vector<element> _UserCards = theCardsReader()->getUserCards();
  for( vector<element>::const_iterator cardlookup=_UserCards.begin(); cardlookup<_UserCards.end();cardlookup++)
    if (cardlookup->first==string("POT")) trig_opt = 0;

  if (!myevent.IsTrigger(trig_opt)) 
    {
      cout << "Event " << myevent.number() << " : Bad Trigger. ";
      cout << "Trigger word is " << rawtrigger << endl;
      return false;
    }
// get vectors of pointers to the objects used in MC analysis
  AlephCollection<AlMCtruth*> MCparticles = EventInfo.MCtruthPV();
// get vectors of pointers to the objects used in the analysis
  // vectors directly obtained from AlphaBank
  AlephCollection<AlTrack *> altp =EventInfo.TrackPV();
  AlephCollection<AlMuon  *> almup=EventInfo.MuonPV();
  AlephCollection<AlElec  *> alelp=EventInfo.ElecPV();
  AlephCollection<AlEflw  *> alefp=EventInfo.EflwPV();
// Good quality charged Tracks selection
  int Nchsel=0;
  float Echsel=0.;
  for (Ich=altp.begin(); Ich<altp.end(); Ich++)
    {
      int Ntpc = (*Ich)->NT();
      float costhch = (*Ich)->QCT();
      float d0 = (*Ich) -> QDB();
      float z0 = (*Ich) -> QZB();

      if ((Ntpc<4)||(costhch>0.95)||(d0>2.)||(z0>10.)
          ||(costhch<-.95)||(d0<-2)||(z0<-10))
        {
          (*Ich)->Lock();          // Lock the tracks (for leptons algos)
          altp.looperase(Ich);     // Erases elements in the altp vector
        }
      else
	{
          Nchsel++;
          Echsel += (*Ich)->QE();
        }
    }

// now select the event according to the good charged tracks
  if ((Nchsel >= 3) && (Echsel >= 2.)) Ngood++;
  else return false;
  if ( myevent.ErrorStatus() != 1) return false;
  if ( alefp.size()==0 ) return false;
// compute some topological quantities
  QvecBase Psum = alefp.GetSum();
  float esum  = Psum.QE();
  float ptsum = Psum.QPT();
  float psum  = Psum.QP();
  float msum  = Psum.QM();
  QvecBase Pmiss = alefp.GetMiss(QELEP);
  float cthmiss=Pmiss.QCT();
  float mmiss=Pmiss.QM();
  float pmiss=Pmiss.QP();
  float minvis=pow(pow((double)QELEP-(mZ*esum/msum),(double)2.)-pow((double)mZ*pmiss/mmiss,(double)2.),(double).5);
  float thethrust  = alefp.AThrust().getThrustValue();
  float sphericity = alefp.Sphericity();
  float planarity  = alefp.Planarity();
  float aplanarity = alefp.Aplanarity();
  // preselection cuts
  if((Pmiss.QPT()<=0) ||(fabs(Pmiss.QCT())>.95)  ||(msum<5)) return false;
  // wedge energy in 30 degree
  float ewedge=0;
  if (Pmiss.QP() >0)
    {
      for(Ifl = alefp.begin(); Ifl < alefp.end(); Ifl++)
         if((acos(min(max(cos(Pmiss.QPH()-((*Ifl)->QPH())),-1.),1.)))*QQRADP<30)
           ewedge+= (*Ifl)->QE();
    }
  else
    return false;
  // preselection cuts
  if ((ewedge>(.2*QELEP))&&(Pmiss.QPT()<(.02*QELEP))) return false;
  //energy in 12 deg cone centred aound beam pipe
  float e12_av=0;
  float econe =0;
  const float c12=0.9781476;
  for(Ifl = alefp.begin(); Ifl < alefp.end(); Ifl++)
    {
      int type = (*Ifl)->getEfType();
      float costheta = fabs((*Ifl)->QCT());
      const double c12=0.9781476;
      float nint=(*Ifl)->QCH();
      if((type == 7) || (type == 8) || ((nint ==0) && (costheta> c12)))
        e12_av += (*Ifl)->QE();
      if(costheta > c12)
        econe += (*Ifl)-> QE();
    }
  if(myrun.number()<4000) e12_av += myevent.gen_e12(QELEP);

// Initialize leptons loops
  //generate raw taus candidates
  AlephCollection<AlTau> JJ = alefp.ATauJn(theCardsReader()->TAIDcuts(),QELEP);
  AlephCollection<AlTau*> altaup = JJ.Pointers();

  //filter muons
  almup.FilterMu(theCardsReader()->MUIDcuts());
  sort(almup.begin(),almup.end(),order());

  //filter electrons
  alelp.FilterEl(almup,theCardsReader()->ELIDcuts());
  sort(alelp.begin(),alelp.end(),order());

  //filter taus
  altaup.FilterTau(theCardsReader()->TAIDcuts());
  // compute max leptonic momentum
  vector<float> pmax(2);
  pmax[0] = (almup.size()  ? almup[almup.size()-1]->QP()   : 0.);
  pmax[1] = (alelp.size()  ? alelp[alelp.size()-1]->QP()   : 0.);
  float plepmax = *max_element(pmax.begin(),pmax.end());
// Select the most anti-parallel (to Pmiss) 
// identified electron or  muon
  int imutag=0;
  int ieltag=0;
  TLorentzVector A4Vmumax;
  TLorentzVector A4Velmax;
  float eelmax=0;
  float cosjmiss;
  AlMuon selmuon;
  AlElec selelec;
  AlTrack* theElTrack;
  AlTrack* theMuTrack;
  float cosjmin=1;
  for (Imu=almup.begin(); Imu<almup.end(); Imu++)
    if(Pmiss.QP() > 0) 
      {
        cosjmiss=(*Imu)->QCOSA(Pmiss);
        if(cosjmiss <= cosjmin)
          {
            cosjmin=cosjmiss;
            A4Vmumax = (*Imu)->A4V();
            selmuon =(**Imu);
            theMuTrack = (*Imu) -> getTrack();
            imutag =1;
          }
      }
  cosjmin=1;
  for (Iel=alelp.begin(); Iel<alelp.end(); Iel++)
    if(Pmiss.QP() > 0) 
      {
	cosjmiss=(*Iel)->QCOSA(Pmiss);
	if(cosjmiss <= cosjmin)
	  {
            cosjmin=cosjmiss;
            A4Velmax = (*Iel)->A4V();
            selelec =(**Iel);
            theElTrack = (*Iel) -> getTrack();
            ieltag =1;
          }
      }
// Select the most anti-parallel (to Pmiss) 
// identified tau with energy > 0.05*ELEP
// Do not select Tau which are already identified as electron or muon...
  int itautag=0;
  TLorentzVector A4Vtaumax;
  AlTau* seltau;
  TauI  Itau;
  cosjmin=1;
  for (Itau=altaup.begin(); Itau<altaup.end(); Itau++)
    {
      int nch=0;
      bool keep=true;
      nch=(*Itau)->getNch();
      if(imutag>0 || ieltag>0)
        for (ObI Ifl=(*Itau)->getObjects().begin();Ifl<(*Itau)->getObjects().end();Ifl++)
          if((((AlEflw*)(*Ifl))->getTrack())==theElTrack || 
             (((AlEflw*)(*Ifl))->getTrack())==theMuTrack) keep=false;
      if(Pmiss.QP()>0 && (keep)) 
        {
          cosjmiss= (*Itau)->QCOSA(Pmiss);
          if(cosjmiss < cosjmin)
            {
              cosjmin=cosjmiss;
              A4Vtaumax = (*Itau)->A4V();
              seltau=(*Itau);
              itautag=nch;
            }
        }
    }

  int alefpsize=0;
  for (AlephCollection<AlEflw*>::iterator i = alefp.begin(); i != alefp.end(); i++)
   if (!((*i)->isLocked())) alefpsize++;
  if (alefpsize<3) return false;

// Compute acoplanarity and acolinearity
//     ( Make 2 jets using Durham PE for a fixed number of jet,
//       enter a negative values of Ycut = -number of jets!    )
  cerr <<  "." ;
  int jetr;
  float Ycut = -2.;// force 2 jets
  int scheme = 1;  // E-scheme
  AlephCollection<AlJet> Jn = alefp.DurhamJet(Ycut, scheme, 0);
  jetr = Jn.size();
  // first set the Sort Criterium ( component of the 4-vector )
  // the default value is 3, so that we may forget this line
  QvecBase::SortCriterium = 3;
  // sort the vector using the component 3 (e) of A4V
  sort(Jn.begin(),Jn.end());
  float acopl=180.;
  float acolin=90.;
  float one=1.;
  if(jetr == 2)
    {
      acopl= acos(min(max(cos(Jn[0].QPH()-Jn[1].QPH()),-1.),1.))*QQRADP;
      acolin= acos(min(max(Jn[1].QCOSA(Jn[0]),-one),one))*QQRADP;
    }
  
  // Final preselection cuts
  bool set1 = ((Pmiss.QPT()<=0) ||(fabs(Pmiss.QCT())>.95)  ||
               (msum<5)         ||(ewedge>(.2*QELEP))      ||(acolin>175));
  bool set2 = ((Pmiss.QPT()<=0) ||(fabs(Pmiss.QCT())>.95)  ||
               (esum>(.9*QELEP))||(Pmiss.QPT()<(.02*QELEP))||(acopl>175));
  if (set1 && set2) return false;
  
  // Calculate Yi variables
  vector<float> Yn = alefp.DurhamYn(scheme,0.);

  // Make 3 jets using Durham PE
  Ycut = -3.;      // force 2 jets
  scheme = 1;      // E-scheme
  AlephCollection<AlJet> Jn2 = alefp.DurhamJet(Ycut, scheme, 0);
  vector<float> interjet(3);
  vector<float> msumjet(3);
  vector<int>   nchtjet(3);
  float interjetmin;
  float msumjetmin;
  float nchtjetmin;
  if (Jn2.size()==3)
    {
      interjet[0] = Jn2[0].QCOSA(Jn2[1]);
      msumjet[0]  = Jn2[0].QM2(Jn2[1]);
      nchtjet[0]  = 0;
      for(ObI iter=Jn2[0].getObjects().begin();iter<Jn2[0].getObjects().end();iter++)
        if (((AlEflw*)(*iter))->getEfType()<=3) nchtjet[0] ++; 
      interjet[1] = Jn2[0].QCOSA(Jn2[2]);
      msumjet[1]  = Jn2[0].QM2(Jn2[2]);
      nchtjet[0]  = 1;
      for(ObI iter=Jn2[1].getObjects().begin();iter<Jn2[1].getObjects().end();iter++)
        if (((AlEflw*)(*iter))->getEfType()<=3) nchtjet[1] ++; 
      interjet[2] = Jn2[1].QCOSA(Jn2[2]);
      msumjet[2]  = Jn2[1].QM2(Jn2[2]);
      nchtjet[2]  = 0;
      for(ObI iter=Jn2[2].getObjects().begin();iter<Jn2[2].getObjects().end();iter++)
        if (((AlEflw*)(*iter))->getEfType()<=3) nchtjet[2] ++; 
      interjetmin = *max_element(interjet.begin(),interjet.end());
      msumjetmin  = *min_element(msumjet.begin(),msumjet.end());
      nchtjetmin  = *min_element(nchtjet.begin(),nchtjet.end());
    }

  // Find the most isolated charged track
  float globalmax=0;
  AlTrack* associated;
  for ( TI track1 = altp.begin(); track1<altp.end(); track1++)
    {
      float localmin = 2;
      for ( TI track2 = altp.begin(); track2<altp.end(); track2++)
        if (track2!=track1)
         {
            float now = (1-(*track2)->QCOSA(**track1));
            localmin = localmin < now ? localmin : now;
         }
      if (globalmax<localmin)
        {
          globalmax = localmin;
          associated = (*track1);
        }
    }
// Check if it is a lepton...
    
  int  lepfound = 0;
  for (MuI mui=almup.begin(); mui<almup.end();mui++)
    lepfound = (*mui)->getTrack()==associated ? 1 : 0;
  if (lepfound==0)
  for (ElI eli=alelp.begin(); eli<alelp.end();eli++)
    lepfound = (*eli)->getTrack()==associated ? 2 : 0;

// If there is a tau, compute msumww acoplww acolww without the tau
  float msumww  = 0.;
  float acoplww = 180.;
  float acolww  = 90.;
  bool validwwjets = false;
  AlephCollection<AlJet> Jn3;
  if(itautag>0)
    {
      // lock all tracks belonging to the Tau.(use the recursive lock)
      seltau->Lock(1);
      // and calculate sumww and acollinww
      int alefpsize=0;
      for (AlephCollection<AlEflw*>::iterator i = alefp.begin(); i != alefp.end(); i++)
         if (!((*i)->isLocked())) alefpsize++;
      if (alefpsize>1)
        { 
         Ycut = -2;
         scheme = 1;
         validwwjets=true;
         Jn3 = alefp.DurhamJet(Ycut, scheme, 0);
         // first set the Sort Criterium ( component of the 4-vector )
         // the default value is 3, so that we may forget this line
         QvecBase::SortCriterium = 3;
         // sort the vector using the component 3 (e) of A4V
         sort(Jn3.begin(),Jn3.end());
         // compute the invariant mass of the 2 jets
         msumww = Jn3[0].QM2(Jn3[1]);
         jetr = Jn3.size();
         // compute acoplanarity and acolinearity
         if(jetr == 2) 
          {
            acoplww= acos(min(max(cos(Jn3[0].QPH()-Jn3[1].QPH()),-1.),1.))*QQRADP;
            acolww= acos(min(max(Jn3[1].QCOSA(Jn3[0]),(float)-1),(float)1))*QQRADP;
          }
       }
      else
       {
         msumww = 0;
         acoplww = 0;
         acolww = 0;
       }
       seltau->unLock(1);
    }
// Compute MC information.
  float Egamma=0;
  vector<float> theFermions_e;
  vector<float> theFermions_x;
  vector<float> theFermions_y;
  vector<float> theFermions_z;
  vector<int> theFermions_c;
  vector<pair<TLorentzVector, int> > theFermions;
  if(myrun.number()<2000)
  {
	// keep only primary particles
	for(AlephCollection<AlMCtruth*>::iterator MCpart=MCparticles.begin();
			MCpart<MCparticles.end();MCpart++)
		if((*MCpart)->NO()!=0) MCparticles.looperase(MCpart);
	// compute energy for gammas, and throw them
	for(AlephCollection<AlMCtruth*>::iterator MCpart=MCparticles.begin();
			MCpart<MCparticles.end();MCpart++)
		if((*MCpart)->PA()==1)
		{
			Egamma+=(*MCpart)->QE();
			MCparticles.looperase(MCpart);
		}
	// now consider the next generations to get a set of fermions
	for(AlephCollection<AlMCtruth*>::iterator MCpart=MCparticles.begin();
			MCpart<MCparticles.end();MCpart++)
	{
		vector<pair<TLorentzVector, int> > toappend = FindFermions(MCpart,(*MCpart)->PA());
		for(vector<pair<TLorentzVector, int> >::iterator appender=toappend.begin();
				appender<toappend.end();appender++)
			theFermions.push_back(*appender);
	}	
	// loop on the resulting vector and create the objects to be stored
	for(vector<pair<TLorentzVector, int> >::iterator resel=theFermions.begin();
			resel<theFermions.end();resel++)
	{
		theFermions_e.push_back((*resel).first.E());
		theFermions_x.push_back((*resel).first.X());
		theFermions_y.push_back((*resel).first.Y());
		theFermions_z.push_back((*resel).first.Z());
		theFermions_c.push_back((*resel).second);
	}
		
  }

// normalize parameters
  Echsel  /= QELEP;
  e12_av  /= QELEP;
  econe   /= QELEP;
  ewedge  /= QELEP;
  psum    /= QELEP;
  msum    /= QELEP;
  ptsum   /= QELEP;
  esum    /= QELEP;
  plepmax /= QELEP;

// Ntuple variable initialization
  int nvars = 90;
  float* myvars = new float[nvars];
  for (int i=0;i<nvars; i++) myvars[i]=0.;

// Prepare output...
#define Keep theNtupleWriter()->Keep
#define KeepV theNtupleWriter()->KeepV
  Keep("run", myrun.number());      //run number
  Keep("event", myevent.number());  //event number
  Keep("trig", rawtrigger);         //raw trigger word
  Keep("nch", Nchsel);              //nch
  Keep("echf", Echsel);             //ech
  Keep("qelep", QELEP);             //LEP energy
  Keep("e12f", e12_av);             //forward E
  Keep("econef", econe);            //E in 12deg cone
  Keep("ewedgef", ewedge);          //wedge Energy
  Keep("msumf", msum);              //invariant mass
  Keep("esumf", esum);              //invariant E
  Keep("ptsumf", ptsum);            //invariant Pt
  Keep("thrust", thethrust);        //thrust value
  Keep("spher", sphericity);        //sphericity
  Keep("plan", planarity);          //planarity
  Keep("aplan", aplanarity);        //aplanarity
  Keep("cthmiss", cthmiss);         //cthmiss
  Keep("ptmiss", Pmiss.QPT()/QELEP);//ptmiss
  Keep("mmiss", Pmiss.QM());        //missing mass
  Keep("minvis", minvis);           //invisible mass (if signal)
  Keep("acopl", acopl);             //acoplanarity
  Keep("acolin", acolin);           //acolinearity
  Keep("y12", Yn[0]);               //y12
  Keep("y23", Yn[1]);               //y23
  Keep("imutag", imutag);           //muon
  Keep("ieltag", ieltag);           //electron
  Keep("itautag", itautag);         //tau
  Keep("Pmumax", A4Vmumax);         //muon A4V
  Keep("Pelmax", A4Velmax);         //electron A4V
  Keep("Ptaumax", A4Vtaumax);       //tau A4V
  Keep("Pj1", Jn[1].A4V());         // WW jets A4Vs
  Keep("Pj2", Jn[0].A4V());
  float v2[4];
  if (validwwjets)
  {
	  Keep("Pj1ww", Jn[1].A4V());
	  Keep("Pj2ww", Jn[0].A4V());
  }
  else
   {
	  float v[4]={0.};
	  Keep("Pj1ww", v, 4);
	  Keep("Pj2ww", v, 4);
   }
  Keep("msumww", msumww);          //WW invariant mass
  Keep("acoplww", acoplww);        //WW acoplanarity
  Keep("acolww", acolww);          //WW acolinearity
  Keep("pmaxf", plepmax);          //max lep P
  Keep("intjets", interjetmin);    //min interjet cos
  Keep("mjets", msumjetmin);       //min invariant mass of 2 jets
  Keep("nchtjet", nchtjetmin);     //min number of charged tracks in jets
  Keep("pisol", associated->QP()/QELEP);//P of the most isolated track.
  Keep("lepton", lepfound);        //is the most isolated track a lepton
  Keep("Egamma", Egamma);          //energy of initial state radiation
  KeepV("MC_e",theFermions_e);      //energy of the MC fermions
  KeepV("MC_x",theFermions_x);      //Px of the MC fermions
  KeepV("MC_y",theFermions_y);      //Py of the MC fermions
  KeepV("MC_z",theFermions_z);      //Pz of the MC fermions
  KeepV("MC_code",theFermions_c);   //code of the MC fermions
  Keep("presel", ((!set1) + 2*(!set2)));// set of cuts satisfied
  
  // Fill ntuple
  theNtupleWriter()->Fill();
  return true;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
//  User Term
///////////////////////////////////////////////////////////////////////
void AlephExManager::UserTerm()
{
  fout << endl << " USER TERM : Ngood = " << Ngood << endl;
}
