///////////////////////////////////////////////////////////////////////
//
//  The main program to be used in connection with an AlephSession
//               A driver to read the alpha++ database
//
//  Author : Guenther Dissertori  ,  3/11/98
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "AlephSession.h"

///////////////////////////////////////////////////////////
// all output is written to the file set by the this env variable 
///////////////////////////////////////////////////////////

ofstream fout(getenv("APPL_OUT"));

///////////////////////////////////////////////////////////////////////
static void usage(const char *name)
{
  cerr << "usage : " << name << " -l[0 | 1 | 2 | 3 ] " << endl;
  exit(1);
}
///////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
// set the input defaults
  int debuglevel = 0;
// read the input
  if (argc < 2)
  {
    usage(argv[0]);
  }
  else
  {
    for (int i=1; i<argc; i++)
    {
      if (argv[i][0]=='-' && argv[i][1]=='l') 
      {
        switch(argv[i][2])
        {
              case '0':
                debuglevel = 0; break;

              case '1':
                debuglevel = 1; break;

              case '2':
                debuglevel = 2; break;
             
              case '3':
                debuglevel = 3; break;
              
              default: usage(argv[0]);
        }
      } 
    }
  }
// create the session singleton
  AlephSession* aSession = AlephSession::TheAlephSession(); 
// store the debuglevel
  aSession->setDebugLevel(debuglevel);
// init
  AlephRC rc;
  rc = aSession->initialize();
  fout << endl << " return code from session.init = " << (int)rc << endl << endl; 
// run the session
  rc = aSession->run();
  fout << endl << " return code from session.run = " << (int)rc << endl << endl; 
// term
  rc = aSession->terminate();
  fout << endl << " return code from session.term = " << (int)rc << endl << endl; 
  return AlephOK;
}

///////////////////////////////////////////////////////////////////////
// small function which checks if a bit in a Word is set
///////////////////////////////////////////////////////////////////////
int jbit(unsigned  x , int n)
{
 int b;
 int j;
 j=0;
 for (b=0; x !=0 ; x>>=1) {
   b++;
   if((x & 01) && b==n ) j=1;
 }
 return j;
}

