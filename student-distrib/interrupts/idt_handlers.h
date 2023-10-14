#ifndef IDT_FNCS_H
#define IDT_FNCS_H

/* IDT handlers. These are the functions that are called when an
* interrupt is requested by a device. */

extern void divide_zero_handler();

// extern void x87_floating_point();
// extern void alignment_check();
// extern void machine_check();
// extern void simd_float_point();
// extern void virtualization();
// extern void control_protection();

// extern void hyper_injection();
// extern void vmm_communication();
// extern void security();

// extern void keyboard();
// extern void rtc();
// extern void system_call();

/* ----------------------------------------------------------------- */

/* Exception functions. Assembly wrappers around interrupt handlers.
* These functions are called within the C code and are implemented in idt_handlers_linkage.S.
* Push all necessary flag and other registers before calling their corresponding interrupt handler.
* TODO - Does this generalize to chained handlers? */

extern void divide_zero_linkage();

#endif // IDT_FNCS_H
