#ifndef _LFINTQUEUE_H_
#define _LFINTQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFIntQueue
{
   void initialize (int aAllocate);
   void finalize   ();

   bool tryWrite  (int  aWriteValue);
   bool tryRead   (int* aReadValue);

   void show();
}
#endif

