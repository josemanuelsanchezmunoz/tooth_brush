#include "GPIO.h" 

volatile bool CHANGE_SPEED = false;

void INTERRUPT_FUNC(void){
    CHANGE_SPEED = true;
    GPIO_PortClearInterruptFlags(GPIOB, 1U << TOUCH);
    SDK_ISR_EXIT_BARRIER;
}

void GPIO_INIT(){
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortA);

    gpio_pin_config_t OUTPUT_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = LOW
    };

    #ifdef ENABLE_GPIO_PINS
    PORT_SetPinMux(PORTB, IN2, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTB, IN1, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOB, IN1, &OUTPUT_config);
    GPIO_PinInit(GPIOB, IN2, &OUTPUT_config);
    GPIO_PinWrite(GPIOB, IN1, LOW);
    GPIO_PinWrite(GPIOB, IN2, LOW);
    #endif

    PORT_SetPinMux(PORTA, SLEEP, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOA, SLEEP, &OUTPUT_config);
    GPIO_PinWrite(GPIOA, SLEEP, LOW);

//-------------------Habilitar pin TOUCH como interrupcion--------------------------------//

    const port_pin_config_t PORTB7_config = {
        kPORT_PullDisable,
        /* Slow slew rate is configured */
        kPORT_SlowSlewRate,
        /* Passive filter is disabled */
        kPORT_PassiveFilterEnable,
        /* Low drive strength is configured */
        kPORT_LowDriveStrength,
        /* Pin is configured as PTB5 */
        kPORT_MuxAsGpio
    };

    PORT_SetPinConfig(PORTB, TOUCH, &PORTB7_config);

    gpio_pin_config_t TOUCH_INPUT_CONFIG = {
        .pinDirection = kGPIO_DigitalInput,
    };

    PORT_SetPinInterruptConfig(PORTB, TOUCH, kPORT_InterruptFallingEdge);
    EnableIRQ(PORTB_IRQn);
    PORT_SetPinMux(PORTB, TOUCH, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOB, TOUCH, &TOUCH_INPUT_CONFIG);

}