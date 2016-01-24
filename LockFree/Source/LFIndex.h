#ifndef _LFINDEX_H_
#define _LFINDEX_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#pragma pack( push, PACK_LFINDEX,1 )

class LFIndex
{
public:

   int mIndex;
   int mCount;

   LFIndex()
   {
      mIndex=0;
      mCount=0;
   }

   LFIndex(int aIndex,int aCount)
   {
      mIndex = aIndex;
      mCount = aCount;
   }

   int* index() {return &mIndex;}
   int* count() {return &mCount;}
};

typedef struct
{ 
   int mIndex;
   int mCount;
} LFIndexT;


#pragma pack( pop, PACK_LFINDEX )

//******************************************************************************

#endif

