#include "idt_handlers.h"
#include "../lib.h"

#define PRINT_HANDLER(task) printf("EXCEPTION: " task "error")

void divide_zero_handler() {
    PRINT_HANDLER("divide_zero");
    while(1);
}

void debug_handler() {
    PRINT_HANDLER("debug");
    while(1);
}

void nmi_handler() {
    PRINT_HANDLER("nmi");
    while(1);
}

void breakpoint_handler() {
    PRINT_HANDLER("breakpoint");
    while(1);
}

void overflow_handler() {
    PRINT_HANDLER("overflow");
    while(1);
}

void bnd_rng_exceed_handler() {
    PRINT_HANDLER("bnd_rng_exceed");
    while(1);
}

void invalid_opcode_handler() {
    PRINT_HANDLER("invalid_opcode");
    while(1);
}

void device_na_handler() {
    PRINT_HANDLER("device_na");
    while(1);
}

void double_fault_handler() {
    PRINT_HANDLER("double_fault");
    while(1);
}

void seg_overrun_handler() {
    PRINT_HANDLER("seg_overrun");
    while(1);
}

void invalid_tss_handler() {
    PRINT_HANDLER("invalid_tss");
    while(1);
}

void seg_nopres_handler() {
    PRINT_HANDLER("seg_nopres");
    while(1);
}

void stack_segfault_handler() {
    PRINT_HANDLER("stack_segfault");
    while(1);
}

void gen_protect_flt_handler() {
    PRINT_HANDLER("gen_protect_flt");
    while(1);
}

void pg_fault_handler() {
    PRINT_HANDLER("pg");
    while(1);
}

void x87_fpe_handler() {
    PRINT_HANDLER("x87_fpe");
    while(1);
}

void align_check_handler() {
    PRINT_HANDLER("align_check");
    while(1);
}

void machine_check_handler() {
    PRINT_HANDLER("machine_check");
    while(1);
}

void simd_fpe_handler() {
    PRINT_HANDLER("simd_fpe");
    while(1);
}

void virt_handler() {
    PRINT_HANDLER("virt");
    while(1);
}

void ctl_protect_handler() {
    PRINT_HANDLER("ctl_protect");
    while(1);
}

void hpi_handler() {
    PRINT_HANDLER("hpi");
    while(1);
}

void vmm_comm_handler() {
    PRINT_HANDLER("vmm_comm");
    while(1);
}

void security_handler() {
    PRINT_HANDLER("security");
    while(1);
}

/* Interrupt Handlers */

void rtc_handler() {
    /* We read register C to see what type of interrupt occured.
    * If register C not read RTC will not send future interrupts */
    // select register C on RTC
    outb(0x0C, 0x70);
    // throw away info about interrupt. Change this later to do something
    (void)inb(0x71);
    
    test_interrupts();
}

void kbd_handler() {
    
}
