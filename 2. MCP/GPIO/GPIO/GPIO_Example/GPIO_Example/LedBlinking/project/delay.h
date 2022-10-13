#ifndef _DELAY_H_
#define _DELAY_H_
#include "MKL46Z4.h"
#define DELAY_COUNT     420UL
enum ModeType
{
    MODE_SMOOTH_INCREASE=0,
    MODE_SMOOTH_DECREASE,
    MODE_STEPED_CONTROLLABLE,
};
void initLed();
void PWM_10ms(unsigned int duty);
void delayMilisecond(unsigned int miliSecond);
void delay100us();
unsigned int Mode1(unsigned int *dutyMode_12,unsigned int *statusButtonSW2);
unsigned int Mode2(unsigned int *dutyMode_12,unsigned int *statusButtonSW2);
unsigned int Mode3(unsigned int *statusButtonSW1,unsigned int *statusButtonSW2);
unsigned int IsPushButtonSW2(unsigned int *statusButtonSW2);
unsigned int IsPushButtonSW1(unsigned int *statusButtonSW1);
#endif  /*_DELAY_H_*/ 