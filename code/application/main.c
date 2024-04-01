#include "gpio.h"
#include "uart.h"
#include "systick.h"
#include "scheduler.h"
#include "task.h"

#define NULL ((void *)0)

static unsigned char stack_a[1024] __attribute__ ((aligned (4)));     // A任务的栈 4字节对齐
static unsigned char stack_b[1024] __attribute__ ((aligned (4)));     // B任务的栈 4字节对齐
static unsigned char stack_c[1024] __attribute__ ((aligned (4)));     // C任务的栈 4字节对齐
static unsigned char stack_d[1024] __attribute__ ((aligned (4)));     // D任务的栈 4字节对齐


int mymain()
{
    gpio_init();
    uart_init();
    systick_init();

    create_task(task_uart_send_char,    (void *)'a',    stack_a, 1024);
    create_task(task_uart_send_char,    (void *)'b',    stack_b, 1024);
    create_task(task_uart_send_char,    (void *)'c',    stack_c, 1024);
    create_task(task_led_breath,        NULL,           stack_d, 1024);

    start_task();

    while(1);

    return 0;
}
