/*==============================================================================

This defines a class template that is used to define classes that encapsulate
integer quotient groups.

==============================================================================*/

#include "Modulo.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
/*

Quotient  = aZ div N
Remainder = aZ mod N

N
QuotientShift
RemainderMask
Quotient Set
Remainder Set
Frequency for Remainder==Zero

4096  12    4095     [0..0]        [0..4095]        1 hz  
2048  11    2047     [0..1]        [0..2047]        2 hz
1024  10    1023     [0..3]        [0..1023]        4 hz
512    9    511      [0..7]        [0..511]         8 hz
256    8    255      [0..15]       [0..255]        16 hz
128    7    127      [0..31]       [0..127]        32 hz
64     6     63      [0..63]       [0..63]         64 hz
32     5     31      [0..127]      [0..31]        128 hz 
16     4     15      [0..255]      [0..15]        256 hz
8      3      7      [0..511]      [0..7]         512 hz 
4      2      3      [0..1023]     [0..3]        1024 hz  
2      1      1      [0..2047]     [0..1]        2048 hz
1      0      0      [0..4095]     [0..0]        4096 hz 
*/

int Mod4096ModN<4096>::mQuotientShift = 12;
int Mod4096ModN<4096>::mRemainderMask = 4095;

int Mod4096ModN<2048>::mQuotientShift = 11;
int Mod4096ModN<2048>::mRemainderMask = 2047;

int Mod4096ModN<1024>::mQuotientShift = 10;
int Mod4096ModN<1024>::mRemainderMask = 1023;

int Mod4096ModN<512>::mQuotientShift = 9;
int Mod4096ModN<512>::mRemainderMask = 511;

int Mod4096ModN<256>::mQuotientShift = 8;
int Mod4096ModN<256>::mRemainderMask = 255;

int Mod4096ModN<128>::mQuotientShift = 7;
int Mod4096ModN<128>::mRemainderMask = 127;

int Mod4096ModN<64>::mQuotientShift = 6;
int Mod4096ModN<64>::mRemainderMask = 63;

int Mod4096ModN<32>::mQuotientShift = 5;
int Mod4096ModN<32>::mRemainderMask = 31;

int Mod4096ModN<16>::mQuotientShift = 4;
int Mod4096ModN<16>::mRemainderMask = 15;

int Mod4096ModN<8>::mQuotientShift = 3;
int Mod4096ModN<8>::mRemainderMask = 7;

int Mod4096ModN<4>::mQuotientShift = 2;
int Mod4096ModN<4>::mRemainderMask = 3;

int Mod4096ModN<2>::mQuotientShift = 1;
int Mod4096ModN<2>::mRemainderMask = 1;

int Mod4096ModN<1>::mQuotientShift = 0;
int Mod4096ModN<1>::mRemainderMask = 0;
