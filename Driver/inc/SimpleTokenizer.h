// 
// Copyright (C) CERN, Geneva 
// 
// header file for class SimpleTokenizer 
// Created by: Andreas PFEIFFER  at Thu Apr 15 17:30:48 1999
// 
// Last update: 
//              
// 
#ifndef INCLUDED_SIMPLETOKENIZER_H
#define INCLUDED_SIMPLETOKENIZER_H

#include <string>
#include <vector>
using namespace std;

typedef string String;

class SimpleTokenizer  { 

public: 
  SimpleTokenizer(String delim=" ", String term="\n\0");
  virtual ~SimpleTokenizer(); 

private: // inhibit use of these
  SimpleTokenizer(const SimpleTokenizer &); 
  SimpleTokenizer & operator = (const SimpleTokenizer &); 

public: 		// public methods
  void setDelimiters (String str) { delimiters  = str; }
  void setTerminators(String str) { terminators = str; }

  vector<String > tokenize(String) const;

protected:		// protected methods


private:		// private methods


private:		// private attributes
  String delimiters;
  String terminators;

}; 

#endif /* INCLUDED_SIMPLETOKENIZER_H */ 
