#ifndef _SOMEMYTREEBLOCKCHANNEL_H_
#define _SOMEMYTREEBLOCKCHANNEL_H_

#include "ccTreeNode.h"
#include "ccTreeNodeTxQueue.h"
#include "ccTreeNodeRxQueue.h"
#include "someMyTreeBlock.h"
#include "someMyTreeBlockVisitor.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

inline void transferMyTreeBlockQueues(
   CC::TreeNodeTxQueue<Some::MyTreeBlock>* aTxQueue,
   CC::TreeNodeRxQueue<Some::MyTreeBlock>* aRxQueue)
{
   while (true)
   {
      Some::MyTreeBlock* tTxNode = aTxQueue->getNextTxNode();

      if (tTxNode != 0)
      {
#if 0
         printf("getNextTxNode        %5d %3d %s\n", 
            tTxNode->mIdentifier,
            tTxNode->mTxAttachLevel,
            tTxNode->mFullPath);
#endif
         Some::MyTreeBlock* tRxNode = Some::MyTreeBlock::create(tTxNode->mIdentifier);
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

inline void printMyTreeBlockRxQueue(
   CC::TreeNodeRxQueue<Some::MyTreeBlock>* aRxQueue)
{
   Some::printAllMyTreeBlocksCO(aRxQueue->mRootNode);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************

inline void printMyTreeBlockTxQueue(
   CC::TreeNodeTxQueue<Some::MyTreeBlock>* aTxQueue)
{
   Some::printAllMyTreeBlocksCO(aTxQueue->mRootNode);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif