#ifndef _SOMEMYTREEBLOCK_H_
#define _SOMEMYTREEBLOCK_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "ccTreeNode.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

//ass MyTreeBlock : public CC::TreeNode, public CC::BlockPoolBlock<Some::MyTreeBlock,Some::cBlockPoolIndex_MyTreeBlock>
class MyTreeBlock : public CC::TreeNode
{
public:

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Memory management, constructors and destructors

   // Create with default memory type and specified member variables
   static MyTreeBlock* create (int aIdentifier);

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete.

   void destroy();

   // Constructor, it is called by create after allocation of a new block.
   MyTreeBlock();
   MyTreeBlock(int aIdentifier);

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Class members

   int  mCode1;
   int  mCode2;
   int  mCode3;
   int  mCode4;

   void method1A();
};

//******************************************************************************
}//namespace

#endif

