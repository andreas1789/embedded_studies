.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global default_handler
.global isr_vector

.word _sbss     // data section in ram where uninitialized data is stored
.word _ebss
.word _sdata    // data section in ram where initialized data is stored
.word _edata
.word _sidata   // initialized data in flash
.word __FLASH_START__
.equ _vtor, 0xE000ED08

// Reset Handler
.section .text.Reset
.type Reset, %function

Reset:
    ldr r0, =_vtor // VTOR register
    ldr r1, =__FLASH_START__ // address of vector table of application
    str r1, [r0] 

    ldr r0, = _sdata
    ldr r1, = _edata
    ldr r2, = _sidata
    movs r3, #0
    b LoopCopyDataInit

LoopCopyData:
    ldr r4, [r2, r3]    // load value from flash
    str r4, [r0, r3]    // and store it into ram
    adds r3, r3, #4

LoopCopyDataInit:
    adds r4, r0, r3
    cmp r4, r1
    bcc LoopCopyData

    ldr r2, = _sbss
    ldr r4, = _ebss
    movs r3, #0
    b FillWithZerosbss

FillZerosbss:
    str r3, [r2]
    adds r2, r2, #4

FillWithZerosbss:
    cmp r2, r4
    bcc FillZerosbss

    bl _Z10SystemInitv

    bl main

    bx lr

.size Reset, .-Reset

// Default Handler
.section .text.default_handler,"ax",%progbits
default_handler:
    infinite_loop:
    b infinite_loop
.size default_handler, .-default_handler

// ISR vector
.section .isr_vector,"a",%progbits
.type isr_vector, %object

isr_vector:
    .word _estack
    .word Reset
    .word NMI
    .word Hard_Fault
    .word Memory_Management_Fault
    .word Bus_Fault
    .word Usage_Fault
    .word 0 // reserved
    .word 0 // reserved
    .word 0 // reserved
    .word 0 // reserved
    .word SVCall
    .word 0 // reserved
    .word 0 // reserved
    .word PendSV
    .word SysTick
    // .word IRQ0
    // .word IRQ1
    // ...

    .weak NMI
    .thumb_set NMI, default_handler

    .weak Hard_Fault
    .thumb_set Hard_Fault, default_handler

    .weak Memory_Management_Fault
    .thumb_set Memory_Management_Fault, default_handler

    .weak Bus_Fault
    .thumb_set Bus_Fault, default_handler

    .weak Usage_Fault
    .thumb_set Usage_Fault, default_handler

    .weak SVCall
    .thumb_set SVCall, default_handler

    .weak PendSV
    .thumb_set PendSV, default_handler

    .weak SysTick
    .thumb_set SysTick, default_handler
.size isr_vector, .-isr_vector
