/////////////////////////////////////////////////////////////////////
// 
// Simple test routine: print the Lorentz vector of the Eflows.
//
// Author : C. Delaere
//
// Date: 2001-08-08
//
//
/////////////////////////////////////////////////////////////////////

#include <fstream>
#include "AlephExManager.h"
#include "AlephCollection.h"
#include <vector>
#include "AlBjet.h"
#include "AlephRegisteredAction.h"

extern ofstream fout;

///////////////////////////////////////////////////////////////////////
//  User Init
///////////////////////////////////////////////////////////////////////

class testclass:public AlephAbstractInteractiveFunction
{
	public:
		testclass(AlephInteractiveHandler *ptr):AlephAbstractInteractiveFunction(ptr) {}
		virtual string Name() {return "test";}
		virtual int Code() {return 555;}
		virtual void Run(vector<float>& options,AlphaBanks& EventInfo) 
			{ 
				// dummy routine: returns always the same track, eflow and the same jet
				vector<float> output;
				output.push_back(2);
				output.push_back(1); // a track
				output.push_back(3); // px
				output.push_back(0); // py
				output.push_back(0); // pz
				output.push_back(0); // ch
				SendMessage(Code(),output,"Dummy test routine");
				output.clear();
				output.push_back(1);
				output.push_back(2);  // an eflow
				output.push_back(10); // E
				output.push_back(0);  // px
				output.push_back(10); // py
				output.push_back(0);  // pz
				output.push_back(1);  // ch
				SendMessage(Code(),output,"Dummy test routine");
				output.clear();
				output.push_back(0);
				output.push_back(4);   // a jet
				output.push_back(0.5); // sin theta ~ radius
				output.push_back(0);   // px
				output.push_back(0);   // py
				output.push_back(5);   // pz
				SendMessage(Code(),output,"Dummy test routine");
			}
		virtual vector<pair<string,float> > OptionsList() 
			{ 
				vector<pair<string,float> > output ; 
				pair<string,float> mypair;
				mypair.first = "option 1";
				mypair.second = 10;
				output.push_back(mypair);
				mypair.first = "dummy 2";
				mypair.second = 3.1415;
				output.push_back(mypair);
				return output;
			}
};

void AlephExManager::UserInit() 
{
AlephRegisteredAction<testclass> mytestclass;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  User Event
///////////////////////////////////////////////////////////////////////
bool AlephExManager::UserEvent(AlphaBanks& EventInfo)
{
int event = EventInfo.Event().number();
int run = EventInfo.Run().number();
cout << run << " " << event << endl;
AlephCollection<AlElec *> theElecs=EventInfo.ElecPV();
cout << theElecs.size() << " Elecs" << endl;
for(AlephCollection<AlElec *>::iterator imu = theElecs.begin(); imu< theElecs.end(); imu++)
{
if(((*imu)->getTrack())&&((*imu)->getEflw()))
cout << (*imu)->getTrack()->QE() << "  " << (*imu)->getEflw()->QE() << endl;
}
return true;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//  User Term
///////////////////////////////////////////////////////////////////////
void AlephExManager::UserTerm() {}
