#include "MKL46Z4.h"

#define DELAY_CNT           (1000000)
#define RED_LED_PIN         (1 << 29)
#define GREEN_LED_PIN       (1 << 5)

void INIT_CLOCK();
void INIT_LED();
void DELAY();
void INIT_PORT();
void INIT_GPIO();
void BUTTON();

int main(void)
{
    INIT_CLOCK();
    INIT_PORT();
    INIT_GPIO();
    INIT_LED();
    
       while (1)
       {   
            BUTTON();      
       }
}

void INIT_LED()
{
    
    /* Initialize the RED LED (PTE29)*/
    /* Set the PTE29 pin multiplexer to GPIO mode */
    PORTE->PCR[29] = PORT_PCR_MUX(1);
    /* Set the pin's direction to output */
    FPTE->PDDR |= RED_LED_PIN;
    /* Set the initial output state to high */
    FPTE->PSOR |= RED_LED_PIN;
    
    /* Initialize the Green LED (PTD5) */
    /* Set the PTD5 pin multiplexer to GPIO mode */
    PORTD->PCR[5]= PORT_PCR_MUX(1);
    /* Set the pin's direction to output */
    FPTD->PDDR |= GREEN_LED_PIN;
    /* Set the initial output state to high */
    FPTD->PSOR |= GREEN_LED_PIN;
}


void INIT_CLOCK()//Enable clock for PORTC,PORTE,PORTD
{  
    /* Enable clock for PORTE & PORTD & PORTC */
    SIM->SCGC5 |= ( SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK|SIM_SCGC5_PORTC_MASK);
//    /* *(uint32_t *)0x40048038 &= ~(1<<11); ========= CLEAN = System Clock Gating Control Register 5 SIM_SCGC5 */ 
//    *(uint32_t *)0x40048038 |= (1<<11);
//   /* *(uint32_t *)0x40048038 |= (1<<11);  ========= SET = System Clock Gating Control Register 5  */ 
//   *(uint32_t *)0x40048038 |= (1<<11);
}
void INIT_PORT()
{
//   /*CLEAN Pin Control Register n (PORTC_PCR12)*/
//  //*(uint32_t *)0x4004B030 &=  ~(0x7<<8); 
//   /*SET Pin Control Register n (PORTC_PCR12) = 001 Alternative 1 (GPIO) */
//  //*(uint32_t *)0x4004B030 |=  (1<<8);
//   PORTC->PCR[12] |= PORT_PCR_MUX(1);
//   
//   /*CLEAN Pin Control Register n (PORTC_PCR12) SELECT PULL UP 1 (PE = 1)*/
//  //*(uint32_t *)0x4004B030 &=  ~(1<<1); 
//   /*SET Pin Control Register n (PORTC_PCR12) SELECT PULL UP 1 (PE = 1)*/
//  //*(uint32_t *)0x4004B030 |=  (1<<1); 
//   PORTC->PCR[12] |= PORT_PCR_PE(1);
//   
//   /*CLEAN Pin Control Register n (PORTC_PCR12) SELECT PULL Select 1 (PS = 1)*/
//  //*(uint32_t *)0x4004B030 &=  ~(1<<0);
//   /*SET Pin Control Register n (PORTC_PCR12) SELECT PULL Select 1 (PS = 1)*/
//  //*(uint32_t *)0x4004B030  |=  (1<<0);
//  PORTC->PCR[12] |= PORT_PCR_PE(1);
  
  
  
  
  /*SET Pin Control Register n (PORTC_PCR3) = 001 Alternative 1 (GPIO) */
  PORTC->PCR[3] |= PORT_PCR_MUX(1);
  
  /*SET Pin Control Register n (PORTC_PCR3) SELECT PULL UP 1 (PE = 1)*/
  PORTC->PCR[3] |= PORT_PCR_PE(1);
  
  /*SET Pin Control Register n (PORTC_PCR3) SELECT PULL Select 1 (PS = 1)*/
  PORTC->PCR[3] |= PORT_PCR_PE(1);
  
  
  
  
}

void INIT_GPIO()
{
   /*CLEAN Port Data Direction Register (GPIOx_PDDR) SET PIN NUMBER 12 = INPUT*/ 
  //*(uint32_t *)0x400FF094 &= ~(1<<12);
  
   /*SET Port Data Direction Register (GPIOx_PDDR) SET PIN NUMBER 12 = INPUT*/ 
 // *(uint32_t *)0x400FF094 |= (0<<12);
  
   // GPIOC->PDDR |= GPIO_PDDR_PDD(12);
    
   // GPIOC->PDDR &= ~ GPIO_PDDR_PDD(3);
    GPIOC->PDDR |= GPIO_PDDR_PDD(3);
    
  
}
void BUTTON()
{
      /*Port Data Input Register (GPIOC_PDIR) SW2 = PTC12*/ 
       //uint32_t SW2 = (*(uint32_t *)0x400FF090  & (1<<12));  
//       uint32_t SW2 = GPIOC->PTOR;
//       
//       GPIOC->PTOR |= GPIO_PTOR_PTTO(12);
//           if(SW2==0)
//           {
//               DELAY();
//               
//                if(GPIOC->PDIR == 0)
//                {
//                      
//                    /* Toggle Red Led */
//                      FPTE->PTOR |= RED_LED_PIN;
//                    /* Toggle Green Led */
//                     FPTD->PTOR |= GREEN_LED_PIN;
//                     
//                }
//            } 
       
           /*Port Data Input Register (GPIOC_PDIR) SW1 = PTC3*/ 
       //uint32_t SW1 = (*(uint32_t *)0x400FF090  & (1<<3));  //
        //GPIOC->PDIR |= GPIO_PDIR_PDI(3);
       uint32_t SW1 = GPIOC->PTOR;
       
       GPIOC->PTOR |= GPIO_PTOR_PTTO(3);
       
       if(SW1==0)
            {
               DELAY();
               
                if(GPIOC->PDIR == 0)
                  {
                      
                    /* Toggle Red Led */
                      FPTE->PTOR |= RED_LED_PIN;
                    /* Toggle Green Led */
                     FPTD->PTOR |= GREEN_LED_PIN;
                     
                  }
           }
       
}
void DELAY()
{
    uint32_t i;
    for (i = 0; i < DELAY_CNT; i++)
    {
        __asm("nop");
    }
}