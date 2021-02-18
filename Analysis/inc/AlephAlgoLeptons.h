//////////////////////////////////////////////////////////
//
// Aleph Algos for Leptons:
// Leptons filtering and Tau Production
//
// Author : C. Delaere, V. Lemaitre, O. van der Aa
//
///////////////////////////////////////////////////////////

#include <map>

//! Muons filtering
/*!
 * the arguments in the vector are:
 *   - d0max
 *   - pmin
 *   - minhit
 *   - cosmax
 *   - z0max
 * Filters a collection of AlMuon (muon candidates)
 */
template <class Type> 
void AlephCollection<Type>::FilterMu(vector<float> argus)
{
  float d0max;
  float pmin;
  int minhit;
  float cosmax;
  float z0max;
  if(argus.size()==5)
  {
  	d0max  = argus[0];
  	pmin   = argus[1];
  	minhit   = (int)argus[2];
  	cosmax = argus[3];
  	z0max  = argus[4];
  }
  else
  {
  	d0max  = 0.5;  
  	pmin   = 1.;
  	minhit = 4;
  	cosmax = 0.95;
  	z0max  = 10.;
  }  
  typename AlephCollection<Type>::iterator imu;
  for (imu=begin();imu<end();imu++)
    // ignore locked objects
    if (!((*imu)->isLocked()))
      { 
	// check if the type is correct...
	if ((*imu)->TYPE() != MUON ) 
	  { 
	    cout << "WARNING Not AlMuon: type not supported !" << endl; 
	    exit(1);
	  }
	// good tracks selection
	bool xtrackdp=true;
	if ((*imu)->getTrack()->isLocked())            xtrackdp=false;
	if ((*imu)->QP() < pmin)                       xtrackdp=false;
	if ((*imu)->getTrack()->NT() < minhit)         xtrackdp=false;
	if (fabs((*imu)->QCT()) >= cosmax)             xtrackdp=false;
	if (fabs((*imu)->getTrack()->QZB()) >= z0max)  xtrackdp=false;
	if (fabs((*imu)->getTrack()->QDB()) >= d0max)  xtrackdp=false;
	// final selection
	if ((!xtrackdp) || ((*imu)->IF() <=  0)) (*this).looperase(imu);
      }
}

//!Electrons filtering
/*!
 * the arguments in the vector are:
 *   - d0max
 *   - pmin
 *   - minhit
 *   - cosmax
 *   - z0max
 *   - nwirem
 *   - r3cut
 *   - r2cut0l
 *   - r2cut1l
 *   - r2cut2l
 *   - r2cuth
 *   - r5cutl
 *   - r5cuth
 * In addition, a vector of filtered muons is needed to avoid double-counting
 * 
 * Filters a collection of AlElec (electron candidates)
 */
template <class Type> 
void AlephCollection<Type>::FilterEl( const AlephCollection<AlMuon *>& almup,
                                  vector<float> argus)
{
  float d0max;
  float pmin;
  int minhit;
  float cosmax;
  float z0max;
  int nwirem;
  float r3cut;
  float r2cut0l;
  float r2cut1l;
  float r2cut2l;
  float r2cuth;
  float r5cutl;
  float r5cuth;
  if (argus.size()==13)
  {
  	d0max   = argus[0];
  	pmin    = argus[1];
  	minhit  = (int)argus[2];
  	cosmax  = argus[3];
  	z0max   = argus[4];
  	nwirem  = (int)argus[5];
  	r3cut   = argus[6];
  	r2cut0l = argus[7];
  	r2cut1l = argus[8];
  	r2cut2l = argus[9];
  	r2cuth  = argus[10];
  	r5cutl  = argus[11];
  	r5cuth  = argus[12];
  }
  else
  {
  	d0max   = 0.5;
  	pmin    = 1.;
  	minhit  = 4;
  	cosmax  = 0.95;
  	z0max   = 10.;
  	nwirem  = 40;
  	r3cut   = 1000.;
  	r2cut0l = -3.;
  	r2cut1l = -7.;
  	r2cut2l = -5.;
  	r2cuth  = 1000.;
  	r5cutl  = 0.5;
  	r5cuth  = 1000.;
  }
  // We've to check that the electron candidate is NOT a muon
  // to loop only once, we first fill a map
  // with all the needed information
  map<int,int> tr;    
  for (unsigned int i=0; i < almup.size(); i++)
    if (!((almup[i])->isLocked()))
      tr[(almup[i]->TN())]=i;
  typename AlephCollection<Type>::iterator iel;
  for (iel=begin();iel<end();iel++)
    // ignore locked objects
    if (!((*iel)->isLocked()))
      { 
	// check the type
	if ((*iel)->TYPE() != ELEC)
	  { 
	    cout << "WARNING Not AlElec: type not supported !" << endl; 
	    exit(1);
	  }
	// check track quality
	bool xtrackdp=true;
	if ((*iel)->getTrack()->isLocked())                xtrackdp=false;
	if ((*iel)->QP() < pmin)                           xtrackdp=false;
	if ((*iel)->getTrack()->NT() < minhit)             xtrackdp=false;
	if (fabs((*iel)->QCT()) >= cosmax)                 xtrackdp=false;
	if (fabs((*iel)->getTrack()->QZB()) >= z0max)      xtrackdp=false;
	if (fabs((*iel)->getTrack()->QDB()) >= d0max)      xtrackdp=false;
	// look in the map if it is a muon or not...
	if (tr.find((*iel)->FR())!=tr.end()) xtrackdp=false; 
	// final selection
	if (xtrackdp) 
	  {
	    switch ((*iel)->IF()) 
	      {
	      case -1 :                 // no EIDT information available
		xtrackdp=false;
		break;
	      case 0  :                 // o.k.
		if (((*iel)->R3() >= r3cut)    || 
		    ((*iel)->R2() <= r2cut0l)  ||
		    ((*iel)->R2() >= r2cuth)     )     xtrackdp=false;
		break;
	      case 1  :                 // in a crack
		if ((((*iel)->R3() >= r3cut)   || 
		     ((*iel)->R2() <= r2cut1l) || 
		     ((*iel)->R2() >= r2cuth)) 
		    &&
		    (((*iel)->R5() >= r5cuth)  || 
		     ((*iel)->R5() <= r5cutl)  || 
		     ((*iel)->getTrack()->NSsum() < nwirem)) )  xtrackdp=false;
		break;
	      case 2  :               // in overlap
		if ((((*iel)->R3() >= r3cut)   || 
		     ((*iel)->R2() <= r2cut2l) || 
		     ((*iel)->R2() >= r2cuth)) 
		    &&
		    (((*iel)->R5() >= r5cuth)  || 
		     ((*iel)->R5() <= r5cutl)  || 
		     ((*iel)->getTrack()->NSsum() < nwirem)) )  xtrackdp=false;
		break;
	      }
	  }
	if (!xtrackdp) (*this).looperase(iel); 
      }
}

//! TauJet clustering
/*! Produces a raw set of Tau candidates...
 * I mean Taujets with one or three Eflws
 * at this stage, Ech is the total energy of eflws objects
 *               the Associated track is the track from the last Eflw.
 * be carefull: this track may be NULL
 *
 * arguments in the vector are:
 *  - Ycut
 *  - Scheme
 *  - metric
 */
template <class Type>
AlephCollection<AlTau> AlephCollection<Type>::ATauJn(vector<float> argus, float Qelep) const
{
  float Ycut;
  int Scheme;
  int Metric;
  if((argus.size()==8)||(argus.size()==3))
  {
  	Ycut = argus[0];
  	Scheme = (int)argus[1];
  	Metric = (int)argus[2];
  }
  else
  {
  	Ycut = 0.01;;
  	Scheme = 1;
  	Metric = 1;
  }
  // Check the type of object. MUST be Eflw
  for (typename AlephCollection<Type>::const_iterator i=begin();i<end();i++)
    if ((*i)->TYPE() != EFLOW)
      { 
	cout << "WARNING Not Eflw: type not supported !" << endl; 
	exit(1);
      }
  // make a lot of mini-jets with JADE algorithm (preferably)
  // we don't have to care about the lock problem 'cause the JetAlgo does it
  AlephCollection<AlJet> Jjade;
  if (Metric)
    Jjade = (*this).JadeJet(Ycut, Scheme, Qelep);
  else
    Jjade = (*this).DurhamJet(Ycut, Scheme, Qelep);
  AlephCollection<AlTau> P;
  int jetn = Jjade.size();
  // loop on the candidates
  for (int ijet = 0; ijet<jetn; ijet++)
    {
      typedef AlephCollection<AlObject*>::iterator ObI;
      AlEflw* theAssEflw = NULL;
      float Echgood=0.;
      int tn=0;
      // loop on objects in the taujet, record #tracks and total E
      for (ObI ifl=Jjade[ijet].getObjects().begin();
	   ifl<Jjade[ijet].getObjects().end();
	   ifl++)
	if (((AlEflw*)(*ifl))->getEfType()<=3)
	  {
	    theAssEflw = ((AlEflw*)(*ifl));
	    tn++;
	    Echgood+=(((AlEflw*)(*ifl))->QE());
	  }
      // check number of objects and save the result
      if ((tn == 1) || (tn == 3))
	{
	  AlTau tmp = Jjade[ijet];
	  tmp.setNch(tn);
	  tmp.setEch(Echgood);
	  tmp.setEflw(theAssEflw);
	  P.push_back(tmp);
	}
      }
  return P;
}

