
#include "uart.h"
#include "tasks.h"

static void clean_bss(void);
void delay(volatile int n);
void os_main(void);

int main(void)
{
    clean_bss();

    uart_init();
    uart_send_string("hello ZOS!\r\n");

    sched_init();
    os_main();
	schedule();

    
    while (1) {
        uart_send_string("Would not go here!\r\n");
        delay(3000000);
    }

    return 0;
}

static void clean_bss(void)
{
    extern char bss_begin[], bss_end[];
    unsigned int * p = (unsigned int *)bss_begin;
    int size = bss_end - bss_begin;
    int i;

    for(i = 0; i < size; i ++) {
        *p = 0;
        p ++;
    }
}

void delay(volatile int n)
{
    while (n--);
}

