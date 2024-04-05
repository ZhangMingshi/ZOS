#include "tasks.h"

#define MAX_TASKS 10
#define STACK_SIZE 1024

void switch_to(struct context *next);

// 任务最大数
static int _top = 0;
// 当前任务是第几个
static int _current = -1;
// 存储任务的上下文
struct context ctx_tasks[MAX_TASKS];
// 创建几个栈
unsigned char task_stack[MAX_TASKS][STACK_SIZE];

static void w_mscratch(reg_t x)
{
    asm volatile("csrw mscratch, %0" : : "r" (x));
}

void sched_init()
{
    w_mscratch(0);
}

void schedule()
{
    struct context *next;

    if(_top <= 0) {
        uart_send_string("Num of task should be greater than zero!\r\n");
        return;
    }

    // 当前任务++
    _current = (_current + 1) % _top;
    
    // 下一个上下文的指针
    next = &(ctx_tasks[_current]);
    
    switch_to(next);
}

int task_create(void (*start_routin)(void))
{
    if (_top < MAX_TASKS) {
        // 初始化栈指针
        ctx_tasks[_top].sp = (reg_t)&task_stack[_top][STACK_SIZE];
        // 保存函数返回地址
        ctx_tasks[_top].ra = (reg_t)start_routin;
        // 添加一个任务
        _top++;
        return 0;
    } else {
        return -1;
    }
}

void task_yield()
{
    schedule();
}