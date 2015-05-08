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
// Initialize the short term memory heap.
    
// This allocates system memory for the short term memory heap and
// initializes internal variables. It is passed the number of bytes of
// system memory to allocate for it.

void initializeSTM(size_t aAllocate);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Allocate from the short term memory heap.

// This allocates a variable sized segment of memory from the short term 
// memory heap. It is used analogously to malloc. For 32 bit systems, it
// allocates on an eight byte boundary. For 64 bit systems, it allocates
// on a sixteen byte boundary.

void* allocateFromSTM(size_t aSize);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// This returns true if the given pointer is within the region of short term
// memory, if this pointer points to an object that was allocated as part of
// short term memory.

bool isInSTM(void* aPtr);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Check a message that is in the short term memory heap.

// This checks a message for consistency, it should show if a message in the 
// heap has been overrun. It returns true if the memory segment was found
// to be consistent. It tests pointer range, message sync word and sequence
// number.

bool checkSTM(void* aMessage);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This function template provides a means to allocate memory for a message on
// the short term memory heap and to call a constructor for the allocated
// message. It is used analogously to new.

template <class Message>
Message* newSTM()
{
   // Allocate memory for the message from the short term memory heap.
   Message* tPointer = (Message*)allocateFromSTM(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message();

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Likewise, this also has constructor arguments.

template <class Message,typename X1>
Message* newSTM(X1 aX1)
{
   // Allocate memory for the message from the message heap.
   Message* tPointer = (Message*)allocateFromSTM(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message(aX1);

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Likewise, this also has constructor arguments.

template <class Message,typename X1,typename X2>
Message* newSTM(X1 aX1,X2 aX2)
{
   // Allocate memory for the message from the message heap.
   Message* tPointer = (Message*)allocateFromSTM(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message(aX1,aX2);

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Likewise, this also has constructor arguments.

template <class Message,typename X1,typename X2,typename X3>
Message* newSTM(X1 aX1,X2 aX2,X3 aX3)
{
   // Allocate memory for the message from the message heap.
   Message* tPointer = (Message*)allocateFromSTM(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message(aX1,aX2,aX3);

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Likewise, this also has constructor arguments.

template <class Message,typename X1,typename X2,typename X3,typename X4>
Message* newSTM(X1 aX1,X2 aX2,X3 aX3,X4 aX4)
{
   // Allocate memory for the message from the message heap.
   Message* tPointer = (Message*)allocateFromSTM(sizeof(Message));

   // Call the constructor on the allocated message using placement new.
   new(tPointer)Message(aX1,aX2,aX3,aX4);

   // Return the pointer to the allocated message.
   return tPointer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif

