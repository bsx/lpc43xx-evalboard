/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2010, Roel Verdult
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

// Declare a weak alias macro as described in the GCC manual[1][2]
#define WEAK_ALIAS(f) __attribute__ ((weak, alias (#f)));
#define SECTION(s) __attribute__ ((section(s)))

/******************************************************************************
 * Forward undefined IRQ handlers to an infinite loop function. The Handlers
 * are weakly aliased which means that (re)definitions will overide these.
 *****************************************************************************/

void irq_undefined() {
  // Do nothing when occured interrupt is not defined, just keep looping
  while(1);
}

void FPU_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void DAC_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void DMA_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void ETH_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void SDIO_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void LCD_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void USB0_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void USB1_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void SCT_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void RIT_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void TIMER0_IRQHandler(void)    WEAK_ALIAS(irq_undefined)
void TIMER1_IRQHandler(void)    WEAK_ALIAS(irq_undefined)
void TIMER2_IRQHandler(void)    WEAK_ALIAS(irq_undefined)
void TIMER3_IRQHandler(void)    WEAK_ALIAS(irq_undefined)
void MCPWM_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void ADC0_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void I2C0_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void I2C1_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void ADC1_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void SSP0_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void SSP1_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void UART0_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void UART1_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void UART2_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void UART3_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void I2S0_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void I2S1_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void SPIFI_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void SGPIO_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GPIO0_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GPIO1_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GPIO2_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GPIO3_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GPIO4_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GPIO5_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GPIO6_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GPIO7_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GINT0_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void GINT1_IRQHandler(void)     WEAK_ALIAS(irq_undefined)
void EVRT_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void CAN1_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void VADC_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void ATIMER_IRQHandler(void)    WEAK_ALIAS(irq_undefined)
void RTC_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void WDT_IRQHandler(void)       WEAK_ALIAS(irq_undefined)
void CAN0_IRQHandler(void)      WEAK_ALIAS(irq_undefined)
void QEI_IRQHandler(void)       WEAK_ALIAS(irq_undefined)



/*****************************************************************************
 * Forward undefined fault handlers to an infinite loop function. The Handlers
 * are weakly aliased which means that (re)definitions will overide these.
 ****************************************************************************/

void fault_undefined() {
  // Do nothing when occured interrupt is not defined, just keep looping
  while(1);
}

void empty() {}

void NMI_Handler(void)          WEAK_ALIAS(fault_undefined)
void HardFault_Handler(void)    WEAK_ALIAS(fault_undefined)
void MemManage_Handler(void)    WEAK_ALIAS(fault_undefined)
void BusFault_Handler(void)     WEAK_ALIAS(fault_undefined)
void UsageFault_Handler(void)   WEAK_ALIAS(fault_undefined)
void SVCall_Handler(void)       WEAK_ALIAS(fault_undefined)
void DebugMon_Handler(void)     WEAK_ALIAS(fault_undefined)
void PendSV_Handler(void)       WEAK_ALIAS(fault_undefined)
void SysTick_Handler(void)      WEAK_ALIAS(empty)

/******************************************************************************
 * Forward undefined IRQ handlers to an infinite loop function. The Handlers
 * are weakly aliased which means that (re)definitions will overide these.
 *****************************************************************************/

// Prototype the entry values, which are handled by the linker script
extern void* stack_entry;
extern void boot_entry(void);

// Defined irq vectors using simple c code following the description in a white
// paper from ARM[3] and code example from Simonsson Fun Technologies[4].
// These vectors are placed at the memory location defined in the linker script
const void *vectors[] SECTION(".irq-vectors") =
{
  // Stack and program reset entry point
  &stack_entry,          // The initial stack pointer
  boot_entry,            // The reset handler

  // Various fault handlers
  NMI_Handler,           // The NMI handler
  HardFault_Handler,     // The hard fault handler
  MemManage_Handler,     // The MPU fault handler
  BusFault_Handler,      // The bus fault handler
  UsageFault_Handler,    // The usage fault handler
  (void *)0x5A5A5A5A,    // Reserved
  0,                     // Reserved
  0,                     // Reserved
  0,                     // Reserved
  SVCall_Handler,        // SVCall handler
  DebugMon_Handler,      // Debug monitor handler
  0,                     // Reserved
  PendSV_Handler,        // The PendSV handler
  SysTick_Handler,       // The SysTick handler

  /* External Interrupts */
  DAC_IRQHandler,           /* 16 D/A Converter */
  0,                        /* 17 Event Router */
  DMA_IRQHandler,           /* 18 General Purpose DMA */
  0,                        /* 19 Reserved */
  0,                        /* 20 Reserved */
  ETH_IRQHandler,           /* 21 Ethernet */
  SDIO_IRQHandler,          /* 22 SD/MMC */
  LCD_IRQHandler,           /* 23 LCD */
  USB0_IRQHandler,          /* 24 USB0*/
  USB1_IRQHandler,          /* 25 USB1*/
  SCT_IRQHandler,           /* 26 State Configurable Timer*/
  RIT_IRQHandler,           /* 27 Repetitive Interrupt Timer*/
  TIMER0_IRQHandler,        /* 28 Timer0*/
  TIMER1_IRQHandler,        /* 29 Timer1*/
  TIMER2_IRQHandler,        /* 30 Timer2*/
  TIMER3_IRQHandler,        /* 31 Timer3*/
  MCPWM_IRQHandler,         /* 32 Motor Control PWM*/
  ADC0_IRQHandler,          /* 33 A/D Converter 0*/
  I2C0_IRQHandler,          /* 34 I2C0*/
  I2C1_IRQHandler,          /* 35 I2C1*/
  0,                        /* 36 Reserved*/
  ADC1_IRQHandler,          /* 37 A/D Converter 1*/
  SSP0_IRQHandler,          /* 38 SSP0*/
  SSP1_IRQHandler,          /* 39 SSP1*/
  UART0_IRQHandler,         /* 40 UART0*/
  UART1_IRQHandler,         /* 41 UART1*/
  UART2_IRQHandler,         /* 42 UART2*/
  UART3_IRQHandler,         /* 43 UART3*/
  I2S0_IRQHandler,          /* 44 I2S*/
  I2S1_IRQHandler,          /* 45 AES Engine*/
  SPIFI_IRQHandler,         /* 46 SPI Flash Interface*/
  SGPIO_IRQHandler,         /* 47 SGPIO*/
  GPIO0_IRQHandler,         /* 48 GPIO0*/
  GPIO1_IRQHandler,         /* 49 GPIO1*/
  GPIO2_IRQHandler,         /* 50 GPIO2*/
  GPIO3_IRQHandler,         /* 51 GPIO3*/
  GPIO4_IRQHandler,         /* 52 GPIO4*/
  GPIO5_IRQHandler,         /* 53 GPIO5*/
  GPIO6_IRQHandler,         /* 54 GPIO6*/
  GPIO7_IRQHandler,         /* 55 GPIO7*/
  GINT0_IRQHandler,         /* 56 GINT0*/
  GINT1_IRQHandler,         /* 57 GINT1*/
  EVRT_IRQHandler,          /* 58 Event Router*/
  CAN1_IRQHandler,          /* 59 C_CAN1*/
  0,                        /* 60 Reserved*/
  VADC_IRQHandler,          /* 61 VADC*/
  ATIMER_IRQHandler,        /* 62 ATIMER*/
  RTC_IRQHandler,           /* 63 RTC*/
  0,                        /* 64 Reserved*/
  WDT_IRQHandler,           /* 65 WDT*/
  0,                        /* 66 M0s*/
  CAN0_IRQHandler,          /* 67 C_CAN0*/
  QEI_IRQHandler,           /* 68 QEI*/

};

/******************************************************************************
 * References
 *  [1] http://gcc.gnu.org/onlinedocs/gcc/Function-Attributes.html
 *  [2] http://gcc.gnu.org/onlinedocs/gcc/Variable-Attributes.html
 *  [3] http://www.arm.com/files/pdf/Cortex-M3_programming_for_ARM7_developers.pdf
 *  [4] http://fun-tech.se/stm32/OlimexBlinky/mini.php
 *****************************************************************************/

