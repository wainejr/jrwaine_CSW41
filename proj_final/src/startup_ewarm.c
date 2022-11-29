/*__________________________________________________________________________________
|       Embedded Systems Course - 2022
|       Prof. Douglas Renaux
| __________________________________________________________________________________
|
|		The original file by Texas Instruments (see comments below) was 
|       significantly modified, based on IAR's cstartup_M.c.
|       The resulting file is targeted for Tiva TM4C1294XL. 
|       Each of the systems exceptions has its own __weak Handler.
| __________________________________________________________________________________
*/


//*****************************************************************************
//
// startup_ewarm.c - Startup code for use with IAR's Embedded Workbench,
//                   version 5.
//
// Copyright (c) 2013-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************



//*****************************************************************************
//
// Enable the IAR extensions for this source file.
// A CSTACK block must be created by the linker config
//
//*****************************************************************************
#pragma language=extended

#pragma segment="CSTACK"

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
extern __weak void Reset(void);
extern __weak void NMI_Handler(void);
extern __weak void HardFault_Handler(void);
extern __weak void MemManage_Handler(void);
extern __weak void BusFault_Handler(void);
extern __weak void UsageFault_Handler(void);
extern __weak void SVC_Handler(void);
extern __weak void DebugMon_Handler(void);
extern __weak void PendSV_Handler(void);
extern __weak void SysTick_Handler(void);
extern __weak void IntDefaultHandler(void);

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
//extern void ADC0SS3IntHandler(void);
//extern void ADC1SS3IntHandler(void);

//*****************************************************************************
//
// The entry point for the application startup code.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" void __iar_program_start(void);
#else
extern void __iar_program_start(void);
#endif

//*****************************************************************************
//
// A union that describes the entries of the vector table.  The union is needed
// since the first entry is the stack pointer and the remainder are function
// pointers.
//
//*****************************************************************************
typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
#pragma location = ".intvec"
__root const intvec_elem __vector_table[] =
{
    { .__ptr = __sfe( "CSTACK" ) },         // 0-The initial stack pointer
    __iar_program_start,                    // 1-Execution start after RESET
    NMI_Handler,                            // 2-The NMI handler
    HardFault_Handler,                      // 3-The hard fault handler
    MemManage_Handler,                      // 4-The MPU fault handler
    BusFault_Handler,                       // 5-The bus fault handler
    UsageFault_Handler,                     // 6-The usage fault handler
    0,                                      // 7-Reserved
    0,                                      // 8-Reserved
    0,                                      // 9-Reserved
    0,                                      // 10-Reserved
    SVC_Handler,                            // 11-SVCall handler
    DebugMon_Handler,                       // 12-Debug monitor handler
    0,                                      // 13-Reserved
    PendSV_Handler,                         // 14-The PendSV handler
    SysTick_Handler,                        // 15-The SysTick handler
    
    //Interrupts                            exception number:                    IRQ number
    IntDefaultHandler,                      // 16-GPIO Port A                ;   0 GPIO Port A
    IntDefaultHandler,                      // 17-GPIO Port B                ;   1 GPIO Port B
    IntDefaultHandler,                      // 18-GPIO Port C                ;   2 GPIO Port C
    IntDefaultHandler,                      // 19-GPIO Port D                ;   3 GPIO Port D
    IntDefaultHandler,                      // 20-GPIO Port E                ;   4 GPIO Port E
    IntDefaultHandler,                      // 21-21-UART0 Rx and Tx         ;   5 UART0 Rx and Tx
    IntDefaultHandler,                      // 22-UART1 Rx and Tx            ;   6 UART1 Rx and Tx
    IntDefaultHandler,                      // 23-SSI0 Rx and Tx             ;   7 SSI0 Rx and Tx
    IntDefaultHandler,                      // 24-I2C0 Master and Slave      ;   8 I2C0 Master and Slave
    IntDefaultHandler,                      // 25-PWM Fault                  ;   9 PWM0 Fault
    IntDefaultHandler,                      // 26P-WM Generator 0            ;  10 PWM0 Generator 0
    IntDefaultHandler,                      // 27P-WM Generator 1            ;  11 PWM0 Generator 1
    IntDefaultHandler,                      // 28P-WM Generator 2            ;  12 PWM0 Generator 2
    IntDefaultHandler,                      // 29-Quadrature Encoder 0       ;  13 Quadrature Encoder 0
    IntDefaultHandler,                      // 30-ADC Sequence 0             ;  14 ADC Sequence 0
    IntDefaultHandler,                      // 31-ADC Sequence 1             ;  15 ADC Sequence 1
    IntDefaultHandler,                      // 32-ADC Sequence 2             ;  16 ADC Sequence 2
    IntDefaultHandler,                      // 33-ADC Sequence 3             ;  17 ADC Sequence 3
    IntDefaultHandler,                      // 34-Watchdog timer             ;  18 Watchdog timer 0
    IntDefaultHandler,                      // 35-Timer 0 subtimer A         ;  19 Timer 0 subtimer A
    IntDefaultHandler,                      // 36-Timer 0 subtimer B         ;  20 Timer 0 subtimer B
    IntDefaultHandler,                      // 37-Timer 1 subtimer A         ;  21 Timer 1 subtimer A
    IntDefaultHandler,                      // 38-Timer 1 subtimer B         ;  22 Timer 1 subtimer B
    IntDefaultHandler,                      // 39-Timer 2 subtimer A         ;  23 Timer 2 subtimer A
    IntDefaultHandler,                      // 40-Timer 2 subtimer B         ;  24 Timer 2 subtimer B
    IntDefaultHandler,                      // 41-Analog Comparator 0        ;  25 Analog Comparator 0
    IntDefaultHandler,                      // 42-Analog Comparator 1        ;  26 Analog Comparator 1
    IntDefaultHandler,                      // 43-Analog Comparator 2        ;  27 Analog Comparator 2
    IntDefaultHandler,                      // 44-System Control(PLL,OSC,BO) ;  28 System Control (PLL, OSC, BO
    IntDefaultHandler,                      // 45-FLASH Control              ;  29 FLASH Control
    IntDefaultHandler,                      // 46-GPIO Port F                ;  30 GPIO Port F
    IntDefaultHandler,                      // 47-GPIO Port G                ;  31 GPIO Port G
    IntDefaultHandler,                      // 48-GPIO Port H                ;  32 GPIO Port H
    IntDefaultHandler,                      // 49-UART2 Rx and Tx            ;  33 UART2 Rx and Tx
    IntDefaultHandler,                      // 50-SSI1 Rx and Tx             ;  34 SSI1 Rx and Tx
    IntDefaultHandler,                      // 51-Timer 3 subtimer A         ;  35 Timer 3 subtimer A
    IntDefaultHandler,                      // 52-Timer 3 subtimer B         ;  36 Timer 3 subtimer B
    IntDefaultHandler,                      // 53-I2C1 Master and Slave      ;  37 I2C1 Master and Slave
    IntDefaultHandler,                      // 54-CAN0                       ;  38 CAN0
    IntDefaultHandler,                      // 55-CAN1                       ;  39 CAN1
    IntDefaultHandler,                      // 56-Ethernet                   ;  40 Ethernet
    IntDefaultHandler,                      // 57-Hibernate                  ;  41 Hibernate
    IntDefaultHandler,                      // 58-USB0                       ;  42 USB0
    IntDefaultHandler,                      // 59-PWM Generator 3            ;  43 PWM0 Generator 3
    IntDefaultHandler,                      // 60-uDMA Software Transfer     ;  44 uDMA Software Transfer
    IntDefaultHandler,                      // 61-uDMA Error                 ;  45 uDMA Error
    IntDefaultHandler,                      // 62-ADC1 Sequence 0            ;  46 ADC1 Sequence 0
    IntDefaultHandler,                      // 63-ADC1 Sequence 1            ;  47 ADC1 Sequence 1
    IntDefaultHandler,                      // 64-ADC1 Sequence 2            ;  48 ADC1 Sequence 2
    IntDefaultHandler,                      // 65-ADC1 Sequence 3            ;  49 ADC1 Sequence 3
    IntDefaultHandler,                      // 66-External Bus Interface 0   ;  50 External Bus Interface 0
    IntDefaultHandler,                      // 67-GPIO Port J                ;  51 GPIO Port J
    IntDefaultHandler,                      // 68-GPIO Port K                ;  52 GPIO Port K
    IntDefaultHandler,                      // 69-GPIO Port L                ;  53 GPIO Port L
    IntDefaultHandler,                      // 70-SSI2 Rx and Tx             ;  54 SSI2 Rx and Tx
    IntDefaultHandler,                      // 71-SSI3 Rx and Tx             ;  55 SSI3 Rx and Tx
    IntDefaultHandler,                      // 72-UART3 Rx and Tx            ;  56 UART3 Rx and Tx
    IntDefaultHandler,                      // 73-UART4 Rx and Tx            ;  57 UART4 Rx and Tx
    IntDefaultHandler,                      // 74-UART5 Rx and Tx            ;  58 UART5 Rx and Tx
    IntDefaultHandler,                      // 75-UART6 Rx and Tx            ;  59 UART6 Rx and Tx
    IntDefaultHandler,                      // 76-UART7 Rx and Tx            ;  60 UART7 Rx and Tx
    IntDefaultHandler,                      // 77-I2C2 Master and Slave      ;  61 I2C2 Master and Slave
    IntDefaultHandler,                      // 78-I2C3 Master and Slave      ;  62 I2C3 Master and Slave
    IntDefaultHandler,                      // 79-Timer 4 subtimer A         ;  63 Timer 4 subtimer A
    IntDefaultHandler,                      // 80-Timer 4 subtimer B         ;  64 Timer 4 subtimer B
    IntDefaultHandler,                      // 81-Timer 5 subtimer A         ;  65 Timer 5 subtimer A
    IntDefaultHandler,                      // 82-Timer 5 subtimer B         ;  66 Timer 5 subtimer B
    IntDefaultHandler,                      // 83-FPU                        ;  67 FPU
    0,                                      // 84-Reserved                   ;  68 Reserved
    0,                                      // 85-Reserved                   ;  69 Reserved
    IntDefaultHandler,                      // 86-I2C4 Master and Slave      ;  70 I2C4 Master and Slave
    IntDefaultHandler,                      // 87-I2C5 Master and Slave      ;  71 I2C5 Master and Slave
    IntDefaultHandler,                      // 88-GPIO Port M                ;  72 GPIO Port M
    IntDefaultHandler,                      // 89-GPIO Port N                ;  73 GPIO Port N
    0,                                      // 90-Reserved                   ;  74 Reserved
    IntDefaultHandler,                      // 91-Tamper                     ;  75 Tamper
    IntDefaultHandler,                      // 92-GPIO Port P (Summary or P0);  76 GPIO Port P (Summary or P0)
    IntDefaultHandler,                      // 93-GPIO Port P1               ;  77 GPIO Port P1
    IntDefaultHandler,                      // 94-GPIO Port P2               ;  78 GPIO Port P2
    IntDefaultHandler,                      // 95-GPIO Port P3               ;  79 GPIO Port P3
    IntDefaultHandler,                      // 96-GPIO Port P4               ;  80 GPIO Port P4
    IntDefaultHandler,                      // 97-GPIO Port P5               ;  81 GPIO Port P5
    IntDefaultHandler,                      // 98-GPIO Port P6               ;  82 GPIO Port P6
    IntDefaultHandler,                      // 99-GPIO Port P7               ;  83 GPIO Port P7
    IntDefaultHandler,                      // 100-GPIO Port Q (Summ. or Q0) ;  84 GPIO Port Q (Summary or Q0)
    IntDefaultHandler,                      // 101-GPIO Port Q1              ;  85 GPIO Port Q1
    IntDefaultHandler,                      // 102-GPIO Port Q2              ;  86 GPIO Port Q2
    IntDefaultHandler,                      // 103-GPIO Port Q3              ;  87 GPIO Port Q3
    IntDefaultHandler,                      // 104-GPIO Port Q4              ;  88 GPIO Port Q4
    IntDefaultHandler,                      // 105-GPIO Port Q5              ;  89 GPIO Port Q5
    IntDefaultHandler,                      // 106-GPIO Port Q6              ;  90 GPIO Port Q6
    IntDefaultHandler,                      // 107-GPIO Port Q7              ;  91 GPIO Port Q7
    IntDefaultHandler,                      // 108-GPIO Port R               ;  92 Reserved
    IntDefaultHandler,                      // 109-GPIO Port S               ;  93 Reserved
    IntDefaultHandler,                      // 110-SHA/MD5 0                 ;  94 Reserved
    IntDefaultHandler,                      // 111-AES 0                     ;  95 Reserved
    IntDefaultHandler,                      // 112-DES3DES 0                 ;  96 Reserved
    IntDefaultHandler,                      // 113-LCD Controller 0          ;  97 Reserved
    IntDefaultHandler,                      // 114-Timer 6 subtimer A        ;  98 Timer 6 subtimer A
    IntDefaultHandler,                      // 115-Timer 6 subtimer B        ;  99 Timer 6 subtimer B
    IntDefaultHandler,                      // 116-Timer 7 subtimer A        ; 100 Timer 7 subtimer A
    IntDefaultHandler,                      // 117-Timer 7 subtimer B        ; 101 Timer 7 subtimer B
    IntDefaultHandler,                      // 118-I2C6 Master and Slave     ; 102 I2C6 Master and Slave
    IntDefaultHandler,                      // 119-I2C7 Master and Slave     ; 103 I2C7 Master and Slave
    IntDefaultHandler,                      // 120-HIM Scan Matrix Keyboard 0; 104 Reserved
    IntDefaultHandler,                      // 121-One Wire 0                ; 105 Reserved
    IntDefaultHandler,                      // 122-HIM PS/2 0                ; 106 Reserved
    IntDefaultHandler,                      // 123-HIM LED Sequencer 0       ; 107 Reserved
    IntDefaultHandler,                      // 124-HIM Consumer IR 0         ; 108 Reserved
    IntDefaultHandler,                      // 125-I2C8 Master and Slave     ; 109 I2C8 Master and Slave
    IntDefaultHandler,                      // 126-I2C9 Master and Slave     ; 110 I2C9 Master and Slave
    IntDefaultHandler                       // 127-GPIO Port T               ; 111 Reserved
    // interrupts 112-224 are not defined in the exception vector !
};                                                                          

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
__weak void
NMI_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
HardFault_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a .
// This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
MemManage_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a .
// This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
BusFault_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a .
// This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
UsageFault_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}


//*****************************************************************************
//
// This is the code that gets called when the processor receives a .
// This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
SVC_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}


//*****************************************************************************
//
// This is the code that gets called when the processor receives a .
// This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
DebugMon_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}


//*****************************************************************************
//
// This is the code that gets called when the processor receives a .
// This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
PendSV_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}


//*****************************************************************************
//
// This is the code that gets called when the processor receives a .
// This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
SysTick_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}