#pragma once

/*==============================================================================

Array based list class template.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element,int NumElements>
class ModList
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Element access indices. They vary as 0..NumElements-1. These
   // are the next element to write to and the next element to read
   // from.
   volatile int mTailIndex;
   volatile int mHeadIndex;

   // Array of elements.
   Element mElement[NumElements];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   ModList()
   {
      reset();
   }
   void reset()
   {
      mTailIndex = 0;
      mHeadIndex = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Return the current size of the list. It is the number of occupied
   // elements. It varies as 0..NumElements-1. This is not thread safe
   // and should only be used for display purposes.

   int size()
   {
      int tOccupied = mTailIndex - mHeadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      return tOccupied;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to write a value to the list. If the list is full then
   // return false. If the list is not full then copy the element
   // to the list array at the tail index, increment the tail index,
   // and return true. 
   // 
   // The list is full when it has NumElements-1 occupied elements. The
   // list only stores at most NumElements-1 elements. It reserves one
   // element to act as a buffer between puts and gets, so that concurrent
   // writes and reads on the same element are avoided.

   bool tryWriteTail (Element aElement)
   {
      // Test if the list is full.
      int tOccupied = mTailIndex - mHeadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == NumElements - 1) return false;

      // Copy the list array element at the tail index.
      mElement[mTailIndex] = aElement;

      // Advance the tail index forward.
      if(++mTailIndex == NumElements) mTailIndex = 0;

      // Success.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to read a value from the list. If the list is empty then
   // return false. If the list is not empty then copy the element
   // from the list array at the head index, increment the head index,
   // and return true. 
   // 
   // The list is not empty if the tail index is not equal to the read
   // index. In other words, the list is not empty when the number of
   // occupied elements is greater than zero.

   bool tryReadHead(Element* aValue)
   {
      // Test if the list is empty.
      int tOccupied = mTailIndex - mHeadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == 0) return false;

      // Copy the list array element at the head index.
      *aValue = mElement[mHeadIndex];
      // Advance the head index forward.
      if(++mHeadIndex == NumElements) mHeadIndex = 0;

      // Success.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to read a value from the list. If the list is empty then
   // return false. If the list is not empty then copy the element
   // from the list array at the head index, increment the head index,
   // and return true. 
   // 
   // The list is not empty if the tail index is not equal to the read
   // index. In other words, the list is not empty when the number of
   // occupied elements is greater than zero.

   bool tryReadTail(Element* aValue)
   {
      // Test if the list is empty.
      int tOccupied = mTailIndex - mHeadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == 0) return false;

      // Advance the tail index backward.
      if(--mTailIndex < 0) mTailIndex = NumElements - 1;
      // Copy the list array element at the tail index.
      *aValue = mElement[mTailIndex];

      // Success.
      return true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Try to write a value to the list. If the list is full then
   // return false. If the list is not full then copy the element
   // to the list array at the tail index, increment the tail index,
   // and return true. 
   // 
   // The list is full when it has NumElements-1 occupied elements. The
   // list only stores at most NumElements-1 elements. It reserves one
   // element to act as a buffer between puts and gets, so that concurrent
   // writes and reads on the same element are avoided.

   bool tryWriteHead (Element aElement)
   {
      // Test if the list is full.
      int tOccupied = mTailIndex - mHeadIndex;
      if (tOccupied < 0) tOccupied = NumElements + tOccupied;
      if (tOccupied == NumElements - 1) return false;

      // Advance the head index backward.
      if(--mHeadIndex < 0) mHeadIndex = NumElements - 1;
      // Copy the list array element at the head index.
      mElement[mHeadIndex] = aElement;

      // Success.
      return true;
   }

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

