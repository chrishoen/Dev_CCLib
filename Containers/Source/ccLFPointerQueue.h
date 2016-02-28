#ifndef _CCLFPOINTERQUEUE_H_
#define _CCLFPOINTERQUEUE_H_
/*==============================================================================

Lock Free Pointer Queue. 

This implements a pointer queue. The queue is thread safe. It uses an atomic
interlocked compare and exchange to guard against concurrency contentions. 
It is based on a multiple writer, single reader model. A writer starts a write, 
obtaining a write index to the next queue element that is available to be can 
written to. If the queue is full then the write start fails. The writer then
writes to the corresponding queue element. After the write is complete the 
writer somehow signals the reader to read from the queue. The reader wakes up 
and starts a read, obtaining a read index to the next queue element that is 
available to be read from. If the queue is empty, then the read start fails 
(this should not happen because writer should not signal the reader). The 
reader then reads from the corresponding queue element and then calls finish 
read to update the queue state.

==============================================================================*/
#include <atomic>
#include "ccLFIndex.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class LFPointerQueue
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   LFPointerQueue();
  ~LFPointerQueue();

   // Allocate memory for the queue array and initialize the queue logic. 
   // variables. aAllocate is the number of pointers to allocate, the size of
   // the array.
   void initialize(int aAllocate);

   // Deallocate memory
   void finalize();

   // Write a pointer to the queue. Return false if the queue is full.
   bool  writePtr(void* aPointer);

   // Read a pointer from of the queue. Return null if the queue is empty.
   void* readPtr();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue Members

   // Number of blocks allocated
   int mAllocate;
   int mQueueAllocate;
   int mListAllocate;

   void**          mValue;
   AtomicLFIndex*  mQueueNext;

   AtomicLFIndex   mQueueHead;
   AtomicLFIndex   mQueueTail;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Free List Members

   AtomicLFIndex*   mListNext;
   AtomicLFIndex    mListHead;
   std::atomic<int> mListSize;
   
   std::atomic<int>* mListHeadIndexPtr = (std::atomic<int>*)&mListHead;

   static const int cInvalid = 0x80000000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Free List Methods

   bool tryWrite  (void*  aValue);
   bool tryRead   (void** aValue);

   bool listPush(int  aNode);
   bool listPop(int*  aNode);

};

//******************************************************************************

}//namespace
#endif

