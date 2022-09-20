#include "setup.h"

void activateLEDGPIOs(){
    // The PWM peripheral must be enabled for use.
    // SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    // Enable LED RGB peripheral.
    SysCtlPeripheralEnable(LED_PERIPH_REGION);

    // Wait for LED RGB to be ready.
    while(!SysCtlPeripheralReady(LED_PERIPH_REGION));

    // GPIOPinConfigure(GPIO_PL1_EPI0S17);
    // GPIOPinConfigure(GPIO_PF3_M0PWM2);

    // Configures LED for PWM output
    GPIOPinTypeGPIOOutput(GPIO_LED_BASE, GPIO_LED_R_PORT);
    GPIOPinTypeGPIOOutput(GPIO_LED_BASE, GPIO_LED_G_PORT);
    GPIOPinTypeGPIOOutput(GPIO_LED_BASE, GPIO_LED_B_PORT);

    // PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_8);
    UARTprintf("setup LED!\n");
}

/**
*   @brief  This functions setups UART0 to be used as the console output through 
*           function `UARTprintf`. This function is based on the examples from TivaWare
*/
void
setupUART0(void)
{
    // Enable GPIO port A which is used for UART0 pins.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    // Enable UART0 so that we can configure the clock.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Select the alternate (UART) function for these pins.
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);
 
    UARTprintf("setup UART!\n");
}

void activateJoystickGPIOs(){
    // Enable Joystick axis peripheral.
    SysCtlPeripheralEnable(JOYSTICK_ANALOG_PERIPH_REGION);
    // Enable Joystick select peripheral.
    SysCtlPeripheralEnable(JOYSTICK_DIGITAL_PERIPH_REGION);

    // Wait for regions to be ready
    while(!SysCtlPeripheralReady(JOYSTICK_ANALOG_PERIPH_REGION));
    while(!SysCtlPeripheralReady(JOYSTICK_DIGITAL_PERIPH_REGION));

    // Set pins as input
    GPIOPinTypeGPIOInput(GPIO_JOYSTICK_ANALOG_BASE, GPIO_JOYSTICK_HOR);
    GPIOPinTypeGPIOInput(GPIO_JOYSTICK_ANALOG_BASE, GPIO_JOYSTICK_VER);
    GPIOPinTypeGPIOInput(GPIO_JOYSTICK_DIGITAL_BASE, GPIO_JOYSTICK_SEL);
    UARTprintf("setup joystick IO...\n");
}

void setupIOs(){
    setupUART0();
    activateLEDGPIOs();
    activateJoystickGPIOs();
}

