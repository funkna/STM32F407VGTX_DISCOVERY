//------------------------------------------------------------------------------
//! \file ringbuffer.c
//! \brief
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "cortex_m4.h"
#include "ringbuffer.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------
#define IRQSAFE_BEGIN(x)    { if(x->bNeedsIRQSafety) { __disable_irq(); } }
#define IRQSAFE_END(x)      { if(x->bNeedsIRQSafety) { __enable_irq();  } }

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void
RingBuffer_Initialize(
   RingBufferStruct* pstRingBuffer_,
   BOOL bNeedsIRQSafety_)
{
   pstRingBuffer_->uiCount = 0;
   pstRingBuffer_->uiHeadIndex = 0;
   pstRingBuffer_->uiTailIndex = 0;
   pstRingBuffer_->bNeedsIRQSafety = bNeedsIRQSafety_;
}

//------------------------------------------------------------------------------
BOOL
RingBuffer_IsEmpty(
   RingBufferStruct* pstRingBuffer_)
{
   BOOL bIsEmpty = FALSE;
   IRQSAFE_BEGIN(pstRingBuffer_);
   bIsEmpty = (0 == pstRingBuffer_->uiCount);
   IRQSAFE_END(pstRingBuffer_);
   return bIsEmpty;
}

//------------------------------------------------------------------------------
BOOL
RingBuffer_IsFull(
   RingBufferStruct* pstRingBuffer_)
{
   BOOL bIsFull = FALSE;
   IRQSAFE_BEGIN(pstRingBuffer_);
   bIsFull = (RINGBUFFER_SIZE == pstRingBuffer_->uiCount);
   IRQSAFE_END(pstRingBuffer_);
   return bIsFull;
}

//------------------------------------------------------------------------------
UINT
RingBuffer_Enqueue(
   RingBufferStruct* pstRingBuffer_,
   UCHAR* pucData_,
   UINT uiDataLength_)
{
   UINT uiBytesEnqueued = 0;
   while((uiBytesEnqueued < uiDataLength_) &&
         !RingBuffer_IsFull(pstRingBuffer_))
   {
      pstRingBuffer_->aucBuffer[pstRingBuffer_->uiTailIndex] = pucData_[uiBytesEnqueued++];
      pstRingBuffer_->uiTailIndex = (pstRingBuffer_->uiTailIndex + 1) % RINGBUFFER_SIZE;

      IRQSAFE_BEGIN(pstRingBuffer_);
      pstRingBuffer_->uiCount++;
      IRQSAFE_END(pstRingBuffer_);
   }

   return uiBytesEnqueued;
}

//------------------------------------------------------------------------------
UINT
RingBuffer_Dequeue(
   RingBufferStruct* pstRingBuffer_,
   UCHAR* pucData_,
   UINT uiDataLength_)
{
   UINT uiBytesDequeued = 0;
   while((uiBytesDequeued < uiDataLength_) &&
         !RingBuffer_IsEmpty(pstRingBuffer_))
   {
      pucData_[uiBytesDequeued++] = pstRingBuffer_->aucBuffer[pstRingBuffer_->uiHeadIndex];
      pstRingBuffer_->uiHeadIndex = (pstRingBuffer_->uiHeadIndex + 1) % RINGBUFFER_SIZE;

      IRQSAFE_BEGIN(pstRingBuffer_);
      pstRingBuffer_->uiCount--;
      IRQSAFE_END(pstRingBuffer_);
   }

   return uiBytesDequeued;
}
