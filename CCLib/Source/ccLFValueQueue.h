#ifndef _CCLFVALUEQUEUE_H_
#define _CCLFVALUEQUEUE_H_
/*==============================================================================

Lock Free Value Queue Class TEmplate. 

This implements a value queue. The queue is thread safe. It uses a atomic
interlocked compare and exchanges to guard against concurrency contentions.
It implements the Michael and Scott algorithm with no backoff.
This can be used for Multiple Writer Multiple Reader.

This implements a value queue. It uses a atomic interlocked compare and
exchanges to guard against concurrency contentions.

It implements the Michael and Scott algorithm with no backoff. It maintains
storage for the blocks by implementing a free list that uses the Trieber 
algorithm with no backoff.

This can be used for Multiple Writer Muliple Reader.

==============================================================================*/
#include <atomic>
#include <new>
#include "cc_functions.h"
#include "ccLFIndex.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// State variables for the stack. These are located in a separate class
// so that they can be located in external memory.

class LFValueQueueState
{
public:

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   // Number of elements allocated.
   int mNumElements;
   int mQueueNumElements;
   int mListNumElements;

   // Queue variables.
   AtomicLFIndex     mQueueHead;
   AtomicLFIndex     mQueueTail;

   // Linked list variables.
   AtomicLFIndex     mListHead;
   std::atomic<int>  mListSize;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods.

   // Constructor.
   LFValueQueueState()
   {
      // All null
      mNumElements=0;
      mQueueNumElements=0;
      mListNumElements=0;
   }

