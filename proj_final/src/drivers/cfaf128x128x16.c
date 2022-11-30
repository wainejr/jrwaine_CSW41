//..............................................................................
//
// Copyright (c) 2017 
// Allan Patrick de Souza - <allansouza@alunos.utfpr.edu.br>
// Guilherme Jacichen     - <jacichen@alunos.utfpr.edu.br>
// Jessica Isoton Sampaio - <jessicasampaio@alunos.utfpr.edu.br>
// Mariana Carri�o        - <mcarriao@alunos.utfpr.edu.br>
//
// cfaf128x128x16.c - Display driver for the Crystalfontz CFAF128128B-0145T
//                  display with an ST7735S.  This version uses an SSI
//                  interface to the display controller. This driver was made 
//					to be used with the TivaWare grlib driver set (ti.com/tivaware), 
//					and was based on the Kentec320x240x16_ssd2119_spi driver for the
//					ek-tm4c1294xl board, the cfal96x64x16 driver for the dk-tm4c123g
//					board and the Energia's Screen_HX8353E driver for dk-tm4c1294xl board
//
// All rights reserved. 
// Software License Agreement
//...............................................................................

//*****************************************************************************
//
//! \addtogroup display_api
//! @{
//
//*****************************************************************************

#include "cfaf128x128x16.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128

// ST7735 LCD controller Command Set
#define CM_NOP             0x00
#define CM_SWRESET         0x01
#define CM_RDDID           0x04
#define CM_RDDST           0x09
#define CM_SLPIN           0x10
#define CM_SLPOUT          0x11
#define CM_PTLON           0x12
#define CM_NORON           0x13
#define CM_INVOFF          0x20
#define CM_INVON           0x21
#define CM_GAMSET          0x26
#define CM_DISPOFF         0x28
#define CM_DISPON          0x29
#define CM_CASET           0x2A
#define CM_RASET           0x2B
#define CM_RAMWR           0x2C
#define CM_RGBSET          0x2D
#define CM_RAMRD           0x2E
#define CM_PTLAR           0x30
#define CM_MADCTL          0x36
#define CM_COLMOD          0x3A
#define CM_SETPWCTR        0xB1
#define CM_SETDISPL        0xB2
#define CM_FRMCTR3         0xB3
#define CM_SETCYC          0xB4
#define CM_SETBGP          0xb5
#define CM_SETVCOM         0xB6
#define CM_SETSTBA         0xC0
#define CM_SETID           0xC3
#define CM_GETHID          0xd0
#define CM_SETGAMMA        0xE0
#define CM_MADCTL_MY       0x80
#define CM_MADCTL_MX       0x40
#define CM_MADCTL_MV       0x20
#define CM_MADCTL_ML       0x10
#define CM_MADCTL_RGB      0x08
#define CM_MADCTL_MH       0x04

//Colors
const uint16_t blackColor    = 0x0000;
const uint16_t whiteColor    = 0xFFFF;
const uint16_t redColor      = 0xF800;
const uint16_t greenColor    = 0x07E0;
const uint16_t blueColor     = 0x001F;
const uint16_t yellowColor   = 0xFFE0;
const uint16_t cyanColor     = 0x07FF;
const uint16_t orangeColor   = 0xFBE0;
const uint16_t magentaColor  = 0xF80F;
const uint16_t violetColor   = 0xF81F;
const uint16_t grayColor     = 0x7BEF;
const uint16_t darkGrayColor = 0x39E7;

//Abstract for delay calls
#define delay(d) ROM_SysCtlDelay(d*10)

#ifndef __SysCtlClockGet
#define __SysCtlClockGet()	\
SysCtlClockFreqSet( 				\
	SYSCTL_XTAL_25MHZ	| 			\
	SYSCTL_OSC_MAIN 	| 			\
	SYSCTL_USE_PLL 		| 			\
	SYSCTL_CFG_VCO_480, 			\
	120000000)
#endif

