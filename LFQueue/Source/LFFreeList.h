#ifndef _LFFREELIST_H_
#define _LFFREELIST_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFFreeList
{
   void initialize (int aAllocate);

   bool tryPush  (int  aIndex);
   bool tryPop   (int* aIndex);
}
#endif

