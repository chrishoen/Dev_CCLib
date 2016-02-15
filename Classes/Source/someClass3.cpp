/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include "prnPrint.h"

#include "someClass3.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Class3A::Class3A()
{
   Prn::print(0, "Class3A::Class3A");
   mCode=101;
}

Class3A::~Class3A()
{
   Prn::print(0, "Class3A::~Class3A");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
#if 0
void* Class3A::operator new(size_t sz)
{
   Prn::print(0, "Class3A::new   %d",(int)sz);
   return ::operator new(sz);
}
  
void* Class3A::operator new[](size_t sz)
{
   Prn::print(0, "Class3A::new[] %d",(int)sz);
   return ::operator new(sz);
}
#endif  
//******************************************************************************
//******************************************************************************
//******************************************************************************
#if 0
void Class3A::operator delete(void* ptr)
{
   Prn::print(0, "Class3A::delete");
   ::operator delete(ptr);
}

void Class3A::operator delete[](void* ptr)
{
   Prn::print(0, "Class3A::delete[]");
   ::operator delete(ptr);
}
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************

void* Class3A::operator new(size_t sz,int aMode)
{
   Prn::print(0, "Class3A::newM   %d %d",aMode,(int)sz);

   void* tPtr = malloc(sz);
   return tPtr;
}
  
void* Class3A::operator new[](size_t sz,int aMode)
{
   Prn::print(0, "Class3A::newM[] %d %d",aMode,(int)sz);

   void* tPtr = malloc(sz + 4);
   return tPtr;
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Class3A::operator delete(void* ptr,int aMode)
{
   Prn::print(0, "Class3A::deleteM   %d",aMode);
   ((Class3A*)ptr)->~Class3A();
   free(ptr);
}

void Class3A::operator delete[](void* tPtr,int aMode)
{
   int* tIntPtr = (int*)tPtr - 1;
   int tArraySize = *tIntPtr; 
   Class3A* tClassPtr = (Class3A*)tPtr;
   Prn::print(0, "Class3A::deleteM[] %d %d",aMode,tArraySize);

   for (int i = 0; i < tArraySize; i++)
   {
      tClassPtr[i].~Class3A();
   }
   free(tIntPtr);
}
}//namespace