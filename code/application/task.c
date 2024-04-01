#include "task.h"
#include "uart.h"
#include "gpio.h"

void task_uart_send_char(void * param)
{
    int character;
    character = (int)param;
    while(1)
    {
        putchar(character);
    }
}

void task_led_breath(void * param)
{
    unsigned int i = 0;
    unsigned int duty = 0;
    unsigned char bright_or_dark = 0;

    while(1)
    {
        led_on_off(0);
        i = 0;
        while(i < duty)
        {
            i ++;
        }
        
        led_on_off(1);
        i = 0;
        while(i < (0x1000 - duty))
        {
            i++;
        }
        
        if(bright_or_dark == 0)
        {
            duty += 0x10;
            if(duty >= 0x1000)
            {
                bright_or_dark = 1;
            }
        }
        else
        {
            duty -= 0x10;
            if(duty <= 0x10)
            {
                bright_or_dark = 0;
            }
        }
    }
}
