//*****************************************************************************
//
// cfaf128x128x16.h - Prototypes for the Crystalfontz CFAF128128B-0145T display
//                                     with an ST7735S controller.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

#ifndef __CFAF128X128X16_H__
#define __CFAF128X128X16_H__

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************
extern void cfaf128x128x16Init(void);
extern const tDisplay g_sCfaf128x128x16;

// Colors
extern const uint16_t blackColor;
extern const uint16_t whiteColor;
extern const uint16_t redColor;
extern const uint16_t greenColor;
extern const uint16_t blueColor;
extern const uint16_t yellowColor;
extern const uint16_t cyanColor;
extern const uint16_t orangeColor;
extern const uint16_t magentaColor;
extern const uint16_t violetColor;
extern const uint16_t grayColor;
extern const uint16_t darkGrayColor;

#endif // __CFAF128X128X16_H__
