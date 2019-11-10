#include "rpi3hw.h"
#include "uart.h"

void uart_init()
{
	writel(AUX_ENABLES, 1);			// enable UART peripheral
	writel(AUX_MU_IER_REG, 0);		// disable UART interrupts for config
	writel(AUX_MU_CNTL_REG, 0);		// disable UART RX/TX for config
	writel(AUX_MU_LCR_REG, 3);		// 8 bit mode (bit 1 reserved!)
	writel(AUX_MU_MCR_REG, 0);		// RTS line high
	writel(AUX_MU_IER_REG, 0);		// disable UART interrupts
	writel(AUX_MU_IIR_REG, 0xC6);	// enable and clear FIFOs
	writel(AUX_MU_BAUD_REG, 270);	// 115200 Baud

	// enable UART RX/TX again
	writel(AUX_MU_CNTL_REG,3);
}

void uart_putchar(char c)
{
	struct bcm283x_mu_regs *regs = (struct bcm283x_mu_regs *) MU_BASE;

	/* Wait until there is space in the FIFO */
	while (!(readl((uint64_t) &regs->lsr) & MU_LSR_TX_NOT_FULL));

	/* Send the character */
	writel((uint64_t) &regs->io, c);
}

char uart_getchar()
{
  // not implemented here
  return (char)0;
}

