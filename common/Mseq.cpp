// Mseq.cpp: implementation of the CMseq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mseq.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMseq::CMseq()
{

}

CMseq::~CMseq()
{

}

void CMseq::Create( unsigned deg, unsigned long poly, unsigned long seed )
{
  if ( deg > 31 ) {
    fprintf(stderr, "mseq_create: ..cannot handle deg > 31\n");
    fprintf(stderr, " Use mseql_create() instead.\n");
	return;
  }

  this->state = seed;
  this->mask  = poly >> 1;

}


/*
 * GetNext() gives the next m-sequence bit of the m-sequence generator.
 * The generated bit is unipolar, ie 1 or 0.
 */
char CMseq::GetNext()
{
  char seq;
  
  seq = char(this->state & 1);
  this->state >>= 1;
  if ( seq ) this->state ^= this->mask;

  return seq;
}

