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
// The pool index value of all ones is reserved to indicate a null pool and the
// block index value of all ones is reserved to indicate a null block.
//

struct BlockHandle
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Memory pool index, specifies which memory pool a block is in.
   unsigned short mPoolIndex;

   // Memory block index, specifies which block within the memory pool.
   unsigned short mBlockIndex;

   // Invalid index value, used to mark a pool or a block as null.
   static const int  cInvalid = 0xFFFF;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructors.

   BlockHandle::BlockHandle();
   BlockHandle::BlockHandle(unsigned short aPoolIndex, unsigned short aBlockIndex);
   void set(unsigned short aPoolIndex, unsigned short aBlockIndex);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Null block handle value.

   void setNull();
   bool isNull();
   static BlockHandle null();
   static BlockHandle nullH;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set a block handle from the given address of the block. This obtains the 
   // block handle by looking it up in the global block pool facility.

   void set(void* aBlockPointer);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Get the address of the block specified by the block handle. This obtains 
   // the handle by looking it up in the global block pool facility.

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