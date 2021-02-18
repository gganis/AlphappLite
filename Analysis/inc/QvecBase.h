//////////////////////////////////////////////////////////
//
// CLASS QvecBase : is independent of Fortran memory 
//                  and serves as base for tracks,
//                  eflows etc.
//
// Author : G. Bagliesi
// modified by C. Delaere: - modified lock (recursive)
//                         - added operator < 
//                           with a variable SortCriterium
//                         - function add converted to 
//                           operator+
//
//////////////////////////////////////////////////////////

 
#ifndef _QVECBASE_H_
#define _QVECBASE_H_

#include "AlObject.h"
#include "TLorentzVector.h"
class QvrtBase;

//! base class for all track-related objects
class QvecBase : public AlObject 
{ 

public:

  //! constructor
  QvecBase();

  //! copy constructor
  QvecBase(const QvecBase & origin);
 
  //! destructor
  ~QvecBase(){}

  //! Compare two objects...
  bool operator<(const QvecBase& other) const;

  //! set the Lorentz Vector
  virtual void setA4V(float x, float y, float z, float e);
  //! set the Lorentz Vector
  virtual void setA4V(TLorentzVector vec){_A4V = vec;}

  //! return the Lorentzvector
  virtual TLorentzVector A4V() const;

  //! set the charge
  virtual void setQCH(float qch){_qch = qch;}

  //! get the type
  virtual ALEPHTYPE TYPE() const {return OBJECT;}
  //! get the origin vertex
  virtual QvrtBase* getOriginVertex() const {return oVertex;}
  //! get the end vertex
  virtual QvrtBase* getEndVertex() const {return eVertex;}
  //! set the origin vertex
  virtual void setOriginVertex(QvrtBase* vrt) {oVertex = vrt;}
  //! set the end vertex
  virtual void setEndVertex(QvrtBase* vrt) {eVertex = vrt;}
  // copies of the ALPHA utility functions (see ALPHA manual)
  virtual float sign(float k) const;   //!< sign
  virtual float QP() const;            //!< |momentum|
  virtual float QX() const;            //!< px
  virtual float QY() const;            //!< py
  virtual float QZ() const;            //!< pz
  virtual float QE() const;            //!< Energy
  virtual float QM() const;            //!< mass
  virtual float QCH() const;           //!< charge
  virtual float QCT() const;           //!< \f$ cos \theta \f$
  virtual float QPH() const;           //!< \f$ \phi \f$
  virtual float QPT() const;           //!< Pt
  virtual float QBETA() const;         //!< \f$ \beta \f$
  virtual float QGAMMA() const;        //!< \f$ \gamma \f$
  virtual float QMSQ2(const QvecBase j) const;   
  virtual float QM2(const QvecBase j) const;     
  virtual float QDMSQ(const QvecBase j) const;   
  virtual float QPPAR(const QvecBase j) const;   
  virtual float QPPER(const QvecBase j) const;   
  virtual float QDOT3(const QvecBase j) const;  //!< 3 dim cross product
  virtual float QDOT4(const QvecBase j) const;  //!< 4 dim cross product
  virtual float QCOSA(const QvecBase j) const;   
  virtual float QDECA2(const QvecBase j) const;  
  virtual float QDECAN(const QvecBase j) const;  

  //! add two objects
  virtual QvecBase operator+(const QvecBase j) const;

  //! get decay angle
  virtual double DECAY_ANG(const QvecBase j) const;

  // the locking
  virtual void Lock(bool recurse=false );   //!< lock the track
  virtual void unLock(bool recurse=false ); //!< unlock the track
  virtual int  isLocked() const;   //!< =0 if not locked, else locked

  //! sort criterium
  //! [0,1,2,3] = [px,py,pz,e]
  //! default is 3 = e
  /*! this is used to define the sort criterium between 2 objects.
   *  Using this, AlephCollections can be sorted as a STL vector, 
   *  just using sort.
   *  Be Carefull: sort will NOT work with collections of pointers.
   *  for that, you have to define some functor calling QvecBase::operator<
   */
  static int SortCriterium;

protected:
  TLorentzVector _A4V; //!< this is a data member containing the instance of the four vector 
  QvrtBase* oVertex;     //!< the origin vertex
  QvrtBase* eVertex;     //!< the end vertex
  int _locked;           //!< lock status, returned by isLocked()
  float  _qch;           //!< charge, returned by QCH()

private:
  static int NERR;
};

#endif

