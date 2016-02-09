/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#define  _SOMECLASS1_CPP_
#include "someClass1.h"

using namespace std::placeholders;

namespace Some
{

Class1A::Class1A()
{
   mCount=0;
   // CallPointers
   mCallPointer1.bind  (this,&Class1A::myCall1);
   mCallPointer2 = std::bind(&Class1A::myCall1,this,_1);
}

//******************************************************************************

void Class1A::myCall1(int aX)
{
// Prn::print(0,"Class1::myCall1 %d",aX);
   mCount = aX;
}

void Class1A::myCall2(int aX)
{
// Prn::print(0,"Class1::myCall2 %d",aX);
   mCount = aX;
}

}//namespace