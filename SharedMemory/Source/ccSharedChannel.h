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

   // Initialize the queue and the synchronization objects.
   // It is passed three parameters.
   // 
   // aServer is true if server, false if client.
   //
   // aMemory is a pointer to external memory allocated for the entire
   // channel. If this is null then system heap memory is allocated for
   // the channel.
   // 
   // If aConstructor is true then constructors are called for all internal
   // objects created for the channel. If false then the constructors are not
   // called.This is false if the block pool resides in shared memory and has
   // already been created. This is true otherwise.

   void initialize(bool aServerFlag,bool aConstructorFlag,void* aMemory);

   // Deallocate memory.
   void finalize();

   // Interprocess synchronization.
   bool putSemaphore     (void);
   bool getSemaphore     (void);
   bool putMutex         (void);
   bool getMutex         (void);

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // pimpl idiom.

protected:
   class Specific;
   Specific* mSpecific;

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