//*****************************************************************************
//
// Defines the SSI and GPIO peripherals that are used for this display.
//
//*****************************************************************************
#define DISPLAY_SSI_PERIPH          SYSCTL_PERIPH_SSI2
#define DISPLAY_SSI_GPIO_PERIPH     SYSCTL_PERIPH_GPIOD
#define DISPLAY_RST_GPIO_PERIPH     SYSCTL_PERIPH_GPIOH
#define DISPLAY_C_D_GPIO_PERIPH     SYSCTL_PERIPH_GPIOL
#define DISPLAY_CS_GPIO_PERIPH      SYSCTL_PERIPH_GPION

//*****************************************************************************
//
// Defines the GPIO pin configuration macros for the pins that are used for
// the SSI function.
//
//*****************************************************************************
#define DISPLAY_PINCFG_SSICLK       GPIO_PD3_SSI2CLK
#define DISPLAY_PINCFG_SSIFSS       GPIO_PD2_SSI2FSS
#define DISPLAY_PINCFG_SSITX        GPIO_PD1_SSI2XDAT0
#define DISPLAY_PINCFG_SSIRX        GPIO_PD0_SSI2XDAT1

//*****************************************************************************
//
// Defines the port and pins for the SSI peripheral.
//
//*****************************************************************************
#define DISPLAY_SSI_PORT            GPIO_PORTD_BASE
#define DISPLAY_SSI_PIN_CLK         GPIO_PIN_3
#define DISPLAY_SSI_PIN_FSS         GPIO_PIN_2
#define DISPLAY_SSI_PIN_TX          GPIO_PIN_1
#define DISPLAY_SSI_PIN_RX          GPIO_PIN_0
#define DISPLAY_SSI_PINS            (DISPLAY_SSI_PIN_CLK | DISPLAY_SSI_PIN_FSS | DISPLAY_SSI_PIN_TX | DISPLAY_SSI_PIN_RX)

//*****************************************************************************
//
// Defines the port and pins for the display voltage enable signal.
//
//*****************************************************************************
//#define DISPLAY_ENV_PORT            GPIO_PORTG_BASE
//#define DISPLAY_ENV_PIN             GPIO_PIN_0

//*****************************************************************************
//
// Defines the port and pins for the display reset signal.
//
//*****************************************************************************
#define DISPLAY_RST_PORT            GPIO_PORTH_BASE
#define DISPLAY_RST_PIN             GPIO_PIN_3

//*****************************************************************************
//
// Defines the port and pins for the display Data/Command (D/C) signal.
//
//*****************************************************************************
#define DISPLAY_D_C_PORT            GPIO_PORTL_BASE
#define DISPLAY_D_C_PIN	            GPIO_PIN_3

//*****************************************************************************
//
// Defines the port and pins for the chip select (CS) signal.
//
//*****************************************************************************
#define DISPLAY_CS_PORT            	GPIO_PORTN_BASE
#define DISPLAY_CS_PIN	            GPIO_PIN_2

//*****************************************************************************
//
// Defines the SSI peripheral used and the data speed.
//
//*****************************************************************************
#define DISPLAY_SSI_BASE            SSI2_BASE // SSI2
#define DISPLAY_SSI_CLOCK           60000000

static uint32_t g_ui32SysClock;
static uint8_t _orientation;

//*****************************************************************************
//
// Translates a 24-bit RGB color to a display driver-specific color.
//
// \param c is the 24-bit RGB color.  The least-significant byte is the blue
// channel, the next byte is the green channel, and the third byte is the red
// channel.
//
// This macro translates a 24-bit RGB color into a value that can be written
// into the display's frame buffer in order to reproduce that color, or the
// closest possible approximation of that color.
//
// \return Returns the display-driver specific color.
//
// 24-bit format: XXXX XXXX RRRR RRRR GGGG GGGG BBBB BBBB
// 18-bit format: ---- ---- ---- XXRR RRRR GGGG GGBB BBBB
// 16-bit format: ---- ---- ---- ---- RRRR RGGG GGGB BBBB
//  8-bit format: ---- ---- ---- ---- ---- ---- RRRG GGBB
//
//
//*****************************************************************************
#define DPYCOLORTRANSLATE18(c)  ((((c) & 0x00fc0000) >> 6) |                  \
                                 (((c) & 0x0000fc00) >> 4) |                  \
                                 (((c) & 0x000000fc) >> 2))
#define DPYCOLORTRANSLATE16(c)  ((((c) & 0x00f80000) >> 8) |                  \
                                 (((c) & 0x0000fc00) >> 5) |                  \
                                 (((c) & 0x000000f8) >> 3))
#define DPYCOLORTRANSLATE8(c)   ((((c) & 0x00e00000) >> 16) |                 \
                                 (((c) & 0x0000e000) >> 11) |                 \
                                 (((c) & 0x000000c0) >> 6))
#define DPYCOLORTRANSLATE DPYCOLORTRANSLATE16

//Swap contents of 2 uint16 variables
static void 
swap_ui16(uint16_t* a, uint16_t* b){
	uint16_t aux = *a;
	*a = *b;
	*b = aux;
}

//Swap contents of 2 uint32 variables
static void 
swap_i32(int32_t* a, int32_t* b){
	int32_t aux = *a;
	*a = *b;
	*b = aux;
}

//Transfer data by the configured SSI (send and receive)
static uint8_t 
cfaf128x128x16SsiTransfer(uint8_t command8){
	uint32_t received32;
	ROM_SSIDataPut(DISPLAY_SSI_BASE, command8);
	while(ROM_SSIBusy(DISPLAY_SSI_BASE));
	ROM_SSIDataGet(DISPLAY_SSI_BASE, &received32);
	return (uint8_t) received32;
}

//*****************************************************************************
//
//! Write a set of command bytes to the display controller.
//
//! \param command8 is a command byte.
//!
//! This function provides a way to send command bytes to the display
//! controller.  It can be used for single commands. It will wait for any previous operation to
//! finish, and then copy all the command bytes to the controller.  It will
//! not return until the last command byte has been written to the SSI FIFO,
//! but data could still be shifting out to the display controller when this
//! function returns.
//!
//! \return None.
//
//*****************************************************************************
static void
cfaf128x128x16WriteCommand(uint8_t command8)
{		
		ROM_GPIOPinWrite(DISPLAY_D_C_PORT, DISPLAY_D_C_PIN, 0);
		ROM_GPIOPinWrite(DISPLAY_CS_PORT, DISPLAY_CS_PIN, 0);
		cfaf128x128x16SsiTransfer(command8);
		ROM_GPIOPinWrite(DISPLAY_CS_PORT, DISPLAY_CS_PIN, DISPLAY_CS_PIN);
}

//*****************************************************************************
//
//! Write a set of data bytes to the display controller.
//
//! \param data8 is a pointer to a set of data bytes, containing pixel data.
//! \param ndata is the count of command bytes.
//!
//! This function provides a way to send a set of pixel data to the display.
//! The data will draw pixels according to whatever the most recent col, row
//! settings are for the display.  It will wait for any previous operation to
//! finish, and then copy all the data bytes to the controller.  It will
//! not return until the last data byte has been written to the SSI FIFO,
//! but data could still be shifting out to the display controller when this
//! function returns.
//!
//! \return None.
//
//*****************************************************************************
static void
cfaf128x128x16WriteData(const uint8_t *data8, uint32_t ndata)
{		
	ROM_GPIOPinWrite(DISPLAY_D_C_PORT, DISPLAY_D_C_PIN, DISPLAY_D_C_PIN);
	ROM_GPIOPinWrite(DISPLAY_CS_PORT, DISPLAY_CS_PIN, 0);
	for(;ndata--;data8++)
		cfaf128x128x16SsiTransfer(*data8);
	ROM_GPIOPinWrite(DISPLAY_CS_PORT, DISPLAY_CS_PIN, DISPLAY_CS_PIN);
}

//Write a command and one data byte
static void 
cfaf128x128x16WriteRegister(uint8_t command8, uint8_t data8){
	cfaf128x128x16WriteCommand(command8);
	cfaf128x128x16WriteData(&data8, 1);
}

//Setup drawing window. Data sent to the display will fill the pixels of 
//the starting coordinate acording to the orientation set.
static void 
cfaf128x128x16SetWindow(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1){
	uint8_t bytes16[2];
	
	switch (_orientation) {
		case 0:
			x0 += 2;
			y0 += 3;
			x1 += 2;
			y1 += 3;
			break;
		case 1:
			x0 += 3;
			y0 += 2;
			x1 += 3;
			y1 += 2;
			break;
		case 2:
			x0 += 2;
			y0 += 1;
			x1 += 2;
			y1 += 1;
			break;
		case 3:
			x0 += 1;
			y0 += 2;
			x1 += 1;
			y1 += 2;
			break;
		default:
			break;
	}
	//Setup columns
	cfaf128x128x16WriteCommand(CM_CASET);
	bytes16[0] = (x0&0xFF00)>>8;
	bytes16[1] =  x0&0xFF;
	cfaf128x128x16WriteData(bytes16, 2);
	bytes16[0] = (x1&0xFF00)>>8;
	bytes16[1] =  x1&0xFF;
	cfaf128x128x16WriteData(bytes16, 2);

	//Setup rows
	cfaf128x128x16WriteCommand(CM_RASET);
	bytes16[0] = (y0&0xFF00)>>8;
	bytes16[1] =  y0&0xFF;
	cfaf128x128x16WriteData(bytes16, 2);
	bytes16[0] = (y1&0xFF00)>>8;
	bytes16[1] =  y1&0xFF;
	cfaf128x128x16WriteData(bytes16, 2);
	
	//Prepare to write to the display pixel matrix
	cfaf128x128x16WriteCommand(CM_RAMWR);
}

//Draws a rectangles with the given limits and color
void 
cfaf128x128x16Rect(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint32_t color){
	uint32_t t;	
	uint32_t hor_size;
	uint32_t ver_size;
	uint8_t	lowByte =   0x00FF & color;
	uint8_t	highByte = (0xFF00 & color)>>8;

	hor_size = x1 - x0 + 1;
	ver_size = y1 - y0 + 1;
		
	cfaf128x128x16SetWindow(x0, x1, y0, y1);
	
	ROM_GPIOPinWrite(DISPLAY_D_C_PORT, DISPLAY_D_C_PIN, DISPLAY_D_C_PIN);
	ROM_GPIOPinWrite(DISPLAY_CS_PORT, DISPLAY_CS_PIN, 0);
	for(t = (uint32_t) hor_size*ver_size; t>0; t--){
		cfaf128x128x16SsiTransfer(highByte);
		cfaf128x128x16SsiTransfer(lowByte);
	}
	ROM_GPIOPinWrite(DISPLAY_CS_PORT, DISPLAY_CS_PIN, DISPLAY_CS_PIN);
}

//Draws a vertical line with the given limits and color
void 
cfaf128x128x16LineVer(uint16_t x, uint16_t y0, uint16_t y1, uint16_t thickness, uint32_t color){
	cfaf128x128x16Rect(x, x+thickness, y0, y1, color);
}

//Draws a horizontal line with the given limits and color
void 
cfaf128x128x16LineHor(uint16_t x0, uint16_t x1, uint16_t y, uint16_t thickness, uint32_t color){
	cfaf128x128x16Rect(x0, x1, y, y+thickness, color);
}

//Draws a dot with the given coordinator and color
void
cfaf128x128x16Dot(uint16_t x, uint16_t y, uint16_t thickness, uint32_t color){
	cfaf128x128x16Rect(x, x+thickness, y, y+thickness, color);
}

//*****************************************************************************
//
//! Draws a pixel on the screen.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param i32X is the X coordinate of the pixel.
//! \param i32Y is the Y coordinate of the pixel.
//! \param ui32Value is the color of the pixel.
//!
//! This function sets the given pixel to a particular color.  The coordinates
//! of the pixel are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
static void
cfaf128x128x16PixelDraw(void *pvDisplayData, int32_t i32X, int32_t i32Y,
                      uint32_t ui32Value)
{
	cfaf128x128x16Dot(i32X, i32Y, 0, ui32Value);
}

