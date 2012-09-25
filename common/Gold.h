// Gold.h: interface for the CGold class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOLD_H__707F6185_12EE_419B_8EA3_D25BB499F5C6__INCLUDED_)
#define AFX_GOLD_H__707F6185_12EE_419B_8EA3_D25BB499F5C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_GOLD_H__707F6185_12EE_419B_8EA3_D25BB499F5C6__INCLUDED_)
