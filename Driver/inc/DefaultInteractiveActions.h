/////////////////////////////////////////////////////////////////////
// Default set of interactive functions
// used for event display using AlVisu
//
// Author : C. Delaere
//
// Date   : 19/04/2002
//
/////////////////////////////////////////////////////////////////////

#ifndef DEFAULTINTERACTIVEACTIONS_H
#define DEFAULTINTERACTIVEACTIONS_H

#include "AlephCollection.h"
#include <vector>
#include "AlphaBanks.h"
#include "AlephAbstractInteractiveFunction.h"
#include "TimeInfo.h"
#include "AlephIoManager.h"
#include "TVector3.h"

using namespace std;
// code 100 : general event informations

class GeneralEventInfo: public AlephAbstractInteractiveFunction
{
	public:
		GeneralEventInfo(AlephInteractiveHandler* ptr):AlephAbstractInteractiveFunction(ptr) {}
		~GeneralEventInfo() {}
		string Name() {return "GeneralEventInfo";}
		int Code() {return 100;}
		vector<pair<string,float> > OptionsList() 
			{ pair<string,float> option;
			  option.first = "Apply preselection";
			  option.second = 1.;
			  vector<pair<string,float> > result;
			  result.push_back(option);
			  return result;
			}
		void Run(vector<float>& options,AlphaBanks& EventInfo);
};
		
// code 200 : tracks

class CollectTracks: public AlephAbstractInteractiveFunction
{
	public:
		CollectTracks(AlephInteractiveHandler* ptr):AlephAbstractInteractiveFunction(ptr) {}
		~CollectTracks() {}
		string Name() {return "CollectTracks";}
		int Code() {return 200;}
		vector<pair<string,float> > OptionsList() 
			{ pair<string,float> option;
			  vector<pair<string,float> > result;
			  option.first = "type";
			  option.second = 0;  
			  result.push_back(option);
			  option.first = "energy cut";
			  option.second = 10;
			  result.push_back(option);
			  option.first = "cos theta cut";
			  option.second = 0.95;
			  result.push_back(option);
			  option.first = "sanity check";
			  option.second = 0;
			  result.push_back(option);
			  return result;
			}
		void Run(vector<float>& options,AlphaBanks& EventInfo);
};

class CollectLeptons: public AlephAbstractInteractiveFunction
{
	public:
		CollectLeptons(AlephInteractiveHandler* ptr):AlephAbstractInteractiveFunction(ptr) {}
		~CollectLeptons() {}
		string Name() {return "CollectLeptons";}
		int Code() {return 300;}
		vector<pair<string,float> > OptionsList() 
			{ pair<string,float> option;
			  vector<pair<string,float> > result;
			  option.first = "mask";
			  option.second = 0;  
			  result.push_back(option);
			  return result;
			}
		void Run(vector<float>& options,AlphaBanks& EventInfo);
};

class CollectJets: public AlephAbstractInteractiveFunction
{
	public:
		CollectJets(AlephInteractiveHandler* ptr):AlephAbstractInteractiveFunction(ptr) {}
		~CollectJets() {}
		string Name() {return "CollectJets";}
		int Code() {return 400;}
		vector<pair<string,float> > OptionsList() 
			{ pair<string,float> option;
			  vector<pair<string,float> > result;
			  option.first = "metric";
			  option.second = 1;
			  result.push_back(option);
			  option.first = "scheme";
			  option.second = 1;
			  result.push_back(option);
			  option.first = "ycut";
			  option.second = -2;
			  result.push_back(option);
			  option.first = "energy scale";
			  option.second = 0;
			  result.push_back(option);
			  return result;
			}
		void Run(vector<float>& options,AlphaBanks& EventInfo);
};

#endif
