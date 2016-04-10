#ifndef _CCDEFS_H_
#define _CCDEFS_H_

/*==============================================================================
==============================================================================*/

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Block memory type

enum
{
   MemoryType_System    = 0,   // System heap storage, malloc/free
   MemoryType_LongTerm  = 1,   // Lifetime that is long term, persistent
   MemoryType_ShortTerm = 2,   // Lifetime that is short term, non persistent
};

enum { MaxLevelDepth = 20 };

static const int cNewArrayExtra = 8;

#ifndef _MSC_VER
#define NOEXCEPT noexcept(true)
#else
#define NOEXCEPT
#endif

} //namespace
#endif

