//////////////////////////////////////////////////////////
// Smart Pointer "package"
// allow the creation of an array of void*
// that you can delete using the right destructors.
//
// Authors : C.Delaere, O. van der Aa
//
//////////////////////////////////////////////////////////

#ifndef _SMARTPOINTER_H_
#define _SMARTPOINTER_H_

//! The base class, returning a void*
/*! using this clas, you can create an heterogeneous array 
 * of pointers, and delete them using the right destructor
 */
class smart_void
{
public:
	virtual void* theaddr() = 0;
	virtual ~smart_void() {}
};

//! The deriving class(es), containing the C++ pointer
/*! this class always knows the pointer type, 
 * so that the correct destructor can be called.
 */
template<class T>
class smart_type: public smart_void
{
public:
	smart_type(unsigned int size = 1) {addr = new T[size];} 
	~smart_type()   {delete [] addr;}
	void* theaddr() {return addr;}
	void* theptr()  {return &addr;}
private:
	T* addr;
};

#endif
