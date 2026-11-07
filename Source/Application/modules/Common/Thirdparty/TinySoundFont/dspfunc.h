#pragma once

#include <stdint.h>

#ifdef __ARM_FEATURE_DSP

#include "main.h"

__attribute__((always_inline)) uint32_t __SMULBB(uint32_t op1, uint32_t op2);

__attribute__((always_inline)) uint32_t __SMULBT(uint32_t op1, uint32_t op2);

__attribute__((always_inline)) uint32_t __SMULTB(uint32_t op1, uint32_t op2);

__attribute__((always_inline)) uint32_t __SMULTT(uint32_t op1, uint32_t op2);

__attribute__((always_inline)) uint32_t __SMLABB(uint32_t op1, uint32_t op2, uint32_t op3);

__attribute__((always_inline)) uint32_t __SMLABT(uint32_t op1, uint32_t op2, uint32_t op3);

__attribute__((always_inline)) uint32_t __SMLATB(uint32_t op1, uint32_t op2, uint32_t op3);

__attribute__((always_inline)) uint32_t __SMLATT(uint32_t op1, uint32_t op2, uint32_t op3);

#else
#define __PKHBT(ARG1, ARG2, ARG3) ((((int32_t)(ARG1) << 0) & (int32_t)0x0000FFFF) | (((int32_t)(ARG2) << ARG3) & (int32_t)0xFFFF0000))
#define __PKHTB(ARG1, ARG2, ARG3) ((((int32_t)(ARG1) << 0) & (int32_t)0xFFFF0000) | (((int32_t)(ARG2) >> ARG3) & (int32_t)0x0000FFFF))

int32_t __SSAT(int32_t x, int32_t y);
uint32_t __QADD(uint32_t x, uint32_t y);
uint32_t __SMUAD(uint32_t x, uint32_t y);
uint32_t __SMUSD(uint32_t x, uint32_t y);
int32_t __SMULBB(int32_t x, int32_t y);
int32_t __SMULBT(int32_t x, int32_t y);
int32_t __SMULTB(int32_t x, int32_t y);
int32_t __SMULTT(int32_t x, int32_t y);
int32_t __SMLABB(int32_t x, int32_t y, int32_t z);
int32_t __SMLABT(int32_t x, int32_t y, int32_t z);
int32_t __SMLATB(int32_t x, int32_t y, int32_t z);
int32_t __SMLATT(int32_t x, int32_t y, int32_t z);

#endif