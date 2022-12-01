#include "buzzer.h"

using namespace drivers;

const uint32_t DUTY_CYCLE = 200;

void delayMS(int ms)
{
    SysCtlDelay((SysCtlClockGet() / (3 * 1000)) * ms);
}

void drivers::setup_buzzer()
{
    // Configure PWM Clock to match system
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    // Buzzer
    // Enable GPIO Port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        ;

    // Enable PWM0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
        ;

    // Configure pin G0 as PWM output
    GPIOPinConfigure(GPIO_PF1_M0PWM1);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);

    // Configure the PWM generator for count down mode with immediate updates
    // to the parameters.
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    // Set the period. For a 50 KHz frequency, the period = 1/5,000, or 200
    // microseconds. For a 120 MHz clock, this translates to 2400 clock ticks.
    // Use this value to set the period.
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, DUTY_CYCLE);

    // Set the pulse width of PWM1 for a 100% duty cycle.
    //
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, DUTY_CYCLE);

    // Start the timers in generator 0.
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    // Enable output
    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);

    // Fade
    /*
    bool fadeUp = true;
    unsigned long increment = 10;
    unsigned long pwmNow = 100;
    while(1)
    {
        delayMS(20);
        if (fadeUp) {
            pwmNow += increment;
            if (pwmNow >= DUTY_CYCLE) {
              fadeUp = false;
            }
        }
        else {
            pwmNow -= increment;
            if (pwmNow <= 10) {
              fadeUp = true;
            }
        }
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, pwmNow);
    }*/
}

void drivers::update_buzzer_value(float width)
{
    /*
        //Fade
      bool fadeUp = true;
      volatile unsigned long increment = 10;
      volatile unsigned long pwmNow = 100;
      while(1)
      {
          delayMS(20);
          if (fadeUp) {
              pwmNow += increment;
              if (pwmNow >= DUTY_CYCLE) {
                fadeUp = false;
              }
          }
          else {
              pwmNow -= increment;
              if (pwmNow <= 10) {
                fadeUp = true;
              }
          }
          PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 0);
      }
  */
    float pwm = width;
    pwm = pwm < 0 ? 0 : pwm;
    pwm = pwm > 1 ? 1 : pwm;

    // Adjusts the intensity of one of the RGB LED color channels
    // according to the current color scheme
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, (uint32_t)DUTY_CYCLE - 1);
}