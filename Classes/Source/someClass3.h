#ifndef _SOMECLASS3_H_
#define _SOMECLASS3_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************


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

   static void* operator new      (size_t sz);
   static void* operator new[]    (size_t sz);
   static void  operator delete   (void* ptr);
   static void  operator delete[] (void* ptr);

   int mCode;
   
};

//******************************************************************************
}//namespace

#endif

