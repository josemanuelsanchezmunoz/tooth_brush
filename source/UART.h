#ifndef UART_H
#define UART_H

#include "fsl_lpuart.h"
#include "board.h"
#include "app.h"
#include "fsl_clock.h"

//#define ENABLE_UART_PINS
#define ENABLE_GPIO_PINS

extern void UART_INIT_115200_BAUD();
extern void LPUART0_WRITE(const uint8_t *chain);

#endif /*UART_H*/