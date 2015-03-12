#ifndef _CCLabelledTreeNode_H_
#define _CCLabelledTreeNode_H_

#include "ccTreeNode.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class LabelledTreeNode : public TreeNode
{
public:
   typedef TreeNode BaseClass;

   // Constructor
   LabelledTreeNode();
   LabelledTreeNode(int aIdentifier,char* aLabel);

   // Label
   enum { MaxLabelSize = 20 };
   char mLabel[MaxLabelSize];

   // Full path
   enum { MaxFullPathSize = 200 };
   char mFullPath[MaxFullPathSize];

   // This is called on a subject node after it is attached to an object node
   virtual void onAttached();

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif