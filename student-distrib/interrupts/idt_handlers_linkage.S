#define INTR_LINK(link_name, handler) \
    .globl link_name                 ;\
    link_name:                       ;\
	pushal                       ;\
	pushfl                       ;\
	call handler                 ;\
	popfl                        ;\
	popal                        ;\
	iret                 
	
.text

### Linkage for exception handlers 

INTR_LINK(divide_zero_linkage, divide_zero_handler)

INTR_LINK(debug_linkage, debug_handler)

INTR_LINK(nmi_linkage, nmi_handler)

INTR_LINK(breakpoint_linkage, breakpoint_handler)

INTR_LINK(overflow_linkage, overflow_handler)

INTR_LINK(bnd_rng_exceed_linkage, bnd_rng_exceed_handler)

INTR_LINK(invalid_opcode_linkage, invalid_opcode_handler)

INTR_LINK(device_na_linkage, device_na_handler)

INTR_LINK(double_fault_linkage, double_fault_handler)

INTR_LINK(seg_overrun_linkage, seg_overrun_handler)

INTR_LINK(invalid_tss_linkage, invalid_tss_handler)

INTR_LINK(seg_nopres_linkage, seg_nopres_handler)

INTR_LINK(stack_segfault_linkage, stack_segfault_handler)

INTR_LINK(gen_protect_flt_linkage, gen_protect_flt_handler)

INTR_LINK(pg_fault_linkage, pg_fault_handler)

INTR_LINK(x87_fpe_linkage, x87_fpe_handler)

INTR_LINK(align_check_linkage, align_check_handler)

INTR_LINK(machine_check_linkage, machine_check_handler)

INTR_LINK(simd_fpe_linkage, simd_fpe_handler)

INTR_LINK(virt_linkage, virt_handler)

INTR_LINK(ctl_protect_linkage, ctl_protect_handler)

INTR_LINK(hpi_linkage, hpi_handler)

INTR_LINK(vmm_comm_linkage, vmm_comm_handler)

INTR_LINK(security_linkage, security_handler)

### Linkage for interrupt handlers
	
INTR_LINK(rtc_linkage, rtc_handler)

INTR_LINK(kbd_linkage, kbd_handler
	
