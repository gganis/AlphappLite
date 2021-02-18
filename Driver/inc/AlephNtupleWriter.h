//////////////////////////////////////////////////////////
// Class AlephNtupleWriter:
// Give access to general methods to write data to files
// possible output formats are: hbook, root
//
// Author : C.Delaere
//
///////////////////////////////////////////////////////////

#ifndef _ALEPHNTUPLEWRITER_H_
#define _ALEPHNTUPLEWRITER_H_

#include "AlephCardsReader.h"
#include "SmartPointer.h"

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TLorentzVector.h"
#include "TVector3.h"

#include "UserClasses.h"
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
#include <stdarg.h>


//! The Ntuple Writer
/*!
 * defines general methods to create ntuples or trees
 * by the same way.
 */
class AlephNtupleWriter {
public:
//! constructor
AlephNtupleWriter();

//! destructor
virtual ~AlephNtupleWriter();

//! initialize
virtual void Initialize(AlephCardsReader*, int) ;

//! add an output variable
template<typename tpe> void AddOutput(tpe obj, char* name)
{
	string clss;
	if (typeid(obj)==typeid(int)) clss = "I";
	else if (typeid(obj)==typeid(unsigned int)) clss = "i";
	else if (typeid(obj)==typeid(float)) clss = "F";
	else if (typeid(obj)==typeid(double)) clss = "D";
	else if (typeid(obj)==typeid(short)) clss = "B";
	else if (typeid(obj)==typeid(unsigned short)) clss = "b";
	else if (typeid(obj)==typeid(long)) clss = "I";
	else if (typeid(obj)==typeid(unsigned long)) clss = "i";
	else clss = typeid(obj).name()+strspn(typeid(obj).name(),"0123456789");
	switch (type)
	{
		case 1 :
			{
				smart_type<tpe>* theObject = new smart_type<tpe>;
				theObjects.push_back(theObject);
				void* address = theObject->theaddr();
				void* ptr     = theObject->theptr();
				NamesIndexes[name] = (theObjects.size()-1);
				if ((strlen(clss.c_str())==1)&&(strpbrk(clss.c_str(),"CBbSsIiFD")!=(char*)NULL))
				{
					string arg3 = string(name)+string("/")+string(clss);
					ROOTtree->Branch(name,address,arg3.c_str());
				}
				else
				{
					ROOTtree->Branch(name,clss.c_str(),ptr);
				}
			}
			break;
		default :
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);
	}
}
//! add several output variables
template<typename tpe> void AddOutput(tpe obj, unsigned int sze, ...)
{
	va_list ap;
	va_start(ap,sze);
	for(unsigned int arg=0;arg<sze;arg++)
	{
	char *name = va_arg(ap,char*);
	string clss;
	if (typeid(obj)==typeid(int)) clss = "I";
	else if (typeid(obj)==typeid(unsigned int)) clss = "i";
	else if (typeid(obj)==typeid(float)) clss = "F";
	else if (typeid(obj)==typeid(double)) clss = "D";
	else if (typeid(obj)==typeid(short)) clss = "B";
	else if (typeid(obj)==typeid(unsigned short)) clss = "b";
	else if (typeid(obj)==typeid(long)) clss = "I";
	else if (typeid(obj)==typeid(unsigned long)) clss = "i";
	else clss = typeid(obj).name()+strspn(typeid(obj).name(),"0123456789");
	switch (type)
	{
		case 1 :
			{
				smart_type<tpe>* theObject = new smart_type<tpe>;
				theObjects.push_back(theObject);
				void* address = theObject->theaddr();
				void* ptr     = theObject->theptr();
				NamesIndexes[name] = (theObjects.size()-1);
				if ((strlen(clss.c_str())==1)&&(strpbrk(clss.c_str(),"CBbSsIiFD")!=(char*)NULL))
				{
					string arg3 = string(name)+string("/")+string(clss);
					ROOTtree->Branch(name,address,arg3.c_str());
				}
				else
				{
					ROOTtree->Branch(name,clss.c_str(),ptr);
				}
			}
			break;
		default :
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);
	}
	}
	va_end(ap);
}

//! add as output an elementary array (variable size)
template<typename tpe> void AddScalableOutput(char* name, tpe obj, unsigned int size)
{
	string clss;
	if (typeid(obj)==typeid(int)) clss = "I";
	else if (typeid(obj)==typeid(unsigned int)) clss = "i";
	else if (typeid(obj)==typeid(float)) clss = "F";
	else if (typeid(obj)==typeid(double)) clss = "D";
	else if (typeid(obj)==typeid(short)) clss = "B";
	else if (typeid(obj)==typeid(unsigned short)) clss = "b";
	else if (typeid(obj)==typeid(long)) clss = "I";
	else if (typeid(obj)==typeid(unsigned long)) clss = "i";
	else 
	{
		cerr << "ERROR: cannot create an array of non-elementary type" << endl;
		return;
	}
	switch (type)
	{
		case 1 :
			{
				smart_type<tpe>* theObject = new smart_type<tpe>(size);
				theObjects.push_back(theObject);
				void* address = theObject->theaddr();
				NamesIndexes[name] = (theObjects.size()-1);
				
				string nname = string("n")+string(name);
				string arg3 = nname + string("/I");
				ROOTtree->Branch(nname.c_str(),SizeAddresses[name] = new int,arg3.c_str());
				arg3 = string(name)+string("[")+nname+string("]/")+string(clss);
				ROOTtree->Branch(name,address,arg3.c_str());
			}
			break;
		default :
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);
	}
}

//! fill the ntuple
virtual void Fill();

//! terminate the session
virtual void Terminate();

//! method to instruct the class to keep the instant value of an array
template <typename entry> void Keep(const char* name , const entry* value , const int size)
{
	switch(type)
	{
		case 1 :
			{
				*((*SizeAddresses.find(name)).second) = size;
				entry* array = (entry*)theObjects[NamesIndexes.find(name)->second]->theaddr();
				for(int i=0;i<size;i++) array[i] = value[i];
			}
			break;
		default:
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);
	}
}

//! method to instruct the class to keep the instant value of a STL vector
template <typename entry> void KeepV(const char* name , vector<entry> value)
{
	unsigned int size = value.size();
	switch(type)
	{
		case 1 :
			{
				*((*SizeAddresses.find(name)).second) = size;
				entry* array = (entry*)theObjects[NamesIndexes.find(name)->second]->theaddr();
				for(unsigned int i=0;i<size;i++) array[i] = value[i];
			}
			break;
		default:
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);
	}
}

//! method to instruct the class to keep the instant value of a variable
template <typename entry> void Keep(const char* name, const entry& value)
{
	switch(type)
	{
		case 1 :
			*(entry*)theObjects[NamesIndexes.find(name)->second]->theaddr() = value;
			break;
		default:
			cerr << "ERROR: Bad Ntuple Type." << endl;
			exit(0);
	}
}

//! method to instruct the class to keep the instant value of a TLorentzVector
void Keep(const char* name, const TLorentzVector& value)
{
	float tmp[4];
	tmp[0] = value[0]; tmp[1] = value[1]; tmp[2] = value[2]; tmp[3] = value[3];
	Keep(name, tmp, 4);
}


//! method to instruct the class to keep the instant value of a TVector3
void Keep(const char* name, const TVector3& value)
{
	float tmp[3];
	tmp[0] = value[0]; tmp[1] = value[1]; tmp[2] = value[2];
	Keep(name, tmp, 3);
}

private:
// general
int type;
AlephCardsReader* cards;
map<string,int> NamesIndexes;

// root used members
TFile* ROOTfile;
TTree* ROOTtree;
map<string,int*>  SizeAddresses;
vector<smart_void*> theObjects;

};

#endif

