#include "joystick.h"

using namespace drivers;

uint32_t val_horizontal = 0;
uint32_t val_vertical = 0;

void setup_horizontal_axis()
{
    // Configure the joystick horizontal axis
    // Enable GPIO Port E
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
        ;

    // Configure pin E4 as analog-to-digital converter input
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4);

    // Enable the ADC0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
        ;

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

    // Register Interrupt function
    // IntRegister(INT_ADC0SS3, ADC0SS3IntHandler);

    // Enable peripheral interrupts
    // ADCIntEnable(ADC0_BASE, 3);

    // Enable interrupts in NVIC
    // IntEnable(INT_ADC0SS3);

    // Start sequencer 3
    ADCSequenceEnable(ADC0_BASE, 3);
}

void setup_vertical_axis()
{
    // Configure the joystick vertical axis
    // Configure pin E3 as analog-to-digital converter input
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    // Enable the ADC1 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1))
        ;

    // Disable sequencer 3 in order to configure it
    ADCSequenceDisable(ADC1_BASE, 3);

    // Configure sequencer 3 for constant triggering
    ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_ALWAYS, 3);

    // Sets the sampling frequency to minimum and the input channel to 0 (corresponds to pin PE3)
    ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0 | ADC_CTL_SHOLD_256);

    // Sets ADC hardware oversampling factor to maximum for more accurate values
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);

    // Register Interrupt function
    // IntRegister(INT_ADC1SS3, ADC1SS3IntHandler);

    // Enable peripheral interrupts
    // ADCIntEnable(ADC1_BASE, 3);

    // Enable interrupts in NVIC
    // IntEnable(INT_ADC1SS3);

    // Start sequencer 3
    ADCSequenceEnable(ADC1_BASE, 3);
}

void drivers::setup_joystick()
{
    setup_horizontal_axis();
    setup_vertical_axis();
}

const int THRESHOLD = 1024;
const int AVERAGE_VALUE_ADC = 2048;

int analog_to_dig(int analog_val)
{
    if (analog_val < -THRESHOLD) {
        return -1;
    } else if (analog_val < THRESHOLD) {
        return 0;
    } else {
        return 1;
    }
}

int drivers::get_joystick_x()
{
    // Read the ADC conversion value for the horizontal axis
    ADCSequenceDataGet(ADC0_BASE, 3, &val_horizontal);

    return ((int)val_horizontal - AVERAGE_VALUE_ADC);
}

int drivers::get_joystick_y()
{
    // Read the ADC conversion value for the vertical axis
    ADCSequenceDataGet(ADC1_BASE, 3, &val_vertical);

    return ((int)val_vertical - AVERAGE_VALUE_ADC);
}

misc::Vector<int> drivers::get_joystick_pos()
{
    int analog_x = get_joystick_x();
    int analog_y = get_joystick_y();

    int dig_x = analog_to_dig(analog_x);
    int dig_y = analog_to_dig(analog_y);

    if (dig_x != 0 && dig_y == 0) {
        return misc::Vector<int>(dig_x, 0);
    } else if (dig_x == 0 && dig_y != 0) {
        return misc::Vector<int>(0, dig_y);
    } else if (dig_x != 0 && dig_y != 0) {
        int abs_x = analog_x > 0 ? analog_x : -analog_x;
        int abs_y = analog_y > 0 ? analog_y : -analog_y;
        if (abs_x > abs_y) {
            return misc::Vector<int>(dig_x, 0);
        } else {
            return misc::Vector<int>(0, dig_y);
        }
    } else {
        return misc::Vector<int>(0, 0);
    }
}