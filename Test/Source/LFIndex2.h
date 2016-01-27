#ifndef _LFINDEX2_H_
#define _LFINDEX2_H_

#include <atomic>

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

struct LFIndex 
{  
   int mIndex;  
   int mCount;  

   LFIndex()
   {
      mIndex = 0;
      mCount = 0;
   }

   LFIndex(int aIndex,int aCount)
   {
      mIndex = 0;
      mCount = 0;
   }
};

typedef std::atomic<LFIndex> AtomicLFIndex;

//******************************************************************************
//******************************************************************************
//******************************************************************************


#endif

