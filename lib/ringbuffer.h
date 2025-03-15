//------------------------------------------------------------------------------
//! \file ringbuffer.h
//! \brief
//------------------------------------------------------------------------------
#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "types.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define RINGBUFFER_SIZE (256)

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief Ring buffer structure
//------------------------------------------------------------------------------
typedef struct
{
   UCHAR aucBuffer[RINGBUFFER_SIZE];
   UINT uiHeadIndex;
   UINT uiTailIndex;
   UINT uiCount;
   BOOL bNeedsIRQSafety;
} RingBufferStruct;

//------------------------------------------------------------------------------
//! Functions
//------------------------------------------------------------------------------
void RingBuffer_Initialize(RingBufferStruct* pstRingBuffer_, BOOL bNeedsIRQSafety_);
BOOL RingBuffer_IsEmpty(RingBufferStruct* pstRingBuffer_);
BOOL RingBuffer_IsFull(RingBufferStruct* pstRingBuffer_);
UINT RingBuffer_Enqueue(RingBufferStruct* pstRingBuffer_, UCHAR* pucData_, UINT uiDataLength_);
UINT RingBuffer_Dequeue(RingBufferStruct* pstRingBuffer_, UCHAR* pucData_, UINT uiDataLength_);


#endif // __RINGBUFFER_H