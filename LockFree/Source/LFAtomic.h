#ifndef _LFATOMIC_H_
#define _LFATOMIC_H_

#include <windows.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Easier to use compare and exchange functions.

inline bool my_bool_cae(int* aDestin, int aCompare, int aExchange)
{
   int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
   return tOriginal == aCompare; 
}

inline int my_val_cae(int* aDestin, int aCompare, int aExchange)
{
   int tOriginal = (int)InterlockedCompareExchange((PLONG)aDestin, *((LONG*)&aExchange), *((LONG*)&aCompare));
   return tOriginal; 
}

inline int my_fetch_add(int* aAddend, int aValue)
{
   int tOriginal = (int)InterlockedExchangeAdd((PLONG)aAddend, *((LONG*)&aValue));
   return tOriginal; 
}

#endif

