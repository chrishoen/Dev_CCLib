#ifndef _LFINDEX_H_
#define _LFINDEX_H_

#include <atomic>

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Index used by lock free container classes.

struct LFIndex
{
   int mIndex;
   int mCount;

   LFIndex()
   {
      mIndex = 0;
      mCount = 0;
   }

   LFIndex(int aIndex, int aCount)
   {
      mIndex = aIndex;
      mCount = aCount;
   }
};

inline bool operator==(const LFIndex& lhs, const LFIndex& rhs)
{
   return lhs.mIndex == rhs.mIndex && lhs.mCount == rhs.mCount;
}

inline bool operator!=(const LFIndex& lhs, const LFIndex& rhs)
{
   return lhs.mIndex != rhs.mIndex && lhs.mCount != rhs.mCount;
}

typedef std::atomic<LFIndex> AtomicLFIndex;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class for lock free container blocks. This is inherited by classes that
// are contained in intrusive lock free containers.

class BaseLFBlock
{
public:
   int mLFNodeIndex;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif