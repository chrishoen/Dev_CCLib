#ifndef _CCNODEBLOCKCHANNEL_H_
#define _CCNODEBLOCKCHANNEL_H_

#include "ccTreeNode.h"
#include "ccTreeNodeTxQueue.h"
#include "ccTreeNodeRxQueue.h"
#include "ccNodeBlock.h"
#include "ccNodeBlockVisitor.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

inline void transferNodeBlockQueues(
   CC::TreeNodeTxQueue<CC::NodeBlock>* aTxQueue,
   CC::TreeNodeRxQueue<CC::NodeBlock>* aRxQueue)
{
   while (true)
   {
      CC::NodeBlock* tTxNode = aTxQueue->getNextTxNode();

      if (tTxNode != 0)
      {
#if 0
         printf("getNextTxNode        %5d %3d %s\n", 
            tTxNode->mIdentifier,
            tTxNode->mTxAttachLevel,
            tTxNode->mFullPath);
#endif
         CC::NodeBlock* tRxNode = new CC::NodeBlock(tTxNode->mIdentifier);
         tRxNode->mTreeNodeTxFlags = tTxNode->mTreeNodeTxFlags;
         tRxNode->mTxAttachLevel = tTxNode->mTxAttachLevel;
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

inline void printNodeBlockRxQueue(
   CC::TreeNodeRxQueue<CC::NodeBlock>* aRxQueue)
{
   CC::printAllNodeBlocks1(aRxQueue->mRootNode);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

inline void printNodeBlockTxQueue(
   CC::TreeNodeTxQueue<CC::NodeBlock>* aTxQueue)
{
   CC::printAllNodeBlocks1(aTxQueue->mRootNode);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif