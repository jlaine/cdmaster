// OGold.h: interface for the COGold class.
//
//////////////////////////////////////////////////////////////////////

#ifndef OGOLD_H
#define OGOLD_H

#include "gold.h"

class COGold  
{
public:

  CGold gold;            /* the Gold code */
  unsigned long period;  /* the period of the Orthogonal Gold code */
  unsigned long counter;

/*
 * It create an OGold code generator with the two preferred m-sequences
 * with the given index. The OGold code generator is returned.
 * The possible range of index is 0 to (2^deg - 1).
 */
	void Create( unsigned deg, unsigned long p0, unsigned long p1,
		     unsigned long index );

/* GetNext() gives the next OGold sequence in unipolar value, ie 1 or 0. */
	char GetNext();
	COGold();
	virtual ~COGold();

};

#endif
