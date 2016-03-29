#ifndef _CCRECURSIVEANCHOR_H_
#define _CCRECURSIVEANCHOR_H_

/*==============================================================================
Recursive Anchor
==============================================================================*/
namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is the recursive anchor class. Instances of it are passed to 
// recursive functions that visit tree nodes. It is used to maintain state
// between the recursive visit calls.

class RecursiveAnchor
{
public:
   // Constructor
   RecursiveAnchor()
   {
      mIndex = 0;
      mLevel = 0;
      mFirstInLevel = true;
   }

   // Members
   // This is incremented for each recursive call
   int   mIndex;
   // This is the recursive level
   int   mLevel;
   // If true the the current visitation is the first in its level
   bool  mFirstInLevel;
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif