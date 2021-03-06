/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "ccCriticalSection.h"
#include "ccPointerStack.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

PointerStack::PointerStack()
{
   // All null
   mArray    = 0;
   mIndex    = 0;
   mAllocate = 0;
   mCount    = 0;
}

PointerStack::~PointerStack()
{
   // Deallocate the array
   if (mArray) delete mArray;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void PointerStack::initialize(int aAllocate)
{
   // Allocate memory for the array
   mArray    = new void*[aAllocate];

   // initialize variables
   mIndex    = 0;
   mAllocate = aAllocate;
   mCount    = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Push an element onto the stack. Return false if stack is full.

bool PointerStack::push (void* aPointer)
{
   // Guard
   if (mIndex == mAllocate) return false;

   // Critical section
   enterCriticalSection();

   //Copy the source element to the element at the stack index
   mArray[mIndex] = aPointer;
   // Increment the index
   ++mIndex;
   // Increment the usage counter
   mCount++;

   // Critical section
   leaveCriticalSection();

   // Done
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Pop an element off of the stack. Return null if stack is empty.

void* PointerStack::pop ()
{
   // Guard
   if (mIndex == 0) return 0;

   // Critical section
   enterCriticalSection();

   // Pop the element above the stack index into a temp pointer
   void* tPointer = mArray[mIndex - 1];
   // Decrement the index
   --mIndex;
   // Decrement the usage counter
   mCount--;

   // Critical section
   leaveCriticalSection();

   // Return the temp pointer
   return tPointer;
}

}//namespace

//******************************************************************************
/*
Stack <Element,Allocate>

This structure implements a stack of type Element and of size Allocate. It 
provides members that implement stack push and pop operations, which use 
element pointers. It provides members that give direct access to the stack
push and pop elements so that pushes and pops can be performed with minimum
copying. This is not thread safe.

I  Index
S  Size
PF PushFlag
GF PopFlag
M  MaxNumOfElements
A  Allocate

In the following example M=4,A=4

           +---+             GF = 0 
         0 |   | P           PF = 1
           +---+              I = 0
         1 |   | 
           +---+   
         2 |   | 
           +---+   
         3 |   | 
           +---+   

           +---+             GF = 1 
         0 | X | G           PF = 1
           +---+              I = 1
         1 |   | P
           +---+   
         2 |   | 
           +---+   
         3 |   | 
           +---+   

           +---+             GF = 1 
         0 | X |             PF = 1
           +---+              I = 2
         1 | X | G
           +---+   
         2 |   | P
           +---+   
         3 |   | 
           +---+   

           +---+             GF = 1 
         0 | X |             PF = 1
           +---+              I = 3
         1 | X | 
           +---+   
         2 | X | G
           +---+   
         3 |   | P
           +---+   

           +---+             GF = 1 
         0 | X |             PF = 0
           +---+              I = 4
         1 | X | 
           +---+   
         2 | X | 
           +---+   
         3 | X | G
           +---+   

*/

