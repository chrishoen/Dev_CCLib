/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"
#include "cmnDefs.h"

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

const char* asStringMuRole(int aX)
{
   switch (aX)
   {
   case cMuRole_Cpu: return "Cpu";
   case cMuRole_Rpu: return "Rpu";
   default: return "UNKNOWN";
   }
}

int getFromString_MuRole(const char* aString)
{
   if (strncmp(aString, Cmn::asStringMuRole(Cmn::cMuRole_Cpu), 16) == 0)
   {
      return Cmn::cMuRole_Cpu;
   }
   else if (strncmp(aString, Cmn::asStringMuRole(Cmn::cMuRole_Rpu), 16) == 0)
   {
      return Cmn::cMuRole_Rpu;
   }
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

const char* asStringMuTestMode(int aX)
{
   switch (aX)
   {
   case cMuTestMode_Uplink: return "Uplink";
   case cMuTestMode_Downlink: return "Downlink";
   case cMuTestMode_RTT: return "RTT";
   default: return "UNKNOWN";
   }
}

int getFromString_MuTestMode(const char* aString)
{
   if (strncmp(aString, Cmn::asStringMuTestMode(Cmn::cMuTestMode_Uplink), 16) == 0)
   {
      return Cmn::cMuTestMode_Uplink;
   }
   else if (strncmp(aString, Cmn::asStringMuTestMode(Cmn::cMuTestMode_Downlink), 16) == 0)
   {
      return Cmn::cMuTestMode_Downlink;
   }
   else if (strncmp(aString, Cmn::asStringMuTestMode(Cmn::cMuTestMode_RTT), 16) == 0)
   {
      return Cmn::cMuTestMode_RTT;
   }
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
