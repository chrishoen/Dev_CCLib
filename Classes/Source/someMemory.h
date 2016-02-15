#ifndef _SOMEMEMORY_H_
#define _SOMEMEMORY_H_

/*==============================================================================
File: someClass1.h
Description:
QCall test Class class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <new>
#include <stdlib.h>
#include <prnPrint.h>

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class MyClass>
MyClass* memCreate(int aMemType=0)
{
   Prn::print(0, "memCreate %d",aMemType);
   void* tPtr = malloc(sizeof(MyClass));
   return new(tPtr)MyClass;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class MyClass>
MyClass* memCreateArray(int aMemType,int aArraySize)
{
   Prn::print(0, "memCreateArray %d %d",aMemType,aArraySize);
   void* tPtr = malloc(sizeof(MyClass)*aArraySize + 4);
   return new(tPtr)MyClass[aArraySize];
   return (MyClass*)tPtr;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class MyClass>
void memDestroy(MyClass* aPtr,int aMemType=0)
{
   Prn::print(0, "memDestroy %d",aMemType);
   aPtr->~MyClass();
   free(aPtr);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class MyClass>
void memDestroyArray(MyClass* aPtr,int aMemType,int aArraySize)
{
   Prn::print(0, "memDestroyArray %d %d",aMemType,aArraySize);
   for (int i = 0; i < aArraySize; i++)
   {
      aPtr[i].~MyClass();
   }
   void* tPtr2 = (void*)((char*)aPtr - 4);
   free(tPtr2);
}

//******************************************************************************
}//namespace

#endif