//! Tau filtering
/*! analyse a vector of pointers to AlTau objects
 * apply standard cuts
 * Ech is the energy of charged tracks
 * The associated track is the most energetic one, with the same sign
 *
 * the arguments in the vector are:
 *   - psummin
 *   - d0max
 *   - minhit
 *   - cosmax
 *   - z0max
 */
template <class Type>
void AlephCollection<Type>::FilterTau(vector<float> argus)
{
  float psummin;
  float d0max;
  int minhit;
  float cosmax;
  float z0max;
  if(argus.size()==8)
  {
  	psummin = argus[3];
  	d0max   = argus[4];
  	minhit    = (int)argus[5];
  	cosmax  = argus[6];
  	z0max   = argus[7];
  }
  else if (argus.size()==5)
  { 
  	psummin = argus[0];
  	d0max   = argus[1];
  	minhit    = (int)argus[2];
  	cosmax  = argus[3];
  	z0max   = argus[4];
  }
  else
  {
  	psummin = 1.; 
  	d0max   = 2.; 
  	minhit  = 4;
  	cosmax  = 0.95; 
  	z0max   = 10.; 
  }
    for (typename AlephCollection<Type>::iterator ijet = begin(); ijet<end(); ijet++)
    {
      int Ntpc;
      float pp;
      float ee;
      float d0;
      float z0;
      float costheta;
      int Nchgood=0;
      int OneBadTrack=0;
      int lock=0;
      typedef AlephCollection<AlObject*>::iterator ObI;
      AlEflw* dummy = new AlEflw;
      AlEflw* theAssEflw = dummy;
      theAssEflw->setA4V(0,0,0,0);
      // loop on objects in the jet
      // compute the associated track and get some parameters
      for (ObI ifl=(*ijet)->getObjects().begin();
	   ifl<(*ijet)->getObjects().end();
	   ifl++) 
	{
	  if (((AlEflw*)(*ifl))->getEfType()<=3)
	    {
	      if (((AlEflw*)(*ifl))->getTrack()==NULL)
		{
		  Ntpc = 0;
		  d0   = 0;
		  z0   = 0;
		  lock = 1;
		  costheta = 1;
		}
	      else
		{
		  Ntpc = ((AlEflw*)(*ifl)) -> getTrack() -> NT();
		  if ((((*ijet)->QCH() * ((AlEflw*)(*ifl))->QCH() > 0 ) && 
		       ( ((AlEflw*)(*ifl))->QE() > theAssEflw->QE()    )     ) ||
		      (( (*ijet)->QCH() == 0 ) && ( ((AlEflw*)(*ifl))->QE()>theAssEflw->QE())))
		    theAssEflw=((AlEflw*)(*ifl));
		  d0 = ((AlEflw*)(*ifl)) -> getTrack() -> QDB();
		  z0 = ((AlEflw*)(*ifl)) -> getTrack() -> QZB();
		  lock = ((AlEflw*)(*ifl)) -> getTrack() -> isLocked();
		  costheta = ((AlEflw*)(*ifl)) -> QCT();
		}
	      // bad tracks rejection
	      if ( (fabs(d0)>=d0max)        ||
		   (fabs(z0)>=z0max)        ||
		   (fabs(costheta)>=cosmax) ||
		   (Ntpc<minhit)            ||
		   (lock==1)                   )
		OneBadTrack++;
	    }
	}
      // final selection
      if(OneBadTrack>0 || (((*ijet)->getEch()) <= psummin))
	looperase(ijet);
      else
	(*ijet)->setEflw(theAssEflw);
      delete dummy;
    }
}

