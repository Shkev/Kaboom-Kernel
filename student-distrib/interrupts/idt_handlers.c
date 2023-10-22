#include "idt_handlers.h"
#include "../lib.h"
#include "../i8259.h"

#define PRINT_HANDLER(task) printf("EXCEPTION: " task "error")

/*divide_zero_handler()
* DESCRIPTION: Prints the divide by zero exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void divide_zero_handler() {
    PRINT_HANDLER("divide_zero");
    while(1);
}

/*debug_handler()
* DESCRIPTION: Prints the debug handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void debug_handler() {
    PRINT_HANDLER("debug");
    while(1);
}

/*nmi_handler()
* DESCRIPTION: Prints the non maskable inturrupt exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void nmi_handler() {
    PRINT_HANDLER("nmi");
    while(1);
}

/*breakpoint_handler()
* DESCRIPTION: Prints the breakpoint handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void breakpoint_handler() {
    PRINT_HANDLER("breakpoint");
    while(1);
}

/*overflow_handler()
* DESCRIPTION: Prints the overflow handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void overflow_handler() {
    PRINT_HANDLER("overflow");
    while(1);
}

/*bnd_rng_exceed()
* DESCRIPTION: Prints the bounds range exceed exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void bnd_rng_exceed_handler() {
    PRINT_HANDLER("bnd_rng_exceed");
    while(1);
}

/*invalid_opcode_handler()
* DESCRIPTION: Prints the invalid opcode handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void invalid_opcode_handler() {
    PRINT_HANDLER("invalid_opcode");
    while(1);
}

/*device_na_handler()
* DESCRIPTION: Prints the device n/A handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void device_na_handler() {
    PRINT_HANDLER("device_na");
    while(1);
}

/*double_fault_handler()
* DESCRIPTION: Prints the double fault handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void double_fault_handler() {
    PRINT_HANDLER("double_fault");
    while(1);
}

/*seg_overrun_handler()
* DESCRIPTION: Prints the segment overrun handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void seg_overrun_handler() {
    PRINT_HANDLER("seg_overrun");
    while(1);
}

/*invalid_tss_handler()
* DESCRIPTION: Prints the invalid tss handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void invalid_tss_handler() {
    PRINT_HANDLER("invalid_tss");
    while(1);
}

/*seg_nopres_handler()
* DESCRIPTION: Prints exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void seg_nopres_handler() {
    PRINT_HANDLER("seg_nopres");
    while(1);
}

/*stack_segfault_handler()
* DESCRIPTION: Prints the stack segfault_handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void stack_segfault_handler() {
    PRINT_HANDLER("stack_segfault");
    while(1);
}

/*gen_protect_flt_handler()
* DESCRIPTION: Prints the exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void gen_protect_flt_handler() {
    PRINT_HANDLER("gen_protect_flt");
    while(1);
}

/*pg_fault_handler()
* DESCRIPTION: Prints the page fault handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void pg_fault_handler() {
    PRINT_HANDLER("pg");
    while(1);
}

/*x87_fpe_handler()
* DESCRIPTION: Prints the exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void x87_fpe_handler() {
    PRINT_HANDLER("x87_fpe");
    while(1);
}

/*align_check_handler()
* DESCRIPTION: Prints the align check handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void align_check_handler() {
    PRINT_HANDLER("align_check");
    while(1);
}

/*machine_check_handler()
* DESCRIPTION: Prints the machine check handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void machine_check_handler() {
    PRINT_HANDLER("machine_check");
    while(1);
}

/*simd_fpe_handler()
* DESCRIPTION: Prints the exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void simd_fpe_handler() {
    PRINT_HANDLER("simd_fpe");
    while(1);
}

/*virt_handler()
* DESCRIPTION: Prints the exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void virt_handler() {
    PRINT_HANDLER("virt");
    while(1);
}

/*ctl_protect_handler()
* DESCRIPTION: Prints the exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void ctl_protect_handler() {
    PRINT_HANDLER("ctl_protect");
    while(1);
}

/*hpi_handler()
* DESCRIPTION: Prints the exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void hpi_handler() {
    PRINT_HANDLER("hpi");
    while(1);
}

/*vmm_comm_handler()
* DESCRIPTION: Prints the exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void vmm_comm_handler() {
    PRINT_HANDLER("vmm_comm");
    while(1);
}

/*security_handler()
* DESCRIPTION: Prints the security handler exception and emulates blue screen of death by infinitly looping
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: the problem
*/
void security_handler() {
    PRINT_HANDLER("security");
    while(1);
}

/* Interrupt Handlers */
/*rtc_handler()
* DESCRIPTION: processes rtc interrupts
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: handles rtc, sends EOI when done
*/
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
    RTC_FLAG = 1;   //raise RTC flag when interrupt signal is recieved
    sti();
}

void system_call_handler() {
    PRINT_HANDLER("system call");
    while(1);
}

/*kbd_handler()
* DESCRIPTION: processes keyboard interrupts
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: handles keyboard, sends EOI when done
*/
void kbd_handler() {
    cli();

    /* array of characters corresponding to the scancode as the index */
    /* only characters in the scancode 1 are included for checkpoint 1 purposes*/
    char key_code_value[] = {'\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 
    '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '\0', 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 
    'm', ',', '.', '/', '\0', '*', '\0', ' ', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
    '\0', '\0', '\0', '\0', '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', 
    '.', '\0', '\0', '\0', '\0', '\0'};

    /* saves the scancode from the keyboard port*/
    uint8_t scan_code;
    scan_code = inb(KBD_PORT);
    
    /* If scancode is within our defined character values in the array, then it is printed*/
    if (scan_code <= 0x59) {
         uint8_t key_value = key_code_value[scan_code];
         printf("%c", key_value);
    }

    /*Sends en of interrupt signal for IRQ1*/
    send_eoi(1);

    sti();
}
