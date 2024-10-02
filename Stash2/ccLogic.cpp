
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ccLogic.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Constructors

ConditionCount::ConditionCount()
{
   reset();
}

void ConditionCount::reset()
{
   mTrueCount=0;
   mFalseCount=0;
   mTotalCount=0;
   mQuantity=cCountNone;
   
   mNoneFlag=true;
   mOneFlag=false;
   mSomeFlag=false;
   mAllFlag=false;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

void ConditionCount::update(bool aCondition)
{
   if (aCondition)
   {
      mTrueCount++;
   }
   else
   {
      mFalseCount++;
   }
   mTotalCount++;

   mNoneFlag = (mTrueCount==0);
   mOneFlag  = (mTrueCount==1);
   mSomeFlag = (mTrueCount!=0);
   mAllFlag  = (mTrueCount==mTotalCount);

   if(mNoneFlag) mQuantity = cCountNone;
   if(mOneFlag ) mQuantity = cCountOne;
   if(mSomeFlag) mQuantity = cCountSome;
   if(mAllFlag)  mQuantity = cCountAll;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace