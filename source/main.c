#include "board.h"
#include "app.h"
#include "fsl_lpuart.h"
#include "fsl_debug_console.h"
#include "GPIO.h"
#include "TIMER.h"
#include "H_Bridge.h"
#include "UART.h"

int main(void)
{

    
    BOARD_InitHardware();
    CONFIG_H_BRIDGE();
    H_BRIDGE_SET_FREC(260.0);
    //ENABLE_H_BRIDGE();
    uint8_t num = 0;
    while(1)
    {
        if(CHANGE_SPEED)
            CHANGE_MOTOR_SPEED();
        
         
 
        
        START_H_BRIDGE();
    }
}


