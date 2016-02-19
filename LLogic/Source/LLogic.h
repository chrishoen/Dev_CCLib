#ifndef _LLOGIC_H_
#define _LLOGIC_H_

/*==============================================================================
File: someClass1.h
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

class LLogic
{
public:

   //--------------------------------------------------------------
   // Support

   float cTrue  = 1.0f;
   float cFalse = 0.0f;
   float cInvalid = -1.0f;

   inline static float fMin (float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }
   inline static float fMax (float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }
   //--------------------------------------------------------------
   // Members

   float mX;

   //--------------------------------------------------------------
   // Constructor

   inline LLogic()
   {
      mX = cInvalid;
   }

   inline LLogic(float aX)
   {
      mX = aX;
   }

   LLogic operator~()
   {
      return LLogic(1.0f - this->mX);
   }
 
   friend LLogic operator &(const LLogic& lhs,   const LLogic& rhs)
   {
      return LLogic(fMin(lhs.mX,rhs.mX));
   }

   friend LLogic operator |(const LLogic& lhs,   const LLogic& rhs)
   {
      return LLogic(fMax(lhs.mX,rhs.mX));
   }
};

#endif

