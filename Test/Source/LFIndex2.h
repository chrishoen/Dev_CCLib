#ifndef _LFINDEX2_H_
#define _LFINDEX2_H_

#include <atomic>

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

typedef union
{
    struct 
    { 
      int mIndex;  
      int mCount;  
    };
    unsigned long long mPack;

} LFIndex22;

struct LFIndex 
{  
   int mIndex;  
   int mCount;  
};

inline LFIndex LFIndexCon(int aIndex,int aCount)
{
   LFIndex tX;
   tX.mIndex = aIndex;
   tX.mCount = aCount;
   return tX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

typedef std::atomic<LFIndex> AtomicLFIndex;

inline int& LFIindex(AtomicLFIndex& tA)
{
   return (((LFIndex*)&tA)->mIndex);
}

inline int& LFIcount(AtomicLFIndex& tA)
{
   return (((LFIndex*)&tA)->mCount);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
#if 0
inline bool operator==(const LFIndex& lhs, const LFIndex& rhs)
{
   return lhs.mIndex==rhs.mIndex && lhs.mCount==rhs.mCount;
}
#endif

//******************************************************************************

#endif


