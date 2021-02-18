//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS AlTrack:
// Concrete class for Tracks, inherits from QvecBase
// NOTE: STILL DEPENDS ALSO ON ALPHA BANKS d:-(
//
// Author :  G. Bagliesi
// modified by:  C. Delaere, V. Lemaitre, O. van der Aa :
//                - now inherit form QvecLink
//                - link to new banks using Rick's stuff
//                - fixed assignement operator
//
///////////////////////////////////////////////////////////

#include "AlTrack.h"
#include "AlMCtruth.h"                 // Added by Rick
#include "AlephCollection.h"               // Added by Rick

// default constructor : 
AlTrack::AlTrack()
{
 theEflw = NULL;
 Match = new AlephCollection<AlMCtruth*>;
}

// copy constructor 
AlTrack::AlTrack(const AlTrack& oldAt):QvecLink(oldAt) 
{
 Match = new AlephCollection<AlMCtruth*>;
 *Match = *(oldAt.Match);
}

// assignement operator 
AlTrack& AlTrack::operator=(const AlTrack& oldAt)
{
	*Match  = *(oldAt.Match);
	theEflw = oldAt.theEflw;
	_A4V    = oldAt._A4V;
	oVertex = oldAt.oVertex;
	eVertex = oldAt.eVertex;
	_locked = oldAt._locked;
	_qch    = oldAt._qch;
	return *this;
}

// destructor
AlTrack::~AlTrack() 
{
 delete Match;
}

/*!
  Triangular _kinematic_ covariance matrix stored in the order:
 - 1
 - 2 3
 - 4 5 6 
 - 7 8 9 10
 */
float AlTrack::SIG(int x) const{ return qvec -> EM[x-1];}
float AlTrack::SIGEE() const { return SIG(10);}
float AlTrack::SIGPP() const { return  
(  QX()*QX()*SIG(1) +
   QY()*QY()*SIG(3) +
   QZ()*QZ()*SIG(6) +
   2*( QX()*( QY()*SIG(2) + QZ()*SIG(4) ) + QY()*QZ()*SIG(5) )   ) / (QP()*QP()); }
 
 
float AlTrack::SIGMM() const { return
( QM()*
  ( QE()*QE()*SIG(10) + 
    QX()*QX()*SIG(1)  +
    QY()*QY()*SIG(3)  + 
    QZ()*QZ()*SIG(6)  +
    2*( QX()*( QY()*SIG(2) + QZ()*SIG(4) ) + QY()*QZ()*SIG(5) - QE()*(QX()*SIG(7) + QY()*SIG(8) + QZ()*SIG(9)) )   )     ); }

int   AlTrack::NV() const{ if ( qvec -> QD != NULL && qvec -> QD -> AL != NULL )
                        return qvec -> QD -> AL -> NV;  
                      else 
                        return -1;}
int   AlTrack::NI() const{ if ( qvec -> QD != NULL && qvec -> QD -> AL != NULL )
                        return qvec -> QD -> AL -> NI;
                      else 
                        return -1; }
int   AlTrack::NT() const{ 
if ( qvec -> QD != NULL && qvec -> QD -> AL != NULL )
                        return qvec -> QD -> AL -> NT;
                      else {
                        return -1; }}
int   AlTrack::NE() const{ if ( qvec -> QD != NULL && qvec -> QD -> AL != NULL )
                        return qvec -> QD -> AL -> NE;
                      else
                        return -1; }
int   AlTrack::NR() const{ if ( qvec -> QD != NULL && qvec -> QD -> AL != NULL )
                        return qvec -> QD -> AL -> NR;
                      else
                        return -1; }

float AlTrack::IR() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> IR;
                      else 
                        return -1; }
float AlTrack::TL() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> TL;
                      else
                        return -1; }
float AlTrack::P0() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> P0;
                      else
                        return -1; }
float AlTrack::D0() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> D0;
                      else
                        return -1; }
float AlTrack::Z0() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> Z0;
                      else 
                        return -1; }
float AlTrack::AL() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> AL;
                      else
                        return -1; }
/*!
  Triangular covariance matrix stored in the order:
 - 1
 - 2 3
 - 4 5 6
 - 7 8 9 10
 - 11 12 13 14 15 
 - 16 17 18 19 20 21
 */
float AlTrack::EM(int x) const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> EM[x-1];
                      else
                        return -1;}
float AlTrack::C2() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> C2;
                      else
                        return -1; }
int   AlTrack::DF() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> DF;
                      else
                        return -1; }
/*!
  nopt=nmult*100+iopt*10+ierr 
 - IOPT=1 Circle+line fit with UFITMS
 - IOPT=2 3-D iteration with UFITMS
 - IOPT=3 M.S. A*(R-R0)/R with UFITMS
 - IOPT=4 M.S. I-DD0(A) I-PH0(A) with UFITMS
 - IOPT=9 Kalman filter fit UFTKAL
 - NMULT=1 Increased TPC errors for M.S. in UFITMS
 - NMULT=0 TPC errors left alone
 - IERR=1 Circle+line fit failed in UFITMS
 - IERR=2 Cannot invert cov matrix from UFITMS
 - IERR=3 Cov. matrix from UFITMS not pos. def.
 - IERR=4 Kalman filter fit was tried but failed; The old fit from UFITMS was retained
 */
int   AlTrack::NO() const{ if ( qvec -> QD != NULL && qvec -> QD -> AF != NULL )
                        return qvec -> QD -> AF -> NO;
                      else
                        return -1; }

int   AlTrack::SI(int seg) const{ if ( qvec -> QD != NULL && qvec -> QD -> AF !=NULL && seg < (qvec -> QD -> NT))
                        return qvec -> QD -> AT[seg] -> SI;
                      else
                        return -1; }
float AlTrack::TM(int seg) const{ if ( qvec -> QD != NULL && qvec -> QD -> AF !=NULL && seg < (qvec -> QD -> NT))
                        return qvec -> QD -> AT[seg] -> TM;
                      else
                        return -1; }
float AlTrack::TL2(int seg) const{ if ( qvec -> QD != NULL && qvec -> QD -> AF !=NULL && seg < (qvec -> QD -> NT))
                        return qvec -> QD -> AT[seg] -> TL;
                      else
                        return -1; }
int   AlTrack::NS(int seg) const{ if ( qvec -> QD != NULL && qvec -> QD -> AF !=NULL && seg < (qvec -> QD -> NT))
                        return qvec -> QD -> AT[seg] -> NS;
                      else
                        return -1; }
float AlTrack::AD(int seg) const{ if ( qvec -> QD != NULL && qvec -> QD -> AF !=NULL && seg < (qvec -> QD -> NT))
                        return qvec -> QD -> AT[seg] -> AD;
                      else
                        return -1; }
int   AlTrack::TN(int seg) const{ if ( qvec -> QD != NULL && qvec -> QD -> AF !=NULL && seg < (qvec -> QD -> NT))
                        return qvec -> QD -> AT[seg] -> TN;
                      else
                        return -1; }
int   AlTrack::SF(int seg) const{ if ( qvec -> QD != NULL && qvec -> QD -> AF !=NULL && seg < (qvec -> QD -> NT))
                        return qvec -> QD -> AT[seg] -> SF;
                      else
                        return -1; }
float AlTrack::TMmean() const{ float TMtmp=0;
                          for (int i=0;i< (qvec -> QD -> NT);i++) TMtmp+=TM(i);
			  TMtmp/=(qvec -> QD -> NT);
			  return TMtmp; }
float AlTrack::TL2sum()  const{ float TL2tmp=0;
			  for (int i=0;i< (qvec -> QD -> NT);i++) TL2tmp+=TL2(i);
			  return TL2tmp; }
int   AlTrack::NSsum()  const{ int NStmp=0;
			  for (int i=0;i< (qvec -> QD -> NT);i++) NStmp+=NS(i);
			  return NStmp; }
float AlTrack::ADmean() const{ float ADtmp=0;
			  for (int i=0;i< (qvec -> QD -> NT);i++) ADtmp+=AD(i);
			  ADtmp/=(qvec -> QD -> NT);
			  return ADtmp; }
			
/*--------------------------------------------------------------------------*/
// set the assoc. track
void AlTrack::setMatchingVector( AlephCollection< AlMCtruth* >& VectorOfTracks )
 {
    	 (*Match) = VectorOfTracks;
 }
 
/*--------------------------------------------------------------------------*/
// get the assoc. track
AlephCollection<AlMCtruth*>* AlTrack::getMatchingVector() const
 {
  return (AlephCollection<AlMCtruth*>*) Match;
 }
/*--------------------------------------------------------------------------*/



