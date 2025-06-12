#include "H_Bridge.h"

volatile int Period;
volatile uint8_t SPEED_INDEX = 0;
volatile bool ENABLE = false;

SPEED_MODES Speed_vector[5] = {
    OFF,
    LOW_SPEED,
    MEDIUM_SPEED,
    HIGH_SPEED,
    MAX_SPEED
};

void CONFIG_H_BRIDGE(){
    GPIO_INIT();
    TIMER_INIT_INTERRUPT_EVERY_10us();
}

void ENABLE_H_BRIDGE(){
    ENABLE  = true;
    us_Counts = 0;
    GPIO_PinWrite(GPIOA, SLEEP, HIGH);
    GPIO_PinWrite(GPIOB, IN1, HIGH);
    GPIO_PinWrite(GPIOB, IN2, LOW);
}

void DISABLE_H_BRIDGE(){
    ENABLE = false;
    GPIO_PinWrite(GPIOA, SLEEP, LOW);
}

void H_BRIDGE_SET_FREC(float _frequency){
    Period = (int)((1000000.0/_frequency)/2.0);
    Period /= 10;
} 

void START_H_BRIDGE(){
    if (us_Counts >= Period && ENABLE)
    {
        us_Counts = 0;
        GPIO_PortToggle(GPIOB, IN2 << 1U);
        GPIO_PortToggle(GPIOB, IN1 << 1U);
    }
}

void CHANGE_MOTOR_SPEED(){
    CHANGE_SPEED = false;
    switch(Speed_vector[++SPEED_INDEX]){
        case OFF:
            DISABLE_H_BRIDGE();
            break;
        case LOW_SPEED:
            ENABLE_H_BRIDGE();
            H_BRIDGE_SET_FREC((float) LOW_SPEED);
            break;
        case MEDIUM_SPEED:
            H_BRIDGE_SET_FREC((float) MEDIUM_SPEED);
            break;
        case HIGH_SPEED:
            H_BRIDGE_SET_FREC((float) HIGH_SPEED);
            break;
        case MAX_SPEED:
            H_BRIDGE_SET_FREC((float) MAX_SPEED);
            break;
        default:
            SPEED_INDEX = 0;
            DISABLE_H_BRIDGE();
            break;
    }
}