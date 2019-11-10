/*
 * Derived from code:
 * 
 * https://github.com/swarren/rpi-3-aarch64-demo
 * Copyright (C) 2012 Vikram Narayananan <vikram186@gmail.com>
 * (C) Copyright 2012-2016 Stephen Warren
 * Copyright (C) 1996-2000 Russell King
 *
 * SPDX-License-Identifier:	GPL-2.0
 *
 * https://github.com/dwelch67/raspberrypi/tree/master/armjtag
 * Copyright (c) 2012 David Welch dwelch@dwelch.com
 */

#ifndef _RPI4HW_H
#define _RPI4HW_H

#include <stdint.h>


#define BIT(x)	(1U << (x))

#define PERI_BASE				(0xFE000000)

#define MU_BASE					(PERI_BASE + 0x00215040)
#define MU_LSR_TX_NOT_FULL		(BIT(5))
#define MU_LSR_RX_READY			(BIT(0))

#define AUX_ENABLES				(PERI_BASE + 0x00215004)
#define AUX_MU_IO_REG			(PERI_BASE + 0x00215040)
#define AUX_MU_IER_REG			(PERI_BASE + 0x00215044)
#define AUX_MU_IIR_REG			(PERI_BASE + 0x00215048)
#define AUX_MU_LCR_REG			(PERI_BASE + 0x0021504C)
#define AUX_MU_MCR_REG			(PERI_BASE + 0x00215050)
#define AUX_MU_LSR_REG			(PERI_BASE + 0x00215054)
#define AUX_MU_MSR_REG			(PERI_BASE + 0x00215058)
#define AUX_MU_SCRATCH			(PERI_BASE + 0x0021505C)
#define AUX_MU_CNTL_REG			(PERI_BASE + 0x00215060)
#define AUX_MU_STAT_REG			(PERI_BASE + 0x00215064)
#define AUX_MU_BAUD_REG			(PERI_BASE + 0x00215068)

#define GPFSEL0					(PERI_BASE + 0x00200000)
#define GPFSEL1					(PERI_BASE + 0x00200004)
#define GPFSEL2					(PERI_BASE + 0x00200008)
#define GPSET0					(PERI_BASE + 0x0020001C)
#define GPCLR0					(PERI_BASE + 0x00200028)

#define GPPUPPDN0                (PERI_BASE + 0x00200000 + (4*57))        /* Pin pull-up/down for pins 15:0  */
#define GPPUPPDN1                (PERI_BASE + 0x00200000 + (4*58))        /* Pin pull-up/down for pins 31:16 */
#define GPPUPPDN2                (PERI_BASE + 0x00200000 + (4*59))        /* Pin pull-up/down for pins 47:32 */
#define GPPUPPDN3                (PERI_BASE + 0x00200000 + (4*60))        /* Pin pull-up/down for pins 57:48 */

#define GPFSEL_PIN_MASK			(7U)//(BIT(2) | BIT(1) | BIT(0))
#define GPFSEL_ALT_0			(4U)
#define GPFSEL_ALT_4			(3U)//(BIT(1) | BIT(0))
#define GPFSEL_ALT_5			(2U)//(BIT(1))

#define __arch_getl(a)		(*(volatile uint32_t *)(a))
#define __arch_putl(v,a)	(*(volatile uint32_t *)(a) = (v))

#define dmb()				__asm__ __volatile__ ("dmb st" : : : "memory")
#define nop()				__asm__ __volatile__ ("nop")
#define __iormb()			dmb()
#define __iowmb()			dmb()

// PL011
// http://infocenter.arm.com/help/topic/com.arm.doc.ddi0183f/DDI0183.pdf
#define UART_BASE				(PERI_BASE + 0x00201000)
#define UART_UARTDR	(UART_BASE + 0x000)
#define UART_UARTRSR	(UART_BASE + 0x004)
#define UART_UARTFR	(UART_BASE + 0x018)
#define UART_UARTIBRD	(UART_BASE + 0x024)
#define UART_UARTFBRD	(UART_BASE + 0x028)
#define UART_UARTLCR_H	(UART_BASE + 0x02c)
#define UART_UARTCR	(UART_BASE + 0x030)


static inline uint32_t readl(uint64_t addr)
{
	uint32_t value = __arch_getl(addr);
	__iormb();
	return value;
}


static inline void writel(uint64_t addr, uint32_t value)
{
	__arch_putl(value, addr);
	__iowmb();
}

void uart_pin_init();

#endif // _RPI4HW_H

