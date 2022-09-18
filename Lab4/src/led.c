#include "led.h"


void activateLedRGB(const uint8_t r, const uint8_t g, const uint8_t b){
    // Write values to LED ports
    GPIOPinWrite(GPIO_LED_BASE, GPIO_LED_R_PORT, 0xFF);
    GPIOPinWrite(GPIO_LED_BASE, GPIO_LED_G_PORT, 0xFF);
    GPIOPinWrite(GPIO_LED_BASE, GPIO_LED_B_PORT, 0xFF);

    printf("activating led rgb %d %d %d...\n", r, g, b);
}

void deactivateLedRGB(){
    GPIOPinWrite(GPIO_LED_BASE, GPIO_LED_R_PORT, 0x0);
    GPIOPinWrite(GPIO_LED_BASE, GPIO_LED_G_PORT, 0x0);
    GPIOPinWrite(GPIO_LED_BASE, GPIO_LED_B_PORT, 0x0);
    printf("deactivating led...\n");
}