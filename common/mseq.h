// Mseq.h: interface for the CMseq class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MSEQ_H
#define MSEQ_H

class CMseq  
{
public:
	unsigned long state; /* PN register state */
	unsigned long mask;  /* the mask to get the next state */


/* 
 * It create an m-sequence generator with the given generator
 * polynomial and the initial register sate.
 * The max degree of the generator poly is 31.
 */
	void Create( unsigned deg, unsigned long poly, unsigned long seed );

/*
 * GetNext() gives the next m-sequence bit of the m-sequence generator.
 * The generated bit is unipolar, ie 1 or 0.
 */
	char GetNext();
	CMseq();
	virtual ~CMseq();
};

#endif
