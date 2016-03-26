#ifndef _CCLabelledTreeNode_H_
#define _CCLabelledTreeNode_H_

#include "ccTreeNode.h"
#include "ccDefs.h"
#include "ccBlockPoolBlock.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class LabelledTreeNode : public TreeNode, public CC::BlockPoolBlock<LabelledTreeNode>
{
public:
   typedef TreeNode BaseClass;

   // Create with default memory type and specified member variables
   static LabelledTreeNode* create (int aIdentifier,char* aLabel);

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete.

   virtual void destroy();

   // Constructor, it is called by create after allocation of a new block.
   LabelledTreeNode();
   LabelledTreeNode(int aIdentifier,char* aLabel);

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Class members

   // Label
   enum { MaxLabelSize = 20 };
   char mLabel[MaxLabelSize];
   void setLabel(char* aLabel);

   // This gets the full path label of a subject node
   char* getFullPath();

   // Full path
   enum { MaxFullPathSize = 200 };
   char mFullPath[MaxFullPathSize];
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif