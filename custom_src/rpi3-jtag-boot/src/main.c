#include "rpi3hw.h"
#include "uart.h"


static void dbg_puts(const char *s)
{
	while (*s)
		uart_putchar(*s++);
}


const int flagmem = 0;

volatile int* flagp = &flagmem;
int main_core0()
{
	uart_init();
	uart_pin_init();
	dbg_puts("Booting board: rpi4\n");

	dbg_puts("Compilation at: ");
	dbg_puts(__DATE__);
	dbg_puts(" (");
	dbg_puts(__TIME__);
	dbg_puts(")\n");

	dbg_puts("Initing JTAG: #0\n");
	enable_jtag();
	dbg_puts("Init complete: #0\n");
	_set_led(1);

        *flagp = *flagp + 1;

	return 0;
}

int main_core1()
{
	while(*flagp != 1);

	dbg_puts("Initing JTAG: #1\n");
	enable_jtag();
	dbg_puts("Init complete: #1\n");

        *flagp = *flagp + 1;

	return 0;
}

int main_core2()
{
	while(*flagp != 2);

	dbg_puts("Initing JTAG: #2\n");
	enable_jtag();
	dbg_puts("Init complete: #2\n");

        *flagp = *flagp + 1;

	return 0;
}

int main_core3()
{
	while(*flagp != 3);

	dbg_puts("Initing JTAG: #3\n");
	enable_jtag();
	dbg_puts("Init complete: #3\n");

        *flagp = *flagp + 1;

	return 0;
}
