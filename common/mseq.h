// Mseq.h: interface for the CMseq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSEQ_H__85F752A2_96C8_42FF_B9F0_DE4EA47FD227__INCLUDED_)
#define AFX_MSEQ_H__85F752A2_96C8_42FF_B9F0_DE4EA47FD227__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_MSEQ_H__85F752A2_96C8_42FF_B9F0_DE4EA47FD227__INCLUDED_)
