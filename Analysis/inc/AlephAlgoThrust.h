/////////////////////////////////////////////////
// part of AlephCollection.h
// Subclass of vector.h
//
// Author: Dan Wallin  Date: 2000-08-11
// modified 9/3/2001 : sphericity,...  C.Delaere
//
/////////////////////////////////////////////////

//! compute the thrust of an event, based on a set of "tracks"
template <class Type>
AlThrust AlephCollection<Type>::AThrust() const
{
  typename AlephCollection<Type>::const_iterator i;  
  for (i=begin();i<end();i++)
    if ((**i).TYPE() != TRACK  && (**i).TYPE() != EFLOW   && 
	(**i).TYPE() != GAMPEC && (**i).TYPE() != ALJET   &&
	(**i).TYPE() != MUON && (**i).TYPE() != ELEC  &&
	(**i).TYPE() != ALTAU )
      {
	cout << "AThrust : WARNING : type not supported!" << endl;
	exit(1);
      }
  vector<TVector3> p;   
  int Np = size();      //number of particles
  AlThrust thr;         //variables of thr are zero as set 
                        //by the default constructor 
 			  
  // select the three-momenta (use only unlocked objects)    
  for(int i=0; i < Np; i++) 
    if (!((*this)[i]->isLocked()))
	    p.push_back((*this)[i]->A4V().Vect());
  Np = p.size(); 
  TVector3 qtbo;
  TVector3 zero(0.,0.,0.);
  float vnew;
  
  // for more than 2 tracks
  if (Np > 2)
    { 
      float vmax  = 0.;
      TVector3 vn, vm, vc, vl;
      
      for(int i=0; i< Np-1; i++) 
	for(int j=i+1; j < Np; j++)
	  {
	    vc = p[i].Cross(p[j]);
	    vl = zero; 
	    
	    for(int k=0; k<Np; k++)
	      if ((k != i) && (k != j))
		if (p[k].Dot(vc) >= 0.) vl = vl + p[k];
		else vl = vl - p[k];
	    
	    // make all four sign-combinations for i,j
	    
	    vn = vl + p[j] + p[i];
	    vnew = vn.Mag2();
	    if (vnew >  vmax)
	      {  
		vmax = vnew;
		vm = vn;
	      }
            
	    vn = vl + p[j] - p[i];
	    vnew = vn.Mag2();
	    if (vnew >  vmax)
	      {  
		vmax = vnew;
		vm = vn;
	      }
	    
	    vn = vl - p[j] + p[i];
	    vnew = vn.Mag2();
	    if (vnew >  vmax)
	      {  
		vmax = vnew;
		vm = vn;
	      }
	    
	    vn = vl - p[j] - p[i];
	    vnew = vn.Mag2();
	    if (vnew >  vmax)
	      {  
		vmax = vnew;
		vm = vn;
	      }    
	    
	  }
      // sum momenta of all particles and iterate
      
      for(int iter=1; iter<=4; iter++)
	{  
	  qtbo = zero;
	  for(int i=0; i< Np; i++)
	    if (vm.Dot(p[i]) >= 0.) 
	      qtbo = qtbo + p[i];
	    else 
	      qtbo = qtbo - p[i];
	  vnew = qtbo.Mag2();
	  if (vnew  == vmax) break;
	  fout << endl << " I have to iterate again " <<  endl << endl;
	  vmax = vnew;
	  vm = qtbo;
	}
    }  // of if Np > 2
  else
    if (Np == 2)
      if (p[0].Dot(p[1]) >= 0.) 
	qtbo = p[0] + p[1];
      else
	qtbo = p[0] - p[1];
    else if (Np == 1)
      qtbo = p[0];
    else
      {
	qtbo = zero;
	// thrustvalue and direction are set to zero by default constructor
	// shall it also be filled into ObjectV ???
	return thr;
      }
  
  // normalize thrust -division by total momentum-
  float vsum = 0.;
  for(int i=0; i < Np; i++) vsum = vsum + p[i].Mag();
  vnew  = qtbo.Mag();
  float v = vnew/vsum; 
  float x = qtbo.X()/vnew;
  float y = qtbo.Y()/vnew;
  float z = qtbo.Z()/vnew;
  thr.setA4V(x, y, z, v);
  return thr;
}

template <class Type>
float AlephCollection<Type>::Sphericity() const
{
  // First a critical check
  if (size()==0)
    {
      cerr << "ERROR: cannot compute Sphericity on an empty vector. ABORTING" << endl;
      exit(-1);
    }
  // first fill the momentum tensor
  TMatrixDSym MomentumTensor(3);
  for(typename AlephCollection<Type>::const_iterator vec=begin();vec<end();vec++)
   {
      for(int i=0;i<3;i++)
        for(int j=0;j<=i;j++)
	  if(!((*vec)->isLocked()))
             MomentumTensor[i][j] += (((*vec)->A4V()[i])*((*vec)->A4V()[j]));
   }
  MomentumTensor*=1/(MomentumTensor[0][0]+MomentumTensor[1][1]+MomentumTensor[2][2]);
  // find the eigen values
  TMatrixDSymEigen eigen(MomentumTensor);
  TVectorD eigenvals = eigen.GetEigenValues();
  vector<float> eigenvalues(3);
  eigenvalues[0] = eigenvals[0];
  eigenvalues[1] = eigenvals[1];
  eigenvalues[2] = eigenvals[2];
  sort(eigenvalues.begin(),eigenvalues.end());
  // compute spericity
  float sph = ( 1.5*(1-eigenvalues[2]));
  return sph;
}

template <class Type>
float AlephCollection<Type>::Aplanarity() const
{
  // First a critical check
  if (size()==0)
    {
      cerr << "ERROR: cannot compute aplanarity on an empty vector. ABORTING" << endl;
      exit(-1);
    }
  // first fill the momentum tensor
  TMatrixDSym MomentumTensor(3);
  for(typename AlephCollection<Type>::const_iterator vec=begin();vec<end();vec++)
   {
      for(int i=0;i<3;i++)
        for(int j=0;j<=i;j++)
	  if(!((*vec)->isLocked()))
             MomentumTensor[i][j] += (((*vec)->A4V()[i])*((*vec)->A4V()[j]));
   }
  MomentumTensor*=1/(MomentumTensor[0][0]+MomentumTensor[1][1]+MomentumTensor[2][2]);
  // find the eigen values
  TMatrixDSymEigen eigen(MomentumTensor);
  TVectorD eigenvals = eigen.GetEigenValues();
  vector<float> eigenvalues(3);
  eigenvalues[0] = eigenvals[0];
  eigenvalues[1] = eigenvals[1];
  eigenvalues[2] = eigenvals[2];
  sort(eigenvalues.begin(),eigenvalues.end());
  // compute aplanarity
  return ( 1.5*eigenvalues[0]);
}

template <class Type>
float AlephCollection<Type>::Planarity() const
{
  // First a critical check
  if (size()==0)
    {
      cerr << "ERROR: cannot compute planarity on an empty vector. ABORTING" << endl;
      exit(-1);
    }
  // first fill the momentum tensor
  TMatrixDSym MomentumTensor(3);
  for(typename AlephCollection<Type>::const_iterator vec=begin();vec<end();vec++)
   {
      for(int i=0;i<3;i++)
        for(int j=0;j<=i;j++)
	  if(!((*vec)->isLocked()))
             MomentumTensor[i][j] += (((*vec)->A4V()[i])*((*vec)->A4V()[j]));
   }
  MomentumTensor*=1/(MomentumTensor[0][0]+MomentumTensor[1][1]+MomentumTensor[2][2]);
  // find the eigen values
  TMatrixDSymEigen eigen(MomentumTensor);
  TVectorD eigenvals = eigen.GetEigenValues();
  vector<float> eigenvalues(3);
  eigenvalues[0] = eigenvals[0];
  eigenvalues[1] = eigenvals[1];
  eigenvalues[2] = eigenvals[2];
  sort(eigenvalues.begin(),eigenvalues.end());
  // compute planarity
  return (eigenvalues[0]/eigenvalues[1]);
}

