#pragma once

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "ccFreeList.h"
#include "ccValueList.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

class MyListNode
{
public:
   int mValue;
   // Used by utlist linked list. Do not touch.
   MyListNode* prev;
   MyListNode* next;

   void reset()
   {
      mValue = 0;
      prev = 0;
      next = 0;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class TestOne
{
public:
   // Members.
   CC::FreeList<MyListNode, 20> mFreeList;
   CC::ValueList<MyListNode*, 9> mList;

   // Methods.
   TestOne::TestOne();
   void reset();

   // Methods.
   void doPutHead(int aValue);
   void doPutTail(int aValue);
   void doGetHead();
   void doGetTail();

   // Methods.
   void doInitialize0();
   void doInitialize4();
   void doShow();

   // Methods.
   void doRun(int aSelect);
   void doRun11();
   void doRun12();
   void doRun13();
   void doRun14();
};
