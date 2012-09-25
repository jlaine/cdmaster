// OGold.h: interface for the COGold class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGOLD_H__5A2E8561_F494_42AD_B58A_A31CB30EB1FE__INCLUDED_)
#define AFX_OGOLD_H__5A2E8561_F494_42AD_B58A_A31CB30EB1FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_OGOLD_H__5A2E8561_F494_42AD_B58A_A31CB30EB1FE__INCLUDED_)
