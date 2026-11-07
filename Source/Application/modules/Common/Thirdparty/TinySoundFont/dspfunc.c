#include "dspfunc.h"

#ifdef __ARM_FEATURE_DSP

__attribute__((always_inline)) uint32_t __SMULBB(uint32_t op1, uint32_t op2)
{
    uint32_t result;

    __asm volatile("smulbb %0, %1, %2"
                   : "=r"(result)
                   : "r"(op1), "r"(op2));
    return (result);
}

__attribute__((always_inline)) uint32_t __SMULBT(uint32_t op1, uint32_t op2)
{
    uint32_t result;

    __asm volatile("smulbt %0, %1, %2"
                   : "=r"(result)
                   : "r"(op1), "r"(op2));
    return (result);
}

__attribute__((always_inline)) uint32_t __SMULTB(uint32_t op1, uint32_t op2)
{
    uint32_t result;

    __asm volatile("smultb %0, %1, %2"
                   : "=r"(result)
                   : "r"(op1), "r"(op2));
    return (result);
}

__attribute__((always_inline)) uint32_t __SMULTT(uint32_t op1, uint32_t op2)
{
    uint32_t result;

    __asm volatile("smultt %0, %1, %2"
                   : "=r"(result)
                   : "r"(op1), "r"(op2));
    return (result);
}

__attribute__((always_inline)) uint32_t __SMLABB(uint32_t op1, uint32_t op2, uint32_t op3)
{
    uint32_t result;

    __asm volatile("smlabb %0, %1, %2, %3"
                   : "=r"(result)
                   : "r"(op1), "r"(op2), "r"(op3));
    return (result);
}

__attribute__((always_inline)) uint32_t __SMLABT(uint32_t op1, uint32_t op2, uint32_t op3)
{
    uint32_t result;

    __asm volatile("smlabt %0, %1, %2, %3"
                   : "=r"(result)
                   : "r"(op1), "r"(op2), "r"(op3));
    return (result);
}

__attribute__((always_inline)) uint32_t __SMLATB(uint32_t op1, uint32_t op2, uint32_t op3)
{
    uint32_t result;

    __asm volatile("smlatb %0, %1, %2, %3"
                   : "=r"(result)
                   : "r"(op1), "r"(op2), "r"(op3));
    return (result);
}

__attribute__((always_inline)) uint32_t __SMLATT(uint32_t op1, uint32_t op2, uint32_t op3)
{
    uint32_t result;

    __asm volatile("smlatt %0, %1, %2, %3"
                   : "=r"(result)
                   : "r"(op1), "r"(op2), "r"(op3));
    return (result);
}

#else

int32_t __SSAT(int32_t x, int32_t y)
{
    if (x > (1 << (y - 1)) - 1)
        return (1 << (y - 1)) - 1;
    else if (x < -(1 << (y - 1)))
        return -(1 << (y - 1)) + 1;
    else
        return (int32_t)x;
}

uint32_t __QADD(uint32_t x, uint32_t y)
{
    return (uint32_t)__SSAT((int64_t)x + (int64_t)y, 32);
}

uint32_t __SMUAD(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) + ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

uint32_t __SMUSD(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) - ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

int32_t __SMULBB(int32_t x, int32_t y)
{
    return ((int32_t)((int16_t)(x & 0xFFFF)) * (int32_t)((int16_t)(y & 0xFFFF)));
}

int32_t __SMULBT(int32_t x, int32_t y)
{
    return ((int32_t)((int16_t)(x & 0xFFFF)) * (int32_t)((int16_t)((y >> 16) & 0xFFFF)));
}

int32_t __SMULTB(int32_t x, int32_t y)
{
    return ((int32_t)((int16_t)((x >> 16) & 0xFFFF)) * (int32_t)((int16_t)(y & 0xFFFF)));
}

int32_t __SMULTT(int32_t x, int32_t y)
{
    return ((int32_t)((int16_t)((x >> 16) & 0xFFFF)) * (int32_t)((int16_t)((y >> 16) & 0xFFFF)));
}

int32_t __SMLABB(int32_t x, int32_t y, int32_t z)
{
    return ((int32_t)((int16_t)(x & 0xFFFF)) * (int32_t)((int16_t)(y & 0xFFFF)) + z);
}

int32_t __SMLABT(int32_t x, int32_t y, int32_t z)
{
    return ((int32_t)((int16_t)(x & 0xFFFF)) * (int32_t)((int16_t)((y >> 16) & 0xFFFF)) + z);
}

int32_t __SMLATB(int32_t x, int32_t y, int32_t z)
{
    return ((int32_t)((int16_t)((x >> 16) & 0xFFFF)) * (int32_t)((int16_t)(y & 0xFFFF)) + z);
}

int32_t __SMLATT(int32_t x, int32_t y, int32_t z)
{
    return ((int32_t)((int16_t)((x >> 16) & 0xFFFF)) * (int32_t)((int16_t)((y >> 16) & 0xFFFF)) + z);
}

#endif