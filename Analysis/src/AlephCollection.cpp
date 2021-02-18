////////////////////////////////////////////////////////
//
// Implementation of Class AlephCollection
//
// Author: Dan Wallin (with contributions from M. Hoerndl)
// modified by:  C. Delaere, V. Lemaitre, O. van der Aa :
//                 - added Pointers method
//                 - added Leptons filter algos
//                 - added GetSum and GetMiss
//                 - new Jet Algos (form Orca)
//
////////////////////////////////////////////////////////

#include "AlephCollection.h"

float  max(float  i, float j)  { return i > j ? i : j; }
float  max(double i, float j)  { return i > j ? i : j; }
double max(double i, double j) { return i > j ? i : j; }
float  min(float  i, float j)  { return i < j ? i : j; }
float  min(double i, float j)  { return i < j ? i : j; }
double min(double i, double j) { return i < j ? i : j; }
float  max(float  i, double j) { return i > j ? i : j; }
float  min(float  i, double j) { return i < j ? i : j; }