//*****************************************************************************
//
//! Draws a horizontal sequence of pixels on the screen.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param i32X is the X coordinate of the first pixel.
//! \param i32Y is the Y coordinate of the first pixel.
//! \param i32X0 is sub-pixel offset within the pixel data, which is valid for 1
//! or 4 bit per pixel formats.
//! \param i32Count is the number of pixels to draw.
//! \param i32BPP is the number of bits per pixel; must be 1, 4, or 8 optionally
//! ORed with various flags unused by this driver.
//! \param pui8Data is a pointer to the pixel data.  For 1 and 4 bit per pixel
//! formats, the most significant bit(s) represent the left-most pixel.
//! \param pui8Palette is a pointer to the palette used to draw the pixels.
//!
//! This function draws a horizontal sequence of pixels on the screen, using
//! the supplied palette.  For 1 bit per pixel format, the palette contains
//! pre-translated colors; for 4 and 8 bit per pixel formats, the palette
//! contains 24-bit RGB values that must be translated before being written to
//! the display.
//!
//! \return None.
//
//*****************************************************************************
static void
cfaf128x128x16PixelDrawMultiple(void *pvDisplayData, int32_t i32X, int32_t i32Y, int32_t i32X0,
                              int32_t i32Count, int32_t i32BPP,
                              const uint8_t *pui8Data,
                              const uint8_t *pui8Palette)
{
	uint8_t	lowByte, highByte;
	uint32_t ui32Byte, color;
	cfaf128x128x16SetWindow(i32X, i32X + i32Count, i32Y, i32Y);

	ROM_GPIOPinWrite(DISPLAY_D_C_PORT, DISPLAY_D_C_PIN, DISPLAY_D_C_PIN);
	ROM_GPIOPinWrite(DISPLAY_CS_PORT, DISPLAY_CS_PIN, 0);
	
	// Determine how to interpret the pixel data based on the number of bits
	// per pixel.
	switch(i32BPP & ~GRLIB_DRIVER_FLAG_NEW_IMAGE) {
		// The pixel data is in 1 bit per pixel format.
		case 1:
			// Loop while there are more pixels to draw.
			while(i32Count){
				ui32Byte = *pui8Data++;
				// Loop through the pixels in this byte of image data.
				for(; (i32X0 < 8) && i32Count; i32X0++, i32Count--) {
					// Get the next byte of image data.
					color = ((uint32_t *)pui8Palette) [(ui32Byte >> (7 - i32X0)) & 1];
					// Draw this pixel in the appropriate color.
					lowByte =   0x00FF & color;
					highByte = (0xFF00 & color)>>8;
					cfaf128x128x16SsiTransfer(highByte);
					cfaf128x128x16SsiTransfer(lowByte);
				}
				// Start at the beginning of the next byte of image data.
				i32X0 = 0;
			}
			// The image data has been drawn.
			break;
		// The pixel data is in 4 bit per pixel format.
		case 4:
			// Loop while there are more pixels to draw.  "Duff's device" is
			// used to jump into the middle of the loop if the first nibble of
			// the pixel data should not be used.  Duff's device makes use of
			// the fact that a case statement is legal anywhere within a
			// sub-block of a switch statement.  See
			// http://en.wikipedia.org/wiki/Duff's_device for detailed
			// information about Duff's device.
			switch(i32X0 & 1){
				case 0:
					while(i32Count){
						// Get the upper nibble of the next byte of pixel data
						// and extract the corresponding entry from the
						// palette.
						ui32Byte = (*pui8Data >> 4) * 3;
						ui32Byte = (*(uint32_t *)(pui8Palette + ui32Byte) &
											0x00ffffff);
						// Translate this palette entry and write it to the
						// screen.
						color = DPYCOLORTRANSLATE(ui32Byte);
						lowByte =   0x00FF & color;
						highByte = (0xFF00 & color)>>8;
						cfaf128x128x16SsiTransfer(highByte);
						cfaf128x128x16SsiTransfer(lowByte);
						// Decrement the count of pixels to draw.
						i32Count--;
						// See if there is another pixel to draw.
						if(i32Count) {
				case 1:
							// Get the lower nibble of the next byte of pixel
							// data and extract the corresponding entry from
							// the palette.
							ui32Byte = (*pui8Data++ & 15) * 3;
							ui32Byte = (*(uint32_t *)(pui8Palette + ui32Byte) &
											0x00ffffff);
							// Translate this palette entry and write it to the
							// screen.
							color = DPYCOLORTRANSLATE(ui32Byte);
							lowByte =   0x00FF & color;
							highByte = (0xFF00 & color)>>8;
							cfaf128x128x16SsiTransfer(highByte);
							cfaf128x128x16SsiTransfer(lowByte);
							// Decrement the count of pixels to draw.
							i32Count--;
						}
					}
			}
			// The image data has been drawn.
			break;
		// The pixel data is in 8 bit per pixel format.
		case 8:
			while(i32Count--) {
				// Get the next byte of pixel data and extract the
				// corresponding entry from the palette.				
				ui32Byte = *pui8Data++ * 3;
				ui32Byte = *(uint32_t *)(pui8Palette + ui32Byte) & 0x00ffffff;
				// Translate this palette entry and write it to the screen.
				color = DPYCOLORTRANSLATE(ui32Byte);
				lowByte =   0x00FF & color;
				highByte = (0xFF00 & color)>>8;
				cfaf128x128x16SsiTransfer(highByte);
				cfaf128x128x16SsiTransfer(lowByte);
			}
			// The image data has been drawn.
			break;
		// We are being passed data in the display's native format.  Merely
		// write it directly to the display.  This is a special case which is
		// not used by the graphics library but which is helpful to
		// applications which may want to handle, for example, JPEG images.
		case 16:
			// Loop while there are more pixels to draw.
			while(i32Count--) {
				// Get the next byte of pixel data and extract the
				// corresponding entry from the palette.
				ui32Byte = *((uint16_t*) pui8Data);
				pui8Data += 2;
				// Translate this palette entry and write it to the screen.
				lowByte =   0x00FF & ui32Byte;
				highByte = (0xFF00 & ui32Byte)>>8;
				cfaf128x128x16SsiTransfer(highByte);
				cfaf128x128x16SsiTransfer(lowByte);
			}
			// The image data has been drawn.
			break;
	}
	ROM_GPIOPinWrite(DISPLAY_CS_PORT, DISPLAY_CS_PIN, DISPLAY_CS_PIN);
}

