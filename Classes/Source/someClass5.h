#ifndef _SOMECLASS5_H_
#define _SOMECLASS5_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

namespace Some
{

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   class Class5A
   {
   public:

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      //------------------------------------------------------------------------

      int mCode5A;

      Class5A()
      {
         mCode5A = 101;
      }

      virtual void method5A1()
      {
         Prn::print(0, "Class5A::method5A1 %d", mCode5A);
      }

      void method5A2()
      {
         Prn::print(0, "Class5A::method5A2 %d", mCode5A);
      }

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      //------------------------------------------------------------------------

      static void method5AS1()
      {
         Prn::print(0, "Class5A::method5AS1");
      }
   };

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   class Class5B : public Class5A
   {
   public:

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      //------------------------------------------------------------------------

      int mCode5B;

      Class5B()
      {
         mCode5A = 102;
         mCode5B = 201;
      }

      virtual void method5A1()
      {
         Prn::print(0, "Class5B::method5A1 %d", mCode5A);
      }

      void method5B2()
      {
         Prn::print(0, "Class5B::method5B2 %d", mCode5B);
      }

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      //------------------------------------------------------------------------

      static void method5AS1()
      {
         Prn::print(0, "Class5B::method5AS1");
      }

      static void method5BS1()
      {
         Prn::print(0, "Class5B::method5BS1");
      }
   };

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
}//namespace
#endif

