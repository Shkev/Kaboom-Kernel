.text

.globl divide_zero_linkage
.globl divide_zero_handler 	# defined externally

divide_zero_linkage:
    pushal
    pushfl
    call divide_zero_handler
    popfl
    popal
    iret

/*
debug:
    pushal
    pushfl
    call exp_debug
    popfl
    popal
    iret

nmi:
    pushal
    pushfl
    call exp_nmi
    popfl
    popal
    iret

breakpoint:
    pushal
    pushfl
    call exp_breakpoint
    popfl
    popal
    iret

overflow:
    pushal
    pushfl
    call exp_overflow
    popfl
    popal
    iret

bounds_range:
    pushal
    pushfl
    call exp_bounds_range
    popfl
    popal
    iret

invalid_opcode:
    pushal
    pushfl
    call exp_invalid_opcode
    popfl
    popal
    iret

device_unavailable:
    pushal
    pushfl
    call exp_device_unavailable
    popfl
    popal
    iret

double_fault:
    pushal
    pushfl
    call exp_double_fault
    popfl
    popal
    iret

seg_overrun:
    pushal
    pushfl
    call exp_seg_overrun
    popfl
    popal
    iret
invalid_tss:
    pushal
    pushfl
    call exp_invalid_tss
    popfl
    popal
    iret

seg_not_present:
    pushal
    pushfl
    call exp_seg_not_resent
    popfl
    popal
    iret

stack_seg_fault:
    pushal
    pushfl
    call exp_stack_seg_fault
    popfl
    popal
    iret

general_protect_fault:
    pushal
    pushfl
    call exp_general_protect_fault
    popfl
    popal
    iret
page_fault:
    pushal
    pushfl
    call exp_page_fault
    popfl
    popal
    iret

x87_floating_point:
    pushal
    pushfl
    call exp_x87_floating_point
    popfl
    popal
    iret
alignment_check:
    pushal
    pushfl
    call exp_alignment_check
    popfl
    popal
    iret
machine_check:
    pushal
    pushfl
    call exp_machine_check
    popfl
    popal
    iret
simd_float_point:
    pushal
    pushfl
    call exp_simd_float_point
    popfl
    popal
    iret

virtualization:
    pushal
    pushfl
    call exp_virtualization
    popfl
    popal
    iret

control_protection:
    pushal
    pushfl
    call exp_control_protection
    popfl
    popal
    iret

hyper_injection:
    pushal
    pushfl
    call exp_hyper_injection
    popfl
    popal
    iret
vmm_communication:
    pushal
    pushfl
    call exp_vmm_communication
    popfl
    popal
    iret

security:
    pushal
    pushfl
    call exp_security
    popfl
    popal
    iret

keyboard:
    pushal
    pushfl
    call int_keyboard
    popfl
    popal
    iret

rtc:
    pushal
    pushfl
    call int_rtc
    popfl
    popal
    iret

system_call:
    pushal
    pushfl
    call int_system_call
    popfl
    popal
    iret
*/
