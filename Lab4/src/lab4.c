/*__________________________________________________________________________________
|       Disciplina de Sistemas Embarcados - 2022-2
|       Prof. Douglas Renaux
| __________________________________________________________________________________
|
|		Lab 4
| __________________________________________________________________________________
*/

/**
 * @file     lab4.c
 * @author   Joao F. S. Machado & Waine B. O. Junior
 * @date     Oct, 2022
 ******************************************************************************/

/*------------------------------------------------------------------------------
 *
 *      File includes
 *
 *------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

/*------------------------------------------------------------------------------
 *
 *      Gloval vars declarations
 *
 *------------------------------------------------------------------------------*/
// Global variable to store the message that will be sent through the serial port
uint8_t Message[45] = {'H', ' ', '=', ' ', '0', '0', '0', '0', ' ', '|', ' ',      //[0:10]
                       'V', ' ', '=', ' ', '0', '0', '0', '0', ' ', '|', ' ',      //[11:21]
                       'B', ' ', '=', ' ', '0', ' ', '|', ' ',                     //[22:29]
                       'L', ' ', '=', ' ', '0', '0', '0', '0', '0', '.', '0', '0', //[30:41]
                       '\r', '\n', '\0'};                                          //[42:44]

// Global variable to store the RGB led color scheme
uint8_t RGB_Mode = 0;

/*------------------------------------------------------------------------------
 *
 *      Functions and Methods
 *
 *------------------------------------------------------------------------------*/

// Joystick button and light sensor interrupt handler
void
PortCIntHandler(void)
{
    // Checks if the interrupt source is the joystick button
    if(GPIOIntStatus(GPIO_PORTC_BASE, true) & GPIO_INT_PIN_6)
    {
        // Clear the interrupt
        GPIOIntClear(GPIO_PORTC_BASE, GPIO_INT_PIN_6);
        
        // If the button is pressed, it changes the message to ASCII character 1. Otherwise, it changes to ASCII 0
        Message[26] = 48 + (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) == 0x0);
        
        // Switch to the next color scheme
        RGB_Mode = (RGB_Mode + 1)%3;
    }
    
    // Checks if the interrupt source is the light sensor
    if(GPIOIntStatus(GPIO_PORTC_BASE, true) & GPIO_INT_PIN_7)
    {
        // Clear the interrupt
        GPIOIntClear(GPIO_PORTC_BASE, GPIO_INT_PIN_7);
        
        // Initiates a communication in written mode with the sensor
        I2CMasterSlaveAddrSet(I2C0_BASE, 0x44, false);
        
        // Send result register address and wait for it to be sent
        I2CMasterDataPut(I2C0_BASE, 0x00);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        while(!I2CMasterBusy(I2C0_BASE));
        while(I2CMasterBusy(I2C0_BASE));
        
        // Switch to read mode communication with the sensor
        I2CMasterSlaveAddrSet(I2C0_BASE, 0x44, true);
        
        // Receives and stores the most significant part of the result register
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
        while(!I2CMasterBusy(I2C0_BASE));
        while(I2CMasterBusy(I2C0_BASE));
        uint32_t RRH = I2CMasterDataGet(I2C0_BASE);
        
        // Receives and stores the least significant part of the result register
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        while(!I2CMasterBusy(I2C0_BASE));
        while(I2CMasterBusy(I2C0_BASE));
        uint32_t RRL = I2CMasterDataGet(I2C0_BASE);

        // Calculates brightness in lux as instructed by the sensor manual
        float lux = 0.01 * (0x1 << (RRH >> 4)) * (RRL | ((RRH & 0xF) << 8));
        
        //Separates the integer part of the read value
        RRH = (uint32_t)lux;
        
        // Separates the fraction part from the read value
        RRL = ((uint32_t)(lux*100))%100;
        
        // Adjusts the intensity of one of the RGB LED color channels according to the current color scheme
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2*(RGB_Mode == 1) | PWM_OUT_3*(RGB_Mode == 2) | PWM_OUT_4*(RGB_Mode == 0), RRH/328);
        
        // Writes the integer part of the luminosity value in the buffer that will be sent by the UART
        Message[38] = RRH%10 + 48;
        RRH /= 10;
        Message[37] = RRH%10 + 48;
        RRH /= 10;
        Message[36] = RRH%10 + 48;
        RRH /= 10;
        Message[35] = RRH%10 + 48;
        RRH /= 10;
        Message[34] = RRH + 48;
        
        // Writes the fraction part of the brightness value in the buffer that will be sent by the UART
        Message[41] = RRL%10 + 48;
        RRL /= 10;
        Message[40] = RRL + 48;
        
        // Reads sensor configuration register to disable interrupt as instructed in manual
        I2CMasterSlaveAddrSet(I2C0_BASE, 0x44, false);
        I2CMasterDataPut(I2C0_BASE, 0x01);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        while(!I2CMasterBusy(I2C0_BASE));
        while(I2CMasterBusy(I2C0_BASE));
        I2CMasterSlaveAddrSet(I2C0_BASE, 0x44, true);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
        while(!I2CMasterBusy(I2C0_BASE));
        while(I2CMasterBusy(I2C0_BASE));
        RRH = I2CMasterDataGet(I2C0_BASE);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        while(!I2CMasterBusy(I2C0_BASE));
        while(I2CMasterBusy(I2C0_BASE));
        RRL = I2CMasterDataGet(I2C0_BASE);
    }
}

// Joystick axis X axis interrupt handler
void
ADC0SS3IntHandler(void)
{
    // Clear the interrupt
    ADCIntClear(ADC0_BASE, 3);
    
    // Read the ADC conversion value for the horizontal axis
    uint32_t Joystick_H;
    ADCSequenceDataGet(ADC0_BASE, 3, &Joystick_H);
    
    // Adjusts the intensity of one of the RGB LED color channels according to the current color scheme
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2*(RGB_Mode == 0) | PWM_OUT_3*(RGB_Mode == 1) | PWM_OUT_4*(RGB_Mode == 2), Joystick_H >> 4);
    
    // Writes the horizontal axis conversion value to the buffer that will be sent by the UART
    Message[7] = Joystick_H%10 + 48;
    Joystick_H /= 10;
    Message[6] = Joystick_H%10 + 48;
    Joystick_H /= 10;
    Message[5] = Joystick_H%10 + 48;
    Joystick_H /= 10;
    Message[4] = Joystick_H + 48;
}

// Joystick axis Y axis interrupt handler
void
ADC1SS3IntHandler(void)
{
    // Clear the interrupt
    ADCIntClear(ADC1_BASE, 3);
    
    // Read the ADC conversion value for the vertical axis
    uint32_t Joystick_V;
    ADCSequenceDataGet(ADC1_BASE, 3, &Joystick_V);
    
    // Adjusts the intensity of one of the RGB LED color channels according to the current color scheme
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2*(RGB_Mode == 2) | PWM_OUT_3*(RGB_Mode == 0) | PWM_OUT_4*(RGB_Mode == 1), Joystick_V >> 4);
    
    // // Writes the vertical axis conversion value to the buffer that will be sent by the UART
    Message[18] = Joystick_V%10 + 48;
    Joystick_V /= 10;
    Message[17] = Joystick_V%10 + 48;
    Joystick_V /= 10;
    Message[16] = Joystick_V%10 + 48;
    Joystick_V /= 10;
    Message[15] = Joystick_V + 48;
}

// Timer interrupt handler
void
Timer0IntHandler(void)
{
    // Clear the interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); 
    
    // Inserts a character in the transmit FIFO of the UART port in a blocking way (If there is no space, it blocks and waits)
    uint32_t index;
    
    for(index = 0; Message[index] != '\0'; index++)
    {
        UARTCharPut(UART0_BASE, Message[index]);
    }
}

// LED RGB initialization
void
RGB_LED_Init(void)
{
    // RGB LED RED
    // Enable GPIO Port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    
    // Configure pin F2 as PWM output
    GPIOPinConfigure(GPIO_PF2_M0PWM2);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
    
    // Enable peripheral PWM 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0));
    
    // Sets the frequency that will be used in the PWM peripheral
    PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_1);
    
    // Sets the value that will correspond to a 100% duty cycle to 255 and turns off synchronization between PWM generators
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 256);
    
    // Sets the duty cycle value to zero
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 0);
    
    // Enable output to pin 2
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    
    // RGB LED GREEN
    // Configure pin F3 as PWM output
    GPIOPinConfigure(GPIO_PF3_M0PWM3);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
    
    // Sets the duty cycle value to zero
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, 0);
    
    // Enable output to pin 3
    PWMOutputState(PWM0_BASE, PWM_OUT_3_BIT, true);
    
    // Enables PWM generator 1, effectively turning on the red and green channel
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    
    // RGB LED BLUE
    // Enable GPIO Port G
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG));
    
    // Configure pin G0 as PWM output
    GPIOPinConfigure(GPIO_PG0_M0PWM4);
    GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_0);
    
    // Sets the value that will correspond to a 100% duty cycle to 255 and turns off synchronization between PWM generators
    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, 256);
    
    // Sets the duty cycle value to zero
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, 0);
    
    // Enable output to pin 4
    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
    
    // Enables PWM generator 2, effectively turning on the blue channel
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
}

// Timer 0 initialization
void
Timer_0_Init(uint32_t ui32SysClock)
{
    // Enable timer 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
    
    // Configures to generate interrupts periodically every one-fifth of a second (200 ms)
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32SysClock/5);
    
    // Enable peripheral interrupts
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);  
    
    // Enable interrupts in NVIC
    IntEnable(INT_TIMER0A);
    
    // Start the timer
    TimerEnable(TIMER0_BASE, TIMER_A);
}

// UART 0 initialization
void
UART_0_Init(uint32_t ui32SysClock)
{
    // Enable GPIO Port A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    
    // Configure pin A0 as UART RX and A1 as UART TX
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    
    // Enable peripheral UART 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
    
    // Disables the UART and sets the frequency source to be the same as the system
    UARTDisable(UART0_BASE);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
    
    // Configures the UART to operate in 115.200 bps 8N1 mode
    UARTConfigSetExpClk(UART0_BASE, ui32SysClock, 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE);
    
    // Enables UART transmit and receive queue
    UARTFIFOEnable(UART0_BASE);
    
    // Start the UART
    UARTEnable(UART0_BASE);
}

// I2C 0 initialization
void
I2C_0_Init(uint32_t ui32SysClock)
{
    // Enable GPIO Port B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));
    
    // Configure pin B2 as I2C Clock and B3 as I2C Data
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
    
    // Resets peripheral I2C 0
    SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0));
    
    // Initialize Master block in fast mode
    I2CMasterInitExpClk(I2C0_BASE, ui32SysClock, true);
}

// Light sensor initialization
void
OPT_3001_Init(void)
{
    // Config Low-Limit Register
    // Initiates a communication in written mode with the sensor
    I2CMasterSlaveAddrSet(I2C0_BASE, 0x44, false);
    
    // Send low-limit register address and wait for it to be sent
    I2CMasterDataPut(I2C0_BASE, 0x02);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(!I2CMasterBusy(I2C0_BASE));
    while(I2CMasterBusy(I2C0_BASE));
    
    // Configures the sensor for end-of-conversion mode
    I2CMasterDataPut(I2C0_BASE, 0xC0);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(!I2CMasterBusy(I2C0_BASE));
    while(I2CMasterBusy(I2C0_BASE));
    I2CMasterDataPut(I2C0_BASE, 0x00);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(!I2CMasterBusy(I2C0_BASE));
    while(I2CMasterBusy(I2C0_BASE));
    
    // Initiates a communication in written mode with the sensor
    I2CMasterSlaveAddrSet(I2C0_BASE, 0x44, false);
    
    // Send configuration register address and wait for it to be sent
    I2CMasterDataPut(I2C0_BASE, 0x01);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    
    // Sets the sensor to automatic full-scale, conversion time of 100 ms, 
    // continuous conversion mode,  latched window-style comparison operation, 
    // low active interrupt polarity, exponent mask off and 
    // interrupt fault count for 8 results in a row
    while(!I2CMasterBusy(I2C0_BASE));
    while(I2CMasterBusy(I2C0_BASE));
    I2CMasterDataPut(I2C0_BASE, 0xC6);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
    while(!I2CMasterBusy(I2C0_BASE));
    while(I2CMasterBusy(I2C0_BASE));
    I2CMasterDataPut(I2C0_BASE, 0x13);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(!I2CMasterBusy(I2C0_BASE));
    while(I2CMasterBusy(I2C0_BASE));    
    
    // Enable GPIO Port C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));
    
    // Configure pin C7 for GPIO input
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_7);
    
    // Enables low level interruptions, according to the polarity defined in the sensor
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_LOW_LEVEL);
    
    // Enable peripheral interrupts
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_7);
    
    // Enable interrupts in NVIC
    IntEnable(INT_GPIOC);  
}

// Joystick initialization
void
Joystick_Init(void)
{
    // Configure the joystick select
    // Enable GPIO Port C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));
    
    // Configure pin C6 for GPIO input
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_6);
    
    // Enable interrupts for both edges
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_BOTH_EDGES);
    
    // Enable peripheral interrupts
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_INT_PIN_6);
    // Enable interrupts in NVIC
    IntEnable(INT_GPIOC);
    
    // Configure the joystick horizontal axis
    // Enable GPIO Port E
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));
    
    // Configure pin E4 as analog-to-digital converter input
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4);
    
    // Enable the ADC0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));
    
    // Sets the frequency of the ADC modules to a quarter of the system frequency, i.e. 30 MHz
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 4);
    
    // Disable sequencer 3 in order to configure it
    ADCSequenceDisable(ADC0_BASE, 3);
    
    // Configure sequencer 3 for constant triggering
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_ALWAYS, 3);
    
    // Sets the sampling frequency to minimum and the input channel to 9 (corresponds to pin PE4)
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH9 | ADC_CTL_SHOLD_256);
    
    // Sets ADC hardware oversampling factor to maximum for more accurate values
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
    
    // Enable peripheral interrupts
    ADCIntEnable(ADC0_BASE, 3);
    
    // Enable interrupts in NVIC
    IntEnable(INT_ADC0SS3);
    
    //Start sequencer 3
    ADCSequenceEnable(ADC0_BASE, 3);
    
    // Configure the joystick vertical axis
    // Configure pin E3 as analog-to-digital converter input
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    
    // Enable the ADC1 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1));
    
    // Disable sequencer 3 in order to configure it
    ADCSequenceDisable(ADC1_BASE, 3);
    
    // Configure sequencer 3 for constant triggering
    ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_ALWAYS, 3);

    // Sets the sampling frequency to minimum and the input channel to 0 (corresponds to pin PE3)
    ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0 | ADC_CTL_SHOLD_256);
    
    // Sets ADC hardware oversampling factor to maximum for more accurate values
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
    
    // Enable peripheral interrupts
    ADCIntEnable(ADC1_BASE, 3);
    
    // Enable interrupts in NVIC
    IntEnable(INT_ADC1SS3);
    
    //Start sequencer 3
    ADCSequenceEnable(ADC1_BASE, 3);
}

//*****************************************************************************
//
// Main 'C' Language entry point.
//
//*****************************************************************************
int main()
{
    // // Run from the PLL at 120 MHz.
    uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
    
    // Configure the RGB LED
    RGB_LED_Init();
    
    // Configure UART 0
    UART_0_Init(ui32SysClock);

    // Configure I2C 0
    I2C_0_Init(ui32SysClock);
    
    // Configure the light sensor
    OPT_3001_Init();
    
    // Configure the joystick
    Joystick_Init();
    
    // Configure timer 0
    Timer_0_Init(ui32SysClock);
    
    // Loop forever
    while(1);
}
