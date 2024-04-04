
#include <uart.h>
#include <clock.h>


void delay(volatile int n)
{
	while (n--);
}

int main(void)
{
	int i = 0;

	uart_init();
	
	while (1) {
		sys_uart_printf("%02d ZOS\r\n", i++);
		delay(1000000);
	}

	return 0;
}

