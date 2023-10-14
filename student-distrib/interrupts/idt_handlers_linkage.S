.text

.globl divide_zero_linkage, debug_linkage, nmi_linkage, breakpoint_linkage, overflow_linkage, bnd_rng_exceed_linkage, invalid_opcode_linkage, device_na_linkage, double_fault_linkage, seg_overrun_linkage, invalid_tss_linkage, seg_nopres_linkage, stack_segfault_linkage, gen_protect_flt_linkage, pg_fault_linkage, x87_fpe_linkage, align_check_linkage, machine_check_linkage, simd_fpe_linkage, virt_linkage, ctl_protect_linkage, hpi_linkage, vmm_comm_linkage, security_linkage
.globl divide_zero_handler, debug_handler, nmi_handler, breakpoint_handler, overflow_handler, bnd_rng_exceed_handler, invalid_opcode_handler, device_na_handler, double_fault_handler, seg_overrun_handler, invalid_tss_handler, seg_nopres_handler, stack_segfault_handler, gen_protect_flt_handler, pg_fault_handler, x87_fpe_handler, align_check_handler, machine_check_handler, simd_fpe_handler, virt_handler, ctl_protect_handler, hpi_handler, vmm_comm_handler, security_handler

divide_zero_linkage:
    pushal
    pushfl
    call divide_zero_handler
    popfl
    popal
    iret
        
debug_linkage:
    pushal
    pushfl
    call debug_handler
    popfl
    popal
    iret
        
nmi_linkage:
    pushal
    pushfl
    call nmi_handler
    popfl
    popal
    iret
        
breakpoint_linkage:
    pushal
    pushfl
    call breakpoint_handler
    popfl
    popal
    iret
        
overflow_linkage:
    pushal
    pushfl
    call overflow_handler
    popfl
    popal
    iret
        
bnd_rng_exceed_linkage:
    pushal
    pushfl
    call bnd_rng_exceed_handler
    popfl
    popal
    iret
        
invalid_opcode_linkage:
    pushal
    pushfl
    call invalid_opcode_handler
    popfl
    popal
    iret
        
device_na_linkage:
    pushal
    pushfl
    call device_na_handler
    popfl
    popal
    iret
        
double_fault_linkage:
    pushal
    pushfl
    call double_fault_handler
    popfl
    popal
    iret
        
seg_overrun_linkage:
    pushal
    pushfl
    call seg_overrun_handler
    popfl
    popal
    iret
        
invalid_tss_linkage:
    pushal
    pushfl
    call invalid_tss_handler
    popfl
    popal
    iret
        
seg_nopres_linkage:
    pushal
    pushfl
    call seg_nopres_handler
    popfl
    popal
    iret
        
stack_segfault_linkage:
    pushal
    pushfl
    call stack_segfault_handler
    popfl
    popal
    iret
        
gen_protect_flt_linkage:
    pushal
    pushfl
    call gen_protect_flt_handler
    popfl
    popal
    iret
        
pg_fault_linkage:
    pushal
    pushfl
    call pg_fault_handler
    popfl
    popal
    iret
        
x87_fpe_linkage:
    pushal
    pushfl
    call x87_fpe_handler
    popfl
    popal
    iret
        
align_check_linkage:
    pushal
    pushfl
    call align_check_handler
    popfl
    popal
    iret
        
machine_check_linkage:
    pushal
    pushfl
    call machine_check_handler
    popfl
    popal
    iret
        
simd_fpe_linkage:
    pushal
    pushfl
    call simd_fpe_handler
    popfl
    popal
    iret
        
virt_linkage:
    pushal
    pushfl
    call virt_handler
    popfl
    popal
    iret
        
ctl_protect_linkage:
    pushal
    pushfl
    call ctl_protect_handler
    popfl
    popal
    iret
        
hpi_linkage:
    pushal
    pushfl
    call hpi_handler
    popfl
    popal
    iret
        
vmm_comm_linkage:
    pushal
    pushfl
    call vmm_comm_handler
    popfl
    popal
    iret
        
security_linkage:
    pushal
    pushfl
    call security_handler
    popfl
    popal
    iret
        
