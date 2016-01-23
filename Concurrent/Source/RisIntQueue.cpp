#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <atomic>
#include "risContainers2.h"

#include "RisIntQueue.h"

using namespace std;

namespace RisIntQueue
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   Ris::Containers::Queue2<int> mQueue;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize

   void initialize(int aAllocate)
   {
      mQueue.initialize(aAllocate);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize

   void finalize()
   {
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show

   void show()
   {
      printf("RisIntQueue\n");
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This attempts to write a value to the queue. If the queue is not full
   // then it succeeds. It attempts to pop a node from the free list. If
   // the free list is empty then the queue is full and it exits. The value
   // is to be written is stored in the new node. The new node is then attached
   // to the queue tail node and the tail index is updated.

   bool tryWrite(int aValue)
   {
      if (!mQueue.isPut()) return false;
      mQueue.put(aValue);
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

   bool tryRead (int* aValue) 
   {
      if (!mQueue.isGet()) return false;
      mQueue.get(*aValue);
      return true;
   }

}//namespace
