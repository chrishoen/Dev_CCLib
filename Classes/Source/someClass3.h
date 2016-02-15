#ifndef _SOMECLASS3_H_
#define _SOMECLASS3_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <new>

namespace Some
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
class  Class3A
{
public:

   Class3A();
  ~Class3A();

#if 0
   static void* operator new      (size_t sz);
   static void* operator new[]    (size_t sz);
   static void  operator delete   (void* ptr);
   static void  operator delete[] (void* ptr);
#endif
   static void* operator new      (size_t sz,int aMode);
   static void* operator new[]    (size_t sz,int aMode);
   static void  operator delete   (void* ptr,int aMode);
   static void  operator delete[] (void* ptr,int aMode);

   int mCode;
};

//******************************************************************************
}//namespace

#endif

