#include "../lib.h"
#include "../i8259.h"
#include "idt_handlers.h"

#define PRINT_HANDLER(task) printf("EXCEPTION: " task "error")

static void fill_buffer(int8_t* buf, int8_t val, uint32_t nbytes);

uint32_t RTC_FLAG = 0;


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
    //test_interrupts();
    // send end of interrupt for IRQ8
    send_eoi(RTC_IRQ);
    RTC_FLAG = 1;   //raise RTC flag when interrupt signal is recieved
    sti();
}

void system_call_handler() {
    PRINT_HANDLER("system call");
    while(1);
}


int shift = 0;
int capslock = 0;
int backspace = 0;
int tab = 0;
int ctrl = 0;
int keybuffcount = 0;

/*kbd_handler()
* DESCRIPTION: processes keyboard interrupts
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: handles keyboard, sends EOI when done
*/
void kbd_handler() {
    cli();
    
    enterflag = 0;
    /* array of characters corresponding to the scancode as the index */
    /* only characters in the scancode 1 are included for checkpoint 1 purposes*/
    char lower_case[] = {'\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 
    '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '\0', 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 
    'm', ',', '.', '/', '\0', '*', '\0', ' ', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
    '\0', '\0', '\0', '\0', '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', 
    '.', '\0', '\0', '\0', '\0', '\0'};

    char upper_case[] = {'\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 
    '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', '\0', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '\0', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 
    'M', ',', '.', '/', '\0', '*', '\0', ' ', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
    '\0', '\0', '\0', '\0', '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', 
    '.', '\0', '\0', '\0', '\0', '\0'};

    char schar[] = {'\0', '\0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 
    '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', '\0', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', '\0', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 
    'M', '<', '>', '?', '\0', '*', '\0', ' ', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
    '\0', '\0', '\0', '\0', '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', 
    '.', '\0', '\0', '\0', '\0', '\0'};

    // char schar[] = {'\0', '\0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 
    // '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', '\0', 'A', 'S',
    // 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', '\0', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 
    // 'M', '<', '>', '?', '\0', '*', '\0', ' ', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 
    // '\0', '\0', '\0', '\0', '\0', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', 
    // '.', '\0', '\0', '\0', '\0', '\0'};

    /* saves the scancode from the keyboard port*/
    uint8_t scan_code;
    scan_code = inb(KBD_PORT);
    
    /* If scancode is within our defined character values in the array, then it is printed*/
    uint8_t lower_case_key = lower_case[scan_code];
    uint8_t upper_case_key = upper_case[scan_code];
    uint8_t schar_case_key = schar[scan_code];

    //SHIFT RELEASE LOGIC
    if (((scan_code == LSHIFT_RELEASE) || (scan_code == RSHIFT_RELEASE)) && (shift == 1))
    {
        shift = 0;
    }

    //BACKSPACE LOGIC
    if (scan_code == 0x0E)
    {
        backspace = 1;
    } else if (scan_code == 0x8E)
    {
        // release
        backspace = 0;
    }

    //TAB LOGIC
    if (scan_code == 0x0F)
    {
        tab = 1;
    } else if (scan_code == 0x8F)
    {
        // release
        tab = 0;
    }

    //ENTER LOGIC
    if (scan_code == 0x1C)
    {
        enterflag = 1;
    } else if (scan_code == 0x9C)
    {
        // release
        fill_buffer(keybuff, '\0', KEYBUF_MAX_SIZE);
        enterflag = 0;
    }

    //CTRL LOGIC
    if (scan_code == 0x1D)
    {
        ctrl = 1;
    } else if (scan_code == 0x9D)
    {
        // release
        ctrl = 0;
    }

    //PRESSING LOGIC
    if (keybuffcount >= KEYBUF_MAX_SIZE-1)
    {
        if(enterflag == 1) 
        {
            putc('\n');
            // keybuff[keybuffcount] = '\n';
            keybuffbackup = keybuffcount;
            keybuffcount = 0; 
        } else if (backspace == 1)
        {
            putc('\b');
            keybuff[--keybuffcount] = '\0';
        } else if ((ctrl == 1) && (scan_code == 0x26)) {
            clear();
            keybuffcount = 0;
            fill_buffer(keybuff, '\0', KEYBUF_MAX_SIZE);
        } 
    }
    else
    {
        if (backspace == 1)
        {
            if(keybuffcount != 0)
            {
                putc('\b');
                keybuff[--keybuffcount] = '\0';
            }
        } else if (tab == 1)
        {
            if (keybuffcount < KEYBUF_MAX_SIZE - TABSIZE - 1)
            {
                putc('\t');
                keybuff[keybuffcount++] = ' ';
                keybuff[keybuffcount++] = ' ';
                keybuff[keybuffcount++] = ' ';
                keybuff[keybuffcount++] = ' ';
            }
        } else if (enterflag == 1) {
            putc('\n');
            keybuffbackup = keybuffcount;
            keybuffcount = 0;   
        } else {
            if (scan_code <= 0x58) {
                if(scan_code == 0x3A && capslock == 0)
                {
                    capslock = 1;
                } else if (scan_code == 0x3A && capslock == 1)
                {
                    capslock = 0;
                } else if (((scan_code == 0x2A) || (scan_code == 0x36)) && (shift == 0)){
                    shift = 1;
                } else if ((ctrl == 1) && (scan_code == 0x26)) {
                    clear();
                    fill_buffer(keybuff, '\0', KEYBUF_MAX_SIZE);
                    keybuffcount = 0;
                } else {
                    // num pad support... does nothing for now but adds a long list of ifs :)
                    if (scan_code == 0x38) {
                        // left alt press
                    } else if (scan_code == 0x1D) {
                        // left control press
                    } else if (scan_code == 0x2A) {
                        // left shift press
                    } else if (scan_code == 0x36) {
                        // right shift press
                    } else if (scan_code == 0x3A) {
                        // caps lock press
                    } else if (scan_code == 0xB8) {
                        // left alt release
                    } else if (scan_code == 0x9D) {
                        // left control release
                    } else if (scan_code == 0xAA) {
                        // left shift release
                    } else if (scan_code == 0xB6) {
                        // right shift release
                    } else if (scan_code == 0xBA) {
                        // caps lock release
                    } else if (scan_code == 0x01) {

                    } else if (scan_code == 0x3B) {
                    
                    } else if (scan_code == 0xFC) {
                    
                    } else if (scan_code == 0x37) {

                    } else if (scan_code == 0x3D) {
                    
                    } else if (scan_code == 0x3E) {
                    
                    } else if (scan_code == 0x3F) {

                    } else if (scan_code == 0x40) {

                    } else if (scan_code == 0x41) {

                    } else if (scan_code == 0x42) {

                    } else if (scan_code == 0x43) {

                    } else if (scan_code == 0x44) {

                    } else if (scan_code == 0x45) {

                    } else if (scan_code == 0x46) {
                    
                    } else if (scan_code == 0x47) {

                    } else if (scan_code == 0x48) {
                    
                    } else if (scan_code == 0x49) {

                    } else if (scan_code == 0x4A) {

                    } else if (scan_code == 0x4B) {
                    
                    } else if (scan_code == 0x4C) {

                    } else if (scan_code == 0x4D) {
                    
                    } else if (scan_code == 0x4E) {
                    
                    } else if (scan_code == 0x4F) {

                    } else if (scan_code == 0x50) {

                    } else if (scan_code == 0x51) {

                    } else if (scan_code == 0x52) {
                    
                    } else if (scan_code == 0x53) {
                    
                    } else if (scan_code == 0x57) {
                    
                    } else if (scan_code == 0x58) {
                        
                    } else {
                        if ((capslock == 1 || shift == 1) && ctrl == 0)
                        {
                            if (capslock == 1 && shift == 1)
                            {
                                // caps lock pressed and want special char
                                if ((scan_code == 0x29) || (scan_code == 0x02) || (scan_code == 0x03) || (scan_code == 0x04) || (scan_code == 0x05) || (scan_code == 0x06) || (scan_code == 0x07) || (scan_code == 0x08) || (scan_code == 0x09) || (scan_code == 0x0A) || (scan_code == 0x0B) || (scan_code == 0x0C) || (scan_code == 0x0D) || (scan_code == 0x1A) || (scan_code == 0x1B) || (scan_code == 0x2B) || (scan_code == 0x27) || (scan_code == 0x28) || (scan_code == 0x33) || (scan_code == 0x34) || (scan_code == 0x35))
                                {
                                    printf("%c", schar_case_key);
                                    keybuff[keybuffcount] = schar_case_key;
                                    keybuffcount++;
                                } else {
                                    printf("%c", lower_case_key);
                                    keybuff[keybuffcount] = lower_case_key;
                                    keybuffcount++;
                                }
                            } else if (shift == 1) {
                                printf("%c", schar_case_key);
                                keybuff[keybuffcount] = schar_case_key;
                                keybuffcount++;
                            } else {
                                printf("%c", upper_case_key);
                                keybuff[keybuffcount] = upper_case_key;
                                keybuffcount++;
                            }
                        } else {
                            printf("%c", lower_case_key);
                            keybuff[keybuffcount] = lower_case_key;
                            keybuffcount++;
                        }
                    }
                }
            }
        }
    }

    /*Sends en of interrupt signal for IRQ1*/
    send_eoi(1);

    sti();
}


static void fill_buffer(int8_t* buf, int8_t val, uint32_t nbytes) {
    int i;
    for (i = 0; i < nbytes; ++i) {
        buf[i] = val;
    }
}