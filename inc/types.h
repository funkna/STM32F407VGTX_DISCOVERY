//------------------------------------------------------------------------------
//! \file types.h
//! \brief Firmware types.
//------------------------------------------------------------------------------
#ifndef __TYPES_H
#define __TYPES_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stddef.h>

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
//#define NULL      ((void*)0)
#define FALSE     (0)
#define TRUE      (!FALSE)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------
typedef char      SCHAR;
typedef int8_t    CHAR;
typedef int16_t   SHORT;
typedef int32_t   INT;
typedef int64_t   LONG;
typedef uint8_t   UCHAR;
typedef uint16_t  USHORT;
typedef uint32_t  UINT;
typedef uint64_t  ULONG;
typedef UCHAR     BOOL;

#endif // __TYPES_H
