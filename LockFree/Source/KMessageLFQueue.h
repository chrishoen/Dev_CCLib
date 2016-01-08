#ifndef _KMESSAGELFQUEUE_H_
#define _KMESSAGELFQUEUE_H_

//****************************************************************************
//****************************************************************************
//****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIN32
#include "ntddk.h"
#include "wdf.h"
#else
#include "windows.h"
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************

LONG     KMsg_LFQueue_calc_buffer_size();
VOID     KMsg_LFQueue_create (PVOID aBuffer);

VOID     KMsg_LFQueue_reset ();
VOID     KMsg_LFQueue_enable();
VOID     KMsg_LFQueue_disable();

PVOID    KMsg_LFQueue_element (LONG aIndex);

BOOLEAN  KMsg_LFQueue_startWrite (LONG* aWriteIndex);
VOID     KMsg_LFQueue_finishWrite ();

BOOLEAN  KMsg_LFQueue_startRead  (LONG* aWriteIndex);
VOID     KMsg_LFQueue_finishRead  ();

BOOLEAN  KMsg_LFQueue_isEmpty ();
BOOLEAN  KMsg_LFQueue_isFull ();

//******************************************************************************
//******************************************************************************
//******************************************************************************

#ifdef __cplusplus
}
#endif
#endif
