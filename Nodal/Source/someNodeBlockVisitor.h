#ifndef _CCNODEBLOCKVISITOR_H_
#define _CCNODEBLOCKVISITOR_H_

#include "ccTreeNodeVisitor.h"
#include "someNodeBlock.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitNodeBlockForPrint (NodeBlock* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor);

void printAllNodeBlocks1(NodeBlock* aSubjectNode);
void printAllNodeBlocks2(NodeBlock* aSubjectNode);
void printAllNodeBlocks3(NodeBlock* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitNodeBlockForDestroy (NodeBlock* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor);

void destroyAllNodeBlocks(NodeBlock* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif