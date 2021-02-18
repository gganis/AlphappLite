//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS AlCalObject:
// Concrete class for CalObjects, inherits from QvecBase
//
// Author :  C. Delaere
//
///////////////////////////////////////////////////////////

#include "AlCalObject.h"
#include "BankClasses.h"

// copy constructor 
AlCalObject::AlCalObject(const AlCalObject& oldAt):QvecLink(oldAt) 
{
	_isolated = false;
}

// assignement operator 
AlCalObject& AlCalObject::operator=(const AlCalObject& oldAt)
{
	_isolated = oldAt._isolated;
	_A4V    = oldAt._A4V;
	_locked = oldAt._locked;
	return *this;
}

// destructor
AlCalObject::~AlCalObject() {}

// type
ALEPHTYPE AlCalObject::AlCalObject::TYPE() const
{
	//Check wether this is ECAL or HCAL
	if (qvec -> QD)
	{
		if(qvec -> QD -> EC) //ECAL
			return ECALE;
		if(qvec -> QD -> HC) //HCAL
			return HCALE;
	}
	return OBJECT;
}

vector<float> AlCalObject::GetRawEnergy()
{
	vector<float> output;
	//Check wether this is ECAL or HCAL
	if (qvec -> QD)
	{
		if(qvec -> QD -> EC) //ECAL
		{
			output.push_back(qvec->QD->EC->ER);
			output.push_back(qvec->QD->EC->E1);
			output.push_back(qvec->QD->EC->E2);
		}
		if(qvec -> QD -> HC) //HCAL
		{
			output.push_back(qvec->QD->HC->ER);
		}
	}
	return output;
}

int AlCalObject::GetRegionCode()
{
	if (qvec -> QD)
	{
		if(qvec -> QD -> EC) //ECAL
			return qvec->QD->EC->KD;
		if(qvec -> QD -> HC) //HCAL
			return qvec->QD->HC->KD;
	}
	return -1;
}

int AlCalObject::GetCorrectionCode()
{
	if (qvec -> QD)
	{
		if(qvec -> QD -> EC) //ECAL
			return qvec->QD->EC->CC;
		if(qvec -> QD -> HC) //HCAL
			return qvec->QD->HC->CC;
	}
	return -1;
}

int AlCalObject::GetRelationBits()
{
	if (qvec -> QD)
	{
		if(qvec -> QD -> EC) //ECAL
			return qvec->QD->EC->RB;
		if(qvec -> QD -> HC) //HCAL
			return qvec->QD->HC->RB;
	}
	return -1;
}

