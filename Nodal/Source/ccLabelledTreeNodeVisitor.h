#ifndef _CCLABELLEDTREENODEVISITOR_H_
#define _CCLABELLEDTREENODEVISITOR_H_

#include "ccLabelledTreeNode.h"
#include "ccTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitLabelledTreeNodeForPrint (LabelledTreeNode* aSubjectNode, RecursiveAnchor* aRecursiveAnchor);

void printAllLabelledTreeNodes1(LabelledTreeNode* aSubjectNode);
void printAllLabelledTreeNodes2(LabelledTreeNode* aSubjectNode);
void printAllLabelledTreeNodes3(LabelledTreeNode* aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif