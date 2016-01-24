#ifndef _LFINDEX_H_
#define _LFINDEX_H_

#include <atomic>

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

};

inline bool operator==(const LFIndex& lhs, const LFIndex& rhs)
{
   return lhs.mIndex==rhs.mIndex && lhs.mCount==rhs.mCount;
}

#pragma pack( pop, PACK_LFINDEX )

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

inline void LFIset(AtomicLFIndex& tA,int aIndex,int aCount)
{
   tA.store(LFIndex(aIndex,aCount));
}


//******************************************************************************
//******************************************************************************
//******************************************************************************


//******************************************************************************

#endif


#if 0

#endif