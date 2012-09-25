// Gold.h: interface for the CGold class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GOLD_H
#define GOLD_H

#include "mseq.h"

class CGold  
{
public:
  CMseq mseq0; /* 1st m-sequence generator */
  CMseq mseq1; /* 2nd m-sequence generator */

/*
 * It creates a Gold code generator with the two preferred m-sequences
 * with the given seeds. The Gold code generator is returned.
 */
	void Create( unsigned deg, unsigned long p0, unsigned long p1,
		    unsigned long s0, unsigned long s1 );

/* GetNext() gives the next Gold sequence. The sequence is unipolar, ie 1 or 0. */
	char GetNext();

	
	CGold();
	virtual ~CGold();

};

#endif
