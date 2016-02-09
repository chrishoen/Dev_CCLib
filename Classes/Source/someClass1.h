#ifndef _SOMECLASS1_H_
#define _SOMECLASS1_H_

/*==============================================================================
File: someClass1.h
Description:
QCall test Class class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <functional>
#include "risCallPointer.h"

namespace Some
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// test1
// test2

class  Class1A
{
public:

   Class1A();

   //--------------------------------------------------------------
   //--------------------------------------------------------------
   //--------------------------------------------------------------
   // CallPointer:

   typedef Ris::CallPointer1<int>   MyCallPointer;
   MyCallPointer            mMyCallPointer1;
   std::function<void(int)> mMyCallPointer2;

   void myCall1(int aX);
   void myCall2(int aX);

};

//******************************************************************************
// Global instance

#ifdef _SOMECLASS1_CPP_
          Class1A gClass1A;
#else
   extern Class1A gClass1A;
#endif

//******************************************************************************
}//namespace

/*==============================================================================
Copyright (C) 2014 Chris Hoen, Hamburg NY.
Legal Notice:  It is forbidden to do anything against me because of this.
Legal Warning: Use this at your own risk, it's software.
Legal Rights:  Other than that, do whatever you want with it.
==============================================================================*/


#endif

