#pragma once

/*==============================================================================
Intrinsics for memory barriers and safe memory accesses.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Safe read of 64 bits from shared memory on a 32 bit cpu.

inline long long saferead_i64(long long* aValuePtr)
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

inline void memory_barrier()
{
   asm volatile ("dsb sy" ::: "memory");
}

inline void load_barrier()
{
   asm volatile ("dsb sy" ::: "memory");
// asm volatile("dsb ld" : : : "memory");
}

inline void store_barrier()
{
   asm volatile ("dsb sy" ::: "memory");
// asm volatile("dsb st" : : : "memory");
}
