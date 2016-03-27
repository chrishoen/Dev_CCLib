#ifndef _SOMECLASS4_H_
#define _SOMECLASS4_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"
#include "ccCallPointer.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

typedef CC::CallPointer0<> Method2Call;

class Base4
{
public:

   Base4()
   {
      mBaseCode1=0;
   }

   virtual void base_method1()
   {
      Prn::print(0, "Base4::base_method1 %d",mBaseCode1);
   }

   void base_method2()
   {
      if (mMethod2Call.isValid())
      {
         mMethod2Call();
      }
      else
      {
         Prn::print(0, "Base4::base_method2 default %d", mBaseCode1);
      }
   }

   int mBaseCode1;
   Method2Call mMethod2Call;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class BlockClass>
class Class4A : public Base4
{
public:

   Class4A()
   {
   }

   void base_method1()
   {
      Prn::print(0, "Class4A::base_method1 %d",mBaseCode1);
   }

   void method4A()
   {
      Prn::print(0, "Class4A::method4A %d",mCode1);
   }

   static int mCode1;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class Class4B : public Class4A<Class4B>
{
public:

   Class4B()
   {
      Base4::mMethod2Call.bind(this,&Class4B::base_method2);

   }

   void method4B()
   {
      Prn::print(0, "Class4B::method4B %d",mCode1);
   }

   void base_method2()
   {
      Prn::print(0, "Class4B::base_method2 %d", mBaseCode1);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

inline void testBase4(Base4* aX)
{
   aX->base_method1();
   aX->base_method2();
}

template <class BlockClass>
inline void testClass4A(Class4A<BlockClass>* aX)
{
   aX->method4A();
   aX->base_method2();
}

//******************************************************************************
}//namespace

#endif
