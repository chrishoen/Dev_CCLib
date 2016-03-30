#ifndef _CCMYTREEBLOCKVISITOR_H_
#define _CCMYTREEBLOCKVISITOR_H_

#include "ccTreeNodeVisitor.h"
#include "someMyTreeBlock.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitMyTreeBlockForPrint (MyTreeBlock* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor);

void printAllMyTreeBlocks1(MyTreeBlock* aSubjectNode);
void printAllMyTreeBlocks2(MyTreeBlock* aSubjectNode);
void printAllMyTreeBlocks3(MyTreeBlock* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitMyTreeBlockForDestroy (MyTreeBlock* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor);

void destroyAllMyTreeBlocks(MyTreeBlock* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif