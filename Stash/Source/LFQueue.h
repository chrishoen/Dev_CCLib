#ifndef _LFQUEUE_H_
#define _LFQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFQueue
{
   void initialize (int aAllocate);

   bool tryWrite  (int  aValue);
   bool tryRead   (int* aValue);
}
#endif

