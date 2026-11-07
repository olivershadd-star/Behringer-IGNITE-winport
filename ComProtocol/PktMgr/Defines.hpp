/*
 * Copyright (c) MUSIC Tribe
 * This file is part of ComProtocol.
 *
 * ComProtocol is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * ComProtocol is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with ComProtocol. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */
#include <stdint.h>

#ifndef DEFINES_H
#define DEFINES_H

#define cplusplus

//#define ENABLE_PRINTF

#define FLASH_VALID 0x12345678

#define UNIT_T_s 		(1.0f)
#define UNIT_T_ms		(0.001f * UNIT_T_s)
#define UNIT_T_us		(0.001f * UNIT_T_ms)
#define UNIT_T_min  (60.0f * UNIT_T_s)

enum enumReturnCode
{
    EN_RET_SUCCESS = 0x00,
    EN_RET_ERROR = 0x01,
};

typedef void (*typeVoidFnVoid) (void);

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef NULL
#define NULL 0
#endif

//..............................
typedef struct
{
    uint8_t  ui8Main;
    uint8_t  ui8Sub;
    uint8_t  ui8Bug;
    uint8_t  ui8Dummy; // Align to Boundary of 4 => Do not use !!!
} typeVersionNo;

//..............................
// Fuction pointers
typedef void (*typeVoidFunctionVoid)(void);
typedef void (*typeVoidFunctionBool)(bool);
typedef void (*typeVoidFunctionFloat)(float);

//......................
// Software Info
//......................
typedef struct
{
    typeVoidFunctionVoid fnSoftwareEntry;
    uint32_t             ui32FlashState;
    uint16_t             ui16ProgramCheckSum;
    uint16_t             ui16SwRevisionNo;
    typeVersionNo        vnSwVersion;
} typeSoftwareInfo;

#endif
