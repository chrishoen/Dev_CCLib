#ifndef _CCMESSAGEHEAP_H_
#define _CCMESSAGEHEAP_H_
/*==============================================================================


==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <stddef.h>

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsualtes byte buffers. It represents memory sections. It

class MessageHeap
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constructor

   // This initializes member variables to null values. The message heap does
   // not have memory allocated for it until initialize is called.
   MessageHeap ();

   // This deallocates system memory that was allocated for the message heap.
  ~MessageHeap ();

   //---------------------------------------------------------------------------
   // Initialize
    
   // This allocates system memory for the message heap and initializes member
   // variables. It is passed the number of bytes of system memory to allocate
   // for the message heap.
   void initialize (size_t aAllocate);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Member variables

   // This is a pointer to the begining of the system memory that is allocated
   // for the message heap.
   char* mHeapBeginPtr;

   // This is a pointer to one byte after the end of the message heap. It is 
   // equal to mmHeapBeginPtr + mAllocate.
   char* mHeapEndPtr;

   // This is a pointer the beginning of the next memory sub segment to be 
   // allocated. The allocate method returns this and then incements it
   // by the size of sub segment.
   char* mWorkingPtr;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Allocate

   // This allocates a sub segment of the message memory heap.
   void* allocate(size_t aSize);

};
//******************************************************************************
}//namespace
#endif

