#ifndef _CCSHAREDCHANNEL_H_
#define _CCSHAREDCHANNEL_H_
/*==============================================================================

Shared memory channel. 


==============================================================================*/
#include "ccLFValueQueue.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

class SharedChannel
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Constructor
   SharedChannel();
  ~SharedChannel();

   // Initialize the stack to either allocate memory from the system heap or
   // to use external memory that has already been allocated for it.
   // If aMemory is null then it mallocs from the system heap. If not, then
   // it uses the memory pointed to by aMemory.
   // If external memory is used, it must be of a size obtained by a call to
   // getMemorySize.
   //
   // Initialize the stack to full. Push the indices of the blocks for which 
   // this will be used onto the stack.
   // For aAllocate==10 this will push 9,8,7,6,5,4,3,2,1,0 so that element
   // zero will be the first one poped.
   void initialize(bool aConstructorFlag,void* aMemory);

   // Deallocate memory.
   void finalize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // If this flag is false then the memory for this object was created
   // externally. If it is true then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mFreeMemoryFlag;

   // Pointer to memory for which the stack resides. This is either created
   // externally and passed as an initialization parameter or it is created
   // on the system heap at initialization.
   void* mMemory;

   // Queue number of elements.
   static const int cNumElements = 1000;
   
   // Queue.
   LFValueQueue<int> mQueue;
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _CCSHAREDCHANNEL_CPP_
          SharedChannel gSharedChannel;
#else
   extern SharedChannel gSharedChannel;
#endif

//******************************************************************************

}//namespace
#endif

