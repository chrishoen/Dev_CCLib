#ifndef _CCBLOCKHANDLE_H_
#define _CCBLOCKHANDLE_H_

/*==============================================================================
Block handle class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Blocks in a block pool are accessed via a block handle. A block handle
// contains a pool index and a block index. The pool index indicates which pool
// a block belongs to and a block index indicates which block within the pool 
// it is. Methods are provided to convert between block pointers and block
// handles.
//
// The pool index value of zero is reserved to indicate a null pool and the
// block index value of zero is reserved to indicate a null block.
//

struct BlockHandle
{
   // Invalid node
   static const int  cInvalid = 0xFFFF;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members

   // Memory pool index, specifies which memory pool a block is in.
   unsigned short mPoolIndex;
   // Memory block index, specifies which block within the memory pool.
   unsigned short mBlockIndex;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constructor

   BlockHandle::BlockHandle()
   {
      mPoolIndex  = cInvalid;
      mBlockIndex = cInvalid;
   }

   BlockHandle::BlockHandle(unsigned short aPoolIndex, unsigned short aBlockIndex)
   {
      mPoolIndex  = aPoolIndex;
      mBlockIndex = aBlockIndex;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Set

   void setNull()
   {
      mPoolIndex  = cInvalid;
      mBlockIndex = cInvalid;
   }

   // Set
   void set(unsigned short aPoolIndex, unsigned short aBlockIndex)
   {
      mPoolIndex  = aPoolIndex;
      mBlockIndex = aBlockIndex;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Null

   bool isNull()
   {
      return mPoolIndex==cInvalid || mBlockIndex==cInvalid;
   }

   static BlockHandle null()
   {
      BlockHandle tTemp;
      tTemp.setNull();
      return tTemp;
   }

   static BlockHandle nullH;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Handle to pointer conversions.

   static void* ptr(BlockHandle aBlockHandle);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators

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