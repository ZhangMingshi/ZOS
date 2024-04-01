#include "interrupt.h"
#include "scheduler.h"

void start_task_asm(unsigned int task_index, unsigned int lr);

void SysTick_Handler(unsigned int lr_back, unsigned int old_sp)
{
	SCB_Type * SCB = (SCB_Type *)SCB_BASE_ADDR;
    unsigned int stack;
    int pre_task;
    int new_task;

    // 清除中断待处理位
	SCB->ICSR |= (1UL << 25U);

    // 启动第一个任务，或者切换任务
    if(!is_task_running())  // 没处于运行状态中
    {
        return;
    }
    else    // 处于运行状态中
    {
        if(get_current_task() == -1)  // 如果之前没有启动过任务
        {
            switch_to_next_task();
            // 从栈里恢复寄存器
            stack = get_task_stack(get_current_task());
            start_task_asm(stack, lr_back);
            return;   // 不会执行至此
        }
        else    // 如果之前已经启动了任务 要切换任务
        {
            pre_task = get_current_task();
            switch_to_next_task();
            new_task = get_current_task();
            if(new_task != pre_task)    // 只有在不等于时才切换（如果只有一个任务，无需切换）
            {
                // 保存pre_task:
                // 在跳转至本函数前的汇编里，已经保存了
                // 更新老任务的SP
                set_task_stack(pre_task, old_sp);
                // 切换到新任务
                stack = get_task_stack(new_task);
                start_task_asm(stack, lr_back);
            }
            stack = get_task_stack(get_current_task());
        }
    }
    
    return;
}

