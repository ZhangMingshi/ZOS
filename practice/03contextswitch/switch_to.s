#define LOAD        ld
#define STORE       sd
#define SIZE_REG    8

# struct context *base = &ctx_task;
.macro reg_save base
    STORE ra,   0*SIZE_REG(\base)
    STORE sp,   1*SIZE_REG(\base)
    STORE t0,   4*SIZE_REG(\base)
    STORE t1,   5*SIZE_REG(\base)
    STORE t2,   6*SIZE_REG(\base)
    STORE s0,   7*SIZE_REG(\base)
    STORE s1,   8*SIZE_REG(\base)
    STORE a0,   9*SIZE_REG(\base)
    STORE a1,  10*SIZE_REG(\base)
    STORE a2,  11*SIZE_REG(\base)
    STORE a3,  12*SIZE_REG(\base)
    STORE a4,  13*SIZE_REG(\base)
    STORE a5,  14*SIZE_REG(\base)
    STORE a6,  15*SIZE_REG(\base)
    STORE a7,  16*SIZE_REG(\base)
    STORE s2,  17*SIZE_REG(\base)
    STORE s3,  18*SIZE_REG(\base)
    STORE s4,  19*SIZE_REG(\base)
    STORE s5,  20*SIZE_REG(\base)
    STORE s6,  21*SIZE_REG(\base)
    STORE s7,  22*SIZE_REG(\base)
    STORE s8,  23*SIZE_REG(\base)
    STORE s9,  24*SIZE_REG(\base)
    STORE s10, 25*SIZE_REG(\base)
    STORE s11, 26*SIZE_REG(\base)
    STORE t3,  27*SIZE_REG(\base)
    STORE t4,  28*SIZE_REG(\base)
    STORE t5,  29*SIZE_REG(\base)
    # we don't save t6 here, due to we have used
    # it as base, we have to save t6 in an extra step
    # outside of reg_save
.endm


# struct context *base = &ctx_task;
.macro reg_restore base
    LOAD ra,   0*SIZE_REG(\base)
    LOAD sp,   1*SIZE_REG(\base)
    LOAD t0,   4*SIZE_REG(\base)
    LOAD t1,   5*SIZE_REG(\base)
    LOAD t2,   6*SIZE_REG(\base)
    LOAD s0,   7*SIZE_REG(\base)
    LOAD s1,   8*SIZE_REG(\base)
    LOAD a0,   9*SIZE_REG(\base)
    LOAD a1,  10*SIZE_REG(\base)
    LOAD a2,  11*SIZE_REG(\base)
    LOAD a3,  12*SIZE_REG(\base)
    LOAD a4,  13*SIZE_REG(\base)
    LOAD a5,  14*SIZE_REG(\base)
    LOAD a6,  15*SIZE_REG(\base)
    LOAD a7,  16*SIZE_REG(\base)
    LOAD s2,  17*SIZE_REG(\base)
    LOAD s3,  18*SIZE_REG(\base)
    LOAD s4,  19*SIZE_REG(\base)
    LOAD s5,  20*SIZE_REG(\base)
    LOAD s6,  21*SIZE_REG(\base)
    LOAD s7,  22*SIZE_REG(\base)
    LOAD s8,  23*SIZE_REG(\base)
    LOAD s9,  24*SIZE_REG(\base)
    LOAD s10, 25*SIZE_REG(\base)
    LOAD s11, 26*SIZE_REG(\base)
    LOAD t3,  27*SIZE_REG(\base)
    LOAD t4,  28*SIZE_REG(\base)
    LOAD t5,  29*SIZE_REG(\base)
    LOAD t6,  30*SIZE_REG(\base)    
.endm


.text
.globl switch_to
.balign 4
switch_to:
    # 把 原t6 存起来
    csrrw   t6, mscratch, t6    # swap t6 and mscratch
    # 如果 第一次执行 直接去下面
    beqz    t6, 1f              # Note: the first time switch_to() is called, 
                                    # mscratch is initialized as zero (in sched_init()),
                                    # which makes t6 zero,
                                    # and that's the special case we have to handle with t6
    # 如果不是第一次执行 ms 里面存储的是 原环境指针 即 t6 里存的是 原环境指针 存储原环境
    reg_save    t6              # save context of prev task
    # 以下3句 用来保存原 t6
    # Save the actual t6 register, which we swapped into mscratch
    mv      t5, t6              # t5 points to the context of current task
    csrr    t6, mscratch        # read t6 back from mscratch
    STORE   t6, 30*SIZE_REG(t5) # save t6 with t5 as base
1:  # ms指向下一个环境
    # switch mscratch to point to the context of the next task
    csrw    mscratch, a0
    # t6指向下一个环境
    # Restore all GP registers
    # Use t6 to point to the context of the new task
    mv      t6, a0
    # 把环境拿出来
    reg_restore t6

    # Do actual context switching.
    ret

.end
