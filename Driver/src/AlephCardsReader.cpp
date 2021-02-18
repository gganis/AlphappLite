//////////////////////////////////////////////////////////
// Implemenatation file for Class AlephCardsReader:
// sets default values, reads cards file and holds the cards
// to be updated whenever new card appears
//
// Author : G.Dissertori
// 08.2001: modified by C.Delaere (new cards and rules)
// 08.2002: FILO card
//
///////////////////////////////////////////////////////////

#include <iostream>

#ifndef OS_NO_STD_NAMESPACE
  using namespace std;
#endif
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "AlephSession.h"
#include "AlephCardsReader.h"
#include "GetDefaultValue.h"

extern int setenv(const char*, const char*, int);
extern ofstream fout;

// constructor : sets defaults and reads the cards
AlephCardsReader::AlephCardsReader()
{
  fout << endl;
  fout << " ======== AlephCardsReader constructor ======== " << endl;
  fout << endl;
  // the cards file is set by an environment variable
  char* CardsFile = getenv("ALPHAPP_CARDS");
  if (CardsFile == "") CardsFile = "alpha++.input";
  fout << " Cardsfile = " << CardsFile << endl << endl;
  // default setting;
  _Nevt.push_back(2000000000);
  string DefDbFile("defaultFile");
  string DefReadFile("mc94");
  vector<int> DefClass(1,-1);
  vector<string> readFiliFiles;
  vector<string> readDbFiles;
  vector<float> DefMuidCuts(5);
      DefMuidCuts[0] = 0.5;
      DefMuidCuts[1] = 1.;
      DefMuidCuts[2] = 4.;
      DefMuidCuts[3] = 0.95;
      DefMuidCuts[4] = 10.;
  vector<float> DefElidCuts(13);
      DefElidCuts[0] = 0.5;      DefElidCuts[7]  = -3.;
      DefElidCuts[1] = 1.;       DefElidCuts[8]  = -7.;
      DefElidCuts[2] = 4.;       DefElidCuts[9]  = -5.;
      DefElidCuts[3] = 0.95;     DefElidCuts[10] = 1000.;
      DefElidCuts[4] = 10.;      DefElidCuts[11] = 0.5;
      DefElidCuts[5] = 40.;      DefElidCuts[12] = 1000.;
      DefElidCuts[6] = 1000.;
  vector<float> DefTaidCuts(8);
      DefTaidCuts[0] = 0.01;     DefTaidCuts[4] = 2.;
      DefTaidCuts[1] = 1.;       DefTaidCuts[5] = 4.;
      DefTaidCuts[2] = 1.;       DefTaidCuts[6] = 0.95;
      DefTaidCuts[3] = 1.;       DefTaidCuts[7] = 10.;
  // read the cards  
  // database type
  string defDbType("root");
  _DbType = GetDefaultValue(CardsFile,"DBTY",defDbType);
  fout << " DBTY " << _DbType << endl;
  // number of events
  _Nevt = GetDefaultValueVector(CardsFile,"NEVT",_Nevt);
  if(_Nevt.size()==2)
	  fout << " NEVT " << _Nevt[0] << " - " << _Nevt[1] << endl;
  else if(_Nevt.size()==1)
  	fout << " NEVT " << _Nevt[0] << endl;
  else cerr << " ERROR : AlephCardReader : no NEVT card. Should be a default value." << endl; 
  // Alpha FILI
  string defAlphaFili(" none ");
  _AlphaFili = GetFILIDefaultValues(CardsFile,"AFII ",defAlphaFili);
  for (vector<string>::iterator Ifile = _AlphaFili.begin(); 
       	                        Ifile < _AlphaFili.end();   Ifile++ )
  {
	fout << " AFII '" << (*Ifile) << "'" << endl;
  }
  // Alpha SRUN
  vector<long> defAlphaSrun(0);
  int cnt = 0;
  _AlphaSrun = GetSRUNDefaultValues(CardsFile,"ASRU",defAlphaSrun);
  if (_AlphaSrun.size()!=0) fout << " ASRU ";
  for (vector<long>::iterator Iruns = _AlphaSrun.begin(); 
       	                      Iruns < _AlphaSrun.end();   Iruns++ )
  {
	cnt++;
	fout << (*Iruns) << " ";
	if((cnt%10)==0) fout << endl << "      ";
  }
  if(defAlphaSrun.size()) fout << endl;
  // Database files to analyze
  _DbFiles = GetManyDefaultValues(CardsFile,"FILI",DefDbFile);
  for (vector<string>::iterator Ifile = _DbFiles.begin(); 
       		                Ifile < _DbFiles.end();   Ifile++ )
  {
	fout << " FILI " << (*Ifile) << endl;
  }
  // Check if FILI files included via READ statement
  readFiliFiles = GetManyDefaultValues(CardsFile,"READ",DefReadFile);
  if (readFiliFiles.size() > 0)
    {
      // now loop over READ files and add in FILI statements
      for (vector<string>::iterator Irfile = readFiliFiles.begin(); 
	   Irfile < readFiliFiles.end(); Irfile++ )
	{
	  fout << " READ " << (*Irfile) << endl;
	  readDbFiles = GetManyDefaultValues((*Irfile).c_str(),"FILI",DefDbFile);
	  for (vector<string>::iterator IrFILI = readDbFiles.begin(); 
	       IrFILI < readDbFiles.end(); IrFILI++ )
	    {
	      fout << " FILI " << (*IrFILI) << endl;
	      _DbFiles.push_back(*IrFILI);
	    }
	}
    }
  // class bits to use
  _Class = GetDefaultValueVector(CardsFile,"CLAS",DefClass);
  if(_Class.size()==1) if (_Class[0]==-1) _Class.resize(0);
  fout << " CLAS ";
  for (vector<int>::iterator Iclass = _Class.begin(); 
       Iclass < _Class.end(); Iclass++ )
    {
      fout << (*Iclass) << "  " ;
    }
  if(_Class.size()) fout << endl;
  // Random generator seed
  _Seed = GetDefaultValue(CardsFile,"SEED",_Seed);
  fout << " SEED " << _Seed << endl;
  // HIST
  string defHist("alpha++.hist");
  _Hist = GetDefaultValue(CardsFile,"HIST",defHist);
  fout << " HIST " << _Hist << endl;
  // transaction type
  string defTaType("read");
  _TaType = GetDefaultValue(CardsFile,"TATY",defTaType);
  fout << " TATY " << _TaType << endl;
  string defSeType("batch");
  _SeType = GetDefaultValue(CardsFile,"SETY",defSeType);
  fout << " SETY " << _SeType << endl;
  AlephSession::TheAlephSession()->setSessionType(_SeType);
  // alpha FILO
  string defAlphaFilo(" none ");
  _AlphaFilo = GetDefaultValue(CardsFile,"AFIO",defAlphaFilo);
  fout << " AFIO " << _AlphaFilo << endl;
  // alpha READ
  string defAlphaRead(" none ");
  _AlphaRead = GetManyDefaultValues(CardsFile,"AREA",defAlphaRead);
  for (vector<string>::iterator Ifile = _AlphaRead.begin(); 
       Ifile < _AlphaRead.end(); Ifile++ )
    {
      fout << " AREA " << (*Ifile) << endl;
    }
  // alpha cards file
  string defAlphaCard(" none ");
  _AlphaCard = GetDefaultValue(CardsFile,"ACAR",defAlphaCard);
  fout << " ACAR " << _AlphaCard << endl;
  // User defined cards
  _UserCards = GetUserDefaultValues(CardsFile,"USER",1.);
  fout << " USER ";
  for (vector<element>::const_iterator subcard = _UserCards.begin();
                                       subcard < _UserCards.end();
                                       subcard++)
   {
     fout << subcard->first << " : ";
     for(vector<double>::const_iterator value = subcard->second.begin();
                                        value < subcard->second.end();
                                        value ++)
        fout << (*value) << "  ";
     fout << endl << "      ";
   }
  fout << endl;
  // lepton id cuts to use
  _Muid = GetDefaultValueVector(CardsFile,"MUID",DefMuidCuts);
  fout << " MUID ";
  for (vector<float>::iterator Imuid = _Muid.begin(); 
       Imuid < _Muid.end(); Imuid++ )
    {
      fout << (*Imuid) << "  " ;
    }
  fout << endl;
  _Elid = GetDefaultValueVector(CardsFile,"ELID",DefElidCuts);
  fout << " ELID ";
  for (vector<float>::iterator Ielid = _Elid.begin(); 
       Ielid < _Elid.end(); Ielid++ )
    {
      fout << (*Ielid) << "  " ;
    }
  fout << endl;
  _Taid = GetDefaultValueVector(CardsFile,"TAID",DefTaidCuts);
  fout << " TAID ";
  for (vector<float>::iterator Itaid = _Taid.begin(); 
       Itaid < _Taid.end(); Itaid++ )
    {
      fout << (*Itaid) << "  " ;
    }
  fout << endl;
  fout << endl;
  fout << " ======== End AlephCardsReader constructor ======== " << endl;
  fout << endl;
}

