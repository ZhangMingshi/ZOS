#include "uart.h"
#include "tasks.h"

void delay(volatile int n);

void user_task0(void)
{
	uart_send_string("Task 0: Created!\n\r");
	while (1) {
		uart_send_string("Task 0: Running...\n\r");
        delay(3000000);
		task_yield();
	}
}

void user_task1(void)
{
	uart_send_string("Task 1: Created!\n\r");
	while (1) {
		uart_send_string("Task 1: Running...\n\r");
        delay(4000000);
		task_yield();
	}
}

/* NOTICE: DON'T LOOP INFINITELY IN main() */
void os_main(void)
{
	task_create(user_task0);
	task_create(user_task1);
}