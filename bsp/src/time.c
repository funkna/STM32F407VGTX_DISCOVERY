//------------------------------------------------------------------------------
//! \file time.c
//! \brief System ticks, timing and delay functioanlity.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Includes
//------------------------------------------------------------------------------
#include "time.h"
#include "systick.h"

//------------------------------------------------------------------------------
//! Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Typedefs
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! Statics, Externs & Globals
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void
DelayMS(
   UINT uiTimeDelayMS_)
{
   UINT uiDelayTicks = (uiTimeDelayMS_ * TICKS_PER_MSEC);
   UINT uiStartTicks = SYSTICK_GetTicks();
   UINT uiEndTicks = (uiStartTicks > uiDelayTicks) ? (uiStartTicks - uiDelayTicks) : (ROLLOVER_TICKS - (uiDelayTicks - uiStartTicks));

   if(uiStartTicks > uiDelayTicks)
   {
      while(SYSTICK_GetTicks() > uiEndTicks);
   }
   else // SYSTICK will roll over in this delay
   {
      while((SYSTICK_GetTicks() > uiEndTicks) || (SYSTICK_GetTicks() < uiStartTicks));
   }
}

//------------------------------------------------------------------------------
UINT
TickDeltaToMS(
   UINT uiTicksFirst_,
   UINT uiTicksLast_)
{
   if(uiTicksFirst_ > uiTicksLast_)
   {
      return ((uiTicksFirst_ - uiTicksLast_) / TICKS_PER_MSEC);
   }
   else
   {
      return ((ROLLOVER_TICKS - (uiTicksLast_ - uiTicksFirst_)) / TICKS_PER_MSEC);
   }
}