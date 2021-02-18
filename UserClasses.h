// max number of entries in the paw ntuple
#define NTMAXIN 100 

// user classes declaration
// the definition must be in your main cpp file, with UserInit(), UserEvent() and UserTerm()
// if you want to use the class with the NtupleWriter facility,
// you have to derive from TObject and to implement a (dummy) operator float()
// and to create a dictionary for the file.. cfr ROOT doc for full details
// note: you may have to modify the makefile 
// and to add some includes to Driver/inc/AlephNtupleWriter.h

#ifndef _USERCLASSES_H_
#define _USERCLASSES_H_

#endif
