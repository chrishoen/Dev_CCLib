
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>
#include "someNodeBlock.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance of the block pool

CC::BlockPool Some::NodeBlock::mBlockPool;

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create with specified member variables

NodeBlock* NodeBlock::create (int aIdentifier)
{ 
      // Block pointer.
      NodeBlock* tPointer = 0;

      // Allocate a block from the block pool.
      tPointer = (NodeBlock*)mBlockPool.get();

      // Call the constructor on the allocated block using placement new.
      new(tPointer)NodeBlock(aIdentifier);

      // Return the pointer to the allocated block.
      return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This method calls the class destructor and then deallocates the object
// from system memory or from block universe short term or long term
// memory block pools. It is analogous to delete.

void NodeBlock::destroy()
{
   CC::BlockPoolBlock<NodeBlock>::deallocate();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

NodeBlock::NodeBlock()
{
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;
}

// Constructor, it is called by create after allocation of a new block.

NodeBlock::NodeBlock(int aIdentifier)
{
   // Identifier
   mIdentifier = aIdentifier;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace