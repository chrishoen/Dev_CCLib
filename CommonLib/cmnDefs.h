#pragma once

/*==============================================================================
This file provides a set of constants that are used to define 
states and modes.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// Program role.
static const int cMuRole_Cpu = 1;
static const int cMuRole_Rpu = 2;

// Test mode.
static const int cMuTestMode_Uplink = 1;
static const int cMuTestMode_Downlink = 2;
static const int cMuTestMode_RTT = 3;

// Helpers.
const char* asStringMuRole(int aX);
const char* asStringMuTestMode(int aX);

int getFromString_MuRole(const char* aString);
int getFromString_MuTestMode(const char* aString);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


