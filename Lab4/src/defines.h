// #define PART_TM4C1294NCPDT

#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/hw_memmap.h"

// Joystick defines
// Use analogRead(pin_number) to read raw analog channels for each direction
#define GPIO_JOYSTICK_ANALOG_BASE (GPIO_PORTE_AHB_BASE)
#define JOYSTICK_ANALOG_PERIPH_REGION (SYSCTL_PERIPH_GPIOE)
// Horizontal: J1.2 -> PE4
#define GPIO_JOYSTICK_HOR (GPIO_PORTE_AHB_BASE+GPIO_PIN_4)
// Vertical: J3.26 -> PE3
#define GPIO_JOYSTICK_VER (GPIO_PORTE_AHB_BASE+GPIO_PIN_3)
// Use digitalRead(pin_number) to read selection state
#define GPIO_JOYSTICK_DIGITAL_BASE (GPIO_PORTC_AHB_BASE)
#define JOYSTICK_DIGITAL_PERIPH_REGION (SYSCTL_PERIPH_GPIOC)
// Select: J1.5 -> PC6
#define GPIO_JOYSTICK_SEL (GPIO_JOYSTICK_DIGITAL_BASE+GPIO_PIN_6)

// Led RGB 
// PWM GPIO, use analogWrite(pin_number, brightness)
#define GPIO_LED_BASE (GPIO_PORTL_BASE)
// Region to activate for LED
#define LED_PERIPH_REGION (SYSCTL_PERIPH_GPIOL)
// Red: J4.39 -> PL2
#define GPIO_LED_R_PORT (GPIO_PIN_2)
// Green: J4.38 -> PL1
#define GPIO_LED_G_PORT (GPIO_PIN_1)
// Blue: J4.37 -> PL0
#define GPIO_LED_B_PORT (GPIO_PIN_0)

// Luminosity sensor
// Use the OPT3001 Library to get the sensor reading. 
// OPT3001 reports back ambient light brightness
#define GPIO_LIGHT_SENSOR_I2C_BASE (GPIO_PORTB_AHB_BASE)
#define GPIO_LIGHT_SENSOR_INT_BASE (GPIO_PORTB_AHB_BASE)
// I2C SDAfor light sensor: J1.10 -> PB3
#define GPIO_LIGHT_SENSOR_I2C_SCL (GPIO_LIGHT_SENSOR_I2C_BASE+GPIO_PIN_2)
// I2C SDAfor light sensor: J1.10 -> PB3
#define GPIO_LIGHT_SENSOR_I2C_SDA (GPIO_LIGHT_SENSOR_I2C_BASE+GPIO_PIN_3)
// INT pin for light sensor: J1.8 -> PC7
#define GPIO_LIGHT_SENSOR_INT_PIN (GPIO_LIGHT_SENSOR_INT_BASE+GPIO_PIN_7)    

#define UART_USE_REPORT UART0_BASE