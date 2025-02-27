

/**
 * Made by: Greg Valijan
 * Last Edit: 02/27/2025
 * main.c
 */

#include "tm4c123gh6pm.h"

#define PIN1_HI          (1 << 1)

const uint32_t PRINT_FREQ         = 11000;           //Frequency of UART print
const uint32_t ADC_PRECISION      = 4096;            //Precision of ADC
const uint32_t VOLTAGE            = 3300;            //Voltage in mV
const uint32_t LOAD               = 318;             //Load of PWM Generator

void adc_config();
void ss_config();
void pwm_config();
void set_frequency(uint32_t);
void EnableUART();
void print(char*);
void uint32_to_str(uint32_t, char*);
void sendChar(char);
void print_voltage(uint32_t);

int main(void)
{
    EnableUART();
    adc_config();
    ss_config();
    pwm_config();

    char str[12];
    uint32_t counter     =  0;
    uint32_t voltage     =  0;
    uint32_t cmp_val     =  0;

    while(1)
    {
        cmp_val = LOAD - ((ADC1_SSFIFO3_R * LOAD) / ADC_PRECISION);      //new comparator value
        set_frequency(cmp_val);                                 //set frequency with new comparator value;

        voltage = (ADC1_SSFIFO3_R * VOLTAGE) / ADC_PRECISION;   //calculate voltage
        uint32_to_str(voltage, str);                            //voltage to string

        if(counter++ == PRINT_FREQ)                             //UART Display for Voltage
        {
            print(str);                                         //print voltage
            print(" mV\n");
            sendChar(13);                                       //new line and begin line
            counter = 0;
        }
    }
}

void print_voltage(uint32_t voltage)
{
    char str[12];
    uint32_t counter = 0;

    uint32_to_str(voltage, str);        //voltage to string

    if(counter++ == PRINT_FREQ)         //UART Display for Voltage
    {
        print(str);                     //print voltage
        print(" mV\n");
        sendChar(13);                   //new line and begin line
        counter = 0;
    }
}
