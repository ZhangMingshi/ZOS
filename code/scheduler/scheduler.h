#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#define TASK_COUNT 32   // 支持多少个任务？

typedef void (*task_function)(void * param);

void create_task(task_function func, void * param, void * stack, int stack_size);
void start_task(void);
int is_task_running(void);
unsigned int get_task_stack(int task_index);
int get_current_task(void);
int get_next_task(void);
void switch_to_next_task(void);
void set_task_stack(int which_task, unsigned int sp);


#endif
