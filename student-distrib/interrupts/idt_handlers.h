#ifndef IDT_FNCS_H
#define IDT_FNCS_H

#include "../init_devices.h"
#include "../types.h"

#define KBD_PORT 0x60
#define KEYBUF_MAX_SIZE 128
#define TABSIZE 4
#define LSHIFT_RELEASE 0xAA
#define RSHIFT_RELEASE 0xB6
#define BACKSPACE_PRESSED 0x0E
#define BACKSPACE_RELEASE 0x8E
#define TAB_PRESSED 0x0F
#define TAB_RELEASE 0x8F
#define ENTER_PRESSED 0x1C
#define ENTER_RELEASE 0x9C
#define F12_BOUNDS 0x58
#define CAPSLOCK_PRESSED 0x3A
#define LEFTSHIFT_PRESSED 0x2A
#define RIGHTSHIFT_PRESSED 0x36
#define L_PRESS 0x26
#define LEFTALT_PRESSED 0x38
#define LEFTCTRL_PRESSED 0x1D
#define LEFTALT_RELEASE 0xB8
#define LEFTCTRL_RELEASE 0x9D
#define CAPSLOCK_RELEASE 0xBA
#define ESCAPE_PRESSED 0x01
#define F1_PRESSED 0x3B
#define F2_PRESSED 0x3C
#define KEYPADMULT_PRESSED 0x37
#define F3_PRESSED 0x3D
#define F4_PRESSED 0x3E
#define F5_PRESSED 0x3F
#define F6_PRESSED 0x40
#define F7_PRESSED 0x41
#define F8_PRESSED 0x42
#define F9_PRESSED 0x43
#define F10_PRESSED 0x44
#define NUMLOCK_PRESSED 0x45
#define SCROLLLOCK_PRESSED 0x46
#define KEYPAD7_PRESSED 0x47
#define KEYPAD8_PRESSED 0x48
#define KEYPAD9_PRESSED 0x49
#define KEYPADMINUS_PRESSED 0x4A
#define KEYPAD4_PRESSED 0x4B
#define KEYPAD5_PRESSED 0x4C
#define KEYPAD6_PRESSED 0x4D
#define KEYPADPLUS_PRESSED 0x4E
#define KEYPAD1_PRESSED 0x4F
#define KEYPAD2_PRESSED 0x50
#define KEYPAD3_PRESSED 0x51
#define KEYPAD0_PRESSED 0x52
#define KEYPADPERIOD_PRESSED 0x53
#define F11_PRESSED 0x57
#define F12_PRESSED 0x58
#define BACKTICK_PRESSED 0x29
#define ONE_PRESSED 0x02
#define TWO_PRESSED 0x03
#define THREE_PRESSED 0x04
#define FOUR_PRESSED 0x05
#define FIVE_PRESSED 0x06
#define SIX_PRESSED 0x07
#define SEVEN_PRESSED 0x08
#define EIGHT_PRESSED 0x09
#define NINE_PRESSED 0x0A
#define ZERO_PRESSED 0x0B
#define MINUS_PRESSED 0x0C
#define EQUAL_PRESSED 0x0D
#define LEFTBRACKET_PRESSED 0x1A
#define RIGHTBRACKET_PRESSED 0x1B
#define BACKSLASH_PRESSED 0x2B
#define SEMICOLON_PRESSED 0x27
#define SINGLEQUOTE_PRESSED 0x28
#define COMMA_PRESSED 0x33
#define PERIOD_PRESSED 0x34
#define FORWARDSLASH_PRESSED 0x35

extern char keybuff[KEYBUF_MAX_SIZE];

extern uint32_t rtc_flag;

int enterflag;
int keybuffbackup;


/* Exception handlers. These are the functions that are called when an
* exception occurs in kernel */

/* TODO - add comments */

/* Divide by zero exception handler */
extern void divide_zero_handler();

/* Debug exception handler */
extern void debug_handler();

/* Non-maskable interrupt exception handler */
extern void nmi_handler();