   // Initialize.
   void initialize(int aNumElements)
   {
      // Store.
      mNumElements       = aNumElements;
      // Allocate for one extra dummy node.
      mQueueNumElements  = aNumElements + 1;
      // Allocate for one extra dummy node.
      mListNumElements   = aNumElements + 1;
   }

   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.
   static int getMemorySize()
   {
      return cc_round_upto16(sizeof(LFValueQueueState));
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element>
class LFValueQueue
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members

   // If this flag is true then the memory for this object was created
   // externally. If it is false then the memory was allocated at 
   // initialization and must be freed at finalization.
   bool mFreeMemoryFlag;

   // Pointer to memory for which the queue resides. This is either created
   // externally and passed as an initialization parameter or it is created
   // on the system heap at initialization.
   void* mMemory;

   // State variables for the queue. These are located in a separate class
   // so that they can be located in externale memory.
   LFValueQueueState* mX;

   // Array of values.
   Element* mElement;

   // Queue array.
   AtomicLFIndex*    mQueueNext;

   // Free List array.
   AtomicLFIndex*    mListNext;

   static const int  cInvalid = 0x80000000;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor

   LFValueQueue()
   {
      // All null.
      mX = 0;
      mFreeMemoryFlag = false;
      mMemory = 0;

      // All null
      mElement = 0;
      mQueueNext = 0;
      mListNext = 0;
   }

   ~LFValueQueue()
   {
      finalize();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize(int aNumElements,void* aMemory = 0)
   {
      //---------------------------------------------------------------------------
      //---------------------------------------------------------------------------
      //---------------------------------------------------------------------------
      // Initialize memory.

      // Deallocate memory, if any exists.
      finalize();

      // If the instance of this class is not to reside in external memory
      // then allocate memory for it on the system heap.
      if (aMemory == 0)
      {
         mMemory = malloc(LFValueQueue<Element>::getMemorySize(aNumElements));
         mFreeMemoryFlag = true;
      }
      // If the instance of this class is to reside in external memory
      // then use the memory pointer that was passed in.
      else
      {
         mMemory = aMemory;
         mFreeMemoryFlag = false;
      }

      // Calculate memory sizes.
      int tStateSize         = LFValueQueueState::getMemorySize();
      int tQueueArraySize    = (aNumElements + 1)*sizeof(AtomicLFIndex);
      int tListArraySize     = (aNumElements + 1)*sizeof(AtomicLFIndex);
      int tElementArraySize  = (aNumElements + 1)*sizeof(Element);
      int tMemorySize = tStateSize + tQueueArraySize + tListArraySize + tElementArraySize;

      // Calculate memory addresses.
      char* tStateMemory        = (char*)mMemory;
      char* tQueueArrayMemory   = tStateMemory      + tStateSize;
      char* tListArrayMemory    = tQueueArrayMemory + tQueueArraySize;
      char* tElementArrayMemory = tListArrayMemory  + tListArraySize;

      // Initialize state.
      mX = new(tStateMemory) LFValueQueueState;
      mX->initialize(aNumElements);

      // Initialize the queue array.
      mQueueNext = new(tQueueArrayMemory) AtomicLFIndex[mX->mQueueNumElements];

      // Initialize the linked list array.
      mListNext = new(tListArrayMemory) AtomicLFIndex[mX->mListNumElements];

      // Initialize the element array.
      mElement = new(tElementArrayMemory) Element[mX->mQueueNumElements];

      //---------------------------------------------------------------------------
      //---------------------------------------------------------------------------
      //---------------------------------------------------------------------------
      // Initialize variables.

      // Initialize linked list array. Each node next node is the one after it.
      for (int i = 0; i < mX->mListNumElements-1; i++)
      {
         mListNext[i].store(LFIndex(i+1,0));
      }
      // The last node has no next node.
      mListNext[mX->mListNumElements-1].store(LFIndex(cInvalid,0));

      // List head points to the first node.
      mX->mListHead.store(LFIndex(0,0));
      // List size is initially a full stack.
      mX->mListSize = mX->mListNumElements;

      // Initialize queue array. Each node has no next node.
      for (int i = 0; i < mX->mListNumElements; i++)
      {
         mQueueNext[i].store(LFIndex(cInvalid, 0));
      }

      // Pop the dummy node.
      int tDummyNode;
      listPop(&tDummyNode);

      // initialize queue head and tail.
      mX->mQueueHead.store(LFIndex(tDummyNode, 0));
      mX->mQueueTail = mX->mQueueHead.load();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   void finalize()
   {
      if (mFreeMemoryFlag)
      {
         if (mMemory)
         {
            free(mMemory);
         }
      }
      mMemory = 0;
      mFreeMemoryFlag = false;
   }
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns the number of bytes that an instance of this class
   // will need to be allocated for it.

   static int getMemorySize(int aNumElements)
   {
      int tStateSize         = LFValueQueueState::getMemorySize();
      int tQueueArraySize    = (aNumElements + 1)*sizeof(AtomicLFIndex);
      int tListArraySize     = (aNumElements + 1)*sizeof(AtomicLFIndex);
      int tElementArraySize  = (aNumElements)*sizeof(Element);
      int tMemorySize = tStateSize + tQueueArraySize + tListArraySize + tElementArraySize;
      return tMemorySize;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Size

   int size()
   {
      return mX->mListNumElements - mX->mListSize.load(std::memory_order_relaxed);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds. It attempts to pop a node from the free list. If
   // the free list is empty then the queue is full and it exits. The value
   // is to be written is stored in the new node. The new node is then attached
   // to the queue tail node and the tail index is updated.

   bool tryWrite(Element aValue)
   {
      // Try to allocate a node from the free list.
      // Exit if it is empty.
      int tNodeIndex;
      if (!listPop(&tNodeIndex)) return false;

      // Initialize the node with the value.
      mElement[tNodeIndex] = aValue;
      mQueueNext[tNodeIndex].store(LFIndex(cInvalid, 0), std::memory_order_relaxed);

      // Attach the node to the queue tail.
      LFIndex tTail, tNext;

      int tLoopCount = 0;
      while (true)
      {
         tTail = mX->mQueueTail.load(std::memory_order_relaxed);
         tNext = mQueueNext[tTail.mIndex].load(std::memory_order_acquire);

         if (tTail == mX->mQueueTail.load(std::memory_order_relaxed))
         {
            if (tNext.mIndex == cInvalid)
            {
               if (mQueueNext[tTail.mIndex].compare_exchange_strong(tNext, LFIndex(tNodeIndex, tNext.mCount + 1), std::memory_order_release, std::memory_order_relaxed)) break;
            }
            else
            {
               mX->mQueueTail.compare_exchange_weak(tTail, LFIndex(tNext.mIndex, tTail.mCount + 1), std::memory_order_release, std::memory_order_relaxed);
            }
         }

         if (++tLoopCount == 10000) throw 101;
      }

      mX->mQueueTail.compare_exchange_strong(tTail, LFIndex(tNodeIndex, tTail.mCount + 1), std::memory_order_release, std::memory_order_relaxed);

      // Done
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This attempts to read a value from the queue. If the queue is not empty
   // then it succeeds. The next node in the queue to be read is the one 
   // immedialtely after the head node. It extracts the read value from the read
   // node, pushes the previous head node back onto the free list and updates the
   // head index.

   bool tryRead(Element* aValue)
   {
      LFIndex tHead, tTail, tNext;

      int tLoopCount = 0;
      while (true)
      {
         tHead = mX->mQueueHead.load(std::memory_order_relaxed);
         tTail = mX->mQueueTail.load(std::memory_order_acquire);
         tNext = mQueueNext[tHead.mIndex].load(std::memory_order_relaxed);

         if (tHead == mX->mQueueHead.load(std::memory_order_acquire))
         {
            if (tHead.mIndex == tTail.mIndex)
            {
               if (tNext.mIndex == cInvalid) return false;
               mX->mQueueTail.compare_exchange_strong(tTail, LFIndex(tNext.mIndex, tTail.mCount + 1), std::memory_order_release, std::memory_order_relaxed);
            }
            else
            {
               *aValue = mElement[tNext.mIndex];
               if (mX->mQueueHead.compare_exchange_strong(tHead, LFIndex(tNext.mIndex, tHead.mCount + 1), std::memory_order_acquire, std::memory_order_relaxed))break;
            }
         }

         if (++tLoopCount == 10000) throw 102;
      }

      listPush(tHead.mIndex);

      // Done.
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the head node.

   bool listPop(int* aNode)
   {
      // Store the head node in a temp.
      // This is the node that will be detached.
      LFIndex tHead = mX->mListHead.load(std::memory_order_relaxed);

      int tLoopCount = 0;
      while (true)
      {
         // Exit if the list is empty.
         if (tHead.mIndex == cInvalid) return false;

         // Set the head node to be the node that is after the head node.
         if (mX->mListHead.compare_exchange_weak(tHead, LFIndex(mListNext[tHead.mIndex].load(std::memory_order_relaxed).mIndex, tHead.mCount + 1), std::memory_order_acquire, std::memory_order_relaxed)) break;

         if (++tLoopCount == 10000) throw 103;
      }

      // Return the detached original head node.
      *aNode = tHead.mIndex;

      // Done.
      mX->mListSize.fetch_sub(1, std::memory_order_relaxed);
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list before the list head node.

   bool listPush(int aNode)
   {
      // Store the head node in a temp.
      LFIndex tHead = mX->mListHead.load(std::memory_order_relaxed);

      int tLoopCount = 0;
      while (true)
      {
         // Attach the head node to the pushed node.
         mListNext[aNode].store(tHead, std::memory_order_relaxed);

         // The pushed node is the new head node.
         std::atomic<int>* tListHeadIndexPtr = (std::atomic<int>*)&mX->mListHead;
         if ((*tListHeadIndexPtr).compare_exchange_weak(tHead.mIndex, aNode, std::memory_order_release, std::memory_order_relaxed)) break;
         if (++tLoopCount == 10000) throw 103;
      }

      // Done.
      mX->mListSize.fetch_add(1, std::memory_order_relaxed);
      return true;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace
#endif

