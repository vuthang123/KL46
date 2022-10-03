#include "MKL46Z4.h"


#define GREEN_LED_ON      GPIOD->PCOR |= (1 << 5)
#define GREEN_LED_OFF     GPIOD->PSOR |= (1 << 5)

#define RED_LED_ON        GPIOE->PCOR |= (1 << 29)
#define RED_LED_OFF       GPIOE->PSOR |= (1 << 29)

#define GREEN_LED_TOGGLE      GPIOD->PTOR |= (1 << 5)

#define SW1_PRESS         (!(GPIOC->PDIR&(1<<3)))

#define IS_PRESSING (1)
#define IS_NOT_PRESSING (0)






/****************************************************************************
Check whether SW1 is pressing or not.
*****************************************************************************/
void IsPushButtonSW1(unsigned int *statusButtonSW1)
{
    if((SW1_PRESS) && (*statusButtonSW1 == IS_NOT_PRESSING))
    {                        
        *statusButtonSW1 = IS_PRESSING;
    }
    if((!SW1_PRESS) && (*statusButtonSW1 == IS_PRESSING))
    {
        *statusButtonSW1 = IS_NOT_PRESSING;
    }
}


void initClock(void)
{
    /*Enable clock for PORTC, PORTD, PORTE */
    SIM->SCGC5 |= (1 << 11);    /* Set bit 11 */
    SIM->SCGC5 |= (1 << 13);    /* Set bit 13 */
    SIM->SCGC5 |= (1 << 12);    /* Set bit 12*/
}

void initPin(void)
{
    /* Configure pin PTE29 and PTD5 as GPIO */
    PORTE->PCR[29] |= PORT_PCR_MUX(1);
    PORTD->PCR[5]  |= PORT_PCR_MUX(1);
    
    /* Configure multiplex of PTC3 and PTC12 as GPIO */
    PORTC->PCR[3]   |= PORT_PCR_MUX(1);  /*SW1*/
    PORTC->PCR[12]  |= PORT_PCR_MUX(1);  /*SW3*/

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

    /* Set PTE29 OFF and PTD5 OFF*/
    RED_LED_OFF;
    GREEN_LED_OFF;
}

void main()
{
    unsigned int statusButtonSW1 = 1;

    initClock();
    initPin();

    while (1)
    {

        IsPushButtonSW1(&statusButtonSW1);
        
        if( statusButtonSW1 == IS_PRESSING)
        {
            /* Toggle green led */
            GREEN_LED_TOGGLE;
        }

    }
}






