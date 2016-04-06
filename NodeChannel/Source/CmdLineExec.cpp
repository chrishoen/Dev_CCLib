#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "ccTreeNodeVisitor.h"
#include "ccTreeNodeDestroyer.h"
#include "ccBlockPoolCentral.h"
#include "someBlockPoolIndex.h"
#include "someMyTreeBlock.h"
#include "someGenerateMyTreeBlocks.h"
#include "someMyTreeBlockVisitor.h"

#include "ccTreeNodeTxQueue.h"
#include "ccTreeNodeRxQueue.h"
#include "someMyTreeBlockChannel.h"

#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
   if(aCmd->isCmd("GO6"    ))  executeGo6(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   printf("**********************************go4\n");
   printf("**********************************go4\n");
   printf("**********************************go4\n");
   printf("\n");


   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------


   Some::MyTreeBlock* tTxQueueRootNode = Some::MyTreeBlock::create(2000);
   Some::MyTreeBlock* tRxQueueRootNode = Some::MyTreeBlock::create(3000);
   Some::MyTreeBlock* tRootNode1       = Some::MyTreeBlock::create(1000);

   CC::TreeNodeTxQueue<Some::MyTreeBlock> tTxQueue;
   CC::TreeNodeRxQueue<Some::MyTreeBlock> tRxQueue;

   tTxQueue.setRootNode(tTxQueueRootNode);
   tRxQueue.setRootNode(tRxQueueRootNode);
   
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   printf("**********************************generateTreeNodes1(tRootNode1)\n");
   Some::generateMyTreeBlocks1(tRootNode1);
   Some::printAllMyTreeBlocks1(tRootNode1);

   printf("**********************************tTxQueue.putTxNode(tRootNode1)\n");
   tTxQueue.putTxNode(tRootNode1);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   printf("**********************************printMyTreeBlockTxQueue\n");
   printf("\n");
   Some::printMyTreeBlockTxQueue(&tTxQueue);
   printf("\n");

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------

   printf("**********************************transferMyTreeBlockQueues\n");
   Some::transferMyTreeBlockQueues(&tTxQueue, &tRxQueue);
   printf("\n");

   printf("**********************************printMyTreeBlockRxQueue\n");
   Some::printMyTreeBlockRxQueue(&tRxQueue);
   printf("\n");

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
   Some::MyTreeBlock* tRootNode = Some::MyTreeBlock::create(999);
   Some::generateMyTreeBlocks1(tRootNode);
   Some::printAllMyTreeBlocks1(tRootNode);

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
// CC::destroyAllTreeNodes(tRootNode);
   Some::destroyAllMyTreeBlocks(tRootNode);
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);

   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);

   Some::MyTreeBlock* tRootNode = Some::MyTreeBlock::create(1);

   if (aCmd->argInt(1) == 1)
   {
      Some::generateMyTreeBlocks1(tRootNode);
   }
   else if (aCmd->argInt(1) == 2)
   {
      Some::generateMyTreeBlocks2(tRootNode);
   }
   else if (aCmd->argInt(1) == 3)
   {
      Some::generateMyTreeBlocks3(tRootNode);
   }

   Some::printAllMyTreeBlocks1(tRootNode);
   CC::showBlockPool(Some::cBlockPoolIndex_MyTreeBlock);
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Some::MyTreeBlock* tRootNode = Some::MyTreeBlock::create(1);
   Some::generateMyTreeBlocks1(tRootNode);
   Some::printAllMyTreeBlocks1(tRootNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}

