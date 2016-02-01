#ifndef _LFBACKOFF_H_
#define _LFBACKOFF_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFBackoff
{


   //******************************************************************************
   // Random wait array and index

   static const int cWaitArraySize = 1000;
#ifdef _LFBACKOFF_CPP_
   int mWaitArray[cWaitArraySize];
   int mWaitIndex;
   int mWaitCount;
#else
   extern int mWaitArray[cWaitArraySize];
   extern int mWaitIndex;
   extern int mWaitCount;
#endif


   void initialize(int aN1, int aN2);

   inline void wait()
   {
      int tLoop = mWaitArray[mWaitIndex];
      if (++mWaitIndex > cWaitArraySize) mWaitIndex=0;
      for (int i=0;i<tLoop;i++) mWaitCount++;
   }

}//namespace
#endif

