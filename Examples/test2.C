/////////////////////////////////////////////////////////////////////
//
// Author : C. Delaere
//
// Date: 2001-08-27
//
/////////////////////////////////////////////////////////////////////


#include <fstream>
#include "AlephExManager.h"
#include "AlephCollection.h"
#include <vector>

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

void AlephExManager::UserInit() {}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

float QQRADP = 57.29577951; // rad -> deg conversion
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
// get vectors of pointers to the objects used in the analysis
  AlephCollection<AlTrack *> altp =EventInfo.TrackPV();
  AlephCollection<AlMuon  *> almup=EventInfo.MuonPV();
  AlephCollection<AlElec  *> alelp=EventInfo.ElecPV();
  AlephCollection<AlEflw  *> alefp=EventInfo.EflwPV();
// get general event information
  float QELEP = EventInfo.Event().Energy();
// Good quality charged Tracks selection
  int Nchsel=0;
  for (AlephCollection<AlTrack *>::iterator Ich=altp.begin(); Ich<altp.end(); Ich++)
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
      else Nchsel++;
    }
// Don't consider events without Eflows, or without enough good tracks
  if (alefp.size()<2) return 0;
  if (altp.size()<2) return 0;
  
// Initialize leptons loops
  //generate raw taus candidates
  AlephCollection<AlTau> JJ = alefp.ATauJn(theCardsReader()->TAIDcuts(),QELEP);
  AlephCollection<AlTau*> altaup = JJ.Pointers();

  //filter muons
  almup.FilterMu(theCardsReader()->MUIDcuts());
  cout << " found " << almup.size() << " muon(s)" << endl;
  
  //filter electrons
  alelp.FilterEl(almup,theCardsReader()->ELIDcuts());
  cout << " found " << alelp.size() << " eletron(s)" << endl;

  //filter taus and select the most energetic one
  altaup.FilterTau(theCardsReader()->TAIDcuts());
  QvecBase::SortCriterium = 0;
  sort(altaup.begin(),altaup.end(),order());
  AlTau* seltau = NULL;
  if(altaup.size()!=0 ) seltau = *(altaup.end()-1);
  cerr << " found " << altaup.size() << " tau(s)" << endl;

// Compute acoplanarity and acolinearity
//     ( Make 2 jets using Durham PE for a fixed number of jet,
//       enter a negative values of Ycut = -number of jets!    )
  int jetr;
  float Ycut = -2.;// force 2 jets
  int scheme = 1;  // E-scheme
  AlephCollection<AlJet> Jn = alefp.DurhamJet(Ycut, scheme, 0);
  jetr = Jn.size();
  float acopl=180.;
  float acolin=90.;
  if(jetr == 2)
    {
      acopl= acos(min(max(cos(Jn[0].QPH()-Jn[1].QPH()),-1.),1.))*QQRADP;
      acolin= acos(min(max(Jn[1].QCOSA(Jn[0]),(float)-1.),(float)1.))*QQRADP;
    }
  cout << "acoplanarity/acolinearity with tau    are: " << acopl << "  " << acolin << endl;
  
// If there is a tau, compute acoplww acolww without the tau
  float acoplww = 180.;
  float acolww  = 90.;
  AlephCollection<AlJet> Jn3;
  if(altaup.size())
    {
      // lock all tracks belonging to the Tau.(use the recursive lock)
      seltau->Lock(1);
      int alefpsize=0;
      for (AlephCollection<AlEflw*>::iterator i = alefp.begin(); i != alefp.end(); i++)
         if (!((*i)->isLocked())) alefpsize++;
      if (alefpsize>1)
        { 
         Ycut = -2;
         scheme = 1;
         Jn3 = alefp.DurhamJet(Ycut, scheme, 0);
         // compute acoplanarity and acolinearity
         if(jetr == 2) 
          {
  	    float acoplww = 180.;
            float acolww  = 90.;
            acoplww= acos(min(max(cos(Jn3[0].QPH()-Jn3[1].QPH()),-1.),1.))*QQRADP;
            acolww= acos(min(max(Jn3[1].QCOSA(Jn3[0]),(float)-1),(float)1))*QQRADP;
  	    cout << "acoplanarity/acolinearity without tau are: " << acoplww << "  " << acolww << endl;
          }
       }
       seltau->unLock(1);
    }
  return true;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  User Term
///////////////////////////////////////////////////////////////////////
void AlephExManager::UserTerm() {}
