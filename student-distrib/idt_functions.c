#include "x86_desc.h"
#include "lib.h"

extern void exp1();

void divide_zero_handler() {
    printf("EXCEPTION: div 0 error");
    while(1);
}

// void exp_debug(){
//     printf("EXCEPTION: debug error");
//     while(1);
// }
// void exp_nmi(){
//     printf("EXCEPTION: non maskable interrupt");
//     while(1);
// }
// void exp_breakpoint(){
//     printf("EXCEPTION: breakpoint");
//     while(1);
// }
// void exp_overflow(){
//     printf("EXCEPTION: overflow");
//     while(1);
// }
// void exp_bounds_range(){
//     printf("EXCEPTION: out of bounds");
//     while(1);
// }
// void exp_invalid_opcode(){
//     printf("EXCEPTION: invalid opcode");
//     while(1);
// }
// void exp_device_unavailable(){
//     printf("EXCEPTION: device unavailable");
//     while(1);
// }
// void exp_double_fault(){
//     printf("EXCEPTION: double fault");
//     while(1);
// }
// void exp_seg_overrun(){
//     printf("EXCEPTION: coprocessor segment overrun");
//     while(1);
// }
// void exp_invalid_tss(){
//     printf("EXCEPTION: invalid tss");
//     while(1);
// }
// void exp_seg_not_present(){
//     printf("EXCEPTION: segment not present");
//     while(1);
// }
// void exp_stack_seg_fault(){
//     printf("EXCEPTION: stack segment fault");
//     while(1);
// }
// void exp_general_protect_fault(){
//     printf("EXCEPTION: general protection fault");
//     while(1);
// }
// void exp_page_fault(){
//     printf("EXCEPTION: page fault");
//     while(1);
// }


// void exp_x87_floating_point(){
//     printf("EXCEPTION: x87 floating point exception");
//     while(1);
// }
// void exp_alignment_check(){
//     printf("EXCEPTION: alignment check");
//     while(1);
// }
// void exp_machine_check(){
//     printf("EXCEPTION: machine check");
//     while(1);
// }
// void exp_simd_float_point(){
//     printf("EXCEPTION: SIMD floating point exception");
//     while(1);
// }
// void exp_virtualization(){
//     printf("EXCEPTION: virtualization exception");
//     while(1);
// }
// void exp_control_protection(){
//     printf("EXCEPTION: control protection exception");
//     while(1);
// }
// void exp_hyper_injection(){
//     printf("EXCEPTION: hypervisor injection exception");
//     while(1);
// }
// void exp_vmm_communication(){
//     printf("EXCEPTION: VMM communication exception");
//     while(1);
// }
// void exp_security(){
//     printf("EXCEPTION: security exception");
//     while(1);
// }
// void exp_triple_fault(){
//     printf("EXCEPTION: triple fault");
//     while(1);
// }

// void int_keyboard();
// void int_rtc();
// void int_system_call();
