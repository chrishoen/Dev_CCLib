#ifndef _LFINDEX_H_
#define _LFINDEX_H_

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
      mIndex = aIndex;
      mCount = aCount;
   }
};

inline bool operator==(const LFIndex& lhs, const LFIndex& rhs)
{
   return lhs.mIndex==rhs.mIndex && lhs.mCount==rhs.mCount;
}

inline bool operator!=(const LFIndex& lhs, const LFIndex& rhs)
{
   return lhs.mIndex!=rhs.mIndex && lhs.mCount!=rhs.mCount;
}

typedef std::atomic<LFIndex> AtomicLFIndex;

struct AtomicLFIndexBlock 
{  
   AtomicLFIndex mX;
   unsigned long long int mPadding[64/8 - 1];
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
#endif