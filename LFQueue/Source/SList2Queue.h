#ifndef _SLIST2QUEUE_H_
#define _SLIST2QUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace SList2Queue
{
   void initialize (int aAllocate);

   bool tryWrite (int  aWriteValue);
   bool tryRead  (int* aReadValue);
}
#endif

