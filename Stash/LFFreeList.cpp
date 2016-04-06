#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "prnPrint.h"

#include "LFAtomic.h"
#include "LFFreeList.h"

using namespace std;

namespace LFFreeList
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // FreeList Members

   typedef struct
   { 
      int mValue;  
      atomic<int> mListNext;
   } FreeListNode;

   static const int cInvalid = 999;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // State Members

   atomic<int> mListIndex;
   atomic<int> mListSize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Node array
   static FreeListNode mNode[1000];

   // Number of blocks allocated
   static int mAllocate = 0;

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
         mNode[i].mListNext  = i + 1;
      }

      mNode[mAllocate-1].mValue = 0;
      mNode[mAllocate-1].mListNext = cInvalid;

      mListSize = 0;  
      mListIndex = mAllocate-1; 
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

   bool listPush0 (int  aIndex);
   bool listPush1 (int  aIndex);

   bool listPush(int aIndex)
   {
      switch (mPushVersion)
      {
      case 0: return listPush0(aIndex);
      case 1: return listPush1(aIndex);
      }
      return false;
   }

   bool listPop0(int* aIndex);
   bool listPop1(int* aIndex);

   bool listPop(int* aIndex)
   {
      switch (mPopVersion)
      {
      case 0: return listPop0(aIndex);
      case 1: return listPop1(aIndex);
      }
      return false;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Insert a node into the list after the tail node.

   bool listPush0 (int aIndex)
   {
      // Exit if the list is full.
      if (mListSize >= mAllocate) return false;

      // Point the new node at the node that the tail points to. 
      mNode[aIndex].mListNext = mNode[mListIndex].mListNext.load();

      // Point the tail at the new node.
      mNode[mListIndex].mListNext = aIndex;

      // Done
      mListSize++;
      return true;
   }

   //***************************************************************************
   // Insert a node into the list after the tail node.

   bool listPush1 (int aIndex)
   {
      // Exit if the list is full.
      if (mListSize >= mAllocate) return false;

      int tNextIndex;
      while (true)
      {
         // Save the index to the next node.
         tNextIndex = mNode[mListIndex].mListNext;

         // Point the new node at the node that the tail points to. 
         mNode[aIndex].mListNext = tNextIndex;

         // Point the tail at the new node.
         if (mNode[mListIndex].mListNext.compare_exchange_weak(tNextIndex, aIndex)) break;
      }

      // Done.
      mListSize++;
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This detaches the node that is after the tail node.

   bool listPop0 (int* aIndex) 
   {
      // Store the index of the node that is to be detached in a temp.
      int tIndex = mNode[mListIndex].mListNext;

      // Exit if the list is empty
      if (tIndex == cInvalid) return false;

      // Detach the node.
      mNode[mListIndex].mListNext = mNode[tIndex].mListNext.load();

      // Reset the detached node.
      mNode[tIndex].mValue = 0;
      mNode[tIndex].mListNext  = cInvalid;

      // Return result.
      *aIndex = tIndex;

      // Done.
      mListSize--;
      return true;
   }

   bool listPop1 (int* aIndex) 
   {
      int tIndex;
      while (true)
      {
         // Store the index of the node that is to be detached in a temp.
         tIndex = mNode[mListIndex].mListNext;

         // Exit if the queue is empty.
         if (tIndex == cInvalid) return false;

         // Attempt to detach the node.
         if (mNode[mListIndex].mListNext.compare_exchange_weak(tIndex, mNode[tIndex].mListNext)) break;
      }

      // Reset the detached node.
      mNode[tIndex].mValue = 0;
      mNode[tIndex].mListNext  = cInvalid;

      // Return result.
      *aIndex = tIndex;

      // Done.
      mListSize--;
      return true;
   }

}