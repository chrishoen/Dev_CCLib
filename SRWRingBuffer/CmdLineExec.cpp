#include "stdafx.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
   Prn::print(0, "RESET");
   mObjectRing.initialize();
   mValueRing.initialize();
   for (int i = 0; i < 4; i++)
   {
      mObjectRing.doWrite(&i);
      mValueRing.doWrite(i);
   }

   for (int i = 0; i < 1000; i++)
   {
      mWriteArray[i] = i;
      mReadArray[i] = 0;
   }
}

void CmdLineExec::init()
{
   Prn::print(0, "INIT");
   mObjectRing.initialize();
   mValueRing.initialize();

   for (int i = 0; i < 1000; i++)
   {
      mWriteArray[i] = i;
      mReadArray[i] = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("RESET"))  reset();
   if (aCmd->isCmd("INIT"))   init();

   if (aCmd->isCmd("PUTO"))   executePutObject(aCmd);
   if (aCmd->isCmd("GETO"))   executeGetObject(aCmd);
   if (aCmd->isCmd("ATO"))    executeAtObject(aCmd);
   if (aCmd->isCmd("MARKO"))  executeMarkObject(aCmd);
   if (aCmd->isCmd("SHOWO"))  executeShowObject(aCmd);

   if (aCmd->isCmd("PUTV"))   executePutValue(aCmd);
   if (aCmd->isCmd("GETV"))   executeGetValue(aCmd);
   if (aCmd->isCmd("ATV"))    executeAtValue(aCmd);
   if (aCmd->isCmd("MARKV"))  executeMarkValue(aCmd);
   if (aCmd->isCmd("SHOWV"))  executeShowValue(aCmd);

   if (aCmd->isCmd("PUTA"))   executePutArray(aCmd);
   if (aCmd->isCmd("GETA"))   executeGetArray(aCmd);
   if (aCmd->isCmd("SHOWA"))  executeShowArray(aCmd);

   if (aCmd->isCmd("GO1"))    executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))    executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))    executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))    executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))    executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))    executeGo6(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePutObject(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   aCmd->setArgDefault(2, 1);
   int tValue = aCmd->argInt(1);
   int tLoop = aCmd->argInt(2);

   for (int i = 0; i < tLoop; i++)
   {
      int tTemp = tValue + i;
      mObjectRing.doWrite(&tTemp);
      Prn::print(0, "PUT %5s %4d", my_string_from_bool(mObjectRing.mFullFlag), tTemp);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGetObject(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tLoop = aCmd->argInt(1);
   int tValue = 0;
   
   for (int i = 0; i < tLoop; i++)
   {
      if (mObjectRing.tryRead(&tValue))
      {
         Prn::print(0, "READ %d", tValue);
      }
      else
      {
         Prn::print(0, "READ FAIL");
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeAtObject(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   int tIndex = aCmd->argInt(1);

   int* tPtr = mObjectRing.atOffset(tIndex);
   Prn::print(0, "AT  %d", *tPtr);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeMarkObject(Ris::CmdLineCmd* aCmd)
{
   for (int i = 0; i < 4; i++)
   {
      int* tPtr = mObjectRing.atOffset(i);
      *tPtr += 1000 + 100 * i;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShowObject(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "FullFlag      %s", my_string_from_bool(mObjectRing.mFullFlag));
   Prn::print(0, "available     %d", mObjectRing.available());
   Prn::print(0, "WriteIndex    %d", mObjectRing.mNextWriteIndex);
   Prn::print(0, "MaxReadIndex  %d", mObjectRing.mMaxReadIndex);
   Prn::print(0, "MinReadIndex  %d", mObjectRing.mMinReadIndex);

   Prn::print(0, "");
   for (int i = 0; i < 4; i++)
   {
      Prn::print(0, "atOffset     %d %d", i, *mObjectRing.atOffset(i));
   }

   return;
   Prn::print(0, "");
   for (int i = 4; i --> 0;)
   {
      Prn::print(0, "history      %d %d", i, mObjectRing.elementAt(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePutValue(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   aCmd->setArgDefault(2, 1);
   int tValue = aCmd->argInt(1);
   int tLoop = aCmd->argInt(2);

   for (int i = 0; i < tLoop; i++)
   {
      int tTemp = tValue + i;
      mValueRing.doWrite(tTemp);
      Prn::print(0, "PUT %5s %4d", my_string_from_bool(mValueRing.mFullFlag), tTemp);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGetValue(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tLoop = aCmd->argInt(1);
   int tValue = 0;

   for (int i = 0; i < tLoop; i++)
   {
      if (mValueRing.tryRead(&tValue))
      {
         Prn::print(0, "READ %d", tValue);
      }
      else
      {
         Prn::print(0, "READ FAIL");
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeAtValue(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   int tIndex = aCmd->argInt(1);

   int* tPtr = mValueRing.atOffset(tIndex);
   Prn::print(0, "AT  %d", *tPtr);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeMarkValue(Ris::CmdLineCmd* aCmd)
{
   for (int i = 0; i < 4; i++)
   {
      int* tPtr = mValueRing.atOffset(i);
      *tPtr += 1000 + 100 * i;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShowValue(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "FullFlag      %s", my_string_from_bool(mValueRing.mFullFlag));
   Prn::print(0, "available     %d", mValueRing.available());
   Prn::print(0, "WriteIndex    %d", mValueRing.mNextWriteIndex);
   Prn::print(0, "MaxReadIndex  %d", mValueRing.mMaxReadIndex);
   Prn::print(0, "MinReadIndex  %d", mValueRing.mMinReadIndex);

   Prn::print(0, "");
   for (int i = 0; i < 4; i++)
   {
      Prn::print(0, "atOffset     %d %d", i, *mValueRing.atOffset(i));
   }

   return;
   Prn::print(0, "");
   for (int i = 4; i-- > 0;)
   {
      Prn::print(0, "history      %d %d", i, mValueRing.elementAt(i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePutArray(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tNumElements = aCmd->argInt(1);
   mValueRing.doWriteArray(mWriteArray, tNumElements);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGetArray(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tNumElements = aCmd->argInt(1);
   int tCount = mValueRing.doReadArray(mReadArray, tNumElements);
   Prn::print(0, "GET ARRAY %d", tCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShowArray(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "AVAILABLE %d", mValueRing.available());
   int tNumElements = aCmd->argInt(1);
   for (int i = 0; i < tNumElements; i++)
   {
      Prn::print(0, "%2d  %3d", i, mReadArray[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "GO1");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
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

