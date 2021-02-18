//////////////////////////////////////////////////////////
//
// Implementation of
// CLASS AlephInteractiveHandler
// handles the communication with the external world
// for interactive sessions
//
// Author :  C. Delaere
//
//////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h> 
#include "AlephInteractiveHandler.h"
#include "AlephRegisteredAction.h"
#include "AlephAbstractInteractiveFunction.h"
#include "AlphaBanks.h"


AlephInteractiveHandler* AlephInteractiveHandler::TheAlephInteractiveHandler()
{
	if (_theAlephInteractiveHandler)
		return _theAlephInteractiveHandler;
	else
		_theAlephInteractiveHandler = new AlephInteractiveHandler;
	return _theAlephInteractiveHandler;
}

AlephInteractiveHandler::AlephInteractiveHandler()
{
	kae = true;      // want all events (default)
	me  = "ALPHA++"; // why change it ?
	you = "AlVisu";  // default client
}

AlephInteractiveHandler::~AlephInteractiveHandler()
{
	ClearAll();
}

void AlephInteractiveHandler::ConfigureProtocol(string myname, string yourname)
{
	me = myname;
	you = yourname;
}

vector<AlephAbstractInteractiveFunction*> AlephInteractiveHandler::InteractiveFunctionsList = vector<AlephAbstractInteractiveFunction*>(0);

AlephInteractiveHandler* AlephInteractiveHandler::_theAlephInteractiveHandler = NULL;

void AlephInteractiveHandler::ClearAll()
{
	for(vector<AlephAbstractInteractiveFunction*>::iterator existing = AlephInteractiveHandler::InteractiveFunctionsList.begin();
			existing<AlephInteractiveHandler::InteractiveFunctionsList.end(); existing++)
	{
		delete *existing;
	}
	AlephInteractiveHandler::InteractiveFunctionsList.clear();
}

void AlephInteractiveHandler::InitiateConnection(int& ier)
{
	//first send the list of user's functions
	int funccnt = InteractiveFunctionsList.size();
	for(vector<AlephAbstractInteractiveFunction*>::iterator existing = AlephInteractiveHandler::InteractiveFunctionsList.begin();
			existing<AlephInteractiveHandler::InteractiveFunctionsList.end(); existing++)
	{
		vector<float> optionstosend;
		optionstosend.push_back(--funccnt);                             // index
		optionstosend.push_back((*existing)->OptionsList().size());     // option[0]
		optionstosend.push_back((*existing)->Code());                   // option[1]
		SendMessage(-1,optionstosend,(*existing)->Name());
		vector<pair<string,float> > options = (*existing)->OptionsList();
		int cnt = -options.size();
		for(vector<pair<string,float> >::iterator subopt=options.begin();subopt<options.end();subopt++)
		{
			vector<float> optionstosend;
			optionstosend.push_back(funccnt);                       // index
			optionstosend.push_back(cnt++);                         // option[0]
			optionstosend.push_back((*existing)->Code());           // option[1]
			optionstosend.push_back(subopt->second);                // option[2]
			SendMessage(-1,optionstosend,subopt->first);
		}
	}
	//then send the ready message
	vector<float> options;
	options.push_back(0);
	SendMessage(0,options,"Ready");
	//wait for the first next message
	int code = 0;
	string comment = "";
	while(code!=100)
	{
		vector<float> options = ReceiveMessage(code, comment);
		if(code==999) {ier = 1; code = 100;}
	}
	kae = !options[0];
}

int AlephInteractiveHandler::HandleEvent(AlphaBanks& bb)
{
	// This is the main "event loop" in interactive sessions
	// message are received
	// then the right function is called
	// this is done as long as the user don't request the next event.
	vector<float> dummy(0);
	int code = 0;
	string comment = "";
	// first return the general event info...
	for(vector<AlephAbstractInteractiveFunction*>::iterator existing = AlephInteractiveHandler::InteractiveFunctionsList.begin();
			existing<AlephInteractiveHandler::InteractiveFunctionsList.end(); existing++)
	{
		if((*existing)->Code() == 100)
		{
			(*existing)->Run(dummy,bb);
			break;
		}
	}
	// now wait for another request...
        while(1)
	{				
		vector<float> options = ReceiveMessage(code, comment);
		// look in the table for the appropriate function to call
		for(vector<AlephAbstractInteractiveFunction*>::iterator existing = AlephInteractiveHandler::InteractiveFunctionsList.begin();
				existing<AlephInteractiveHandler::InteractiveFunctionsList.end(); existing++)
		{
			if((*existing)->Code() == code)
			{
				(*existing)->Run(options,bb);
				break;
			}
		}
		if (code==100) kae = !options[0]; 
		if ((code==100)||(code==999)) break;
	}
	return (code==999 ? 1 : 0);
}

void AlephInteractiveHandler::CloseConnection()
{
	vector<float> options;
	options.push_back(0);
	SendMessage(999,options,"Terminated");
}

void AlephInteractiveHandler::SendMessage(int code, vector<float>& options, string comment)
{
	char buffer[256];
	// build the message according to options passed
	string message = me;
	message += "><";
	sprintf ( buffer, "%i><", code); 
	message += buffer;
	for(vector<float>::iterator i=options.begin();i<options.end();i++)
	{
		sprintf ( buffer, "%f><", *i);
		message += buffer;
	}
	message += comment;
	// send the message to the standard output.
	cout << message << endl;
}

void Tokenize(const string& str, vector<string>& tokens,const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
          // Found a token, add it to the vector.
          tokens.push_back(str.substr(lastPos, pos - lastPos));
          // Skip delimiters.  Note the "not_of"
          lastPos = str.find_first_not_of(delimiters, pos);
          // Find next "non-delimiter"
          pos = str.find_first_of(delimiters, lastPos);
    }
}

vector<float> AlephInteractiveHandler::ReceiveMessage(int& code, string& comment)
{
	// wait for a full line...
	char command[1024] = {0};
	cin.getline(command,1024);
	// test if it is a formated message (step1)
	if(strcspn(command, you.c_str())!=0)
	{
		code = -1;
		comment = "";
		vector<float> result;
		return result;
	}
	// put the result in a string
	string tobeanalyzed = command;
	// decompose the command in tokens
	vector<string> tokens;
	Tokenize(tobeanalyzed,tokens,"><");
	// Now we have got the tokens... interpret them.
	// test if it is a formated message (step2)
	if(tokens.size()<4)
	{
		code = -1;
		comment = "";
		vector<float> result;
		return result;
	}
	// seems ok... use it.
	sscanf( tokens[1].c_str(), "%i", &code);
	comment = *(tokens.end()-1);
	vector<float> result;
	for(vector<string>::iterator i=tokens.begin()+2;i<tokens.end()-1;i++)
	{
		float num;
		sscanf( i->c_str(), "%f", &num);
		result.push_back(num);
	}
	return result;
}

