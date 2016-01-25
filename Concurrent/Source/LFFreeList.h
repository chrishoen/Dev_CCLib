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

   bool listPush(int  aIndex);
   bool listPop(int* aIndex);

   void show();

   void initializeTest (int aTest);
   bool test ();
}
#endif

