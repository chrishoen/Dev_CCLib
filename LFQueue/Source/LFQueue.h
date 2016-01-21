#ifndef _LFQUEUE_H_
#define _LFQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFQueue
{
   void initialize (int aAllocate);

   bool tryWrite  (int  aWriteValue);
   bool tryRead   (int* aReadValue);
}
#endif

