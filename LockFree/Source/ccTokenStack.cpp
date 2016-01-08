/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "ccTokenStack.h"

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

TokenStack::TokenStack()
{
   // All null
   mArray    = 0;
   mIndex    = 0;
   mCapacity = 0;
}

TokenStack::~TokenStack()
{
   // Deallocate the array
   if (mArray) delete mArray;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

VOID TokenStack::initialize(int aCapacity)
{
   // Allocate memory for the array
   mArray    = new int[100];

   // initialize variables
   mIndex    = 0;
   mCapacity = aCapacity;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Push an element onto the stack. Return false if stack is full.
//
// The stack index range is [0 , mIndex  ]
// Pushes are valid for     [0 , mIndex-1]
//
//    push(aX)
//       mArray[mIndex]=aX
//       mIndex++
//

bool TokenStack::push (int aValue)
{
   // Guard for full, stack index is at capacity
   if (mIndex >= mCapacity) return false;

   // Increment the stack index
   int tOriginal = (int)InterlockedExchangeAdd((PLONG)&mIndex,1);

   // Guard for full again
   if (tOriginal >= mCapacity)
   {
      // Undo the increment and exit
      InterlockedDecrement((PLONG)&mIndex);
      return false;
   }

   // Push the value at the original stack index
   mArray[tOriginal] = aValue;
   return true;

   // Done
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Pop an element off of the stack. Return null if stack is empty.
//
// The stack index range is [0 , mIndex  ]
// Pops are valid for       [1 , mIndex  ]
//
//    pop(aX)
//       tX = mArray[mIndex]
//       mIndex--
//       aX = tX
// 

bool TokenStack::pop (int* aValue)
{
   // Guard for full, stack index is at zero
   if (mIndex <= 0) return false;

   // Decrement the stack index
   int tOriginal = (int)InterlockedExchangeAdd((PLONG)&mIndex,-1);

   if (tOriginal <= 0)
   {
      // Undo the decrement and exit
      InterlockedDecrement((PLONG)&mIndex);
      return false;
   }

   // Pop the element before the stack index
   *aValue = mArray[tOriginal - 1];

   // Done
   return true;
}

}//namespace

//******************************************************************************
/*
Stack <Element,Allocate>

This structure implements a stack of type Element and of size Allocate. It 
provides members that implement stack push and pop operations, which use 
element Tokens. It provides members that give direct access to the stack
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
         0 | I | P           PF = 1
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
         1 | I | P
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
         2 | I | P
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
         3 | I | P
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
             I
*/

