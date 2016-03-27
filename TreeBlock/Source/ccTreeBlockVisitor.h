#ifndef _CCTREEBLOCKVISITOR_H_
#define _CCTREEBLOCKVISITOR_H_

#include <stdio.h>
#include "ccTreeBlock.h"

/*==============================================================================

This provides a set of functions that can be used to visit tree nodes in a
recursive manner. Tree nodes collections can be visited in two orders:
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
void visitTest101(
   TreeBlock<T>*    aSubjectNode) 
{
   printf("visitTest101 %d\n",aSubjectNode->mIdentifier);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class T>
void visitTest102(
   TreeBlock<T>*    aSubjectNode, 
   void (*aTestVisitorCall)(void*))
{
   printf("visitTest102 %d\n",aSubjectNode->mIdentifier);
   aTestVisitorCall(aSubjectNode);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

template <class T>
void visitTest103(
   TreeBlock<T>*    aSubjectNode, 
   void (*aTestVisitorCall)(TreeBlock<T>*))
{
   printf("visitTest103 %d\n",aSubjectNode->mIdentifier);
   aTestVisitorCall(aSubjectNode);
}



//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif