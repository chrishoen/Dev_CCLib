
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <new>
#include "someVariableOne.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance of the block pool

CC::BlockPool Some::VariableOne::mBlockPool;

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create with specified member variables

VariableOne* VariableOne::create (int aIdentifier)
{ 
      // Block pointer.
      VariableOne* tPointer = 0;

      // Allocate a block from the block pool.
      tPointer = (VariableOne*)mBlockPool.get();

      // Call the constructor on the allocated block using placement new.
      new(tPointer)VariableOne(aIdentifier);

      // Return the pointer to the allocated block.
      return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This method calls the class destructor and then deallocates the object
// from system memory or from block universe short term or long term
// memory block pools. It is analogous to delete.

void VariableOne::destroy()
{
   CC::BlockPoolBlock<VariableOne>::deallocate();
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructor, it is called by create after allocation of a new block.

VariableOne::VariableOne()
{
   mIdentifier = 0;
   mValue = 0;
}

// Constructor, it is called by create after allocation of a new block.

VariableOne::VariableOne(int aIdentifier)
{
   mIdentifier = aIdentifier;
   mValue = 0;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace