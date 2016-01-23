#ifndef _SLISTQUEUE_H_
#define _SLISTQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace SListQueue
{
   void initialize (int aAllocate);

   bool tryWrite (int  aWriteValue);
   bool tryRead  (int* aReadValue);
}
#endif

