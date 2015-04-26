/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccShortTermMemory.h"

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// structors

ShortTermMemory::ShortTermMemory ()
{
   mBasePtr=0;
   mWorkingPtr=0;
   mWorkingLength=0;                               
   mMaxLength=0;
   mMemAllocCode=0;
}

ShortTermMemory::ShortTermMemory (char* address,int size)
{
   mBasePtr=address;
   mWorkingPtr=mBasePtr;
   mWorkingLength=0;
   mMaxLength=size;
   mMemAllocCode=0;
}

ShortTermMemory::ShortTermMemory (int size,bool fillZero)
{
   memAlloc(size);

   if (fillZero)
   {
      memset(mBasePtr,0,size);
   }
}

//******************************************************************************
// buffer base address

void ShortTermMemory::setBaseAddress (char* address,int size)
{
   memFree();

   mBasePtr=address;
   mWorkingPtr=mBasePtr;
   mWorkingLength=0;
   mMaxLength=size;
   mMemAllocCode=0;
}

char* ShortTermMemory::getBaseAddress ()
{
   return mBasePtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// memory management

void ShortTermMemory::memAlloc (int size)
{
   mBasePtr = (char*) malloc(size);

   mWorkingPtr=mBasePtr;
   mWorkingLength=0;
   mMaxLength=size;
   mMemAllocCode=1;
}

//******************************************************************************

void ShortTermMemory::memFree ()
{
   if(mMemAllocCode)
   {
      free((void*)mBasePtr);
   }

   mBasePtr=0;
   mWorkingPtr=0;
   mMemAllocCode=0;
   mWorkingLength=0;
   mMaxLength=0;
}

//******************************************************************************

void ShortTermMemory::reset ()
{
   mWorkingPtr=mBasePtr;
   mWorkingLength=0;
}

//******************************************************************************

void ShortTermMemory::rewind ()
{
   mWorkingPtr=mBasePtr;
}

//******************************************************************************

void ShortTermMemory::forward (int size)
{
   if (size + mWorkingPtr - mBasePtr > mMaxLength) return;

   mWorkingPtr    += size;
   mWorkingLength += size;
}

//******************************************************************************

void ShortTermMemory::advance (int size)
{
   if (size + mWorkingPtr - mBasePtr > mMaxLength) return;

   mWorkingPtr    += size;
   mWorkingLength += size;
}

//******************************************************************************

void ShortTermMemory::fillZero (int size)
{
}

//******************************************************************************
// buffer position

bool ShortTermMemory::setPosition (char* address)
{
   mWorkingPtr=address;
   return true;
}

bool ShortTermMemory::setPosition (int index)
{
   if (index>=mMaxLength) return false;

   mWorkingPtr=&mBasePtr[index];

   return true;
}

char* ShortTermMemory::getPosition ()
{
   return mWorkingPtr;
}

char* ShortTermMemory::getPositionC ()
{
   return mWorkingPtr;
}

void* ShortTermMemory::getPositionV ()
{
   return (void*)mWorkingPtr;
}

//******************************************************************************
void ShortTermMemory::show()
{
   int tLength = mMaxLength;
   if (tLength>50) tLength=50;
	printf(" 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");
	for (int i=0;i<tLength;i++)
	{
		printf("%02X",(unsigned char)mBasePtr[i]);
	}
   printf("\n\n");
}

//******************************************************************************
}//namespace



