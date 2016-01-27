#ifndef _LFINDEX_H_
#define _LFINDEX_H_

#include <atomic>

/*==============================================================================
==============================================================================*/


#endif

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

typedef std::atomic<LFIndex> AtomicLFIndex;

#if 0

//******************************************************************************
//******************************************************************************
//******************************************************************************
#pragma pack( push, PACK_LFINDEX,1 )

typedef union
{
    struct 
    { 
      int mIndex;  
      int mCount;  
    };
    unsigned long long mPack;

} LFIndex;

#pragma pack( pop, PACK_LFINDEX )

//******************************************************************************
//******************************************************************************
//******************************************************************************

inline LFIndex LFIndexCon(int aIndex,int aCount)
{
   LFIndex tX;
   tX.mIndex = aIndex;
   tX.mCount = aCount;
   return tX;
}

inline std::atomic<LFIndex>& AtomicLFIndex(LFIndex& aX)
{
   return *(std::atomic<LFIndex>*)&aX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************


//******************************************************************************
#endif