#ifndef _CCMEMHANDLE_H_
#define _CCMEMHANDLE_H_

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

struct MemHandle
{
   // Memory pool index, specifies which memory pool a block is in.
   unsigned short mPoolIndex;
   // Memory block index, specifies which block within the memory pool.
   unsigned short mBlockIndex;

   // Constructor
   MemHandle()
   {
      mPoolIndex = 0;
      mBlockIndex = 0;
   }

   // Constructor
   MemHandle(unsigned short aPoolIndex, unsigned short aBlockIndex)
   {
      mPoolIndex = aPoolIndex;
      mBlockIndex = aBlockIndex;
   }
};

// Operator
inline bool operator==(const MemHandle& lhs, const MemHandle& rhs)
{
   return lhs.mPoolIndex == rhs.mPoolIndex && lhs.mBlockIndex == rhs.mBlockIndex;
}

// Operator
inline bool operator!=(const MemHandle& lhs, const MemHandle& rhs)
{
   return lhs.mPoolIndex != rhs.mPoolIndex && lhs.mBlockIndex != rhs.mBlockIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class for classes whose storage is managed by memory pools.
// Inheriting classes contain a memory handle.

class HasMemHandle
{
public:
   MemHandle mMemHandle;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif