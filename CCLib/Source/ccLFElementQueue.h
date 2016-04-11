#ifndef _CCLFELEMENTQUEUE_H_
#define _CCLFELEMENTQUEUE_H_
/*==============================================================================

Lock Free Element Queue.

It is Multiple Writer Single Reader.
It is lock free, non blocking.
It is shared memory safe.
It is zero copy.

This implements a queue of fixed size elements, where the queue provides the
memory allocation for the elements (memory for the elements is contained
within the queue). The queue is thread safe. It uses atomic compare and
exchanges to guard against concurrency contentions.

It implements the Michael and Scott algorithm with no backoff. It maintains
storage for the elements by implementing a free list that uses the Trieber 
algorithm with no backoff.

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
// State variables for the queue. These are located in a separate class
// so that they can be located in external memory.

class LFElementQueueState
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Number of elements allocated.
   int mNumElements;
   int mQueueNumElements;
   int mListNumElements;
   int mElementSize;

   // Queue variables.
   AtomicLFIndex     mQueueHead;
   AtomicLFIndex     mQueueTail;

   // Linked list variables.
   AtomicLFIndex     mListHead;
   std::atomic<int>  mListSize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   LFElementQueueState();

   // Initialize.
   void initialize(int aNumElements,int aElementSize,bool aConstructorFlag);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class LFElementQueue
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize(int aNumElements,int aElementSize);

   class MemorySize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // If this flag is false then the memory for this object was created
   // externally. If it is true then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mFreeMemoryFlag;

   // Pointer to memory for which the queue resides. This is either created
   // externally and passed as an initialization parameter or it is created
   // on the system heap at initialization.
   void* mMemory;

   // State variables for the queue. These are located in a separate class
   // so that they can be located in externale memory.
   LFElementQueueState* mX;

   // Array of values.
   void* mElement;

   // Queue array.
   AtomicLFIndex*    mQueueNext;

   // Free List array.
   AtomicLFIndex*    mListNext;

   static const int  cInvalid = 0x80000000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor
   LFElementQueue();
  ~LFElementQueue();

   // Allocate memory for the queue and free list arrays and initialize the
   // queue logic variables. Allocate is the number of elements to allocate
   // memory for. ElementSize is the element size in bytes.
   void initialize(int aNumElements,int aElementSize);
   void initialize(int aNumElements,int aElementSize,bool aConstructorFlag, void* aMemory);

   // Deallocate memory.
   void finalize();

   // Queue size
   int  size();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue and Free List Methods. These write or read values from the queue
   // and pop or push node indices from the free list.

   // These are used to enqueue a element. StartWrite pops a element from the free
   // list and returns a pointer to it. After writing to the element, FinishWrite
   // is called to enqueue it. The node index is passed between the two methods.

   void* startWrite  (int* aNodeIndex);
   void  finishWrite (int  aNodeIndex);

   // These are used to dequeue a element. StartRead dequeues a element from the 
   // queue and returns a pointer to it. After reading from the element,
   // FinishRead is called to push it onto the free list. The node index is 
   // passed between the two methods.

   void* startRead   (int* aNodeIndex);
   void  finishRead  (int  aNodeIndex);

   // These are called by the above write and read methods.
   bool  listPop     (int* aNode);
   bool  listPush    (int  aNode);

   // Return a pointer to a element, based on its element index.
   void* element(int aIndex);
};

//******************************************************************************

}//namespace
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Example

#if 0
   //---------------------------------------------------------------------------
   // Management

   // includes
   #include <new>
   #include "ccLFElementQueue.h"

   // Declare element queue
   CC::LFElementQueue mElementQueue;
   // Initialize element queue
   mElementQueue.initialize(100,sizeof(Class1A));

   //---------------------------------------------------------------------------
   // Enqueue a element

   // Example counter
   int tWriteCount;
   // This is passed between StartWrite and FinishWrite
   int tWriteIndex;

   // Try to start a write to allocate a element
   void* tElement = mElementQueue.startWrite(&tWriteIndex);
   // If the queue is not full
   if (tElement)
   {
      // Create a new object with placement new on the allocated element.
      // Placement new must be used with any classes that use vtables.
      Class1A* tObject = new(tElement) Class1A;
      // Access the new object
      tObject->mCode1 = tWriteCount;
      // Finish the write
      mElementQueue.finishWrite(tWriteIndex);
   }

   //---------------------------------------------------------------------------
   // Dequeue a element 

   // Example counter
   int tReadCount;
   // This is passed between StartRead and FinishRead
   int tReadIndex;

   // Try to start a element read, returns a pointer to an object
   Class1A* tObject = (Class1A*)mElementQueue.startRead(&tReadIndex);
   // If the queue is not empty
   if (tObject)
   {
      // Access the object
      tReadCount = tObject->mCode1;
      // Finish the read
      mElementQueue.finishRead(tReadIndex);
   }
#endif

