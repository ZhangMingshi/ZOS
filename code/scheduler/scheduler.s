                PRESERVE8
                THUMB
                AREA    |.text|, CODE, READONLY
start_task_asm  PROC
                EXPORT  start_task_asm
                ; 从任务的栈里把r4~r11读出来写入寄存器
                LDMIA   R0!, {R4-R11}       ; R0是传来的参数，指向任务的栈
                ; 更新SP
				MOV 	SP, R0
                ; 触发硬件中断返回：让硬件把栈里的其他值读出来写入寄存器
                BX      R1                  ; R1是传来的参数，存储着LR中特殊的值
				ENDP

SysTick_Handler_asm PROC
                EXPORT 	SysTick_Handler_asm
                IMPORT  SysTick_Handler

                STMDB   SP!, {R4-R11}       ; 把现场压入栈中（这样，即使在处理函数中调用切换也已经保存原任务的现场）
                STMDB   SP!, {LR}           ; 把LR也压入栈中

                MOV     R0, LR              ; LR作为参数传入函数
                ADD     R1, SP, #4          ; 原任务的栈（不包含LR所以+4）作为参数传入栈中
                BL      SysTick_Handler     ; 调用处理函数

                LDMIA   SP!, {R0}           ; 把LR出栈到R0
                LDMIA   SP!, {R4-R11}       ; 把其余寄存器出栈到相应位置（其实没必要出栈，只需要改变SP的位置即可。这么写更简洁，但执行效率被影响）

                BX      R0                  ; 跳出中断服务函数

				ENDP

                END
