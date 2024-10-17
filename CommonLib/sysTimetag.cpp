/*==============================================================================
==============================================================================*/

#include "stdafx.h"

#include "risMemMap.h"
#include "sysTimetag.h"

namespace Sys
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Regionals.

// Pointers to memory mapped timer registers.
static const unsigned cPhysicalAddress_TSTMR_LO = 0x442c0000;
static char* mVirtualAddress_TSTMR_LO = 0;
static char* mVirtualAddress_TSTMR_HI = 0;
   
// Automatically initialize on program enter and 
// finalize on program exit.
class TimetagInitClass
{
public:
   TimetagInitClass()
   {
      mVirtualAddress_TSTMR_LO = Ris::getMemMapVirtualAddress(cPhysicalAddress_TSTMR_LO, 1);
      mVirtualAddress_TSTMR_HI = mVirtualAddress_TSTMR_LO + 4;
   }
   ~TimetagInitClass()
   {
      Ris::unmapMemMapVirtualAddress(mVirtualAddress_TSTMR_LO, 1);
   }
};
TimetagInitClass gTimetagInitInstance;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return the current timetag nanoseconds. 

inline long long int my_get_timetag_ns()
{
   // Guard.
   if (mVirtualAddress_TSTMR_LO == 0) return 0;

   // Read the lo and hi timestamp timer registers.
   // Read the lo register first. The high register is latched when
   // you read the low register. 
   unsigned tTimetagLo;
   unsigned tTimetagHi;
   unsigned tTimetagHi0;

   
   // Read the registers. Read the high register twice and compare to
   // avoid a possible race condition. This might be interrupted and the
   // high register might be latched when somebody else reads the low
   // register and might also change at the same time. Not likely.
   for (int i = 0; i < 100; i++)
   {
      tTimetagHi0 = *((unsigned*)mVirtualAddress_TSTMR_HI);
      tTimetagLo = *((unsigned*)mVirtualAddress_TSTMR_LO);
      tTimetagHi = *((unsigned*)mVirtualAddress_TSTMR_HI);
      if (tTimetagHi0 == tTimetagHi) break;
      if (i == 99) printf("my_get_timetag_ns something seriously wrong\n");
   }

   // Combine the hi and lo into a 64 bit integer. The lsb is 1/24MHz.
   long long tTimetag24MHz = ((long long)tTimetagHi) << 32 | ((long long)tTimetagLo);

   // Convert to ns. Note: (1e9/24e6) = 41.66666.. = 125/3.
   long long tTimetagNs = (125 * tTimetag24MHz) / 3;
   return tTimetagNs;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return the current timetag.

double getTimetag()
{
   // Return the current timetag in seconds.
   return (double)(my_get_timetag_ns())*1E-9;
}

int getTimetagMs()
{
   // Return the current timetag in milliseconds.
   return (int)(my_get_timetag_ns() / (1000 * 1000));
}

double getTimetagUs()
{
   // Return the current timetag in microseconds.
   return (double)(my_get_timetag_ns()) * 1E-3;
}

long long getTimetagNs()
{
   // Return the current timetag in nanoseconds.
   return my_get_timetag_ns();
}

// Convert to seconds.
double getTimetagFromNs(long long aTimetagNs)
{
   return aTimetagNs * 1E9;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

