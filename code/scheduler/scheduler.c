#include "scheduler.h"

static unsigned int task_stacks_position[TASK_COUNT];
static int task_count;
static int task_current = -1;
static int task_running_flag = 0;

void create_task(task_function func, void * param, void * stack, int stack_size)
{
    // 一个指针指向栈顶
    unsigned int *top = (unsigned int *)((unsigned char *)stack + stack_size);

    // 伪造：任务第一次运行时的现场
    top -= 16;
    top[0]  = 0;                    // r4   以下寄存器理应由软件保护=====================
    top[1]  = 0;                    // r5
    top[2]  = 0;                    // r6
    top[3]  = 0;                    // r7
    top[4]  = 0;                    // r8
    top[5]  = 0;                    // r9
    top[6]  = 0;                    // r10
    top[7]  = 0;                    // r11
    top[8]  = (unsigned int)param;  // r0（传参数） 以下寄存器理应由硬件保护================
    top[9]  = 0;                    // r1
    top[10] = 0;                    // r2
    top[11] = 0;                    // r3
    top[12] = 0;                    // r12
    top[13] = 0;                    // lr（不会再返回了，所以这个值无所谓）
    top[14] = (unsigned int)func;   // 所创建的任务的函数的地址
    top[15] = (1<<24);              // PSR（使用 Thumb 指令集，所以把T位写为1）
    // 至此，只保存了16个寄存器的值

    // 记录本任务的栈的位置
    task_stacks_position[task_count] = (unsigned int)top;
    task_count ++;
}

// 开始任务：把开始标志置位，这样在中断中看到后将会开始任务
void start_task()
{
    task_running_flag = 1;
    while (1);  // 一直等待中断
}

// 返回开始标志的状态，这是为了让中断函数看到是否开始
int is_task_running(void)
{
    return task_running_flag;
}

// 获取当前任务的栈指针
unsigned int get_task_stack(int task_index)
{
    return task_stacks_position[task_index];
}


// 获取当前任务描述符
int get_current_task(void)
{
    return task_current;
}

// 获取下一个任务描述符
int get_next_task(void)
{
    if(task_current + 1 >= task_count)
    {
        return 0;
    }
    else
    {
        return (task_current + 1);
    }
}

// 切换下一个任务
void switch_to_next_task(void)
{
    task_current ++;

    if(task_current >= task_count)
    {
        task_current = 0;
    }
}

// 设置任务的栈的位置
void set_task_stack(int which_task, unsigned int sp)
{
    task_stacks_position[which_task] = sp;
}

