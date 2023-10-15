#ifndef IDT_FNCS_H
#define IDT_FNCS_H

#include "../init_devices.h"

#define KBD_PORT 0x60

/* Exception handlers. These are the functions that are called when an
* exception occurs in kernel */

/* TODO - add comments */

extern void divide_zero_handler();

extern void debug_handler();

/* Non-maskable interrupt handler */
extern void nmi_handler();

extern void breakpoint_handler();

extern void overflow_handler();

extern void bnd_rng_exceed_handler();

extern void invalid_opcode_handler();

extern void device_na_handler();

extern void double_fault_handler();

/* maybe deprecated (?) */
extern void seg_overrun_handler();

extern void invalid_tss_handler();

extern void seg_nopres_handler();

extern void stack_segfault_handler();

extern void gen_protect_flt_handler();

/* page fault */
extern void pg_fault_handler();

extern void x87_fpe_handler();

extern void align_check_handler();

extern void machine_check_handler();

extern void simd_fpe_handler();

extern void virt_handler();

extern void ctl_protect_handler();

/* Hypervisor Injection Exception */
extern void hpi_handler();

/* VMM Communication Exception handler */
extern void vmm_comm_handler();

/* security exception handler */
extern void security_handler();


/* Interrupt handlers. Do something in response to interrupt from a device */

extern void rtc_handler();

extern void kbd_handler();

/* ----------------------------------------------------------------- */

/* Exception functions. Assembly wrappers around interrupt handlers.
* These functions are called within the C code and are implemented in idt_handlers_linkage.S.
* Push all necessary flag and other registers before calling their corresponding interrupt handler.
* TODO - Does this generalize to chained handlers? */

extern void divide_zero_linkage();

extern void debug_linkage();

/* Non-maskable interrupt linkage */
extern void nmi_linkage();

extern void breakpoint_linkage();

extern void overflow_linkage();

extern void bnd_rng_exceed_linkage();

extern void invalid_opcode_linkage();

extern void device_na_linkage();

extern void double_fault_linkage();

/* maybe deprecated (?) */
extern void seg_overrun_linkage();

extern void invalid_tss_linkage();

extern void seg_nopres_linkage();

extern void stack_segfault_linkage();

extern void gen_protect_flt_linkage();

extern void pg_fault_linkage();

extern void x87_fpe_linkage();

extern void align_check_linkage();

extern void machine_check_linkage();

extern void simd_fpe_linkage();

extern void virt_linkage();

extern void ctl_protect_linkage();

extern void hpi_linkage();

extern void vmm_comm_linkage();

extern void security_linkage();

/* linkage for interrupts */

extern void rtc_linkage();

extern void kbd_linkage();

#endif // IDT_FNCS_H
