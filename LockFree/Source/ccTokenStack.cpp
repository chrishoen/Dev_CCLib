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
   mAllocate = 0;
}

TokenStack::~TokenStack()
{
   // Deallocate the array
   if (mArray) delete mArray;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TokenStack::initialize(LONG aAllocate)
{
   // Allocate memory for the array
   mArray    = new LONG[aAllocate];

   // initialize variables
   mIndex    = 0;
   mAllocate = aAllocate;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Push an element onto the stack. Return false if stack is full.

bool TokenStack::push (LONG aValue)
{
   // Guard
   if (mIndex == mAllocate) return false;

   LONG tOriginal = InterlockedIncrement(&mIndex);

   //Copy the source element to the element at the stack index
   mArray[tOriginal] = aValue;

   // Done
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Pop an element off of the stack. Return null if stack is empty.

LONG TokenStack::pop ()
{
   // Guard
   if (mIndex == 0) return 0;

   LONG tOriginal = InterlockedDecrement(&mIndex);
   if (tOriginal == 0) return -1;

   // Pop the element above the stack index into a temp Token
   return mArray[tOriginal - 1];
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

