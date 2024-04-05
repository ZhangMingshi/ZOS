
#include <uart.h>
#include <clock.h>

int glo_array[] = {
    0x1234, 0x1234, 0x1234, 0x1234, 0x1234, 0x1234, 0x1234, 0x1234,
    0x1234, 0x1234, 0x1234, 0x1234, 0x1234, 0x1234, 0x1234, 0x1234,
};

int glo = 0x1234;

static void clean_bss(void);

void delay(volatile int n)
{
    while (n--);
}

int main(void)
{
    int i = 0;
    clean_bss();

    uart_init();
    
    while (1) {
        sys_uart_printf("%02d ZOS\r\n", i++);
        sys_uart_printf("glo = 0x%x", glo);
        sys_uart_printf("glo = 0x%x", glo_array[15]);
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