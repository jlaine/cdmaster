// Gold.cpp: implementation of the CGold class.
//
//////////////////////////////////////////////////////////////////////

#include "Gold.h"

#include <cstdio>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGold::CGold()
{

}

CGold::~CGold()
{

}

/*
 * It creates a Gold code generator with the two preferred m-sequences
 * with the given seeds. The Gold code generator is returned.
 */
void CGold::Create( unsigned deg, unsigned long p0, unsigned long p1,
		    unsigned long s0, unsigned long s1 )
{
  if ( deg > 31 ) {
    fprintf(stderr, "gold_create: ..cannot handle deg > 31\n");
    return; 
  }

  this->mseq0.Create( deg, p0, s0 );
  this->mseq1.Create( deg, p1, s1 );
}


/* GetNext() gives the next Gold sequence. The sequence is unipolar, ie 1 or 0. */
char CGold::GetNext()
{
  return this->mseq0.GetNext() ^ this->mseq1.GetNext();
}


