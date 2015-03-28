#ifndef _CCNODEBLOCKVISITOR_H_
#define _CCNODEBLOCKVISITOR_H_

#include "ccNodeBlock.h"
#include "ccTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitNodeBlockForPrint (NodeBlock* aSubjectNode, RecursiveAnchor* aRecursiveAnchor);

void printAllNodeBlocks1(NodeBlock* aSubjectNode);
void printAllNodeBlocks2(NodeBlock* aSubjectNode);
void printAllNodeBlocks3(NodeBlock* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitNodeBlockForDestroy (NodeBlock* aSubjectNode, RecursiveAnchor* aRecursiveAnchor);

void destroyAllNodeBlocks(NodeBlock* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif