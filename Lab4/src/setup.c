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
}

void activateUART0(){
    // printf("activating UART0...\n");

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
}

void setupIOs(){
    activateLEDGPIOs();
    activateUART0();
    activateJoystickGPIOs();
}

