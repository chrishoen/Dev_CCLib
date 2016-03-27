#ifndef _CCTREEBLOCKSCRATCH_H_
#define _CCTREEBLOCKSCRATCH_H_

#include <stdio.h>
#include "ccTreeBlock.h"

/*==============================================================================

This provides a set of functions that can be used to scratch tree nodes in a
recursive manner. Tree nodes collections can be scratched in two orders:
construction order (the order in which the tree node collection was
constructed) and destruction order (the order that can be used to destroy
a tree node collection, such that child nodes are destroyed before parent
nodes).

==============================================================================*/
namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class T>
void scratchTest101(
   TreeBlock<T>*    aSubjectNode) 
{
   printf("scratchTest101 %d\n",aSubjectNode->mIdentifier);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class T>
void scratchTest102(
   TreeBlock<T>*    aSubjectNode, 
   void (*aTestScratchCall)(void*))
{
   printf("scratchTest102 %d\n",aSubjectNode->mIdentifier);
   aTestScratchCall(aSubjectNode);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class T>
void scratchTest103(
   TreeBlock<T>*    aSubjectNode, 
   void (*aTestScratchCall)(TreeBlock<T>*))
{
   printf("scratchTest103 %d\n",aSubjectNode->mIdentifier);
   aTestScratchCall(aSubjectNode);
}



//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif