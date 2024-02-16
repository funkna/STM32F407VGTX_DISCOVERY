// Redundancy Prevention --------------------------------------------------------------------------
#ifndef TYPES_H_
#define TYPES_H_

// Includes ---------------------------------------------------------------------------------------
#include <stdint.h>

// Defines ----------------------------------------------------------------------------------------
#define NULL      ((void*)0)
#define FALSE     (0)
#define TRUE      (!FALSE)

// Typedefs ---------------------------------------------------------------------------------------

//--------------------------------------------------------------
// Typedefs for primitives.
//--------------------------------------------------------------
typedef int8_t    CHAR;
typedef int16_t   SHORT;
typedef int32_t   INT;
typedef int64_t   LONG;
typedef uint8_t   UCHAR;
typedef uint16_t  USHORT;
typedef uint32_t  UINT;
typedef uint64_t  ULONG;
typedef UCHAR     BOOL;

#endif // TYPES_H_
