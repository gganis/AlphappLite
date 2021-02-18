//////////////////////////////////////////////////////////
//
// CLASS AlephRegisteredAction
// Registers an interactive function class to ALPHA++
//
// Author :  C. Delaere
//
/////////////////////////////////////////////////////////////

#ifndef _ALEPHREGISTEREDACTION_H_
#define _ALEPHREGISTEREDACTION_H_

#include <vector>

#if defined(__GNUC__)
#pragma interface
#endif

class AlephAbstractInteractiveFunction;
class AlephExManager;

template<class Type>
class AlephRegisteredAction
{
	public:
		AlephRegisteredAction();
		virtual ~AlephRegisteredAction() {}
};


#if defined(__GNUC__)
#pragma implementation
#endif

#include <typeinfo>
#include "AlephAbstractInteractiveFunction.h"
#include "AlephInteractiveHandler.h"

template <class Type>
AlephRegisteredAction<Type>::AlephRegisteredAction()
{
	// instanciate the class
	Type* myclass = new Type(AlephInteractiveHandler::TheAlephInteractiveHandler());
	// check that it is an AlephAbstractInteractiveFunction
	AlephAbstractInteractiveFunction* mycheckedclass = dynamic_cast<AlephAbstractInteractiveFunction*>(myclass);
	if(mycheckedclass==NULL)
	{
		cerr << "ERROR: tried to register the class " << typeid(myclass).name() << " as an AlephAbstractInteractiveFunction" << endl;
		delete myclass;
		return;
	}
	// check that it is not already registered
	string name = mycheckedclass->Name();
	for(vector<AlephAbstractInteractiveFunction*>::iterator existing = AlephInteractiveHandler::InteractiveFunctionsList.begin();
			existing<AlephInteractiveHandler::InteractiveFunctionsList.end(); existing++)
		if ((*existing)->Name() == name)
		{
			delete myclass;
			return;
		}
	// check if there is an old action for this code... if this is the case, delete it.
	int code = mycheckedclass->Code();
	for(vector<AlephAbstractInteractiveFunction*>::iterator existing = AlephInteractiveHandler::InteractiveFunctionsList.begin();
			existing<AlephInteractiveHandler::InteractiveFunctionsList.end(); existing++)
		if ((*existing)->Code() == code)
		{
			delete *existing;
			*existing = myclass;
			return;
		}
	// add the class to the registry.
	AlephInteractiveHandler::InteractiveFunctionsList.push_back(myclass);
}

#endif
