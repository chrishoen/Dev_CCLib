#ifndef _CCLABELLEDTREENODECHANNEL_H_
#define _CCLABELLEDTREENODECHANNEL_H_

#include "ccTreeNode.h"
#include "ccTreeNodeTxQueue.h"
#include "ccTreeNodeRxQueue.h"
#include "ccLabelledTreeNode.h"
#include "ccLabelledTreeNodeVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

inline void transferLabelledTreeNodeQueues(
   CC::TreeNodeTxQueue<CC::LabelledTreeNode>* aTxQueue,
   CC::TreeNodeRxQueue<CC::LabelledTreeNode>* aRxQueue)
{
   while (true)
   {
      CC::LabelledTreeNode* tTxNode = aTxQueue->getNextTxNode();

      if (tTxNode != 0)
      {
#if 0
         printf("getNextTxNode        %5d %s\n", 
            tTxNode->mIdentifier,
            tTxNode->mFullPath);
#endif
         CC::LabelledTreeNode* tRxNode = new CC::LabelledTreeNode(tTxNode->mIdentifier, tTxNode->mLabel);
         tRxNode->mTreeNodeTxFlags = tTxNode->mTreeNodeTxFlags;
         aRxQueue->putRxNode(tRxNode);
      }
      else
      {
         break;
      }
   }

}

//****************************************************************************
//****************************************************************************
//****************************************************************************

inline void printLabelledTreeNodeRxQueue(
   CC::TreeNodeRxQueue<CC::LabelledTreeNode>* aRxQueue)
{
   CC::printAllLabelledTreeNodes1(aRxQueue->mRootNode);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

inline void printLabelledTreeNodeTxQueue(
   CC::TreeNodeTxQueue<CC::LabelledTreeNode>* aTxQueue)
{
   CC::printAllLabelledTreeNodes1(aTxQueue->mRootNode);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif