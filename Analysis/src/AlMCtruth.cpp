////////////////////////////////////////////////////////////////////
//
// Implementation of class AlMCtruth
//
// Author : R. Cavanaugh
//
////////////////////////////////////////////////////////////////////


#include "AlMCtruth.h"
#include "ParticleCodes.h"


/*--------------------------------------------------------------------------*/

char* AlMCtruth::name() const
{
  if( qvec -> PA == GAMMA       ) return "gamma";
  if( qvec -> PA == E_PLUS      ) return "e+";
  if( qvec -> PA == E_MINUS     ) return "e-";
  if( qvec -> PA == MU_PLUS     ) return "mu+";
  if( qvec -> PA == MU_MINUS    ) return "mu-";
  if( qvec -> PA == TAU_PLUS    ) return "tau+";
  if( qvec -> PA == TAU_MINUS   ) return "tau-";
  if( qvec -> PA == W_PLUS      ) return "W+";
  if( qvec -> PA == W_MINUS     ) return "W-";
  if( qvec -> PA == Z_ZERO      ) return "Z0";
  if( qvec -> PA == NU_E        ) return "nue";
  if( qvec -> PA == NU_E_BAR    ) return "nue_bar";
  if( qvec -> PA == NU_MU       ) return "numu";
  if( qvec -> PA == NU_MU_BAR   ) return "numu_bar";
  if( qvec -> PA == NU_TAU      ) return "nutau";
  if( qvec -> PA == NU_TAU_BAR  ) return "nutau_bar";
  if( qvec -> PA == U_QUARK     ) return "u";
  if( qvec -> PA == D_QUARK     ) return "d";
  if( qvec -> PA == S_QUARK     ) return "s";
  if( qvec -> PA == C_QUARK     ) return "c";
  if( qvec -> PA == U_QUARK_BAR ) return "u_bar";
  if( qvec -> PA == D_QUARK_BAR ) return "d_bar";
  if( qvec -> PA == S_QUARK_BAR ) return "s_bar";
  if( qvec -> PA == C_QUARK_BAR ) return "c_bar";
  if( qvec -> PA == GLUON ) return "gluon";
  if( qvec -> PA == HIGGS ) return "Higgs";
  if( qvec -> PA == PIO ) return "pi0";
  if( qvec -> PA == PIP ) return "pi+";
  if( qvec -> PA == PIM ) return "pi-";
  return "particle not defined! ";
} 
 
/*--------------------------------------------------------------------------*/
AlMCtruth::AlMCtruth(){}                                 // default constructor
AlMCtruth::AlMCtruth(const AlMCtruth& oldM):QvecLink(oldM) {}//copy constructor

/*--------------------------------------------------------------------------*/
// destructor
AlMCtruth::~AlMCtruth(){
}
/*--------------------------------------------------------------------------*/
// set the assoc. track
void AlMCtruth::setMotherVector(   AlephCollection< AlMCtruth* > VectorOfTracks )
{
  Mother   = VectorOfTracks;
}
/*--------------------------------------------------------------------------*/
// set the assoc. track
void AlMCtruth::setDaughterVector( AlephCollection< AlMCtruth* > VectorOfTracks )
{
  Daughter = VectorOfTracks;
}
/*--------------------------------------------------------------------------*/
// get the assoc. track
AlephCollection<AlMCtruth*> AlMCtruth::getMotherVector() const
{
  return Mother;
}
/*--------------------------------------------------------------------------*/
// get the assoc. track
AlephCollection<AlMCtruth*> AlMCtruth::getDaughterVector() const
{
  return Daughter;
}
/*--------------------------------------------------------------------------*/

 
