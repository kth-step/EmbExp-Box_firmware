#include "rpi2hw.h"

static void enable_af_pins(int clock, uint32_t bitmask)
{
	uint32_t clock_reg;
	int i;

	switch(clock)
	{
	case 0: clock_reg = GPPUDCLK0; break;
	case 1: clock_reg = GPPUDCLK1; break;
	default: return;
	}

	writel(GPPUD, 0);

	for(i = 0; i < 150; i++) nop();

	writel(clock_reg, bitmask);

	for(i = 0; i < 150; i++) nop();

	writel(clock_reg, 0);
}

void enable_jtag()
{
	uint32_t gpfsel2;

	gpfsel2 = readl(GPFSEL2);
	gpfsel2 &= ~(GPFSEL_PIN_MASK	<<  6);	// Gpio22
	gpfsel2 |=  (GPFSEL_ALT_4		<<  6);	// Alt4: ARM_TRST
	gpfsel2 &= ~(GPFSEL_PIN_MASK	<<  9);	// Gpio23
	gpfsel2 |=  (GPFSEL_ALT_4		<<  9);	// Alt4: ARM_RTCK
	gpfsel2 &= ~(GPFSEL_PIN_MASK	<< 12);	// Gpio24
	gpfsel2 |=  (GPFSEL_ALT_4		<< 12);	// Alt4: ARM_TDO
	gpfsel2 &= ~(GPFSEL_PIN_MASK	<< 15);	// Gpio25
	gpfsel2 |=  (GPFSEL_ALT_4		<< 15);	// Alt4: ARM_TCK
	gpfsel2 &= ~(GPFSEL_PIN_MASK	<< 18);	// Gpio26
	gpfsel2 |=  (GPFSEL_ALT_4		<< 18);	// Alt4: ARM_TDI
	gpfsel2 &= ~(GPFSEL_PIN_MASK	<< 21);	// Gpio27
	gpfsel2 |=  (GPFSEL_ALT_4		<< 21);	// Alt4: ARM_TMS
	writel(GPFSEL2,gpfsel2);

	enable_af_pins(0, BIT(22) | BIT(23) | BIT(24) | BIT(25) | BIT(26) | BIT(27));
}

void uart_pin_init()
{
	uint32_t gpfsel1;

	gpfsel1 = readl(GPFSEL1);
	gpfsel1 &= ~(GPFSEL_PIN_MASK << 12);	// Gpio14
	gpfsel1 |= (GPFSEL_ALT_5		<< 12);	// Alt5: UART_TXD
	gpfsel1 &= ~(GPFSEL_PIN_MASK << 15); // Gpio15
	gpfsel1 |= (GPFSEL_ALT_5		<< 15);	// Alt5: UART_RXD
	writel(GPFSEL1, gpfsel1);

	enable_af_pins(0, BIT(14) | BIT(15));
}

