//-----------------------------------------------------------------------------
//
//  originally taken from:
//
//  COOL Program Library  
//  Copyright (C) CERES collaboration, 1996
//
//  Returns resource value read from file. If not available uses default
//  value passed as argument.
//  The resource line must be given as:
//          resource: value
//  Comments beginning with '!' or '#' can be added to the resource file.
//
//  05-aug-99 ap: modified to not use RW any longer (use SimpleTokenizer instead)
//                limitation for T=string: returns only the first token after the name
//
//  10-aug-99 ap: added some further readers to increase flexibility (by G. Dissertori)
//
//  summer 2001 : added some further readers to handle very specific cases (by C. Delaere)
//
//
//-----------------------------------------------------------------------------

#ifndef _GETDEFAULT_H_
#define _GETDEFAULT_H_

#include <fstream>
#include <sstream>
#include <vector>

#include "SimpleTokenizer.h"

using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


//! version for reading in a simple type
template<class T>
T GetDefaultValue(const char* filename, const char* inName, const T& defv)
{
   T value = defv;
   ifstream ifs(filename);
   
   String name(inName);

   SimpleTokenizer *next;
   vector<String> tokens;

   char buffer[512];
   ifs.getline(buffer,512);
   String *line = new String(buffer);

   while (!ifs.eof()) {
      next = new SimpleTokenizer(" :\t", "!#\n\0"); // token delimiters: <space>, ":" or <tab>
				                    // terminators: "!", "#", "\n", "\0"
      tokens = next->tokenize(*line);
      if (tokens.size() > 1) {
	if (tokens[0] == name) {		    // resource found
	  istringstream ist(tokens[1]);
	  ist >> value;				    // let istream do the type conversion
	  delete next;				    // remove old tokenizer
	  tokens.clear();
	  break;
	}
      }
      tokens.clear();
      delete next;				    // remove old tokenizer
      
      delete line;				    // get rid of old content
      ifs.getline(buffer,512);
      line = new String(buffer);
   }
   delete line;
   return value;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//! version which looks for more than one token of the same name, returns vector<T>
template<class T>
vector<T> GetManyDefaultValues(const char* filename, const char* inName, const T& defv)
{
   T value = defv;
   ifstream ifs(filename);
   
   String name(inName);

   SimpleTokenizer *next;
   vector<String> tokens;
   vector<T> ValueVector;

   char buffer[512];
   ifs.getline(buffer,512);
   String *line = new String(buffer);


   next = new SimpleTokenizer(" :\t", "!#\n\0"); // token delimiters: <space>, ":" or <tab>
                                                    // terminators: "!", "#", "\n", "\0"
   while (!ifs.eof()) {
      tokens = next->tokenize(*line);
      if (tokens.size() > 1) {
	if (tokens[0] == name) {		    // resource found
	  istringstream ist(tokens[1]);
	  ist >> value;				    // let istream do the type conversion
	  
	  tokens.clear();
	  ValueVector.push_back(value);
	}
      }
      tokens.clear();
      
      delete line;				    // get rid of old content
      ifs.getline(buffer,512);
      line = new String(buffer);
   }
   delete next;                                  // remove old tokenizer
   delete line;

   return ValueVector;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//! version which looks for more than one token of the same name, returns vector<T>
//! specialized for the use of alpha FILIs (specialized delimitors)
template<class T>
vector<T> GetFILIDefaultValues(const char* filename, const char* inName, const T& defv)
{
   T value = defv;
   ifstream ifs(filename);
   
   String name(inName);

   SimpleTokenizer *next;
   vector<String> tokens;
   vector<T> ValueVector;

   char buffer[512];
   ifs.getline(buffer,512);
   String *line = new String(buffer);


   next = new SimpleTokenizer("'", "!#\n\0"); // token delimiters: "'"
                                                    // terminators: "!", "#", "\n", "\0"
   while (!ifs.eof()) {
      tokens = next->tokenize(*line);
      if (tokens.size() > 1) {
	if (tokens[0] == name) {		    // resource found
	  char output[512];
 	  strncpy(output,tokens[1].c_str(),tokens[1].size());
          output[tokens[1].size()]=0;
	  tokens.clear();
	  value = output;
	  ValueVector.push_back(value);
	}
      }
      tokens.clear();
      
      delete line;				    // get rid of old content
      ifs.getline(buffer,512);
      line = new String(buffer);
   }
   delete next;                                  // remove old tokenizer
   delete line;

   return ValueVector;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//! version which looks only once for a token, but which may hold a vector of
//! entries distributed on several lines. Return also a vector<T>
template<class T>
vector<T> GetSRUNDefaultValues(const char* filename, const char* inName, const vector<T>& defv)
{
   ifstream ifs(filename);
   
   String name(inName);

   SimpleTokenizer *next;
   vector<String> tokens;
   vector<T> ValueVector;
   T value;
   char buffer[512];
   ifs.getline(buffer,512);
   String *line = new String(buffer);

   while (!ifs.eof()) 
   {
      next = new SimpleTokenizer(" :\t", "!#\n\0"); // token delimiters: <space>, ":" or <tab>
				                    // terminators: "!", "#", "\n", "\0"
      tokens = next->tokenize(*line);
      if (tokens.size() > 1) 
      {
	if (tokens[0] == name) 
	{		    // resource found
      		// loop over tokens
	  for (uint i=1; i<tokens.size(); i++)
	    {
	      istringstream ist( tokens[i] );
	      ist >> value;	      // let istream do the type conversion

	      ValueVector.push_back(value);
	    }
	  delete next;				    // remove old tokenizer
	  tokens.clear();
          delete line;
      	  ifs.getline(buffer,512);                  // read the next line
          line = new String(buffer);
          while (!ifs.eof()) 
	  {
             next = new SimpleTokenizer(" :\t", "!#\n\0");  // token delimiters: <space>, ":" or <tab>
	   				                    // terminators: "!", "#", "\n", "\0"
	     tokens = next->tokenize(*line);
	     if (tokens.size() > 0)                // loop over tokens until: EOF or no new value. 
	     {
		     for (uint i=0; i<tokens.size(); i++)
		     {
			     istringstream ist( tokens[i] );
			     ist >> value;
			     if(value == T(0)) 
			     {
				     delete next;
				     tokens.clear();
				     delete line;
				     return ValueVector;
			     }
			     ValueVector.push_back(value);
		     }
	     }
	     else
	     {
		     delete next;
		     tokens.clear();
		     delete line;
		     return ValueVector;
	     }
	     tokens.clear();
	     delete next;                                  // remove old tokenizer
	     delete line;                                  // get rid of old content
	     ifs.getline(buffer,512);
	     line = new String(buffer);
	  }
	  delete line;
	  return ValueVector;
	}
      }
      tokens.clear();
      delete next;				    // remove old tokenizer
      delete line;				    // get rid of old content
      ifs.getline(buffer,512);
      line = new String(buffer);
   }
   delete line;
   return defv;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//! version which looks only once for a token, but which may hold a vector of
//! entries. Return also a vector<T>
template<class T>
vector<T> GetDefaultValueVector(const char* filename, const char* inName, const vector<T>& defv)
{
   ifstream ifs(filename);
   
   String name(inName);

   SimpleTokenizer *next;
   vector<String> tokens;
   vector<T> ValueVector;
   T value;
   char buffer[512];
   ifs.getline(buffer,512);
   String *line = new String(buffer);

   while (!ifs.eof()) {
      next = new SimpleTokenizer(" :\t", "!#\n\0"); // token delimiters: <space>, ":" or <tab>
				                    // terminators: "!", "#", "\n", "\0"
      tokens = next->tokenize(*line);
      if (tokens.size() > 1) {
	if (tokens[0] == name) {		    // resource found

	  // loop over tokens
	  for (uint i=1; i<tokens.size(); i++)
	    {
	      istringstream ist( tokens[i] );
	      ist >> value;	      // let istream do the type conversion

	      ValueVector.push_back(value);
	    }
	  delete next;				    // remove old tokenizer
	  tokens.clear();
          delete line;
	  return ValueVector;
	}
      }
      tokens.clear();
      delete next;				    // remove old tokenizer
      
      delete line;				    // get rid of old content
      ifs.getline(buffer,512);
      line = new String(buffer);
   }
   delete line;
   return defv;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//! version which looks for more than one token of the same name, 
//! returns pair< subname, vector<T> >. 
//! Usefull for user defined cards.
template<class T>
vector< pair< String, vector<T> > > GetUserDefaultValues(const char* filename, const char* inName, T dummy)
{
   T value ;
   typedef vector<T> Tvector;
   typedef pair<String,Tvector> element;
   ifstream ifs(filename);
   
   String name(inName);
   String subname;
   
   SimpleTokenizer *next;
   vector<String> tokens;
   vector<T> ValueVector;

   element processed;
   vector<element> output;
   
   char buffer[512];
   ifs.getline(buffer,512);
   String *line = new String(buffer);


   next = new SimpleTokenizer(" :\t", "!#\n\0");    // token delimiters: <space>, ":" or <tab>
                                                    // terminators: "!", "#", "\n", "\0"
   while (!ifs.eof()) 
   {
      tokens = next->tokenize(*line);
      if (tokens.size() > 2) 
      {
	if (tokens[0] == name)                      // resource found
        {
	  subname =  tokens[1];			    // the subname (user-defined)
	  for (uint i=2; i<tokens.size(); i++)      // loop over tokens
	    {
	      istringstream ist( tokens[i] );
	      ist >> value;	    		    // let istream do the type conversion
	      ValueVector.push_back(value);
	    }
	  processed.first  = subname;
	  processed.second = ValueVector;
	  output.push_back(processed);
	}
      }
      ValueVector.clear();
      tokens.clear();
      delete line;				    // get rid of old content
      ifs.getline(buffer,512);
      line = new String(buffer);
   }
   delete next;                                     // remove old tokenizer
   delete line;

   return output;
}



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//! version which looks only once for a token, but which may hold an array of 
//! some size. Read in are nitems items.
template<class T>
void GetDefaultValue(const char*  filename, const char* inName, T* value, const int nitems)
{  
   int i;
   ifstream ifs(filename);
   SimpleTokenizer *next;
   vector<String> tokens;

   String name(inName);

   char buffer[512];
   ifs.getline(buffer,512);
   String *line = new String(buffer);
   
   while (!ifs.eof()) {
      next = new SimpleTokenizer(" :\t", "!#\n\0"); // token delimiters: <space>, ":" or <tab>
				                    // terminators: "!", "#", "\n", "\0"
      tokens = next->tokenize(*line);
      if (tokens.size() > 1) {
	if (tokens[0] == name) {		    // resource found
	  for (i=0; i<nitems; i++) {
	    if (tokens.size() > size_t(i) ) {
	      istringstream ist( tokens[i+1] );
	      ist >> value[i];                        // let istream do the type conversion
	    }
	  }
         delete next;
	 tokens.clear();
         break;
	}
      }
      delete next;                                // remove old tokenizer
      tokens.clear();

      delete line;				    // get rid of old content
      ifs.getline(buffer,512);
      line = new String(buffer);
   }
  delete line;
}


#endif


