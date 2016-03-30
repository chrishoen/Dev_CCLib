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

void printAllLabelledTreeNodes1(LabelledTreeNode* aSubjectNode);
void printAllLabelledTreeNodes2(LabelledTreeNode* aSubjectNode);
void printAllLabelledTreeNodes3(LabelledTreeNode* aSubjectNode);

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