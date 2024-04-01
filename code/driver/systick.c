#include "systick.h"

void systick_init(void)
{
    SysTick_Type *SysTick = (SysTick_Type *)SysTick_BASE;

    //  设置周期 : 1S  设置 Load 寄存器
    SysTick->VAL  = SYSTICK_FRE / 10000;    // 24位向下计数器（此值应当等于重装载寄存器）
    SysTick->LOAD = SYSTICK_FRE / 10000;    // 重装载寄存器（因为8MHz时钟并未修改，要延时100us需要计数8M/10,000次）

    // 选择时钟源, 使能systick定时器, 使能中断 BIT[2] : 时钟源 BIT[1] : 使能中断 BIT[0] : 使能systick定时器 
    SysTick->CTRL = (1<<2) | (1<<1) | (1<<0);
}
