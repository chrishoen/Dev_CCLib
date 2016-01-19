#ifndef _LFQUEUE_H_
#define _LFQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFQueue
{
   void initialize (unsigned aAllocate);

   bool tryWrite (unsigned  aWriteValue);
   bool tryRead  (unsigned* aReadValue);
}
#endif

