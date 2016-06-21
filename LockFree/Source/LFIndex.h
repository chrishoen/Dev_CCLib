#ifndef _LFINDEX_H_
#define _LFINDEX_H_

#include <atomic>

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

__declspec(align(8))
struct LFIndex
{  
   int mIndex;  
   int mCount;  

   LFIndex() noexcept
   {
      mIndex = 0;
      mCount = 0;
   }

   LFIndex(int aIndex,int aCount) noexcept
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