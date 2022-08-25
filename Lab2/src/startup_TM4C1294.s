;/******************************************************************************
; * @file     startup_TM4C1294.s (based on startup_ARMCM4.s & startup_TM4C129.s)
; * @brief    CMSIS Core Device Startup File for
; *                   TM4C1294 Device
; * @version  V5.3.1
; * @date     11. August 2019 (modified by Hugo Vieira Neto)
; ******************************************************************************/
;/*
; * Copyright (c) 2009-2018 ARM Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table
                PUBLIC  __vector_table_0x1c
                PUBLIC  __Vectors
                PUBLIC  __Vectors_End
                PUBLIC  __Vectors_Size

                DATA

__vector_table
                DCD     sfe(CSTACK)         ;     Top of Stack
                DCD     Reset_Handler       ;     Reset Handler
                DCD     NMI_Handler         ; -14 NMI Handler
                DCD     HardFault_Handler   ; -13 Hard Fault Handler
                DCD     MemManage_Handler   ; -12 MPU Fault Handler
                DCD     BusFault_Handler    ; -11 Bus Fault Handler
                DCD     UsageFault_Handler  ; -10 Usage Fault Handler
__vector_table_0x1c
                DCD     0                   ;     Reserved
                DCD     0                   ;     Reserved
                DCD     0                   ;     Reserved
                DCD     0                   ;     Reserved
                DCD     SVC_Handler         ;  -5 SVCall Handler
                DCD     DebugMon_Handler    ;  -4 Debug Monitor Handler
                DCD     0                   ;     Reserved
                DCD     PendSV_Handler      ;  -2 PendSV Handler
                DCD     SysTick_Handler     ;  -1 SysTick Handler

                ; Interrupts
                DCD     GPIOA_Handler       ;    0 GPIO Port A
                DCD     GPIOB_Handler       ;    1 GPIO Port B
                DCD     GPIOC_Handler       ;    2 GPIO Port C
                DCD     GPIOD_Handler       ;    3 GPIO Port D
                DCD     GPIOE_Handler       ;    4 GPIO Port E
                DCD     UART0_Handler       ;    5 UART0 Rx and Tx
                DCD     UART1_Handler       ;    6 UART1 Rx and Tx
                DCD     SSI0_Handler        ;    7 SSI0 Rx and Tx
                DCD     I2C0_Handler        ;    8 I2C0 Master and Slave
                DCD     PMW0_FAULT_Handler  ;    9 PWM0 Fault
                DCD     PWM0_0_Handler      ;   10 PWM0 Generator 0
                DCD     PWM0_1_Handler      ;   11 PWM0 Generator 1
                DCD     PWM0_2_Handler      ;   12 PWM0 Generator 2
                DCD     QEI0_Handler        ;   13 Quadrature Encoder 0
                DCD     ADC0SS0_Handler     ;   14 ADC Sequence 0
                DCD     ADC0SS1_Handler     ;   15 ADC Sequence 1
                DCD     ADC0SS2_Handler     ;   16 ADC Sequence 2
                DCD     ADC0SS3_Handler     ;   17 ADC Sequence 3
                DCD     WDT0_Handler        ;   18 Watchdog timer 0
                DCD     TIMER0A_Handler     ;   19 Timer 0 subtimer A
                DCD     TIMER0B_Handler     ;   20 Timer 0 subtimer B
                DCD     TIMER1A_Handler     ;   21 Timer 1 subtimer A
                DCD     TIMER1B_Handler     ;   22 Timer 1 subtimer B
                DCD     TIMER2A_Handler     ;   23 Timer 2 subtimer A
                DCD     TIMER2B_Handler     ;   24 Timer 2 subtimer B
                DCD     COMP0_Handler       ;   25 Analog Comparator 0
                DCD     COMP1_Handler       ;   26 Analog Comparator 1
                DCD     COMP2_Handler       ;   27 Analog Comparator 2
                DCD     SYSCTL_Handler      ;   28 System Control (PLL, OSC, BO)
                DCD     FLASH_Handler       ;   29 FLASH Control
                DCD     GPIOF_Handler       ;   30 GPIO Port F
                DCD     GPIOG_Handler       ;   31 GPIO Port G
                DCD     GPIOH_Handler       ;   32 GPIO Port H
                DCD     UART2_Handler       ;   33 UART2 Rx and Tx
                DCD     SSI1_Handler        ;   34 SSI1 Rx and Tx
                DCD     TIMER3A_Handler     ;   35 Timer 3 subtimer A
                DCD     TIMER3B_Handler     ;   36 Timer 3 subtimer B
                DCD     I2C1_Handler        ;   37 I2C1 Master and Slave
                DCD     CAN0_Handler        ;   38 CAN0
                DCD     CAN1_Handler        ;   39 CAN1
                DCD     ETH_Handler         ;   40 Ethernet
                DCD     HIB_Handler         ;   41 Hibernate
                DCD     USB0_Handler        ;   42 USB0
                DCD     PWM0_3_Handler      ;   43 PWM0 Generator 3
                DCD     UDMA_Handler        ;   44 uDMA Software Transfer
                DCD     UDMAERR_Handler     ;   45 uDMA Error
                DCD     ADC1SS0_Handler     ;   46 ADC1 Sequence 0
                DCD     ADC1SS1_Handler     ;   47 ADC1 Sequence 1
                DCD     ADC1SS2_Handler     ;   48 ADC1 Sequence 2
                DCD     ADC1SS3_Handler     ;   49 ADC1 Sequence 3
                DCD     EBI0_Handler        ;   50 External Bus Interface 0
                DCD     GPIOJ_Handler       ;   51 GPIO Port J
                DCD     GPIOK_Handler       ;   52 GPIO Port K
                DCD     GPIOL_Handler       ;   53 GPIO Port L
                DCD     SSI2_Handler        ;   54 SSI2 Rx and Tx
                DCD     SSI3_Handler        ;   55 SSI3 Rx and Tx
                DCD     UART3_Handler       ;   56 UART3 Rx and Tx
                DCD     UART4_Handler       ;   57 UART4 Rx and Tx
                DCD     UART5_Handler       ;   58 UART5 Rx and Tx
                DCD     UART6_Handler       ;   59 UART6 Rx and Tx
                DCD     UART7_Handler       ;   60 UART7 Rx and Tx
                DCD     I2C2_Handler        ;   61 I2C2 Master and Slave
                DCD     I2C3_Handler        ;   62 I2C3 Master and Slave
                DCD     TIMER4A_Handler     ;   63 Timer 4 subtimer A
                DCD     TIMER4B_Handler     ;   64 Timer 4 subtimer B
                DCD     TIMER5A_Handler     ;   65 Timer 5 subtimer A
                DCD     TIMER5B_Handler     ;   66 Timer 5 subtimer B
                DCD     FPU_Handler         ;   67 FPU
                DCD     0                   ;   68 Reserved
                DCD     0                   ;   69 Reserved
                DCD     I2C4_Handler        ;   70 I2C4 Master and Slave
                DCD     I2C5_Handler        ;   71 I2C5 Master and Slave
                DCD     GPIOM_Handler       ;   72 GPIO Port M
                DCD     GPION_Handler       ;   73 GPIO Port N
                DCD     0                   ;   74 Reserved
                DCD     TAMPER_Handler      ;   75 Tamper
                DCD     GPIOP0_Handler      ;   76 GPIO Port P (Summary or P0)
                DCD     GPIOP1_Handler      ;   77 GPIO Port P1
                DCD     GPIOP2_Handler      ;   78 GPIO Port P2
                DCD     GPIOP3_Handler      ;   79 GPIO Port P3
                DCD     GPIOP4_Handler      ;   80 GPIO Port P4
                DCD     GPIOP5_Handler      ;   81 GPIO Port P5
                DCD     GPIOP6_Handler      ;   82 GPIO Port P6
                DCD     GPIOP7_Handler      ;   83 GPIO Port P7
                DCD     GPIOQ0_Handler      ;   84 GPIO Port Q (Summary or Q0)
                DCD     GPIOQ1_Handler      ;   85 GPIO Port Q1
                DCD     GPIOQ2_Handler      ;   86 GPIO Port Q2
                DCD     GPIOQ3_Handler      ;   87 GPIO Port Q3
                DCD     GPIOQ4_Handler      ;   88 GPIO Port Q4
                DCD     GPIOQ5_Handler      ;   89 GPIO Port Q5
                DCD     GPIOQ6_Handler      ;   90 GPIO Port Q6
                DCD     GPIOQ7_Handler      ;   91 GPIO Port Q7
                DCD     0                   ;   92 Reserved
                DCD     0                   ;   93 Reserved
                DCD     0                   ;   94 Reserved
                DCD     0                   ;   95 Reserved
                DCD     0                   ;   96 Reserved
                DCD     0                   ;   97 Reserved
                DCD     TIMER6A_Handler     ;   98 Timer 6 subtimer A
                DCD     TIMER6B_Handler     ;   99 Timer 6 subtimer B
                DCD     TIMER7A_Handler     ;  100 Timer 7 subtimer A
                DCD     TIMER7B_Handler     ;  101 Timer 7 subtimer B
                DCD     I2C6_Handler        ;  102 I2C6 Master and Slave
                DCD     I2C7_Handler        ;  103 I2C7 Master and Slave
                DCD     0                   ;  104 Reserved
                DCD     0                   ;  105 Reserved
                DCD     0                   ;  106 Reserved
                DCD     0                   ;  107 Reserved
                DCD     0                   ;  108 Reserved
                DCD     I2C8_Handler        ;  109 I2C8 Master and Slave
                DCD     I2C9_Handler        ;  110 I2C9 Master and Slave
                DCD     0                   ;  111 Reserved
                DCD     0                   ;  112 Reserved
                DCD     0                   ;  113 Reserved

                DS32    (110)               ; Interrupts 114 .. 224 are left out
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


                THUMB

                PUBWEAK Reset_Handler
                SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK __iar_init_vfp
__iar_init_vfp
                BX      LR                  ; FPU init is left to SytemInit()


                PUBWEAK NMI_Handler
                PUBWEAK HardFault_Handler
                PUBWEAK MemManage_Handler
                PUBWEAK BusFault_Handler
                PUBWEAK UsageFault_Handler
                PUBWEAK SVC_Handler
                PUBWEAK DebugMon_Handler
                PUBWEAK PendSV_Handler
                PUBWEAK SysTick_Handler

                PUBWEAK GPIOA_Handler
                PUBWEAK GPIOB_Handler
                PUBWEAK GPIOC_Handler
                PUBWEAK GPIOD_Handler
                PUBWEAK GPIOE_Handler
                PUBWEAK UART0_Handler
                PUBWEAK UART1_Handler
                PUBWEAK SSI0_Handler
                PUBWEAK I2C0_Handler
                PUBWEAK PMW0_FAULT_Handler
                PUBWEAK PWM0_0_Handler
                PUBWEAK PWM0_1_Handler
                PUBWEAK PWM0_2_Handler
                PUBWEAK QEI0_Handler
                PUBWEAK ADC0SS0_Handler
                PUBWEAK ADC0SS1_Handler
                PUBWEAK ADC0SS2_Handler
                PUBWEAK ADC0SS3_Handler
                PUBWEAK WDT0_Handler
                PUBWEAK TIMER0A_Handler
                PUBWEAK TIMER0B_Handler
                PUBWEAK TIMER1A_Handler
                PUBWEAK TIMER1B_Handler
                PUBWEAK TIMER2A_Handler
                PUBWEAK TIMER2B_Handler
                PUBWEAK COMP0_Handler
                PUBWEAK COMP1_Handler
                PUBWEAK COMP2_Handler
                PUBWEAK SYSCTL_Handler
                PUBWEAK FLASH_Handler
                PUBWEAK GPIOF_Handler
                PUBWEAK GPIOG_Handler
                PUBWEAK GPIOH_Handler
                PUBWEAK UART2_Handler
                PUBWEAK SSI1_Handler
                PUBWEAK TIMER3A_Handler
                PUBWEAK TIMER3B_Handler
                PUBWEAK I2C1_Handler
                PUBWEAK CAN0_Handler
                PUBWEAK CAN1_Handler
                PUBWEAK ETH_Handler
                PUBWEAK HIB_Handler
                PUBWEAK USB0_Handler
                PUBWEAK PWM0_3_Handler
                PUBWEAK UDMA_Handler
                PUBWEAK UDMAERR_Handler
                PUBWEAK ADC1SS0_Handler
                PUBWEAK ADC1SS1_Handler
                PUBWEAK ADC1SS2_Handler
                PUBWEAK ADC1SS3_Handler
                PUBWEAK EBI0_Handler
                PUBWEAK GPIOJ_Handler
                PUBWEAK GPIOK_Handler
                PUBWEAK GPIOL_Handler
                PUBWEAK SSI2_Handler
                PUBWEAK SSI3_Handler
                PUBWEAK UART3_Handler
                PUBWEAK UART4_Handler
                PUBWEAK UART5_Handler
                PUBWEAK UART6_Handler
                PUBWEAK UART7_Handler
                PUBWEAK I2C2_Handler
                PUBWEAK I2C3_Handler
                PUBWEAK TIMER4A_Handler
                PUBWEAK TIMER4B_Handler
                PUBWEAK TIMER5A_Handler
                PUBWEAK TIMER5B_Handler
                PUBWEAK FPU_Handler
                PUBWEAK I2C4_Handler
                PUBWEAK I2C5_Handler
                PUBWEAK GPIOM_Handler
                PUBWEAK GPION_Handler
                PUBWEAK TAMPER_Handler
                PUBWEAK GPIOP0_Handler
                PUBWEAK GPIOP1_Handler
                PUBWEAK GPIOP2_Handler
                PUBWEAK GPIOP3_Handler
                PUBWEAK GPIOP4_Handler
                PUBWEAK GPIOP5_Handler
                PUBWEAK GPIOP6_Handler
                PUBWEAK GPIOP7_Handler
                PUBWEAK GPIOQ0_Handler
                PUBWEAK GPIOQ1_Handler
                PUBWEAK GPIOQ2_Handler
                PUBWEAK GPIOQ3_Handler
                PUBWEAK GPIOQ4_Handler
                PUBWEAK GPIOQ5_Handler
                PUBWEAK GPIOQ6_Handler
                PUBWEAK GPIOQ7_Handler
                PUBWEAK TIMER6A_Handler
                PUBWEAK TIMER6B_Handler
                PUBWEAK TIMER7A_Handler
                PUBWEAK TIMER7B_Handler
                PUBWEAK I2C6_Handler
                PUBWEAK I2C7_Handler
                PUBWEAK I2C8_Handler
                PUBWEAK I2C9_Handler


                SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler

GPIOA_Handler
GPIOB_Handler
GPIOC_Handler
GPIOD_Handler
GPIOE_Handler
UART0_Handler
UART1_Handler
SSI0_Handler
I2C0_Handler
PMW0_FAULT_Handler
PWM0_0_Handler
PWM0_1_Handler
PWM0_2_Handler
QEI0_Handler
ADC0SS0_Handler
ADC0SS1_Handler
ADC0SS2_Handler
ADC0SS3_Handler
WDT0_Handler
TIMER0A_Handler
TIMER0B_Handler
TIMER1A_Handler
TIMER1B_Handler
TIMER2A_Handler
TIMER2B_Handler
COMP0_Handler
COMP1_Handler
COMP2_Handler
SYSCTL_Handler
FLASH_Handler
GPIOF_Handler
GPIOG_Handler
GPIOH_Handler
UART2_Handler
SSI1_Handler
TIMER3A_Handler
TIMER3B_Handler
I2C1_Handler
CAN0_Handler
CAN1_Handler
ETH_Handler
HIB_Handler
USB0_Handler
PWM0_3_Handler
UDMA_Handler
UDMAERR_Handler
ADC1SS0_Handler
ADC1SS1_Handler
ADC1SS2_Handler
ADC1SS3_Handler
EBI0_Handler
GPIOJ_Handler
GPIOK_Handler
GPIOL_Handler
SSI2_Handler
SSI3_Handler
UART3_Handler
UART4_Handler
UART5_Handler
UART6_Handler
UART7_Handler
I2C2_Handler
I2C3_Handler
TIMER4A_Handler
TIMER4B_Handler
TIMER5A_Handler
TIMER5B_Handler
FPU_Handler
I2C4_Handler
I2C5_Handler
GPIOM_Handler
GPION_Handler
TAMPER_Handler
GPIOP0_Handler
GPIOP1_Handler
GPIOP2_Handler
GPIOP3_Handler
GPIOP4_Handler
GPIOP5_Handler
GPIOP6_Handler
GPIOP7_Handler
GPIOQ0_Handler
GPIOQ1_Handler
GPIOQ2_Handler
GPIOQ3_Handler
GPIOQ4_Handler
GPIOQ5_Handler
GPIOQ6_Handler
GPIOQ7_Handler
TIMER6A_Handler
TIMER6B_Handler
TIMER7A_Handler
TIMER7B_Handler
I2C6_Handler
I2C7_Handler
I2C8_Handler
I2C9_Handler
                B       .


                END
