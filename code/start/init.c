void my_memcpy(void *dest, void *src, unsigned int len)
{
    unsigned char *pcDest = dest;
    unsigned char *pcSrc  = src;

    while (len --)
    {
        *pcDest = *pcSrc;
        pcSrc++;
        pcDest++;
    }
}

void my_memset(void *dest, unsigned char val, unsigned int len)
{
    unsigned char *pcDest = dest;

    while (len --)
    {
        *pcDest = val;
        pcDest++;
    }
}

void SystemInit(void)
{
    extern int Image$$ER_IROM1$$Base;
    extern int Image$$ER_IROM1$$Length;
    extern int Load$$ER_IROM1$$Base;
    extern int Image$$RW_IRAM1$$Base;
    extern int Image$$RW_IRAM1$$Length;
    extern int Load$$RW_IRAM1$$Base;
    extern int Image$$RW_IRAM1$$ZI$$Base;
    extern int Image$$RW_IRAM1$$ZI$$Length;	

    /* 代码段重定位 */
    if (&Image$$ER_IROM1$$Base != &Load$$ER_IROM1$$Base)    // 只有源地址不等于目的地址才复制
        my_memcpy(&Image$$ER_IROM1$$Base, &Load$$ER_IROM1$$Base, (unsigned int)&Image$$ER_IROM1$$Length);

    /* RW数据段重定位 */
    if (&Image$$RW_IRAM1$$Base != &Load$$RW_IRAM1$$Base)    // 只有源地址不等于目的地址才复制
        my_memcpy(&Image$$RW_IRAM1$$Base, &Load$$RW_IRAM1$$Base, (unsigned int)&Image$$RW_IRAM1$$Length);

    /* bss 段清零 */
    my_memset(&Image$$RW_IRAM1$$ZI$$Base, 0, (unsigned int)&Image$$RW_IRAM1$$ZI$$Length);
}