/* Breakpoint exception handler*/
extern void breakpoint_handler();

/* Overflow exception handler*/
extern void overflow_handler();

/* Bound Range Exceeded handler */
extern void bnd_rng_exceed_handler();

/* Invalid opcode exception handler */
extern void invalid_opcode_handler();

/* Device not available exception handler*/
extern void device_na_handler();

/* Double fault exception handler*/
extern void double_fault_handler();

/* Coprocessor segment overrun exception handler*/
extern void seg_overrun_handler();

/* Invalid TSS exception handler*/
extern void invalid_tss_handler();

/* Segment not present exception handler*/
extern void seg_nopres_handler();

/* Stack segment fault exception handler*/
extern void stack_segfault_handler();

/* General protection fault exception handler*/
extern void gen_protect_flt_handler();

/* page fault exception handler*/
extern void pg_fault_handler();

/* x87 floating-point exception handler*/
extern void x87_fpe_handler();

/* Alignment check exception handler*/
extern void align_check_handler();

/* Machine check exception handler*/
extern void machine_check_handler();

/* SIMD floating point exception handler*/
extern void simd_fpe_handler();

/* Virualization exception handler*/
extern void virt_handler();

/* Control protection exception handler*/
extern void ctl_protect_handler();

/* Hypervisor Injection Exception handler*/
extern void hpi_handler();

/* VMM Communication Exception handler */
extern void vmm_comm_handler();

/* Security exception handler */
extern void security_handler();


/* Interrupt handlers. Do something in response to interrupt from a device */

extern void rtc_handler(); //RTC

extern void kbd_handler(); //Keyboard handler

extern void system_call_handler(); //system call

/* ----------------------------------------------------------------- */

/* Exception functions. Assembly wrappers around interrupt handlers.
* These functions are called within the C code and are implemented in idt_handlers_linkage.S.
* Push all necessary flag and other registers before calling their corresponding interrupt handler.
* TODO - Does this generalize to chained handlers? */

/* Divide by zero exception linkage */
extern void divide_zero_linkage();

/* Debug exception linkage */
extern void debug_linkage();

/* Non-maskable interrupt exception linkage */
extern void nmi_linkage();

/* Breakpoint exception linkage*/
extern void breakpoint_linkage();

/* Overflow exception linkage*/
extern void overflow_linkage();

/* Bound Range Exceeded linkage */
extern void bnd_rng_exceed_linkage();

/* Invalid opcode exception linkage */
extern void invalid_opcode_linkage();

/* Device not available exception linkage*/
extern void device_na_linkage();

/* Double fault exception linkage*/
extern void double_fault_linkage();

/* Coprocessor segment overrun exception linkage*/
extern void seg_overrun_linkage();

/* Invalid TSS exception linkage*/
extern void invalid_tss_linkage();

/* Segment not present exception linkage*/
extern void seg_nopres_linkage();

/* Stack segment fault exception linkage*/
extern void stack_segfault_linkage();

/* General protection fault exception linkage*/
extern void gen_protect_flt_linkage();

/* page fault exception linkage*/
extern void pg_fault_linkage();

/* x87 floating-point exception linkage*/
extern void x87_fpe_linkage();

/* Alignment check exception linkage*/
extern void align_check_linkage();

/* Machine check exception linkage*/
extern void machine_check_linkage();

/* SIMD floating point exception linkage*/
extern void simd_fpe_linkage();

/* Virualization exception linkage*/
extern void virt_linkage();

/* Control protection exception linkage*/
extern void ctl_protect_linkage();

/* Hypervisor Injection Exception linkage*/
extern void hpi_linkage();

/* VMM Communication Exception linkage */
extern void vmm_comm_linkage();

/* Security exception linkage */
extern void security_linkage();


/* linkage for interrupts */

extern void rtc_linkage(); //RTC

extern void kbd_linkage(); //Keyboard 

extern void system_call_linkage(); //system call

#endif // IDT_FNCS_H
