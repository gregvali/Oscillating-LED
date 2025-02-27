
/**
 * Made by: Greg Valijan
 * Last Edit: 02/27/2025
 * pwn.c
 */

#include "tm4c123gh6pm.h"

#define GENA_SET            0x0000008C                  //Generator Settings for comparator and load
#define LOAD                0x0000013F                  //x13F + 1 = 319 + 1 = 400 ticks per period
#define CMPA_VAL1           0x00000000                  //initial comparator value (100% duty cycle)
#define EN                  0x00000001                  //Enable
#define DN                  0x00000000                  //Disable

void pwm_config();
void set_frequency(uint32_t value);

void pwm_config()                                       //Configure PWM module
{
    SYSCTL_RCGCPWM_R        |=  SYSCTL_RCGCPWM_R0;      //PWM Clock
    SYSCTL_RCGCGPIO_R       |=  (1 << 1);               //Port B Clock
    SYSCTL_RCC_R            &= ~SYSCTL_RCGC0_PWM0;      //Set clock to 16 mHz
    GPIO_PORTB_AFSEL_R      |=  (1 << 6);               //PB6 AFSEL enable
    GPIO_PORTB_PCTL_R       |=  GPIO_PCTL_PB6_M0PWM0;   //PCTL function #4 of PB6
    GPIO_PORTB_DEN_R        |=  (1 << 6);               //PB6 Digital Enable
    PWM0_0_CTL_R             =  DN;                     //Disable PWM0 for Configuration
    PWM0_0_GENA_R            =  GENA_SET;               //Settings for comparator handling
    PWM0_0_LOAD_R            =  LOAD;                   //Load value of 219 for counter
    PWM0_0_CMPA_R            =  CMPA_VAL1;              //Load initial comparator value
    PWM0_0_CTL_R             =  EN;                     //Enable Generator
    PWM0_ENABLE_R            =  EN;                     //Enable Output
}

void set_frequency(uint32_t value)                      //Set PWM frequency. Requires value between 0 - LOAD -> 0 - 219;
{
    PWM0_0_CTL_R              =  DN;                    //Disable PWM0 for Configuration
    PWM0_0_CMPA_R             =  value;                 //Set new Comparator value
    PWM0_0_CTL_R              =  EN;                    //Enable PWM0
}
