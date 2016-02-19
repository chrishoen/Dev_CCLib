#ifndef _LLOGIC_H_
#define _LLOGIC_H_

/*==============================================================================
==============================================================================*/
#include <string.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************
class LLogic
{
public:

   //--------------------------------------------------------------
   // Support

   static const float cTrueX;
   static const float cFalseX;
   static const float cNullX;

   static const LLogic cNull;
   static const LLogic cTrue;
   static const LLogic cFalse;

   static float fMin (float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }
   static float fMax (float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }
   bool isNull() const {return mX==cNullX;}

   //--------------------------------------------------------------
   // Members

   float mX;
   char  mString[8];

   //--------------------------------------------------------------
   // Constructor

   LLogic()
   {
      mX = cNullX;
      mString[0]=0;
   }

   LLogic(float aX)
   {
      mX = aX;
   }

   //--------------------------------------------------------------
   // String

   char* str()
   {
      if (mX == cNullX) strcpy(mString, "NULL");
      else             sprintf(mString, "%4.3f",mX);
      return mString;
   }

   //--------------------------------------------------------------
   // Operator NOT

   LLogic operator~()
   {
      if (isNull()) return cNull;
      return LLogic(cTrueX - this->mX);
   }
 
   //--------------------------------------------------------------
   // Operator AND

   friend LLogic operator &(const LLogic& lhs,const LLogic& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LLogic(fMin(lhs.mX,rhs.mX));
   }

   //--------------------------------------------------------------
   // Operator OR

   friend LLogic operator |(const LLogic& lhs,const LLogic& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LLogic(fMax(lhs.mX,rhs.mX));
   }

   //--------------------------------------------------------------
   // Operator IMPLIES

   friend LLogic operator >>(const LLogic& lhs,const LLogic& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LLogic(fMin(cTrueX,lhs.mX+rhs.mX));
   }

   //--------------------------------------------------------------
   // Operator EQUIVALENCE

   friend LLogic operator %(const LLogic& lhs,const LLogic& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LLogic(cTrueX - (lhs.mX > rhs.mX ? lhs.mX : rhs.mX));
   }
};

#endif

