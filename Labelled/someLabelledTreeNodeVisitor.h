#ifndef _CCLABELLEDTREENODEVISITOR_H_
#define _CCLABELLEDTREENODEVISITOR_H_

#include "someLabelledTreeNode.h"
#include "ccTreeNodeVisitor.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitLabelledTreeNodeForPrint (LabelledTreeNode* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor);

void printAllLabelledTreeNodesCO(LabelledTreeNode* aSubjectNode);
void printAllLabelledTreeNodesDO(LabelledTreeNode* aSubjectNode);
void printAllLabelledTreeNodesVN(LabelledTreeNode* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitLabelledTreeNodeForDestroy (LabelledTreeNode* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor);

void destroyAllLabelledTreeNodes(LabelledTreeNode* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif