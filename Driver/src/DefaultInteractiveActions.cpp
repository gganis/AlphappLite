#include "DefaultInteractiveActions.h"

extern ofstream fout;
float  max(float  i, float j)  { return i > j ? i : j; }
float  max(double i, float j)  { return i > j ? i : j; }
double max(double i, double j) { return i > j ? i : j; }
float  min(float  i, float j)  { return i < j ? i : j; }
float  min(double i, float j)  { return i < j ? i : j; }
double min(double i, double j) { return i < j ? i : j; }
float  max(float  i, double j) { return i > j ? i : j; }
float  min(float  i, double j) { return i < j ? i : j; }


void GeneralEventInfo::Run(vector<float>& options,AlphaBanks& EventInfo)
{
  const float QQRADP=180./M_PI;
  // initialize the run/event related quantities
  AlEvent myevent = EventInfo.Event();
  vector<float> output; 
  output.push_back(1);
  output.push_back(myevent.number());
  SendMessage(Code(),output,"event");
  AlRun myrun = EventInfo.Run();
  output.clear();
  output.push_back(2);
  output.push_back(myrun.number());
  SendMessage(Code(),output,"run");
  // event date/hour
  output.clear();
  output.push_back(3);
  output.push_back(myevent.Time().year);
  output.push_back(myevent.Time().month ? myevent.Time().month : 1);
  output.push_back(myevent.Time().day ? myevent.Time().day : 1);
  output.push_back(myevent.Time().hour);
  output.push_back(myevent.Time().min);
  output.push_back(myevent.Time().sec);
  SendMessage(Code(),output,"Time information");
  // the class word
  output.clear();
  output.push_back(4);
  output.push_back(myevent.EdirClass());
  SendMessage(Code(),output,"EDIR class word");
  // summed quantities
  AlephCollection<AlEflw  *> alefp=EventInfo.EflwPV();
  QvecBase Psum = alefp.GetSum();
  output.clear();
  output.push_back(5);
  output.push_back(Psum.QM());
  output.push_back(Psum.QP());
  SendMessage(Code(),output,"summed quantities");
  // topological quantities
  output.clear();
  output.push_back(6);
  if(alefp.size())
  {
  AlephCollection<AlJet> Jn = alefp.DurhamJet(-2,1,0);
  int jetr = Jn.size();
  float acopl          = Jn.size() == 2 ? acos(min(max(cos(Jn[0].QPH()-Jn[1].QPH()),-1.),1.))*QQRADP     : 180.;
  float acolin         = Jn.size() == 2 ? acos(min(max(Jn[1].QCOSA(Jn[0]),(float)-1.),(float)1.))*QQRADP : 90. ;
  float thethrust      = alefp.AThrust().getThrustValue();
  TVector3 thrustdir   = alefp.AThrust().getThrustDirection();
  float sphericity     = alefp.Sphericity();
  float planarity      = alefp.Planarity();
  float aplanarity     = alefp.Aplanarity();
  output.push_back(acopl);
  output.push_back(acolin);
  output.push_back(thethrust);
  output.push_back(thrustdir.x());
  output.push_back(thrustdir.y());
  output.push_back(thrustdir.z());
  output.push_back(aplanarity);
  output.push_back(planarity);
  output.push_back(sphericity);
  }
  else
  {
   output.push_back(0);
   output.push_back(0);
   output.push_back(0);
   output.push_back(0);
   output.push_back(0);
   output.push_back(0);
   output.push_back(0);
   output.push_back(0);
   output.push_back(0);
  }
  SendMessage(Code(),output,"topological quantities");
}

void CollectTracks::Run(vector<float>& options,AlphaBanks& EventInfo)
{
	AlephCollection<AlTrack *>::iterator Ich;
	AlephCollection<AlEflw  *>::iterator Ief;
	vector<float> output;
	int request = int(options[0]);
	switch(request)
	{
	case 0:
		{
			// do nothing
			output.push_back(0);
			SendMessage(Code(),output,"empty list");
			break;
		}
	case 1:
		{
			AlephCollection<AlTrack *> altp = EventInfo.TrackPV();
			// Good quality charged Tracks selection
			if(options[3])
			{
			  	for (Ich=altp.begin(); Ich<altp.end(); Ich++)
				{
				      int Ntpc = (*Ich)->NT();
				      float costhch = (*Ich)->QCT();
				      float d0 = (*Ich) -> QDB();
				      float z0 = (*Ich) -> QZB();
				      if ((Ntpc<4)||(costhch>0.95)||(d0>2.)||(z0>10.)||(costhch<-.95)||(d0<-2)||(z0<-10))
				          altp.looperase(Ich);     // Erases elements in the altp vector
			        }
			}
			// filter according to energy and costheta
			int counter = 0;
			for (Ich=altp.begin(); Ich<altp.end(); Ich++)
			{
				if(((*Ich)->QE()<options[1])||(fabs((*Ich)->QCT())>options[2]))
					altp.looperase(Ich);     // Erases elements in the altp vector
				else
					counter++;
			}
			// send the tracks
			if (counter==0) 
			{
				output.push_back(0);
				SendMessage(Code(),output,"empty list");
			}
			for (Ich=altp.begin(); Ich<altp.end(); Ich++)
			{
				output.clear();
				output.push_back(--counter);
				output.push_back((*Ich)->QE());
				output.push_back((*Ich)->QX());
				output.push_back((*Ich)->QY());
				output.push_back((*Ich)->QZ());
				output.push_back((*Ich)->QCH());
				SendMessage(Code(),output,"track");
			}
			break;
		}
	case 2:
		{
  			AlephCollection<AlEflw  *> alefp=EventInfo.EflwPV();
			// filter according to energy and costheta
			int counter = 0;
			for (Ief=alefp.begin(); Ief<alefp.end(); Ief++)
			{
				if(((*Ief)->QE()<options[1])||(fabs((*Ief)->QCT())>options[2]))
					alefp.looperase(Ief);     // Erases elements in the altp vector
				else
					counter++;
			}
			// send the tracks
			if (counter==0) 
			{
				output.push_back(0);
				SendMessage(Code(),output,"empty list");
			}
			for (Ief=alefp.begin(); Ief<alefp.end(); Ief++)
			{
				output.clear();
				output.push_back(--counter);
				output.push_back((*Ief)->QE());
				output.push_back((*Ief)->QX());
				output.push_back((*Ief)->QY());
				output.push_back((*Ief)->QZ());
				output.push_back((*Ief)->QCH());
				SendMessage(Code(),output,"Energy Flow");
			}
			break;
		}
	default:
		{
			// error, ignore.
		}
	}
}

void CollectLeptons::Run(vector<float>& options,AlphaBanks& EventInfo)
{
	if(options[0]==0)
	{
		vector<float> output;
		output.push_back(0);
		SendMessage(Code(),output,"no lepton");
		return;
	}
	AlephCollection<AlMuon  *> almup=EventInfo.MuonPV();
	AlephCollection<AlElec  *> alelp=EventInfo.ElecPV();
	AlephCollection<AlEflw  *> alefp=EventInfo.EflwPV();
	AlephCollection<AlTrack *> altp = EventInfo.TrackPV();
	AlephCollection<AlTrack *>::iterator Ich;
	AlephCollection<AlElec   *>::iterator Iel;
	AlephCollection<AlMuon   *>::iterator Imu;
	AlephCollection<AlTau    *>::iterator Itau;
	AlephCardsReader *tcr = &(((AlephIoManager*)AlephIoManager::TheAlephIoManager())->theCardsReader());
	vector<float> output;
	// Good quality charged Tracks selection
  	for (Ich=altp.begin(); Ich<altp.end(); Ich++)
	{
	      int Ntpc = (*Ich)->NT();
	      float costhch = (*Ich)->QCT();
	      float d0 = (*Ich) -> QDB();
	      float z0 = (*Ich) -> QZB();
	      if ((Ntpc<4)||(costhch>0.95)||(d0>2.)||(z0>10.)||(costhch<-.95)||(d0<-2)||(z0<-10))
	          (*Ich)->Lock();     // Erases elements in the altp vector
        }
	int nl = 0; 
	if((int(options[0]))&1)
	{
		// electrons
		alelp.FilterEl(almup,tcr->ELIDcuts());
		nl+=alelp.size();
	}
	if((int(options[0]))&2)
	{
		// muons
		almup.FilterMu(tcr->MUIDcuts());
		nl+=almup.size();
	}
	AlephCollection<AlTau> JJ;
	AlephCollection<AlTau*> altaup;
	if((int(options[0]))&4)
	{
		//taus
		AlEvent myevent = EventInfo.Event();
		float QELEP = myevent.Energy();
		JJ = alefp.ATauJn(tcr->TAIDcuts(),QELEP);
		altaup = JJ.Pointers();
		altaup.FilterTau(tcr->TAIDcuts());
		nl+=altaup.size();
	}
	if(nl==0)
	{
		vector<float> output;
		output.push_back(0);
		SendMessage(Code(),output,"no lepton");
		return;
	}
	if((int(options[0]))&1)
		for (Iel = alelp.begin(); Iel<alelp.end(); Iel++)
		{
			output.clear();
			output.push_back(--nl);
			output.push_back((*Iel)->QE());
			output.push_back((*Iel)->QX());
			output.push_back((*Iel)->QY());
			output.push_back((*Iel)->QZ());
			output.push_back((*Iel)->QCH());
			output.push_back(1);
			SendMessage(Code(),output,"Electron");
		}
	if((int(options[0]))&2)
		for (Imu = almup.begin(); Imu<almup.end(); Imu++)
		{
			output.clear();
			output.push_back(--nl);
			output.push_back((*Imu)->QE());
			output.push_back((*Imu)->QX());
			output.push_back((*Imu)->QY());
			output.push_back((*Imu)->QZ());
			output.push_back((*Imu)->QCH());
			output.push_back(2);
			SendMessage(Code(),output,"Muon");
		}
	if((int(options[0]))&4)
		for (Itau = altaup.begin(); Itau<altaup.end(); Itau++)
		{
			output.clear();
			output.push_back(--nl);
			output.push_back((*Itau)->QE());
			output.push_back((*Itau)->QX());
			output.push_back((*Itau)->QY());
			output.push_back((*Itau)->QZ());
			output.push_back((*Itau)->QCH());
			output.push_back(3);
			SendMessage(Code(),output,"tau");
		}
  	for (Ich=altp.begin(); Ich<altp.end(); Ich++)
	          (*Ich)->unLock();
}

void CollectJets::Run(vector<float>& options,AlphaBanks& EventInfo)
{
	// compute the jets
	AlephCollection<AlEflw  *> alefp=EventInfo.EflwPV();
	float Ycut = options[2];
	int scheme = int(options[1]);
	AlEvent myevent = EventInfo.Event();
	float QELEP = myevent.Energy();
	float energy = options[3]==-1 ? QELEP : options[3];
	AlephCollection<AlJet> Jn = options[0] ? alefp.DurhamJet(Ycut, scheme, energy) : alefp.JadeJet(Ycut, scheme, energy);
	// find the radius and send informations
	vector<float> output;
	int counter = Jn.size();
	for( AlephCollection<AlJet>::iterator jet = Jn.begin();jet<Jn.end();jet++)
	{
		AlephCollection<AlObject*> constituants = jet->getObjects();
		float costhetamin=1;
		for(AlephCollection<AlObject*>::iterator element = constituants.begin(); element<constituants.end();element++)
		{
			float costheta = ((QvecBase*)(*element))->QCOSA(*jet);
			costhetamin = costheta<costhetamin ? costheta : costhetamin;
		}
		output.clear();
		output.push_back(--counter);
		output.push_back(costhetamin);
		output.push_back(jet->QX());
		output.push_back(jet->QY());
		output.push_back(jet->QZ());
		SendMessage(Code(),output,"jet");
	}
}

