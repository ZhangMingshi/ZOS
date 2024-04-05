SECTIONS
{
    /* 加载入口地址 */
    . = 0x20000;

    text_begin = .;
    .text : { *(.text) }
    text_end = .;
    . = ALIGN(8);

    rodata_begin = .;
    .rodata : { *(.rodata) }
    rodata_end = .;
    . = ALIGN(8);

    data_begin = .;
    .data : { *(.data) }
    data_end = .;
    . = ALIGN(8);

    sdata_begin = .;
    .sdata : { *(.sdata) }
    sdata_end = .;
    . = ALIGN(0x8);

    bss_begin = .;
    .bss : { *(.bss*) } 
    bss_end = .;
    
    PROVIDE(__bin_size = bss_begin - text_begin);
}
    
