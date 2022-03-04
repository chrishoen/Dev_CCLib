#include "stdafx.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "ccModulo.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
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
   if(aCmd->isCmd("RESET"))   reset();
   if (aCmd->isCmd("GO1"))    executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))    executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))    executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))    executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))    executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))    executeGo6(aCmd);
   if (aCmd->isCmd("GO7"))    executeGo7(aCmd);
   if (aCmd->isCmd("GO8"))    executeGo8(aCmd);
   if (aCmd->isCmd("GO91"))   executeGo91(aCmd);
   if (aCmd->isCmd("GO92"))   executeGo92(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

typedef union PackedS
{
   unsigned char mUint8;
   unsigned short mUint16;
   unsigned int mUint32;
   int mInt32;
} PackedT;

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   PackedT tP; tP.mInt32 = 0;
   tP.mUint8 = 0xff;
   Prn::print(0, "mUint8     %x", tP.mInt32);

   tP.mUint8 += 1;
   Prn::print(0, "mUint8     %x", tP.mInt32);

   tP.mUint8 += 1;
   Prn::print(0, "mUint8     %x", tP.mInt32);

   tP.mUint8 = 0;
   tP.mUint8 -= 1;

   Prn::print(0, "mUint8     %x", tP.mInt32);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   unsigned tN1 = 0;
   unsigned tN2 = 0;
   unsigned tN3 = 0;

   tN1 = 10;
   tN2 = 20;

   tN3 = tN1 - tN2;
   Prn::print(0, "TEST1 %u  %u  %u", tN1, tN2, tN3);

   tN3 = (tN1 - tN2) % 100;
   Prn::print(0, "TEST2 %u  %u  %u", tN1, tN2, tN3);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   int tMod = 100;
   int tN1 = 0;
   int tN2 = 0;
   int tN3 = 0;

   tN1 = 11;
   tN2 = 93;

   tN3 = CC::mod_add(tMod, tN1,tN2);
   Prn::print(0, "add      %d %d %d", tN1, tN2, tN3);

   tN3 = CC::mod_minus(tMod, tN1);
   Prn::print(0, "minus1   %d %d", tN1, tN3);

   tN3 = CC::mod_minus(tMod, tN2);
   Prn::print(0, "minus2   %d %d", tN2, tN3);

   tN3 = CC::mod_subtract(tMod, tN1, tN2);
   Prn::print(0, "subtract %d %d %d", tN1, tN2, tN3);

   tN3 = CC::mod_add(tMod, tN1, CC::mod_minus(tMod, tN2));
   Prn::print(0, "subtract %d %d %d", tN1, tN2, tN3);

   tN3 = CC::mod_add(tMod, tN1, CC::mod_minus(tMod, tN1));
   Prn::print(0, "test1    %d %d", tN1, tN3);

   tN3 = CC::mod_subtract(tMod, tN1, CC::mod_minus(tMod, tN2));
   Prn::print(0, "test2    %d %d %d", tN1, tN2, tN3);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   unsigned tMod = 100;
   unsigned tN1 = 0;
   unsigned tN2 = 0;
   unsigned tN3 = 0;

   tN1 = 11;
   tN2 = 93;

   tN3 = CC::mod_add(tMod, tN1, tN2);
   Prn::print(0, "add      %u %u %u", tN1, tN2, tN3);

   tN3 = CC::mod_minus(tMod, tN1);
   Prn::print(0, "minus1   %u %u", tN1, tN3);

   tN3 = CC::mod_minus(tMod, tN2);
   Prn::print(0, "minus2   %u %u", tN2, tN3);

   tN3 = CC::mod_subtract(tMod, tN1, tN2);
   Prn::print(0, "subtract %u %u %u", tN1, tN2, tN3);

   tN3 = CC::mod_add(tMod, tN1, CC::mod_minus(tMod, tN2));
   Prn::print(0, "subtract %u %u %u", tN1, tN2, tN3);

   tN3 = CC::mod_add(tMod, tN1, CC::mod_minus(tMod, tN1));
   Prn::print(0, "test1    %u %u", tN1, tN3);

   tN3 = CC::mod_subtract(tMod, tN1, CC::mod_minus(tMod, tN2));
   Prn::print(0, "test2    %u %u %u", tN1, tN2, tN3);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   int tMod = 100;
   int tN1 = 0;
   int tN2 = 0;
   int tN3 = 0;
   int tN4 = 0;

   tN1 = 21;
   tN2 = 92;
   tN3 = 63;

   tN4 = CC::mod_add(tMod, tN1, CC::mod_add(tMod, tN2, tN3));
   Prn::print(0, "test1    %d %d %d %d", tN1, tN2, tN3, tN4);

   tN4 = CC::mod_add(tMod, CC::mod_add(tMod, tN1, tN2), tN3);
   Prn::print(0, "test2    %d %d %d %d", tN1, tN2, tN3, tN4);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   int tMod = 100;
   int tN1 = 0;
   int tN2 = 0;
   int tN3 = 0;
   int tN4 = 0;

   tN1 = 21;
   tN2 = 92;
   tN3 = 63;

   tN4 = CC::mod_mult(tMod, tN1, CC::mod_mult(tMod, tN2, tN3));
   Prn::print(0, "test1    %d %d %d %d", tN1, tN2, tN3, tN4);

   tN4 = CC::mod_mult(tMod, CC::mod_mult(tMod, tN1, tN2), tN3);
   Prn::print(0, "test2    %d %d %d %d", tN1, tN2, tN3, tN4);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
   int tMod = 100;
   int tN1 = 0;
   int tN2 = 0;
   int tN3 = 0;
   int tN4 = 0;

   tN1 = 21;
   tN2 = 92;
   tN3 = 63;

   tN4 = CC::mod_mult(tMod, tN1, CC::mod_add(tMod, tN2, tN3));
   Prn::print(0, "test1    %d %d %d %d", tN1, tN2, tN3, tN4);

   tN4 = CC::mod_add(tMod, CC::mod_mult(tMod, tN1, tN2), CC::mod_mult(tMod, tN1, tN3));
   Prn::print(0, "test2    %d %d %d %d", tN1, tN2, tN3, tN4);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
   for (int i = -15; i <= 15; i++)
   {  
      int n = i;
      CC::mod_normalize(4, &n);
      Prn::print(0, "%3d %3d %3d", i, n, CC::mod_minus(4, i));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo91(Ris::CmdLineCmd* aCmd)
{

   int tMod = 10;
   int tN1 = 0;
   int tN2 = 0;
   int tN3 = 0;
   int tN41 = 0;
   int tN42 = 0;

   for (int i = 0; i < tMod; i++)
   {
      for (int j = 0; j < tMod; j++)
      {
         for (int k = 0; k < tMod; k++)
         {
            tN1 = i;
            tN2 = j;
            tN3 = k;

            tN41 = CC::mod_mult(tMod, tN1, CC::mod_add(tMod, tN2, tN3));
            tN42 = CC::mod_add(tMod, CC::mod_mult(tMod, tN1, tN2), CC::mod_mult(tMod, tN1, tN3));
            Prn::print(0, "some    %d %d %d %d %d", tN1, tN2, tN3, tN41, tN42);
            if (tN41 != tN42)
            {
               Prn::print(0, "ERROR    %d %d %d %d %d", tN1, tN2, tN3, tN41, tN42);
               return;
            }
         }
      }
   }
   Prn::print(0, "done    %d %d %d %d %d", tN1, tN2, tN3, tN41, tN42);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo92(Ris::CmdLineCmd* aCmd)
{
   unsigned tMod = 97;
   unsigned tN1 = 0;
   unsigned tN2 = 0;
   unsigned tN3 = 0;
   unsigned tN41 = 0;
   unsigned tN42 = 0;

   for (unsigned i = 0; i < tMod; i++)
   {
      for (unsigned j = 0; j < tMod; j++)
      {
         for (unsigned k = 0; k < tMod; k++)
         {
            tN1 = i;
            tN2 = j;
            tN3 = k;

            tN41 = CC::mod_mult(tMod, tN1, CC::mod_add(tMod, tN2, tN3));
            tN42 = CC::mod_add(tMod, CC::mod_mult(tMod, tN1, tN2), CC::mod_mult(tMod, tN1, tN3));
            if (tN41 != tN42)
            {
               Prn::print(0, "ERROR    %u %u %u %u %u", tN1, tN2, tN3, tN41, tN42);
               return;
            }
         }
      }
   }
   Prn::print(0, "done    %u %u %u %u %u", tN1, tN2, tN3, tN41, tN42);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

