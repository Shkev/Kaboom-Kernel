#include "idt_handlers.h"
#include "../lib.h"
#include "../i8259.h"

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
    cli();

    /* We read register C to see what type of interrupt occured.
    * If register C not read RTC will not send future interrupts */
    // select register C on RTC
    outb(0x0C, RTC_INDEX);
    // throw away info about interrupt. Change this later to do something
    (void)inb(RTC_DATA);
    test_interrupts();
    // send end of interrupt for IRQ8
    send_eoi(RTC_IRQ);
    
    sti();
}

void kbd_handler() {
    cli();

    char key_code_value[] = {'\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 
    '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', '\0', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '\0', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 
    'M', ',', '.', '/', '\0', '*', '\0', ' ', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
    '\0', '\0', '\0', '\0', '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', 
    '.', '\0', '\0', '\0', '\0', '\0'};

    uint8_t scan_code;
    scan_code = inb(KBD_PORT);
    
    if (scan_code <= 0x59) {
         uint8_t key_value = key_code_value[scan_code];
         printf("%c", key_value);
    }

    send_eoi(1);

    sti();
}
