//////////////////////////////////////////////////////////
//
// CLASS AlephInteractiveHandler.h
// handles the communication with the external world 
// for interactive sessions
//
// Author :  C. Delaere
//
//////////////////////////////////////////////////////////


#ifndef _ALEPHINTERACTIVEHANDLER_H_
#define _ALEPHINTERACTIVEHANDLER_H_

#include <vector>
using namespace std;

class AlphaBanks;
class AlephAbstractInteractiveFunction;

class AlephInteractiveHandler
{
	public:
		// the instance function of the  Singleton
		static AlephInteractiveHandler* TheAlephInteractiveHandler();
		// the list of interactive functions
		static vector<AlephAbstractInteractiveFunction*> InteractiveFunctionsList;
		// configure the communications
		void ConfigureProtocol(string myname, string yourname);
		// prepare the run (send list of user's functions, finish with ready
		void InitiateConnection(int& ier);
		// communicate with the external world using driver and user's functions
		int HandleEvent(AlphaBanks& bb);
		// terminate the session by sending the 999 message.
		void CloseConnection();
		// Do we want all the events or just selected ones ?
		bool KeepAllEvents() {return kae;}

	protected:
		// constructor and destructor
		AlephInteractiveHandler();
		~AlephInteractiveHandler();

	private:
		// the pointer to the single static instance
		static AlephInteractiveHandler* _theAlephInteractiveHandler;
		// reset the InteractiveFunctionsList
		void ClearAll();
		// the protocol
		void SendMessage(int code, vector<float>& options, string comment);
		vector<float> ReceiveMessage(int& code, string& comment);
		// Do we want all the events or just selected ones ?
		bool kae;
		// some parameters for the communication
		string me, you;
	friend class AlephAbstractInteractiveFunction;
};

#endif
