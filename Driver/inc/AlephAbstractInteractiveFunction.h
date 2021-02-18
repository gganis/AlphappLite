//////////////////////////////////////////////////////////
//
// CLASS AlephAbstractInteractiveFunction
// Abstract class for interactive commands
//
// Author :  C. Delaere
//
/////////////////////////////////////////////////////////////

#ifndef _ALEPHABSTRACTINTERACTIVEFUNCTION_H_
#define _ALEPHABSTRACTINTERACTIVEFUNCTION_H_

#include <vector>
#include <utility>
#include <string>
#include <iostream>

#include "AlephInteractiveHandler.h"

class AlephAbstractInteractiveFunction
{
	public:
		AlephAbstractInteractiveFunction() {cerr << "AlephAbstractInteractiveFunction: default constructor should not be used..." << endl;}
		AlephAbstractInteractiveFunction(AlephInteractiveHandler* ptr) {theHandler=ptr;}
		virtual ~AlephAbstractInteractiveFunction() {}
		virtual string Name() = 0;
		virtual int Code() = 0;
		virtual void Run(vector<float>& options,AlphaBanks& EventInfo) = 0;
		virtual vector<pair<string,float> > OptionsList() = 0;
	protected:
		void SendMessage(int code, vector<float>& options, string comment) { theHandler->SendMessage(code,options,comment);}
	private:
		AlephInteractiveHandler* theHandler;
};

#endif
