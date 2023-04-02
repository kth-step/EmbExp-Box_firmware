#include "rpi4hw.h"

static void enable_af_pin(int gpio)
{
	uint64_t pullreg = GPPUPPDN0 + ((gpio>>4) * 4);
	int pullshift = (gpio & 0xf) << 1;
	unsigned int pullbits;
	unsigned int pull;

	pull = 0;

	pullbits = readl(pullreg);
	pullbits &= ~(3 << pullshift);
	pullbits |= (pull << pullshift);
	writel(pullreg, pullbits);
}

void uart_pin_init() {
	uint32_t gpfsel1;

	gpfsel1 = readl(GPFSEL1);
	gpfsel1 &= ~(GPFSEL_PIN_MASK << 12);	// Gpio14
	gpfsel1 |= (GPFSEL_ALT_0		<< 12);	// Alt5: UART_TXD
	gpfsel1 &= ~(GPFSEL_PIN_MASK << 15); // Gpio15
	gpfsel1 |= (GPFSEL_ALT_0		<< 15);	// Alt5: UART_RXD
	writel(GPFSEL1, gpfsel1);

	enable_af_pin(14);
	enable_af_pin(15);
}

