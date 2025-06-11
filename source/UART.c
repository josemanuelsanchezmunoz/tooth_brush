#include "UART.h"

void UART_INIT_115200_BAUD(){
    lpuart_config_t config;

    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = 115200U;
    config.enableTx     = true;
    config.enableRx     = true;

    LPUART_Init(DEMO_LPUART, &config, DEMO_LPUART_CLK_FREQ);
}

void LPUART0_WRITE(const uint8_t *chain){
    LPUART_WriteBlocking(DEMO_LPUART, chain, strlen(chain));
}