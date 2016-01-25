#ifndef _LFINTQUEUE_H_
#define _LFINTQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFIntQueue
{
   void initialize (int aAllocate);
   void finalize   ();
   int  listSize();

   bool tryWrite  (int  aValue);
   bool tryRead   (int* aValue);

   void show();

   void initializeTest (int aTest);
   bool test ();
}
#endif

