// OGold.cpp: implementation of the COGold class.
//
//////////////////////////////////////////////////////////////////////

#include "OGold.h"

#include <cstdio>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COGold::COGold()
{

}

COGold::~COGold()
{

}

void COGold::Create( unsigned deg, unsigned long p0, unsigned long p1,
		     unsigned long index )
{
  if ( deg > 31 ) {
    fprintf(stderr, "ogold_create: ..cannot handle deg > 31\n");
    return;
  }

  this->gold.Create( deg, p0, p1, index, 1 );
  this->period  = 1 << deg; /* 2^deg */
  this->counter = 1;
}

/* GetNext() gives the next OGold sequence in unipolar value, ie 1 or 0. */
char COGold::GetNext()
{
  if ( this->counter == this->period ) {
    this->counter = 1;
    return 0;
  }

  this->counter++;

  return this->gold.GetNext();
}

