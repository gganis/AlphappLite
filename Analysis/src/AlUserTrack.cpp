#include "AlUserTrack.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"

// default constructor
AlUserTrack::AlUserTrack()
{
  _daughters.resize(0);
  TMatrixDSym temp1(5);
  _EM = temp1;
  TMatrixDSym temp2(4);
  _EM_kin = temp2;
  TMatrix temp3(3,3);
  _corr_track_vertex = temp3;

  eVertex = NULL;  
  
}
 
// copy constructor
AlUserTrack::AlUserTrack(const AlUserTrack& rhsAt): QvecBase(rhsAt)
{
  _daughters.resize(rhsAt._daughters.size());
    
  for (unsigned int i = 0; i < rhsAt._daughters.size(); i++) {
    _daughters[i] = rhsAt._daughters[i];
  }
   
  eVertex = rhsAt.eVertex;  // dangerous, but don't know how to do better
  _EM = rhsAt._EM;
  _EM_kin = rhsAt._EM_kin;
  _corr_track_vertex = rhsAt._corr_track_vertex;

}

//-----------------------------------------------------------------------
AlephCollection<AlObject*>& AlUserTrack::getDaughters() 
{ 
  return _daughters;
}
     
//-----------------------------------------------------------------------
void AlUserTrack::addDaughter(AlObject* d)
{ 
  _daughters.push_back(d); 
}

//-----------------------------------------------------------------------
float  AlUserTrack::EM(int i) const
{ 
  if (i < 0 || i > 15) return -9999.;
  int j = 0;
  float val;
  for (int m = 1; m <= 5; m++) {
    for (int n = 1; n <= m; n++) {
      if (++j == i) { 
	val = _EM(m,n);
	break;
      }
    }      
  } 
  return val;
}

//-----------------------------------------------------------------------
float  AlUserTrack::EM(int m, int n) const
{ 
  return _EM(m,n);
}

//-----------------------------------------------------------------------
TMatrixDSym&  AlUserTrack::EM() 
{ 
  return _EM;
}

//-----------------------------------------------------------------------
void AlUserTrack::setEM(int i, float val)
{ 
  if (i > 0 && i < 15) {
    int j = 0;
    for (int m = 1; m <= 5; m++) {
      for (int n = 1; n <= m; n++) {
	if (++j == i) _EM(m,n) = val;
      }      
    } 
  }
}  

//-----------------------------------------------------------------------
void AlUserTrack::setEM(const TMatrixDSym& em)
{ 
  _EM = em;
}  


//-----------------------------------------------------------------------
float  AlUserTrack::SIG(int i) const
{ 
  if (i < 0 || i > 15) return -9999.;
  int j = 0;
  float val;
  for (int m = 1; m <= 5; m++) {
    for (int n = 1; n <= m; n++) {
      if (++j == i) { 
	val = _EM_kin(m,n);
	break;
      }
    }      
  } 
  return val;
}

//-----------------------------------------------------------------------
float  AlUserTrack::EM_kin(int m, int n) const
{ 
  return _EM_kin(m,n);
}

//-----------------------------------------------------------------------
TMatrixDSym&  AlUserTrack::EM_kin()
{ 
  return _EM_kin;
}

//-----------------------------------------------------------------------
void AlUserTrack::setEM_kin(int i, float val) 
{ 
  if (i > 0 && i < 15) {
    int j = 0;
    for (int m = 1; m <= 5; m++) {
      for (int n = 1; n <= m; n++) {
	if (++j == i) {
	  _EM_kin(m,n) = val;
	  break;
	}
      }      
    } 
  }
}  

//-----------------------------------------------------------------------
void AlUserTrack::setEM_kin(const TMatrixDSym& em)
{ 
  _EM_kin = em;
}  

//-----------------------------------------------------------------------
float AlUserTrack::SIGEE() const { return SIG(10);}

//-----------------------------------------------------------------------
float AlUserTrack::SIGPP() const { return  
(  QX()*QX()*SIG(1) +
   QY()*QY()*SIG(3) +
   QZ()*QZ()*SIG(6) +
   2*( QX()*( QY()*SIG(2) + QZ()*SIG(4) ) + QY()*QZ()*SIG(5) )   ) / (QP()*QP()); }
 
//----------------------------------------------------------------------- 
float AlUserTrack::SIGMM() const { return
( QM()*
  ( QE()*QE()*SIG(10) + 
    QX()*QX()*SIG(1)  +
    QY()*QY()*SIG(3)  + 
    QZ()*QZ()*SIG(6)  +
    2*( QX()*( QY()*SIG(2) + QZ()*SIG(4) ) + QY()*QZ()*SIG(5) - QE()*(QX()*SIG(7) + QY()*SIG(8) + QZ()*SIG(9)) )   )     ); }


//-----------------------------------------------------------------------
float  AlUserTrack::corrMatrix(int m, int n) const
{ 
  return _corr_track_vertex(m,n);
}

//-----------------------------------------------------------------------
TMatrixD&  AlUserTrack::corrMatrix()
{ 
  return _corr_track_vertex;
}

//-----------------------------------------------------------------------
void AlUserTrack::setCorrMatrix(int i, int j, float val)
{ 
  _corr_track_vertex(i,j) = val;
	
}  

//-----------------------------------------------------------------------
void AlUserTrack::setCorrMatrix(const TMatrixD& cm)
{ 
  _corr_track_vertex = cm;
}  
