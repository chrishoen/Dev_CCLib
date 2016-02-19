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

   static const int cTrueX;
   static const int cFalseX;
   static const int cNullX;

   static const LLogic cNull;
   static const LLogic cTrue;
   static const LLogic cFalse;

   static int iMin (int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }
   static int iMax (int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }
   bool isNull() const {return mX==cNullX;}

   //--------------------------------------------------------------
   // Members

   int mX;

   //--------------------------------------------------------------
   // Constructor

   LLogic()
   {
      mX = cNullX;
   }

   LLogic(int aX)
   {
      mX = aX;
   }

   //--------------------------------------------------------------
   // String

   char* str(char* aString)
   {
      if (mX == cNullX) strcpy(aString, "NULL");
      else             sprintf(aString, "%3d",mX);
      return aString;
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
      return LLogic(iMin(lhs.mX,rhs.mX));
   }

   //--------------------------------------------------------------
   // Operator OR

   friend LLogic operator |(const LLogic& lhs,const LLogic& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LLogic(iMax(lhs.mX,rhs.mX));
   }

   //--------------------------------------------------------------
   // Operator IMPLIES

   friend LLogic operator >>(const LLogic& lhs,const LLogic& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LLogic(iMin(cTrueX,lhs.mX+rhs.mX));
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

