#ifndef _CCMYBLOCKVISITOR_H_
#define _CCMYBLOCKVISITOR_H_

#include "ccTreeBlockVisitor.h"
#include "someMyBlock.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitMyBlockForPrint (MyBlock* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor);

void printAllMyBlocks1(MyBlock* aSubjectNode);

void test101(MyBlock* aSubjectNode);


//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif