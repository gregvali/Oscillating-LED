
/**
 * Made by: Greg Valijan
 * Last Edit: 02/27/2025
 * adc.c
 */

#include "tm4c123gh6pm.h"

#define PIN1_HI                 (1 << 1)

void adc_config();
void ss_config();

void adc_config()
{
    SYSCTL_RCGCADC_R         =  PIN1_HI;               //Clock Gating ADC1

    SYSCTL_RCGCGPIO_R       |=  (1 << 4);              //Clock Gating Port E
    GPIO_PORTE_DIR_R        &= ~PIN1_HI;               //PE1 as input
    GPIO_PORTE_AFSEL_R       =  PIN1_HI;               //PE1 Alternate Function
    GPIO_PORTE_DEN_R        &=  PIN1_HI;               //PE1 Digital Function Disable
    GPIO_PORTE_AMSEL_R       =  PIN1_HI;               //PE1 Analog Isolation Circuit Disable
}

void ss_config()
{
    ADC1_ACTSS_R            &= ~ADC_ACTSS_ASEN3;        //Sample Sequencer 3 Disable
    ADC1_EMUX_R              =  ADC_EMUX_EM3_ALWAYS;    //SS3 Continuous Sample
    ADC1_SSMUX3_R            =  2;                      //PE1/ANI2 input source
    ADC1_SSCTL3_R            =  0x6;                    //Sample Interrupt Enable + End of Sequence Set
    ADC1_ACTSS_R            |=  ADC_ACTSS_ASEN3;        //SS 3 Enable
}
