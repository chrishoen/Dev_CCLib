#ifndef _CCSTMEMORY_H_
#define _CCSTMEMORY_H_
/*==============================================================================


==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <stddef.h>
#include <new>

namespace CC
{

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Initialize
    
   // This allocates system memory for the message heap and initializes member
   // variables. It is passed the number of bytes of system memory to allocate
   // for the message heap.
   void initializeSTMemory(size_t aAllocate);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Allocate

   // This allocates a variable sized segment of memory from the message heap.
   // It is used analogously to malloc. For 32 bit systems, it allocates on
   // an eight byte boundary. For 64 bit systems, it allocates on a sixteen
   // byte boundary.
   void* allocateSTMemory(size_t aSize);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Check

   // This checks a message for consistency, it should show if a message in the 
   // heap has been overrun. It returns true if the memory seqgment was found
   // to be consistent. It tests pointer range, message sync word and sequence
   // number.

   bool checkSTMemory(void* aMessage);

//******************************************************************************
//******************************************************************************
//******************************************************************************
template <class Message>
Message* newSTMemory()
{
   // Allocate memory for the message from the message heap.
   Message* tPointer = (Message*)allocateSTMemory(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message();

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif

