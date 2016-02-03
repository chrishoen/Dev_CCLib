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
   bool mWaitEnable;
#else
   extern int mWaitArray[cWaitArraySize];
   extern int mWaitIndex;
   extern int mWaitCount;
   extern bool mWaitEnable;
#endif


   void initialize(int aN1, int aN2);
   void show();

   inline void wait()
   {
      if (!mWaitEnable)return;
      int tLoop = mWaitArray[mWaitIndex];
      if (++mWaitIndex >= cWaitArraySize-10) mWaitIndex=0;
      for (int i = 0; i < tLoop; i++){}
   }

   inline void delay()
   {
      int tCount=0;
      int tLoop = my_irand(0, 2*750);
      for (int i=0;i<tLoop;i++) tCount++;

   }


}//namespace
#endif

