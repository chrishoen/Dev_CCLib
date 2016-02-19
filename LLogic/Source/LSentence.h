#ifndef _LSENTENCE_H_
#define _LSENTENCE_H_

/*==============================================================================
==============================================================================*/
#include "LLogic.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
class LSentence
{
public:
   //--------------------------------------------------------------
   // Support
   static const int cNullN = -1;
   static const LSentence cNull;
   //--------------------------------------------------------------
   // Members

   int mN;
   LLogic mX;

   int mRefN;
   LLogic mRefX;

   //--------------------------------------------------------------
   // Constructor

   LSentence()
   {
      mN    = cNullN;
      mRefN = cNullN;
   }

   LSentence(int aN,LLogic aX)
   {
      mN = aN;
      mX = aX;
   }

   LSentence(int aN,LSentence* aRef)
   {
      mN    = aN;
      mX    = LLogic::cTrue;
      mRefN = aRef->mN;
      mRefX = aRef->mX;
   }

};

#endif

