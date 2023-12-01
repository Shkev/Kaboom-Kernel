#include "sched.h"
#include "../lib.h"

volatile uint8_t curr_term = 0;
term_info_t terminals[MAX_TERMINAL];

/////////// HELPER FUNCTIONS ///////////////////

static void setup_term_page(term_id_t term_id);
static void swap_out_curr_term();
static void swap_in_next_term(term_id_t term_id);

static pid_t next_active_pid();

////////////////////////////////////////////////

////////////////// TERMINAL STUFF ////////////////////////////////

/* init_term()
 * 
 * DESCRIPTION:   initialize new terminal and set curr_term to its terminal id
 * INPUTS:        term_id  -  id of new terminal to initialize
 * OUTPUTS:       none
 * RETURNS:       0 on success, negative value on failure
 * SIDE EFFECTS:  new term info struct populated in global terminals state.
 */
int32_t init_term(term_id_t term_id) {
    if (invalid_term_id(term_id)) {
	return -1;
    }
    
    const uint32_t term_vidmem_addr = TERM0_VIDMEM_ADDR + term_id*PAGE_SIZE_4KB;
    terminals[term_id].vidmem_addr = term_vidmem_addr;
    setup_term_page(term_id);
    
    terminals[term_id].cursor_x = 0;
    terminals[term_id].cursor_y = 0;
    terminals[term_id].term_id = term_id;
    terminals[term_id].nprocess = 0;
    terminals[term_id].keybufcnt = 0;
    terminals[term_id].prev_keybufcnt = 0;
    terminals[term_id].key_flags = 0;
    terminals[term_id].curr_pid = -1;
    memset(terminals[term_id].keybuf, '\0', KEYBUF_MAX_SIZE);

    return 0;
}


/* invalid_term_id()
 * 
 * DESCRIPTION:   determines whether given terminal id is considered invalid
 * INPUTS:        term_id  -  id of new terminal to check
 * OUTPUTS:       none
 * RETURNS:       nonzero value if given id is invalid, otherwise 0.
 * SIDE EFFECTS:  new term info struct populated in global terminals state.
 */
int32_t invalid_term_id(term_id_t term_id) {
    return term_id >= MAX_TERMINAL;
}


/* switch_terminal()
 * 
 * DESCRIPTION:   switch active terminal to terminal with given id
 * INPUTS:        term_id  -  id of terminal to switch to
 * OUTPUTS:       none
 * RETURNS:       none
 * SIDE EFFECTS:  change current terminal and modify page tables
 */
void switch_terminal(term_id_t term_id) {
    // TODO
    swap_out_curr_term();
    swap_in_next_term(term_id);
    flush_tlb();
}


/* setup_term_page()
 * 
 * DESCRIPTION:   setup page in page table for terminal's vidmem
 * INPUTS:        term_id  -  id of terminal to setup
 * OUTPUTS:       none
 * RETURNS:       none
 * SIDE EFFECTS:  modifies page tables
 */
static void setup_term_page(term_id_t term_id) {
    uint32_t pt_idx = get_pt_idx(terminals[term_id].vidmem_addr);

    pt0[pt_idx].present = 1;
    pt0[pt_idx].rw = 1;
    // vmem and physical address are the same (like for actual vidmem and kernel)
    pt0[pt_idx].page_baseaddr = terminals[term_id].vidmem_addr >> 12;
    flush_tlb();
}


void swap_out_curr_term() {
    // saving screen x, y done through lib.c function (i.e., printf, putc, etc.)
    // doing video memory copying stuff here...
    const uint32_t term_vidmem_addr = TERM0_VIDMEM_ADDR + curr_term*PAGE_SIZE_4KB;
    terminals[curr_term].vidmem_addr = term_vidmem_addr;
    memcpy((char*)term_vidmem_addr, (char*)VIDEO, PAGE_SIZE_4KB);
}


void swap_in_next_term(term_id_t term_id) {
    curr_term = term_id; 	/* handles restoring cursor position */
    const uint32_t term_vidmem_addr = TERM0_VIDMEM_ADDR + term_id*PAGE_SIZE_4KB;
    memcpy((char*)VIDEO, (char*)term_vidmem_addr, PAGE_SIZE_4KB);
    terminals[term_id].vidmem_addr = VIDEO;
    update_cursor(terminals[term_id].cursor_x, terminals[term_id].cursor_y);
}

////////////////////// SCHEDULING PROCESSES STUFF ///////////////////////////

/* schedule()
 * 
 * DESCRIPTION:   switch to next process in run queue
 * INPUTS:        none
 * OUTPUTS:       none
 * RETURNS:       none
 * SIDE EFFECTS:  modify esp, ebp, tss, eip
 */
void schedule() {
    pid_t next_pid = next_active_pid();
    if (next_pid == -1) { 	/* no process to schedule, should never happen since shell always running */
	return;
    }

    // save current procss stack pointers
    register uint32_t saved_ebp asm("ebp");
    register uint32_t saved_esp asm("esp");
    /* asm volatile( */
    /* 	"movl %%ebp, %0;" */
    /* 	"movl %%esp, %1;" */
    /* 	: "=r"(saved_ebp), "=r"(saved_esp) */
    /* 	: */
    /* 	: "memory", "cc" */
    /* 	); */
    pcb_arr[curr_pid]->stack_ptr = saved_esp;
    pcb_arr[curr_pid]->stack_base_ptr = saved_ebp;
    
    curr_pid = next_pid;
    set_process_tss(next_pid);
    
    /* if (next_pid == 3) { */
    /* 	printf("state: %d ", pcb_arr[curr_pid]->state); */
    /* } */
    
    // swap to next process kernel stack
    saved_ebp = pcb_arr[next_pid]->stack_base_ptr;
    saved_esp = pcb_arr[next_pid]->stack_ptr;
    asm volatile(
	"movl %0, %%ebp;"
	"movl %1, %%esp;"
	:   
	: "r"(saved_ebp), "r"(saved_esp)
	: "memory", "cc"
	);

    return;
}


pid_t next_active_pid() {
    pid_t i;
    for (i = curr_pid+1; i < NUM_PROCESS; ++i) {
	if (pcb_arr[i] != NULL && pcb_arr[i]->state == ACTIVE) {
	    return i;
	}
    }
    for (i = 0; i <= curr_pid; ++i) {
	if (pcb_arr[i] != NULL && pcb_arr[i]->state == ACTIVE) {
	    return i;
	}
    }
    return -1;
}
