/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>

#include "LLogic.h"

const float LLogic::cTrueX  = 1.0f;
const float LLogic::cFalseX = 0.0f;
const float LLogic::cNullX  = -1.0f;

const LLogic LLogic::cNull;
const LLogic LLogic::cTrue(LLogic::cTrueX);
const LLogic LLogic::cFalse(LLogic::cFalseX);

