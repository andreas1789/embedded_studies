/*
* linker script for stm32f103c8t6
*/

_estack = ORIGIN(RAM) + LENGTH(RAM);

MEMORY
{
    RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
    FLASH (xr) : ORIGIN = 0x08000000, LENGTH = 64K
}


SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        *(.isr_vector)
        . = ALIGN(4);
    } > FLASH

    .text :
    {
        . = ALIGN(4);
        KEEP(*(.text))
        KEEP(*(.text*))
        . = ALIGN(4);
    } > FLASH

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        . = ALIGN(4);
    } > FLASH

    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    } > RAM
}
