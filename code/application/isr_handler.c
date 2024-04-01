#include "gpio.h"
#include "interrupt.h"

// void SysTick_Handler(void)
// {
//     static int led_status = 1;
//     SCB_Type * SCB = (SCB_Type *)SCB_BASE_ADDR;

//     // led_status(0);
//     // 每次中断 翻转led状态
//     if(led_status == 0)
//     {
//         led_on_off(0);
//         led_status = 1;
//     }
//     else
//     {
//         led_on_off(1);
//         led_status = 0;
//     }

//     // 清除中断待处理位
//     SCB->ICSR |= (1UL << 25U);
// }
