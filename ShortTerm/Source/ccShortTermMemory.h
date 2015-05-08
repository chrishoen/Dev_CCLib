#ifndef _CCSHORTTERMMEMORY_H_
#define _CCSHORTTERMMEMORY_H_
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
// Initialize short term memory
    
// This allocates system memory for the message heap and initializes member
// variables. It is passed the number of bytes of system memory to allocate
// for the message heap.

void initializeShortTermMemory(size_t aAllocate);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Allocate from short term memory

// This allocates a variable sized segment of memory from the message heap.
// It is used analogously to malloc. For 32 bit systems, it allocates on
// an eight byte boundary. For 64 bit systems, it allocates on a sixteen
// byte boundary.

void* allocateFromShortTermMemory(size_t aSize);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Check short term memory

// This checks a message for consistency, it should show if a message in the 
// heap has been overrun. It returns true if the memory seqgment was found
// to be consistent. It tests pointer range, message sync word and sequence
// number.

bool checkSTM(void* aMessage);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This function template provides a means to allocate memory for a message on
// the short term message heap and to call a constructor for the allocated
// message. It is used analogously to new.

template <class Message>
Message* newSTM()
{
   // Allocate memory for the message from the message heap.
   Message* tPointer = (Message*)allocateFromShortTermMemory(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message();

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Likewise, this also provides constructor arguments.

template <class Message,typename X1>
Message* newSTM(X1 aX1)
{
   // Allocate memory for the message from the message heap.
   Message* tPointer = (Message*)allocateFromShortTermMemory(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message(aX1);

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Likewise, this also provides constructor arguments.

template <class Message,typename X1,typename X2>
Message* newSTM(X1 aX1,X2 aX2)
{
   // Allocate memory for the message from the message heap.
   Message* tPointer = (Message*)allocateFromShortTermMemory(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message(aX1,aX2);

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif

