#include "gpio.h"   

void gpio_init(void)
{
    unsigned int *pReg;

    /* 使能GPIOB */
    pReg = (unsigned int *)(0x40021000 + 0x18);
    *pReg |= (1 << 3);

    /* 设置GPIOB0 为输出引脚 */
    pReg = (unsigned int *)(0x40010C00 + 0x00);
    *pReg |= (1 << 0);

    // 默认关闭led灯
    led_on_off(0);
}

void led_on_off(int status)
{
    unsigned int *pReg;
    pReg = (unsigned int *)(0x40010C00 + 0x0C);

    if(status)
    {
        /* 输出低电平让led亮 */
        *pReg &= ~(1 << 0);
    }
    else
    {
        /* 输出高电平让led灭 */
        *pReg |= 1<<0;
    }
}
