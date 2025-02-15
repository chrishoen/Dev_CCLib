#pragma once

#if defined(WIN32)
#include <intrin.h>
#endif

/*==============================================================================
Intrinsics for memory barriers and safe memory accesses.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Safe read of 64 bits from shared memory on a 32 bit cpu.

static inline long long saferead_i64(volatile long long* aValuePtr)
{
   // Loop to do two consecutive reads. If the top 32 bits of both are
   // the same then done. If they're never the same and the loop finishes
   // then something is wrong.
   for (int i = 0; i < 20; i++)
   {
      const long long cMask = 0xffffffff00000000;
      long long volatile tValue1 = *aValuePtr;
      long long volatile tValue2 = *aValuePtr;
      if ((tValue1 & cMask) == (tValue2 & cMask)) return tValue1;
   }
   return -1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory barriers.

#if 0
#if defined(WIN32) || defined(__x86_64) // If x86_64
#define memory_barrier(x)   asm volatile ("mfence" ::: "memory");
#define load_barrier(x)     asm volatile ("mfence" ::: "memory");
#define store_barrier(x)    asm volatile ("mfence" ::: "memory");
#else // Else armv7 or armv8
#define memory_barrier(x)   asm volatile ("dsb sy" ::: "memory");
#define load_barrier(x)     asm volatile ("dsb sy" ::: "memory");
#define store_barrier(x)    asm volatile ("dsb sy" ::: "memory");
#endif
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory barriers.

#if defined(WIN32)
static inline void memory_barrier()
{
   __faststorefence();
}

static inline void load_barrier()
{
   __faststorefence();
}

static inline void store_barrier()
{
   __faststorefence();
}

#else // Else armv7 or armv8
static inline void memory_barrier()
{
// asm volatile ("dsb sy" ::: "memory");
   asm volatile ("dsb sy" ::: "memory");
}

static inline void load_barrier()
{
// asm volatile ("dsb ld" ::: "memory");
   asm volatile ("dsb sy" ::: "memory");
}

static inline void store_barrier()
{
// asm volatile ("dsb st" ::: "memory");
   asm volatile ("dsb sy" ::: "memory");
}
#endif
