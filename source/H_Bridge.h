#ifndef H_Bridge_H
#define H_Bridge_H 

#include "GPIO.h"
#include "TIMER.h"

typedef enum {
    OFF,
    LOW_SPEED = 40,
    MEDIUM_SPEED = 150,
    HIGH_SPEED = 200,
    MAX_SPEED = 300,
}SPEED_MODES;

extern void CONFIG_H_BRIDGE();
extern void ENABLE_H_BRIDGE();
extern void DISABLE_H_BRIDGE();
extern void H_BRIDGE_SET_FREC(float _frequency);
extern void START_H_BRIDGE();
extern void CHANGE_MOTOR_SPEED();

#endif /*H_Bridge_H*/ 