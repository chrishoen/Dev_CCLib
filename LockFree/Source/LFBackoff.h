#ifndef _LFBACKOFF_H_
#define _LFBACKOFF_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************


void LFBackoff_reset();
void LFBackoff_reset(int aN1,int aN2);

class LFBackoff
{
    int mInitial;
    int mStep;
    int mThreshold;
    int mCurrent;
    int mCount;
public:
   LFBackoff(int aMode=1);
   void backoff();
   void nop();
};
#endif

