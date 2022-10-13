#include "MKL46Z4.h"


#define RED_LED_PIN         (1 << 29)
#define GREEN_LED_PIN       (1 << 5)

void GPIO_INIT_LED();
void DELAY_MS(uint32_t time);
void SYSTEM_CLOCK_INIT();

int main(void)
{
   GPIO_INIT_LED();  
   SYSTEM_CLOCK_INIT();
   while (1)
    {      
        /* Toggle Red Led */
        FPTE->PTOR |= RED_LED_PIN; 
        DELAY_MS(5000); //delay 4s
    }
}

void SYSTEM_CLOCK_INIT(){
    
   /* Set bit number 6 */
     MCG->C1    |= MCG_C1_CLKS(1);
     
  /* Select Internal clock for MCG4 ================ *(uint8_t *)(0x40064008) &= ~(1<<1);*/       
     MCG->SC    |= MCG_SC_FCRDIV(1);                  //FCRDIV (Divide Factor is 2) 
     
  /* Seclect 4MHZ                   =============== *(uint8_t *)(0x40064001) |= (1<<0);  */
     
     MCG->C2    |= MCG_C2_IRCS(1);
     
  /*  seclect out MCGIRCLK          ===============*(uint32_t *)(0x40048004)|=(1<<7); */           
     SIM->SOPT2 |= SIM_SOPT2_CLKOUTSEL(4);
     
  //  *(uint32_t *)(0x40048038)|=(0x3<<12);       //set bit 12 Enable clock PORTE 
     SIM->SCGC5 |= SIM_SCGC5_PORTE(1);
}
void GPIO_INIT_LED()
{
    SYSTEM_CLOCK_INIT();
    
   /* Initialize the RED LED (PTE29)*/  
    /* Set the PTE29 pin multiplexer to GPIO mode */
    PORTE->PCR[29] = PORT_PCR_MUX(1);
    
    /* Set the pin's direction to output */
    FPTE->PDDR |= RED_LED_PIN;
    
    /* Set the initial output state to high */
    FPTE->PSOR |= RED_LED_PIN;   
}

void DELAY_MS( uint32_t time)
{
    uint32_t x;
    uint32_t y;
    
    for (x = 0; x < time ; x++)
    {
        for (y=0;y<123;y++)
        {
            
            __asm("nop"); 
        }
         
    
    }

}