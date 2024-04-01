
                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                IMPORT  SysTick_Handler_asm

__Vectors       DCD     0                  
                DCD     Reset_Handler           ; Reset Handler
                DCD     0                       ; NMI Handler
                DCD     0                       ; Hard Fault Handler
                DCD     0                       ; MPU Fault Handler
                DCD     0                       ; Bus Fault Handler
                DCD     0                       ; Usage Fault Handler
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     0                       ; Reserved
                DCD     0                       ; SVCall Handler
                DCD     0                       ; Debug Monitor Handler
                DCD     0                       ; Reserved
                DCD     0                       ; PendSV Handler
                DCD     SysTick_Handler_asm     ; SysTick Handler
				AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  mymain
                IMPORT  SystemInit

                LDR SP, =(0x20000000+0x10000)   ; 设置栈

                BL  SystemInit
                
                LDR R0, =mymain
                BLX R0                          ; 跳去执行main函数

                ENDP


                END


