#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "prnPrint.h"

#include "ccTokenStack.h"
#include "SList2Queue.h"

namespace SList2Queue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // SList Members

   typedef struct
   { 
      int mValue;  
      int mNext;  
   } SListNode;

   static const int cInvalid = 999;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Queue State Members

   int mHeadIndex;  
   int mTailIndex;  

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Memory Members

   // Node array
   static SListNode mNode[1000];

   // Number of blocks allocated
   static int mAllocate = 0;

   // Stack of indices into block array
   static CC::TokenStack mStack;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Version Members

   int mWriteVersion = 2;
   int mReadVersion  = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize (int aAllocate)
   {
      // Initialize variables
      mAllocate = aAllocate + 1;

      mStack.initialize(mAllocate);

      for (int i=mAllocate-1; i>=0; --i)
      {
         mStack.tryPush(i);
         mNode[i].mValue = 0;
         mNode[i].mNext = cInvalid;
      }

      mStack.tryPop(&mHeadIndex);
      mTailIndex = mHeadIndex;  
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

   bool tryWrite0 (int  aWriteValue);
   bool tryWrite1 (int  aWriteValue);
   bool tryWrite2 (int  aWriteValue);
   bool tryWrite3 (int  aWriteValue);

   bool tryWrite(int aWriteValue)
   {
      switch (mWriteVersion)
      {
      case 0: return tryWrite0(aWriteValue);
      case 1: return tryWrite1(aWriteValue);
      case 2: return tryWrite2(aWriteValue);
      case 3: return tryWrite3(aWriteValue);
      }
      return false;
   }

   bool tryRead0(int* aReadValue);
   bool tryRead1(int* aReadValue);

   bool tryRead(int* aReadValue)
   {
      switch (mReadVersion)
      {
      case 0: return tryRead0(aReadValue);
      case 1: return tryRead1(aReadValue);
      }
      return false;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Easier to use compare and exchange functions.

   static bool boolCae(int* aDestin, int aExchange, int aCompare)
   {
      int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
      return tOriginal == aCompare; 
   }

   static int valCae(int* aDestin, int aExchange, int aCompare)
   {
      int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
      return tOriginal; 
   }

   static int valExchange(int* aDestin, int aExchange)
   {
      int tOriginal = (int)InterlockedExchange((PLONG)aDestin, *((LONG*)&aExchange));
      return tOriginal; 
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds. It attempts to pop an index from the index stack. If
   // the stack is empty then the queue is full and it exits. The popped index
   // is used to initialize a new node, which stores the input value that is
   // to be written. The new node is then attached to the queue tail node and
   // the tail index is updated.
   // 
   // There are different versions:
   //
   //    tryWrite0 can be used for single writer queues. It doesn't need to
   //    use any cas logic and it is fastest.
   //
   //    tryWrite1 can be used for multple writer queues where, if a writer
   //    process halts it will always proceed.
   // 
   //    tryWrite2 is a variation on tryWrite1.
   // 
   //    tryWrite3 can be used for multple writer queues where, if a writer
   //    process halts it might not proceed, but it is faster.
   // 

   //***************************************************************************

   bool tryWrite0 (int aWriteValue)
   {
      // Try to allocate an index from the stack. Exit if the stack is empty.
      int tWriteIndex;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in a new node.
      mNode[tWriteIndex].mValue = aWriteValue;
      mNode[tWriteIndex].mNext = cInvalid;

      // Attach the node to the queue tail node and update the tail index.
      mNode[mTailIndex].mNext = tWriteIndex;
      mTailIndex = tWriteIndex;

      // Done
      return true;
   }

   //***************************************************************************

   bool tryWrite1 (int aWriteValue)
   {
      // Try to allocate an index from the stack
      // Exit if the stack is empty.
      int tWriteIndex;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in a new node.
      mNode[tWriteIndex].mValue = aWriteValue;
      mNode[tWriteIndex].mNext = cInvalid;

      // Attach the node to the queue tail.
      int tTailIndex;
      while (true)
      {
         tTailIndex = mTailIndex;

         if (boolCae(&mNode[tTailIndex].mNext, tWriteIndex, cInvalid)) break;
         boolCae(&mTailIndex, mNode[tTailIndex].mNext, tTailIndex);
      }
      boolCae(&mTailIndex,tWriteIndex,tTailIndex);

      // Done
      return true;
   }

   //***************************************************************************

   bool tryWrite2 (int aWriteValue)
   {
      // Try to allocate an index from the stack
      // Exit if the stack is empty.
      int tWriteIndex;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in a new node.
      mNode[tWriteIndex].mValue = aWriteValue;
      mNode[tWriteIndex].mNext = cInvalid;

      // Attach the node to the queue tail.
      int tTailIndex    = mTailIndex;
      int tOldTailIndex = tTailIndex;
      while (true)
      {
         while (mNode[tTailIndex].mNext != cInvalid)
         {
            tTailIndex = mNode[tTailIndex].mNext;
         }
         if (boolCae(&mNode[tTailIndex].mNext, tWriteIndex, cInvalid)) break;
      }
      boolCae(&mTailIndex,tWriteIndex,tOldTailIndex);

      // Done
      return true;
   }

   //***************************************************************************

   bool tryWrite3 (int aWriteValue)
   {
      // Try to allocate an index from the stack
      // Exit if the stack is empty.
      int tWriteIndex;
      if (!mStack.tryPop(&tWriteIndex)) return false;

      // Store the write value in a new node.
      mNode[tWriteIndex].mValue = aWriteValue;
      mNode[tWriteIndex].mNext = cInvalid;

      // Attach the node to the queue tail.
      int tTailIndex;
      while (true)
      {
         tTailIndex = mTailIndex;

         if (boolCae(&mNode[tTailIndex].mNext, tWriteIndex, cInvalid)) break;
      }
      boolCae(&mTailIndex,tWriteIndex,tTailIndex);

      // Done
      return true;
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This attempts to read a value from the queue. If the queue is not empty
   // then it succeeds. It extracts the read value from the head node, pushes the
   // previous head index back onto the stack and updates the head index.
   // 
   // There are different versions:
   //
   //    tryRead0 can be used for single reader queues. It doesn't need to
   //    use any cas logic and it is fastest.
   //
   //    tryRead1 can be used for multple reader queues where, if a reader
   //    process halts it will always proceed.

   bool tryRead0 (int* aReadValue) 
   {
      // Store the read index in a temp.
      int tReadIndex = mNode[mHeadIndex].mNext;

      // Exit if the queue is empty.
      if (tReadIndex == cInvalid) return false;

      // Extract the read value from the head node.
      *aReadValue = mNode[tReadIndex].mValue;

      // Push the previous head index back onto the stack.
      mStack.tryPush(mHeadIndex);

      // Update the head index.
      mHeadIndex = tReadIndex;

      // Done.
      return true;
   }

   bool tryRead1 (int* aReadValue) 
   {
      int tHeadIndex;
      while (true)
      {
         // Store the read index in a temp.
         tHeadIndex = mHeadIndex;

         // Exit if the queue is empty.
         if (mNode[tHeadIndex].mNext == cInvalid) return false;

         if (boolCae(&mHeadIndex, mNode[tHeadIndex].mNext, tHeadIndex)) break;
      }
      // Extract the read value from the head block.
      int tReadIndex = mNode[tHeadIndex].mNext;
      *aReadValue = mNode[tReadIndex].mValue;

      // Push the previous head index back onto the stack.
      mStack.tryPush(tHeadIndex);

      // Done.
      return true;
   }


}