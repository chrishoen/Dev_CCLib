#pragma once

/*==============================================================================

Single reader single writer object queue class template.

It is single writer single reader thread safe.
It is lock free and non blocking.
It is shared memory safe.

ALSO, DON'T FORGET:
The following rules apply to using shared memory:

1) No constructors.
2) No pointers.
3) No dynamic memory, this means no std::vector, ...
4) No vtables, this means no virtual functions.
5) Be careful with your loads and stores.
6) alignas(16) for classes and long long.

==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element,int NumElements>
class alignas(16) SRSWObjectQueue
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Element access indices. They vary as 0..NumElements-1. These
   // are the next element to write to and the next element to read
   // from.
   volatile int mWriteIndex;
   volatile int mReadIndex;

   // Array of elements.
   alignas(16) Element mElement[NumElements];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // No constructor.
   void reset()
   {
      mWriteIndex = 0;
      mReadIndex = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Return the current size of the queue. It is the number of occupied
   // elements. It varies as 0..NumElements-1. This is not thread safe
   // and should only be used for display purposes.

   int size()
   {
      int tOccupied = mWriteIndex - mReadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      return tOccupied;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to write an object to the queue. If the queue is full then
   // return false. If the queue is not full then copy the element
   // to the queue array at the write index, increment the write index,
   // and return true. 
   // 
   // The queue is full when it has NumElements-1 occupied elements. The
   // queue only stores at most NumElements-1 elements. It reserves one
   // element to act as a buffer between puts and gets, so that concurrent
   // writes and reads on the same element are avoided.

   bool tryWrite(Element* aElement)
   {
      // Get local indices.
      int tWriteIndex = mWriteIndex;
      int tReadIndex = mReadIndex;

      // Test if the queue is full.
      int tOccupied = tWriteIndex - tReadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == NumElements - 1) return false;

      // Copy the queue array element at the write index.
      mElement[tWriteIndex] = *aElement;
      store_barrier();

      // Advance the write index.
      if (++tWriteIndex == NumElements) tWriteIndex = 0;
      mWriteIndex = tWriteIndex;

      // Success.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to read an object from the queue. If the queue is empty then
   // return false. If the queue is not empty then copy the element
   // from the queue array at the read index, increment the read index,
   // and return true. 
   // 
   // The queue is not empty if the write index is not equal to the read
   // index. In other words, the queue is not empty when the number of
   // occupied elements is greater than zero.

   bool tryRead(Element* aValue)
   {
      // Get local indices.
      int tWriteIndex = mWriteIndex;
      int tReadIndex = mReadIndex;

      // Test if the queue is empty.
      int tOccupied = tWriteIndex - tReadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == 0) return false;

      // Copy the queue array element at the read index.
      load_barrier();
      *aValue = mElement[tReadIndex];
      // Advance the read index.
      if (++tReadIndex == NumElements) tReadIndex = 0;
      mReadIndex = tReadIndex;

      // Success.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to write a value to the queue. If the queue is full then
   // return false. If the queue is not full then copy the element
   // to the queue array at the write index, increment the write index,
   // and return true. 
   // 
   // The queue is full when it has NumElements-1 occupied elements. The
   // queue only stores at most NumElements-1 elements. It reserves one
   // element to act as a buffer between puts and gets, so that concurrent
   // writes and reads on the same element are avoided.

   Element* startWrite()
   {
      // Local write index.
      int tWriteIndex = mWriteIndex;
      // Test if the queue is full.
      int tOccupied = tWriteIndex - mReadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied >= NumElements - 1) return 0;

      // Return a pointer to the element at the write index.
      return &mElement[tWriteIndex];
   }

   void finishWrite()
   {
      // Local write index.
      int tWriteIndex = mWriteIndex;
      // Advance the write index.
      if (++tWriteIndex == NumElements) tWriteIndex = 0;
      mWriteIndex = tWriteIndex;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to read a value from the queue. If the queue is empty then
   // return false. If the queue is not empty then copy the element
   // from the queue array at the read index, increment the read index,
   // and return true. 
   // 
   // The queue is not empty if the write index is not equal to the read
   // index. In other words, the queue is not empty when the number of
   // occupied elements is greater than zero.
  
   Element* startRead()
   {
      // Local index.
      int tReadIndex = mReadIndex;
      // Test if the queue is empty.
      int tOccupied = mWriteIndex - tReadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == 0) return 0;

      // Return a pointer to the element at the read index.
      return &mElement[mReadIndex];
   }

   void finishRead()
   {
      // Local index.
      int tReadIndex = mReadIndex;
      // Advance the read index.
      if (++tReadIndex == NumElements) tReadIndex = 0;
      mReadIndex = tReadIndex;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

