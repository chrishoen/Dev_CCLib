#ifndef _LFFREELIST_H_
#define _LFFREELIST_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFFreeList
{
   void initialize (int aAllocate);
   void finalize   ();
   int  listSize();
   void show();

   void initializeTest (int aTest);
   void initializeBackoff(int aB1, int aB2);
   bool test ();

   unsigned long long popRetry();
   unsigned long long pushRetry();

   bool listPop(int* aNode);
   bool listPush(int aNode);
}
#endif