//////////////////////
// methods : 
//////////////////////

// get the cards info

vector<long>   AlephCardsReader::getNevt() const { return _Nevt; }
vector<int>    AlephCardsReader::getClass() const { return _Class ; }
vector<string> AlephCardsReader::getDbFiles() const { return _DbFiles; }
string         AlephCardsReader::getDbType() const { return _DbType; }
string         AlephCardsReader::getTaType() const { return _TaType; }
string         AlephCardsReader::getSeType() const { return _SeType; }
string         AlephCardsReader::getAlphaFilo() const { return _AlphaFilo; } 
vector<string> AlephCardsReader::getAlphaFili() const { return _AlphaFili; }
vector<string> AlephCardsReader::getAlphaRead() const { return _AlphaRead; }
vector<long>   AlephCardsReader::getAlphaSrun() const { return _AlphaSrun; }
string         AlephCardsReader::getAlphaCard() const { return _AlphaCard; } 
string         AlephCardsReader::getHist() const { return _Hist; }
unsigned long  AlephCardsReader::getSeed() const { return _Seed; }
vector<element> AlephCardsReader::getUserCards() const { return _UserCards; }
vector<float>  AlephCardsReader::MUIDcuts() const { return _Muid ; }
vector<float>  AlephCardsReader::ELIDcuts() const { return _Elid ; }
vector<float>  AlephCardsReader::TAIDcuts() const { return _Taid ; }

