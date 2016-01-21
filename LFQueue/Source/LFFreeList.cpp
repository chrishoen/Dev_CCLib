#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "prnPrint.h"

#include "ccTokenStack.h"
#include "LFAtomic.h"
#include "LFFreeList.h"

namespace LFFreeList
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // FreeList Members

   typedef struct
   { 
      int mValue;  
      int mNext;  
   } FreeListNode;

   static const int cInvalid = 999;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // State Members

   int mTailIndex;
   int mListSize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Node array
   static FreeListNode mNode[1000];

   // Number of blocks allocated
   static int mAllocate = 0;

   // Stack of indices into block array
   static CC::TokenStack mStack;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Version Members

   int mPushVersion = 2;
   int mPopVersion  = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize (int aAllocate)
   {
      // Initialize variables
      mAllocate = aAllocate;

      for (int i=0; i<mAllocate-1; i++)
      {
         mNode[i].mValue = 0;
         mNode[i].mNext  = i + 1;
      }

      mNode[mAllocate-1].mValue = 0;
      mNode[mAllocate-1].mNext = cInvalid;

      mListSize = 0;  
      mTailIndex = mAllocate-1; 
   }

   //***************************************************************************
   // Finalize

   void finalize()
   {
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Select version.

   bool tryPush0 (int  aPushValue);
   bool tryPush1 (int  aPushValue);

   bool tryPush(int aPushValue)
   {
      switch (mPushVersion)
      {
      case 0: return tryPush0(aPushValue);
      case 1: return tryPush1(aPushValue);
      }
      return false;
   }

   bool tryPop0(int* aPopValue);
   bool tryPop1(int* aPopValue);

   bool tryPop(int* aPopValue)
   {
      switch (mPopVersion)
      {
      case 0: return tryPop0(aPopValue);
      case 1: return tryPop1(aPopValue);
      }
      return false;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list after the tail node.

   bool tryPush0 (int aIndex)
   {
      // Point the new node at the node that the tail points to. 
      mNode[aIndex].mNext = mNode[mTailIndex].mNext;

      // Point the tail at the new node.
      mNode[mTailIndex].mNext = aIndex;

      // Done
      mListSize++;
      return true;
   }

   //***************************************************************************
   // Insert a node into the list after the tail node.

   bool tryPush1 (int aIndex)
   {
      int tNextIndex;
      while (true)
      {
         // Save the index to the next node.
         tNextIndex = mNode[mTailIndex].mNext;

         // Point the new node at the node that the tail points to. 
         mNode[aIndex].mNext = tNextIndex;

         // Point the tail at the new node.
         if (my_bool_cae(&mNode[mTailIndex].mNext, aIndex, tNextIndex)) break;
      }

      // Done.
      my_fetch_add(&mListSize,1);
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the node that is after the tail node.

   bool tryPop0 (int* aIndex) 
   {
      // Store the index of the node that is to be detached in a temp.
      int tIndex = mNode[mTailIndex].mNext;

      // Exit if the list is empty
      if (tIndex == cInvalid) return false;

      // Detach the node.
      mNode[mTailIndex].mNext = mNode[tIndex].mNext;

      // Reset the detached node.
      mNode[tIndex].mValue = 0;
      mNode[tIndex].mNext  = cInvalid;

      // Return result.
      *aIndex = tIndex;

      // Done.
      mListSize--;
      return true;
   }

   bool tryPop1 (int* aIndex) 
   {
      int tIndex;
      while (true)
      {
         // Store the index of the node that is to be detached in a temp.
         tIndex = mNode[mTailIndex].mNext;

         // Exit if the queue is empty.
         if (tIndex == cInvalid) return false;

         // Attempt to detach the node to pop.
         if (my_bool_cae(&mNode[mTailIndex].mNext, mNode[tIndex].mNext, tIndex)) break;
      }

      // Reset the detached node.
      mNode[tIndex].mValue = 0;
      mNode[tIndex].mNext  = cInvalid;

      // Return result.
      *aIndex = tIndex;

      // Done.
      my_fetch_add(&mListSize,-1);
      return true;
   }


}