//*****************************************************************************
//
//! Draws a horizontal line.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param i32X1 is the X coordinate of the start of the line.
//! \param i32X2 is the X coordinate of the end of the line.
//! \param i32Y is the Y coordinate of the line.
//! \param ui32Value is the color of the line.
//!
//! This function draws a horizontal line on the display.  The coordinates of
//! the line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
static void
cfaf128x128x16LineDrawH(void *pvDisplayData, int32_t i32X1, int32_t i32X2, int32_t i32Y,
                      uint32_t ui32Value)
{
	if(i32X1 > i32X2) swap_i32(&i32X1, &i32X2);
	cfaf128x128x16LineHor(i32X1, i32X2, i32Y, 0, ui32Value);
}

//*****************************************************************************
//
//! Draws a vertical line.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param i32X is the X coordinate of the line.
//! \param i32Y1 is the Y coordinate of the start of the line.
//! \param i32Y2 is the Y coordinate of the end of the line.
//! \param ui32Value is the color of the line.
//!
//! This function draws a vertical line on the display.  The coordinates of the
//! line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
static void
cfaf128x128x16LineDrawV(void *pvDisplayData, int32_t i32X, int32_t i32Y1, int32_t i32Y2,
                      uint32_t ui32Value)
{
	if(i32Y1 > i32Y2) swap_i32(&i32Y1, &i32Y2);
	cfaf128x128x16LineVer(i32X, i32Y1, i32Y2, 0, ui32Value);
}

//*****************************************************************************
//
//! Fills a rectangle.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param pRect is a pointer to the structure describing the rectangle.
//! \param ui32Value is the color of the rectangle.
//!
//! This function fills a rectangle on the display.  The coordinates of the
//! rectangle are assumed to be within the extents of the display, and the
//! rectangle specification is fully inclusive (in other words, both i16XMin and
//! i16XMax are drawn, aint32_t with i16YMin and i16YMax).
//!
//! \return None.
//
//*****************************************************************************
static void
cfaf128x128x16RectFill(void *pvDisplayData, const tRectangle *pRect,
                     uint32_t ui32Value)
{
	uint16_t x0 = pRect->i16XMin;
	uint16_t x1 = pRect->i16XMax;
	uint16_t y0 = pRect->i16YMin;
	uint16_t y1 = pRect->i16YMax;
	
	if(x0 > x1) swap_ui16(&x0, &x1);
	if(y0 > y1) swap_ui16(&y0, &y1);
	cfaf128x128x16Rect(x0, x1, y0, y1, ui32Value);
}

//*****************************************************************************
//
//! Translates a 24-bit RGB color to a display driver-specific color.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param ui32Value is the 24-bit RGB color.  The least-significant byte is the
//! blue channel, the next byte is the green channel, and the third byte is the
//! red channel.
//!
//! This function translates a 24-bit RGB color into a value that can be
//! written into the display's frame buffer in order to reproduce that color,
//! or the closest possible approximation of that color.
//!
//! \return Returns the display-driver specific color.
//
//*****************************************************************************
static uint32_t
cfaf128x128x16ColorTranslate(void *pvDisplayData, uint32_t ui32Value)
{
    // Translate from a 24-bit RGB color to a 3-3-2 RGB color.
    return(DPYCOLORTRANSLATE(ui32Value));
}

//*****************************************************************************
//
//! Flushes any cached drawing operations.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//!
//! This functions flushes any cached drawing operations to the display.  This
//! is useful when a local frame buffer is used for drawing operations, and the
//! flush would copy the local frame buffer to the display.  Since no memory
//! based frame buffer is used for this driver, the flush is a no operation.
//!
//! \return None.
//
//*****************************************************************************
static void
cfaf128x128x16Flush(void *pvDisplayData)
{
    //
    // There is nothing to be done.
    //
}

//*****************************************************************************
//
//! The display structure that describes the driver for the Crystalfontz
//! CFAF128128B-0145T panel with ST7735 controller.
//
//*****************************************************************************
const tDisplay g_sCfaf128x128x16 =
{
    sizeof(tDisplay),
    0,
    DISPLAY_WIDTH,
    DISPLAY_HEIGHT,
    cfaf128x128x16PixelDraw,
    cfaf128x128x16PixelDrawMultiple,
    cfaf128x128x16LineDrawH,
    cfaf128x128x16LineDrawV,
    cfaf128x128x16RectFill,
    cfaf128x128x16ColorTranslate,
    cfaf128x128x16Flush
};

//Set the orientation for the rect filling
void 
cfaf128x128x16SetOrientation(uint8_t orientation){
	uint8_t data = 0;
	
	_orientation = orientation & 0x11; //%4	
	
	cfaf128x128x16WriteCommand(CM_MADCTL);
	switch (orientation){
		case 0:
			data = CM_MADCTL_MX | CM_MADCTL_MY | CM_MADCTL_RGB;
			break;
		case 1:
			data = CM_MADCTL_MY | CM_MADCTL_MV | CM_MADCTL_RGB;
			break;
		case 2:
			data = CM_MADCTL_RGB;
			break;
		case 3:
			data = CM_MADCTL_MX | CM_MADCTL_MV | CM_MADCTL_RGB;
			break;
	}
	cfaf128x128x16WriteData(&data, 1);
}

//Clear screen with solid color
void 
cfaf128x128x16ClearColor(uint16_t color) {
	uint8_t lastOrientation = _orientation;
	
	cfaf128x128x16SetOrientation(0);
	cfaf128x128x16Rect(0, DISPLAY_WIDTH-1, 0, DISPLAY_HEIGHT-1, color);
	cfaf128x128x16SetOrientation(lastOrientation);
}

//Clear screen with black color
void
cfaf128x128x16Clear(){
	cfaf128x128x16ClearColor(blackColor);
}

//Set SSI data mode
static void 
ssiSetDataMode(uint8_t mode) {
	HWREG(DISPLAY_SSI_BASE + SSI_O_CR0) &= ~(SSI_CR0_SPO | SSI_CR0_SPH);
	HWREG(DISPLAY_SSI_BASE + SSI_O_CR0) |= mode;
}

//Set SSI clock divider
static void
ssiSetClockDivider(uint8_t divider){
  //value must be even
  HWREG(DISPLAY_SSI_BASE + SSI_O_CPSR) = divider;
}

