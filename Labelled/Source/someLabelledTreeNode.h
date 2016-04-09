#ifndef _SOMELABELLEDTREENODE_H_
#define _SOMELABELLEDTREENODE_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "ccBlockPoolBlock.h"
#include "someBlockPoolIndex.h"
#include "ccTreeNode.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class LabelledTreeNode : public CC::TreeNode,public CC::BlockPoolBlock<Some::cBlockPoolIndex_LabelledTreeNode>
{
public:

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Constructors.

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

//******************************************************************************
}//namespace

#endif

