#include "delay.h"
#define GREEN_LED_ON      GPIOD->PCOR |= (1 << 5)
#define GREEN_LED_OFF     GPIOD->PSOR |= (1 << 5)
#define RED_LED_ON    GPIOE->PCOR |= (1 << 29)
#define RED_LED_OFF   GPIOE->PSOR |= (1 << 29)
#define GREEN_LED_TOGGLE      GPIOD->PTOR |= (1 << 5)

#define SW1_NHAN    (!(GPIOC->PDIR&(1<<3)))
#define SW2_NHAN    (!(GPIOC->PDIR&(1<<12)))

#define DANG_NHA (1)
#define DANG_NHAN (0)

void delayMilisecond(unsigned int miliSecond)
{
    unsigned long timeDelayMilisecond=miliSecond*DELAY_COUNT;
    unsigned long i;
    for (i = 0; i < timeDelayMilisecond; i++)
    {
        __asm("nop");
    }
}

void delay100us()
{
    unsigned long i;
    unsigned long DelayLoop;
    DelayLoop = DELAY_COUNT;   
    for (i = 0; i < DelayLoop; i++)
    {
        __asm("nop");
    }
}

void PWM_10ms(unsigned int duty)
{
    unsigned int i;
    RED_LED_ON;
    for(i=0;i<duty;i++)
    {
        delay100us();
    }
    RED_LED_OFF;
    for(i=0;i<100-duty;i++)
    {
        delay100us();
    }   
}

void initLed()
{
    /*Enable clock for PORTC, PORTE */
    SIM->SCGC5 |= (1 << 11);    /* Set bit 11 */
    SIM->SCGC5 |= (1 << 13);    /* Set bit 13 */
    SIM->SCGC5 |= (1 << 12);    /* Set bit 12*/

    /* Configure pin PTE29 and PTD5 tp GPIO */
    PORTE->PCR[29] |= PORT_PCR_MUX(1);
    PORTD->PCR[5] |= PORT_PCR_MUX(1);
    
    /* Configure multiplex of PTC3 and PTC12 as GPIO */
    PORTC->PCR[3]   |= PORT_PCR_MUX(1);
    PORTC->PCR[12]  |= PORT_PCR_MUX(1);

    /* Configure pull of PTC3*/
    PORTC->PCR[3] |= PORT_PCR_PE(1);
    PORTC->PCR[3] |= PORT_PCR_PS(1);

    /* Configure pull of  PTC12 */
    PORTC->PCR[12] |= PORT_PCR_PE(1);
    PORTC->PCR[12] |= PORT_PCR_PS(1);

    /* Configure PTE29 as output */
    GPIOE->PDDR |= (1 << 29);
    GPIOD->PDDR |= (1 << 5);
    
    /* Configure PTC3 and PTC12 as input */
    GPIOC->PDDR &= ~(1 << 3);
    GPIOC->PDDR &= ~(1 << 12);

    /* Set PTE29 OFF*/
    RED_LED_OFF;
    GREEN_LED_OFF;
}

/************************************************************************************************
Mode 1: Tang do sang cua led 1%
*************************************************************************************************/
unsigned int Mode1(unsigned int *dutyMode_12,unsigned int *statusButtonSW2)
{     
    if(IsPushButtonSW2(statusButtonSW2)==DANG_NHAN)
    {
        return MODE_STEPED_CONTROLLABLE;
    }
    if(*dutyMode_12 < 100)
    {
        PWM_10ms(*dutyMode_12);
        *dutyMode_12+=1;
        return MODE_SMOOTH_INCREASE;
    }
    else
    {
        return MODE_SMOOTH_DECREASE;
    }
}
/****************************************************************************
Mode 2: Giam dan do sang cua led 1%
*****************************************************************************/
unsigned int Mode2(unsigned int *dutyMode_12,unsigned int *statusButtonSW2)
{
    if(IsPushButtonSW2(statusButtonSW2)==DANG_NHAN)
    {
        return MODE_STEPED_CONTROLLABLE;
    }
    if(*dutyMode_12 > 0)
    {
        PWM_10ms(*dutyMode_12);
        *dutyMode_12-=1;
        return MODE_SMOOTH_DECREASE;
    }
    if(*dutyMode_12 == 0)
    {
        return MODE_SMOOTH_INCREASE;
    }
}
/****************************************************************************
Mode 3: Su dung SW1 de tang do sang 
*****************************************************************************/
unsigned int Mode3(unsigned int *statusButtonSW1, unsigned int *statusButtonSW2)
{
    static unsigned int dutyMode_3 = 0;
    if(IsPushButtonSW2(statusButtonSW2) == DANG_NHAN)
    {
        return MODE_SMOOTH_INCREASE;
    }
    else
    {
        PWM_10ms(dutyMode_3);
        if(IsPushButtonSW1(statusButtonSW1)== DANG_NHAN)
        {
            dutyMode_3+=25;
            if(dutyMode_3>100)
            {
                dutyMode_3=0;
            }
            PWM_10ms(dutyMode_3);
        }         
        return MODE_STEPED_CONTROLLABLE;
    }          
}
/****************************************************************************
Kiem tra xem SW2 nhan nut hay khong
*****************************************************************************/
unsigned int IsPushButtonSW2(unsigned int *statusButtonSW2)
{
    if((SW2_NHAN) && (*statusButtonSW2 == DANG_NHA))
    {                        
        *statusButtonSW2 = DANG_NHAN;
        return *statusButtonSW2;
    }
    if((!SW2_NHAN) && (*statusButtonSW2 == DANG_NHAN))
    {
        *statusButtonSW2 = DANG_NHA;
        return *statusButtonSW2;
    }
}
/****************************************************************************
Kiem tra xem SW1 nhan nut hay khong
*****************************************************************************/
unsigned int IsPushButtonSW1(unsigned int *statusButtonSW1)
{
    if((SW1_NHAN) && (*statusButtonSW1 == DANG_NHA))
    {                        
        *statusButtonSW1 = DANG_NHAN;
        return *statusButtonSW1;
    }
    if((!SW1_NHAN) && (*statusButtonSW1 == DANG_NHAN))
    {
        *statusButtonSW1 = DANG_NHA;
        return *statusButtonSW1;
    }
}


