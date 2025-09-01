/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "utlist.h"
#include "TestOne.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

TestOne::TestOne()
{
   reset();
}

void TestOne::reset()
{
   mFreeList.reset();
   mHead = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doInitialize()
{
   mFreeList.reset();
   mHead = 0;
   MyListNode* tNode = 0;

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 101;
   DL_APPEND(mHead, tNode);

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 102;
   DL_APPEND(mHead, tNode);

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 103;
   DL_APPEND(mHead, tNode);

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 104;
   DL_APPEND(mHead, tNode);
}

void TestOne::doShow()
{
   printf("FreeList %d\n", mFreeList.allocated());
   MyListNode* tNode = 0;
   DL_FOREACH(mHead, tNode)
   {
      printf("%d\n", tNode->mValue);
   }     
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun1()
{
   printf("TestOne::doRun1 ****************\n");
   doInitialize();
   doShow();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun2()
{
   printf("TestOne::doRun2 ****************\n");
   doInitialize();
   doShow();

   MyListNode* tNode = 0;
   MyListNode* tTemp = 0;
   DL_FOREACH_SAFE(mHead, tNode, tTemp)
   {
      if (tNode->mValue == 103)
      {
         DL_DELETE(mHead, tNode);
         mFreeList.doFree(tNode);
      }
   }     
   doShow();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun3()
{
   printf("TestOne::doRun3 ****************\n");
   doInitialize();
   doShow();

   printf("TestOne::doRun3 delete 103\n");
   MyListNode* tNode = 0;
   MyListNode* tTemp = 0;
   DL_FOREACH_SAFE(mHead, tNode, tTemp)
   {
      if (tNode->mValue == 103)
      {
         DL_DELETE(mHead, tNode);
         mFreeList.doFree(tNode);
      }
   }     
   doShow();

   printf("TestOne::doRun3 append 203 after 102\n");
   DL_FOREACH_SAFE(mHead, tNode, tTemp)
   {
      if (tNode->mValue == 102)
      {
         if ((tTemp = mFreeList.doAllocate()) == 0) return;
         tTemp->mValue = 203;
         DL_APPEND_ELEM(mHead, tNode, tTemp);
      }
   }     
   doShow();
}

