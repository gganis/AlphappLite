//////////////////////////////////////////////////////////
// Class AlephCardsReader:
// sets default values, reads cards file and holds the cards
// to be updated whenever new card appears
//
// Author : G.Dissertori
//
///////////////////////////////////////////////////////////

#ifndef _ALCARDSREADER_H_
#define _ALCARDSREADER_H_

#include "GetDefaultValue.h"

typedef pair<String,vector<double> > element; //!< what makes the user card information 

class AlephCardsReader {

public:

  //! constructor : sets defaults and reads the cards
  AlephCardsReader();

 
  // methods : 
  vector<long>   getNevt() const;      //!< NEVT card

  vector<int>    getClass() const;     //!< CLAS card

  vector<string> getDbFiles() const;   //!< FILI card = database files for alpha++

  string         getDbType() const;    //!< DBTY card = database type

  string         getTaType() const;    //!< TATY card = transaction type (read or write)

  string         getSeType() const;    //!< SETY card = session type (batch or inter)
  
  string         getAlphaFilo() const; //!< card AFIO = FILO for alpha

  vector<string> getAlphaFili() const; //!< card AFII = FILI for alpha

  vector<string> getAlphaRead() const; //!< card AREA = READ for alpha

  vector<long>   getAlphaSrun() const; //!< card ASRU = SRUN for Alpha
  
  string         getAlphaCard() const; //!< card ACAR = use std. user ALPHA cards

  string         getHist() const;      //!< HIST card

  unsigned long  getSeed() const;      //!< SEED card = seed for the random generator
  
  vector<element> getUserCards() const;//!< USER card = what the user wants
  
  vector<float>  MUIDcuts() const;     //!< MUID card

  vector<float>  ELIDcuts() const;     //!< ELID card

  vector<float>  TAIDcuts() const;     //!< TAID card
  

private:

  void parseInputCards();
  
  vector<long>      _Nevt;
  vector<int>       _Class;
  vector<string>    _DbFiles;
  string            _DbType;
  string            _TaType;
  string            _SeType;
  string            _AlphaFilo;
  vector<string>    _AlphaFili;
  vector<string>    _AlphaRead;
  vector<long>      _AlphaSrun;
  string            _AlphaCard;
  string            _Hist;
  vector<element>   _UserCards;
  vector<float>     _Muid;
  vector<float>     _Elid;
  vector<float>     _Taid;
  unsigned long     _Seed;
};

#endif

