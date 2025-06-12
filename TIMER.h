#ifndef TIMER_H
#define TIMER_H

#include "fsl_tpm.h"
#include "board.h"
#include "app.h"
#include "fsl_clock.h"

extern volatile uint32_t us_Counts;

extern void TIMER_INIT_INTERRUPT_EVERY_10us();
extern void Delay_ms(uint16_t time);

#endif /*TIMER_H*/