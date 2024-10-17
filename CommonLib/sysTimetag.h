#pragma once

/*==============================================================================
Timetag derived from system imx TSTMR timestamp timer, which is a 56 bit
timer that is clocked at 24MHz beginning from system boot.
==============================================================================*/

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

namespace Sys
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read current system time.

// Return the current system time in seconds.
double getTimetag();

// Return the current system time in milliseconds.
int getTimetagMs();

// Return the current system time in microseconds.
double getTimetagUs();

// Return the current system time in nanoseconds.
long long getTimetagNs();

// Convert to seconds.
double getTimetagFromNs(long long aTimetagNS);

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
}//namespace

