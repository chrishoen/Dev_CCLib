#ifndef _LFFREELIST_H_
#define _LFFREELIST_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFFreeList
{
   void initialize (int aAllocate);

   bool listPush  (int  aIndex);
   bool listPop   (int* aIndex);

}
#endif

