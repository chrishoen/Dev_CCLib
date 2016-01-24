#ifndef _LFINTQUEUE_H_
#define _LFINTQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFIntQueue
{
   void initialize (int aAllocate);
   void finalize   ();

   bool tryWrite  (int  aValue);
   bool tryRead   (int* aValue);

   void show();

   void test (int  aTest);
}
#endif

