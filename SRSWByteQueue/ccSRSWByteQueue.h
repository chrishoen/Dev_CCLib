#pragma once

/*==============================================================================

Single Reader Writer Byte Queue C language structure. 

It is single writer single reader thread safe.
It is uses no thread synchronization.
It is shared memory safe.

This implements a value queue of bytes. 

It is thread safe for separate single writer and single reader threads.

==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Queue structure and initializer.

typedef struct SRSWByteQueueS
{
   // Number of elements allocated is size + 1. There is an extra element
   // allocated.
   int mNumElements;
   // Index to put to.
   int mPutIndex;
   // Index to get from.
   int mGetIndex;
   // Array of elements. This must be preallocated before initialization.
   char* mElement;
}  SRSWByteQueue;

inline void SRSWByteQueue_initialize(SRSWByteQueue* aQueue, char* aElements, int aSize)
{
   aQueue->mNumElements = aSize + 1;
   aQueue->mPutIndex = 0;
   aQueue->mGetIndex = 0;
   aQueue->mElement = aElements;
}

inline void SRSWByteQueue_reset(SRSWByteQueue* aQueue)
{
   aQueue->mPutIndex = 0;
   aQueue->mGetIndex = 0;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// This is the current size of the queue. It is the difference between the 
// mPutIndex and the mGetIndex.

inline int SRSWByteQueue_size(SRSWByteQueue* aQueue)
{
   int tSize = aQueue->mPutIndex - aQueue->mGetIndex;
   if (tSize < 0) tSize = aQueue->mNumElements + tSize;
   return tSize;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// This attempts to write a value to the queue. If the queue is not full
// then it succeeds.
// 
// This tests if put operations are allowed. Puts are allowed if the 
// current size is less than or equal to NumElements - 2. If the size is equal
// to NumElements - 2 then the next put operation would put the size to
// cNumElements - 1, which is the max number of elements. This is the same
// as "is not full".
// 
// This puts an element to the queue and advances the put index. It does a 
// copy from a source element into the queue array element at the put index.
// It uses a temp index variable so that writing to the index is atomic.

inline bool SRSWByteQueue_tryWrite(SRSWByteQueue* aQueue, char aElement)
{
   // Test if the queue is full.
   int tSize = aQueue->mPutIndex - aQueue->mGetIndex;
   if (tSize < 0) tSize = aQueue->mNumElements + tSize;
   if (tSize > aQueue->mNumElements - 2) return false;

   // Local put index.
   int tPutIndex = aQueue->mPutIndex;
   // Copy the source element into the element at the queue put index.
   aQueue->mElement[tPutIndex] = aElement;
   // Advance the put index.
   if (++tPutIndex == aQueue->mNumElements) tPutIndex = 0;
   aQueue->mPutIndex = tPutIndex;
   // Done.
   return true;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
// This attempts to read a value to the queue. If the queue is not empty
// then it succeeds.
//
// This gets an element from the queue and advances the get index. It does a 
// copy from the queue array element at the get index into a destination
// element. It uses a temp index variable so that writing to the index is
// atomic. Note that the destination element must be of element size.

inline bool SRSWByteQueue_tryRead(SRSWByteQueue* aQueue, char* aValue)
{
   // Test if the queue is empty.
   int tSize = aQueue->mPutIndex - aQueue->mGetIndex;
   if (tSize < 0) tSize = aQueue->mNumElements + tSize;
   if (tSize == 0) return false;

   // Local index.
   int tGetIndex = aQueue->mGetIndex;
   // Copy the queue array element at the get index.
   *aValue = aQueue->mElement[tGetIndex];
   // Advance the get index.
   if (++tGetIndex == aQueue->mNumElements) tGetIndex = 0;
   aQueue->mGetIndex = tGetIndex;

   // Done.
   return true;
}

//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
// Reference: ccSRSWValueQueue.h 
#if 0
namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element,int Size>
class SRSWValueQueue
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Number of elements allocated is size + 1. There is an extra element
   // allocated.
   static const int cNumElements = Size + 1;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Element access indices.
   int mPutIndex;
   int mGetIndex;

   // Array of elements.
   Element mElement[cNumElements];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SRSWValueQueue()
   {
      reset();
   }

   void reset()
   {
      // Initialize variables.
      mPutIndex = 0;
      mGetIndex = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This is the current size of the queue. It is the difference between the 
   // mPutIndex and the mGetIndex.

   int size()
   {
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = cNumElements + tSize;
      return tSize;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds.
   // 
   // This tests if put operations are allowed. Puts are allowed if the 
   // current size is less than or equal to NumElements - 2. If the size is equal
   // to NumElements - 2 then the next put operation would put the size to
   // cNumElements - 1, which is the max number of elements. This is the same
   // as "is not full".
   // 
   // This puts an element to the queue and advances the put index. It does a 
   // copy from a source element into the queue array element at the put index.
   // It uses a temp index variable so that writing to the index is atomic.

   bool tryWrite (Element aElement)
   {
      // Test if the queue is full.
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = cNumElements + tSize;
      if (tSize > cNumElements - 2) return false;

      // Local put index.
      int tPutIndex = mPutIndex;
      // Copy the source element into the element at the queue put index.
      mElement[tPutIndex] = aElement;
      // Advance the put index.
      if(++tPutIndex == cNumElements) tPutIndex = 0;
      mPutIndex = tPutIndex;
      // Done.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to read a value to the queue. If the queue is not empty
   // then it succeeds.
   //
   // This gets an element from the queue and advances the get index. It does a 
   // copy from the queue array element at the get index into a destination
   // element. It uses a temp index variable so that writing to the index is
   // atomic. Note that the destination element must be of element size.
  
   bool tryRead(Element* aValue)
   {
      // Test if the queue is empty.
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = cNumElements + tSize;
      if (tSize == 0) return false;

      // Local index.
      int tGetIndex = mGetIndex;
      // Copy the queue array element at the get index.
      *aValue = mElement[tGetIndex];
      // Advance the get index.
      if(++tGetIndex == cNumElements) tGetIndex = 0;
      mGetIndex = tGetIndex;

      // Done.
      return true;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif
