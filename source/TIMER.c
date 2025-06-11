#include "TIMER.h"

#define DEMO_TIMER_PERIOD_US 10U
#define BOARD_TPM TPM0
#define TPM_SOURCE_CLOCK (CLOCK_GetFreq(kCLOCK_McgIrc48MClk))
#define TPM_PRESCALER TPM_CalculateCounterClkDiv(BOARD_TPM, 1000000U / DEMO_TIMER_PERIOD_US, TPM_SOURCE_CLOCK);

volatile uint32_t us_Counts = 0U;
volatile bool First_time = false;

void TIMER_INIT_INTERRUPT_EVERY_10us(){
    CLOCK_SetTpmClock(1U);
    tpm_config_t tpmInfo;
    TPM_GetDefaultConfig(&tpmInfo);
    tpmInfo.prescale = TPM_PRESCALER;

    TPM_Init(BOARD_TPM, &tpmInfo);
    TPM_SetTimerPeriod(BOARD_TPM, USEC_TO_COUNT(DEMO_TIMER_PERIOD_US, TPM_SOURCE_CLOCK / (1U << tpmInfo.prescale)));
    TPM_EnableInterrupts(BOARD_TPM, kTPM_TimeOverflowInterruptEnable);
    EnableIRQ(TPM0_IRQn);
    TPM_StartTimer(BOARD_TPM, kTPM_SystemClock);
}

void TPM0_IRQHandler(void){
    TPM_ClearStatusFlags(BOARD_TPM, kTPM_TimeOverflowFlag);
    us_Counts++;
    SDK_ISR_EXIT_BARRIER
}

void Delay_ms(uint16_t time){
    us_Counts = 0;
    uint16_t ms_Counts = 0;
    while(ms_Counts <= time){
        if(us_Counts >= 100){
            ms_Counts++;
            us_Counts = 0;
        }
    }
}