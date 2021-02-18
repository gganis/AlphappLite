////////////////////////////////////////////////////////////////////
//
// Implementation of class AlGamp
//
// Author : G. Bagliesi
// modified by C. Delaere: now derive from QvecLink
//                         fixed assignement operator
//
////////////////////////////////////////////////////////////////////


#include "AlGamp.h"
#include "BankClasses.h"

// default constructor : does nothing
AlGamp::AlGamp()  
{
	fake = NULL;
}

// copy constructor :
AlGamp::AlGamp(const AlGamp& oldG):QvecLink(oldG) 
{
	fake = oldG.fake;
}

void AlGamp::SetFake(AlGamp* parent)
{
	fake = parent;
}

void AlGamp::UseCorrectedA4V()
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
	{
		TLorentzVector tmp(0,0,1,qvec->QD->PG->EC);
		tmp.SetTheta(qvec->QD->PG->TC);
		tmp.SetPhi(qvec->QD->PG->PC);
		tmp.SetRho(qvec->QD->PG->EC);
		setA4V(tmp);
	}
	else
		setA4V(0,0,0,0);
}

void AlGamp::UseStandardA4V()
{
	if(qvec!=NULL)
		setA4V(qvec->QX, qvec->QY, qvec->QZ, qvec->QE);
	else
		setA4V(0,0,0,0);
}

void AlGamp::UseRawA4V()
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
	{
		TLorentzVector tmp(0,0,1,qvec->QD->PG->ER);
		tmp.SetTheta(qvec->QD->PG->TR);
		tmp.SetPhi(qvec->QD->PG->PR);
		tmp.SetRho(qvec->QD->PG->ER);
		setA4V(tmp);
	}
	else
		setA4V(0,0,0,0);
}

TLorentzVector AlGamp::GetCorrectedA4V() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
	{
		TLorentzVector tmp(0,0,1,qvec->QD->PG->EC);
		tmp.SetTheta(qvec->QD->PG->TC);
		tmp.SetPhi(qvec->QD->PG->PC);
		tmp.SetRho(qvec->QD->PG->EC);
		return tmp;
	}
	else
		return TLorentzVector(0,0,0,0);
}

TLorentzVector AlGamp::GetStandardA4V() const
{
	if(qvec!=NULL)
		return TLorentzVector(qvec->QX, qvec->QY, qvec->QZ, qvec->QE);
	else
		return TLorentzVector(0,0,0,0);
}

TLorentzVector AlGamp::GetRawA4V() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
	{
		TLorentzVector tmp(0,0,1,qvec->QD->PG->ER);
		tmp.SetTheta(qvec->QD->PG->TR);
		tmp.SetPhi(qvec->QD->PG->PR);
		tmp.SetRho(qvec->QD->PG->ER);
		return tmp;
	}
	else
		return TLorentzVector(0,0,0,0);
}

float AlGamp::EnergyFractionInStack(const int stack) const
{
	if ((stack!=1)||(stack!=2)) return 0;
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL)&&(stack==1))
		return qvec->QD->PG->R1;
	else if ((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL)&&(stack==2))
		return qvec->QD->PG->R2;
	else return -1;
}

float AlGamp::EnergyFractionInCentralTowers() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->F4;
	else return -1;
}

float AlGamp::Isolation() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->DM;
        else return -1;
}

int AlGamp::StoreyFlag() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->ST;
	else return -1;
}

int AlGamp::QualityFlag() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->QU;
	else return -1;
}

float AlGamp::QualityEstimator(const int estimator) const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL)&&(estimator==1))
		return qvec->QD->PG->Q1;
	else if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL)&&(estimator==2))
		return qvec->QD->PG->Q2;
	else return -1;
}

float AlGamp::Moment(const int moment) const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL)&&(moment==1))
		return qvec->QD->PG->M1;
	else if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL)&&(moment==2))
		return qvec->QD->PG->M2;
	else return -1;
}

float AlGamp::Pi0Mass() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->MA;
	else return -1;
}

float AlGamp::ExpectedEnergyFractionInCentralTowers() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->EF;
	else return -1;
}

float AlGamp::GeometricalCorrection() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->GC;
	else return -1;
}

float AlGamp::ZeroSupression() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->ZS;
	else return -1;
}

float AlGamp::FakeEcalProbability() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->PL;
	else return -1;
}

float AlGamp::FakeHcalProbability() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->PH;
	else return -1;
}

AlGamp* AlGamp::ParentGivingFake() const
{
	return fake;
}

int AlGamp::FakeEquality() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		 return qvec->QD->PG->FA;
	else return -1;
}

int AlGamp::PecoObject() const
{
	if((qvec!=NULL)&&(qvec->QD!=NULL)&&(qvec->QD->PG!=NULL))
		return qvec->QD->PG->PE;
	else return -1;
}

