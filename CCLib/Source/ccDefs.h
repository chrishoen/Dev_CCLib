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

// operator new[] adds extra bytes to store number of elements.
static const int cNewArrayExtraMemory = 4;

#ifndef _MSC_VER
#define NOEXCEPT noexcept(true)
#else
#define NOEXCEPT
#endif

} //namespace
#endif

