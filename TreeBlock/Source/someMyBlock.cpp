
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>
#include "someMyBlock.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance of the block pool

CC::BlockPool Some::MyBlock::mBlockPool;

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create with specified member variables

MyBlock* MyBlock::create (int aIdentifier)
{ 
      // Block pointer.
      MyBlock* tPointer = 0;

      // Allocate a block from the block pool.
      tPointer = (MyBlock*)mBlockPool.get();

      // Call the constructor on the allocated block using placement new.
      new(tPointer)MyBlock(aIdentifier);

      // Return the pointer to the allocated block.
      return tPointer;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

MyBlock::MyBlock()
{
   mCode1=101;
   mCode2=102;
   mCode3=103;
   mCode4=104;
}

// Constructor, it is called by create after allocation of a new block.

MyBlock::MyBlock(int aIdentifier)
{
   // Identifier
   mIdentifier = aIdentifier;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace