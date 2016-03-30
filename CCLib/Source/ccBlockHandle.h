#ifndef _CCBLOCKHANDLE_H_
#define _CCBLOCKHANDLE_H_

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
// Memory handle.

struct BlockHandle
{
   // Memory pool index, specifies which memory pool a block is in.
   unsigned short mPoolIndex;
   // Memory block index, specifies which block within the memory pool.
   unsigned short mBlockIndex;

   // Reset
   inline void reset()
   {
      mPoolIndex = 0;
      mBlockIndex = 0;
   }

   // Set
   inline void set(unsigned short aPoolIndex, unsigned short aBlockIndex)
   {
      mPoolIndex = aPoolIndex;
      mBlockIndex = aBlockIndex;
   }

   inline bool isNull()
   {
      return mBlockIndex==0;
   }

};

// Operator
inline bool operator==(const BlockHandle& lhs, const BlockHandle& rhs)
{
   return lhs.mPoolIndex == rhs.mPoolIndex && lhs.mBlockIndex == rhs.mBlockIndex;
}

// Operator
inline bool operator!=(const BlockHandle& lhs, const BlockHandle& rhs)
{
   return lhs.mPoolIndex != rhs.mPoolIndex && lhs.mBlockIndex != rhs.mBlockIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class for classes whose storage is managed by memory pools.
// Inheriting classes contain a memory handle.

class HasBlockHandle
{
public:
   BlockHandle mBlockHandle;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif