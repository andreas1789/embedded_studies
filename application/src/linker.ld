/*
* linker script for stm32f103c8t6
*/

INCLUDE ../memory_map.ld

_estack = ORIGIN(RAM) + LENGTH(RAM);


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

    .preinit_array :
    {
        . = ALIGN(4);
        _spreinit_array = .;
        KEEP(*(.preinit_array))
        KEEP(*(.preinit_array*))
        . = ALIGN(4);
        _epreinit_array = .;
    } > FLASH

    .init_array :
    {
        . = ALIGN(4);
        _sinit_array = .;
        KEEP(*(.init_array))
        KEEP(*(.init_array*))
        . = ALIGN(4);
        _einit_array = .;
    } > FLASH

    .fini_array :
    {
        . = ALIGN(4);
        _sfini_array = .;
        KEEP(*(.fini_array))
        KEEP(*(.fini_array*))
        . = ALIGN(4);
        _efini_array = .;
    } > FLASH
}