//Initialiaze SSI comunication configuration
void
InitSSICom(void){
	uint32_t initialData = 0;
	g_ui32SysClock = __SysCtlClockGet();
	
	// Enable the peripherals used by this driver
	ROM_SysCtlPeripheralEnable(DISPLAY_SSI_PERIPH);
	ROM_SysCtlPeripheralEnable(DISPLAY_SSI_GPIO_PERIPH);

	ROM_GPIOPinConfigure(DISPLAY_PINCFG_SSICLK);
	ROM_GPIOPinConfigure(DISPLAY_PINCFG_SSIFSS);
	ROM_GPIOPinConfigure(DISPLAY_PINCFG_SSITX);
	ROM_GPIOPinConfigure(DISPLAY_PINCFG_SSIRX);
	
	ROM_GPIOPinTypeSSI(DISPLAY_SSI_PORT, DISPLAY_SSI_PINS);
	
	ROM_SSIClockSourceSet(DISPLAY_SSI_BASE, SSI_CLOCK_PIOSC);
	ROM_SSIConfigSetExpClk(DISPLAY_SSI_BASE, g_ui32SysClock, 
		SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, DISPLAY_SSI_CLOCK, 8);

	ROM_SSIEnable(DISPLAY_SSI_BASE);
	while(ROM_SSIDataGetNonBlocking(DISPLAY_SSI_BASE, &initialData));
}

//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the ST7735S display controller on the panel,
//! preparing it to display data.
//!
//! \return None.
//
//*****************************************************************************
void
cfaf128x128x16Init(void)
{	
	InitSSICom();
	//ssiSetClockDivider(2);
	//ssiSetDataMode(0);

	ROM_SysCtlPeripheralEnable(DISPLAY_RST_GPIO_PERIPH);
	ROM_SysCtlPeripheralEnable(DISPLAY_C_D_GPIO_PERIPH);
	ROM_SysCtlPeripheralEnable(DISPLAY_CS_GPIO_PERIPH);
	
	//ROM_GPIOPinConfigure();
		
	// Configure display control pins as GPIO output
	ROM_GPIOPinTypeGPIOOutput(DISPLAY_RST_PORT, DISPLAY_RST_PIN);
	ROM_GPIOPinTypeGPIOOutput(DISPLAY_D_C_PORT, DISPLAY_D_C_PIN);
	ROM_GPIOPinTypeGPIOOutput(DISPLAY_CS_PORT,  DISPLAY_CS_PIN);
	
	//-----------------
	//Backlight configuration - lacking for now
	//-----------------
	
	//Display reset
	ROM_GPIOPinWrite(DISPLAY_RST_PORT, DISPLAY_RST_PIN, DISPLAY_RST_PIN);
	delay(100);	
	ROM_GPIOPinWrite(DISPLAY_RST_PORT, DISPLAY_RST_PIN, 0);
	delay(50);
	ROM_GPIOPinWrite(DISPLAY_RST_PORT, DISPLAY_RST_PIN, DISPLAY_RST_PIN);
	delay(120);
	
	//Display initialization command set
	cfaf128x128x16WriteCommand(CM_SWRESET);
	delay(150);
	cfaf128x128x16WriteCommand(CM_SLPOUT);
	delay(200);
	cfaf128x128x16WriteRegister(CM_GAMSET, 0x04);
	cfaf128x128x16WriteCommand(CM_SETPWCTR);
	cfaf128x128x16WriteData((const uint8_t*)"\x0A\x14", 2);
	cfaf128x128x16WriteCommand(CM_SETSTBA);
	cfaf128x128x16WriteData((const uint8_t*)"\x0A\x00", 2);
	cfaf128x128x16WriteRegister(CM_COLMOD, 0x05);
	delay(10);
	cfaf128x128x16WriteRegister(CM_MADCTL, CM_MADCTL_RGB);
	cfaf128x128x16WriteCommand(CM_CASET);
	cfaf128x128x16WriteData((const uint8_t*)"\x00\x00\x00\x79", 4);
	cfaf128x128x16WriteCommand(CM_RASET);
	cfaf128x128x16WriteData((const uint8_t*)"\x00\x00\x00\x79", 4);
	cfaf128x128x16WriteCommand(CM_NORON);
	delay(10);
	cfaf128x128x16WriteCommand(CM_DISPON);
	
	delay(120);
	cfaf128x128x16WriteCommand(CM_RAMWR);
	//Set backlight - if there's any
	cfaf128x128x16SetOrientation(0);
	cfaf128x128x16Clear();
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************