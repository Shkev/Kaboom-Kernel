#include "process.h"
#include "../x86_desc.h"
#include "../filesystems/filesystem.h"
#include "syscalls.h"

int32_t curr_pid = -1;
pcb_t* pcb_arr[NUM_PROCCESS];
uint32_t return_status = 0;

volatile uint32_t exception_flag = 0;
static inline void flush_tlb();

static int32_t get_next_pid(int32_t pid);

/////////////////// SYSTEM EXECUTE HELPERS /////////////////////////////

/* parse args from shell */
static int32_t parse_args(const int8_t* arg, int8_t* const buf);

/* check if file with given contents is an executable */
static inline uint32_t is_executable(const int8_t* file_contents);

/* setup process page addresses for process with given pid */
static void setup_process_page(int32_t pid);

/* initialize pcb memory block in kernel for given pid */
static pcb_t* create_new_pcb();

/* set entries in TSS for process */
static inline void set_process_tss(int32_t pid);

/* set up stack and iret to user space */
static inline void switch_to_user(uint32_t user_eip);

//////////////// SYSTEM HALT HELPERS //////////////////////////////////

/* clear all entries in file descriptor array of given process */
static inline void clear_fd_array(int32_t pid);

/* set all entries in file operations jtab to a badcall fnc */
static inline void set_jtab_badcall(struct file_ops* jtab);

///////////////////////////////////////////////////////////////////////

int32_t start_process(const int8_t* cmd) {
    int32_t res;    /* check whether file system operations succeeded */
    // later change to get all arguments to given command as well (probably get_args syscall?)
    int8_t fname[FILENAME_LEN+1] = {'\0'};
    (void)parse_args(cmd, fname);
    setup_process_page(get_next_pid(curr_pid));
    flush_tlb();

    // Obtain directory entry info for file
    dentry_t file_dentry;
    res = read_dentry_by_name(fname, &file_dentry);
    if (res < 0) {
	// reverse paging back to current process's page before returning
	setup_process_page(curr_pid);
	return -1;
    }

    // reads file contents
    uint32_t file_len = fs_inode_arr[file_dentry.inode_num].length;
    res = read_data(file_dentry.inode_num, 0, (int8_t*)PROGRAM_VIRTUAL_ADDR, file_len);
    if (res < 0) { // read failed
	setup_process_page(curr_pid);
	return -1;
    }

    if (!is_executable((int8_t*)PROGRAM_VIRTUAL_ADDR)) {
	setup_process_page(curr_pid);
	return -1;
    }

    (void)create_new_pcb();
    curr_pid = get_next_pid(curr_pid);
    set_process_tss(curr_pid);

    // set up stack for iret
    uint32_t *first_instr_addr = (uint32_t*)(PROGRAM_VIRTUAL_ADDR + 24);

    switch_to_user(*first_instr_addr);

    return return_status;
}


int32_t squash_process(uint8_t status) {
    if (curr_pid == 0) {
        curr_pid = pcb_arr[curr_pid]->parent_pid;
        // always start shell if nothing else running
        sys_execute("shell");
    } else {
        clear_fd_array(curr_pid);
        setup_process_page(pcb_arr[curr_pid]->parent_pid);
        flush_tlb();
        set_process_tss(pcb_arr[curr_pid]->parent_pid);
	    curr_pid = pcb_arr[curr_pid]->parent_pid;

        if(exception_flag == 1){
            exception_flag = 0;
            return_status = 256;
        }
        else{
            return_status = (uint32_t)status;
        }
        // restore saved ebp and esp from before running execute
	uint32_t saved_ebp = pcb_arr[curr_pid]->stack_base_ptr;
	uint32_t saved_esp = pcb_arr[curr_pid]->stack_ptr; 
	asm volatile(
	    "movl %0, %%ebp;"
	    "movl %1, %%esp;"
	    :   
	    : "r"(saved_ebp), "r"(saved_esp)
	    : "%eax"
	    );
        return return_status;
    }
    return -1;
}


//////////// HELPER FUNCTIONS ///////////////

void flush_tlb() {
    asm volatile(
    	"movl %0, %%eax;"
    	"movl %%eax, %%cr3;"
    	:
    	: "r"(pd)
    	: "%eax"
	);
}

int32_t get_next_pid(int32_t pid) {
    return pid+1;
}

/* EXECUTE helper functions */

// returns number of bytes copied into buffer
int32_t parse_args(const int8_t* arg, int8_t* const buf) {
    uint32_t start_pos = 0;
    // skip leading spaces/null chars
    while ((arg[start_pos] == ' ') || (arg[start_pos] == '\0')) {
	    start_pos++;
    }
    // copy to buf until space or null
    uint32_t idx = 0;
    while ((arg[start_pos + idx] != ' ') && (arg[start_pos + idx] != '\0')) {
	    buf[idx] = arg[start_pos + idx];
	    idx++;
    }
    buf[idx] = '\0';
    return idx;
}


/* is_executable
 * DESCRIPTION:     Check if file with given contents is an exectuable
 * INPUTS:          file_contents  - The contents of the file to check
 * OUTPUTS:         none
 * RETURN VALUE:    1 (true) if file is executable, 0 (false) otherwise
 */
uint32_t is_executable(const int8_t* file_contents) {
    // check ELF magic number at start of file
    return (file_contents[0] == 0x7f) && (file_contents[1] == 0x45) && (file_contents[2] == 0x4C) && (file_contents[3] == 0x46);
}


void setup_process_page(int32_t pid) {
    //Chooses correct page directory entry offset based on page
    if (pid == 0) {
	    pd[PROCESS_DIR_IDX].mb.page_baseaddr_bit31_22 = PROCCESS_0_ADDR >> 22;
    } else {
	    pd[PROCESS_DIR_IDX].mb.page_baseaddr_bit31_22 = PROCCESS_1_ADDR >> 22;
    }
}

pcb_t* create_new_pcb() {
    int32_t next_pid = get_next_pid(curr_pid);
    
    uint32_t pcb_bottom_addr = KERNEL_END_ADDR - (next_pid)*PCB_SIZE;
    pcb_arr[next_pid] = (pcb_t*)(pcb_bottom_addr - PCB_SIZE);

    pcb_arr[next_pid]->pid = next_pid;
    pcb_arr[next_pid]->parent_pid = curr_pid;
	
    //Initializes fd array for PCB with stdin and stdout
    SET_FD_FLAG_INUSE(pcb_arr[next_pid]->fd_arr[STDIN_FD].flags); // stdin
    FILL_STDIN_OPS(pcb_arr[next_pid]->fd_arr[STDIN_FD].ops_jtab);
    SET_FD_FLAG_INUSE(pcb_arr[next_pid]->fd_arr[STDOUT_FD].flags); // stdout
    FILL_STDOUT_OPS(pcb_arr[next_pid]->fd_arr[STDOUT_FD].ops_jtab);

    //Saves Kernel stack pointer
    pcb_arr[next_pid]->stack_base_ptr = pcb_bottom_addr - sizeof(uint32_t);
    pcb_arr[next_pid]->stack_ptr = pcb_bottom_addr - sizeof(uint32_t);
	
    //Sets PCB status to active
    pcb_arr[next_pid]->state = ACTIVE;

    return pcb_arr[next_pid];
}

static void switch_to_user(uint32_t user_eip) {
    /* no need for stack pointer later if there is no parent process since in that case halt
     * will just restart shell and not return to execute/syscall linkage */
    if (pcb_arr[curr_pid]->parent_pid >= 0) {
	uint32_t saved_ebp;
	uint32_t saved_esp;
//    uint32_t saved_registers_flag;
	// save current ebp and esp
	asm volatile(
	    "movl %%ebp, %0;"
	    "movl %%esp, %1;"
	    : "=r"(saved_ebp), "=r"(saved_esp) 
	    :
	    : "%eax"
	    );
	pcb_arr[pcb_arr[curr_pid]->parent_pid]->stack_ptr = saved_esp;
	pcb_arr[pcb_arr[curr_pid]->parent_pid]->stack_base_ptr = saved_ebp;
    }

    // set up stack and iret
    asm volatile(
    	"pushl $%P1;"       // push user_ds
        "pushl $%P2;"       
        "pushfl;"
        "pushl $%P3;"       // push user_cs
        "pushl %0;"
        "iret;"
            : 
            : "r"(user_eip),
              "p"(USER_DS),
              "p"(PROCESS_IMG_ADDR + PAGE_SIZE_4MB - 4),
              "p"(USER_CS)
            : "%eax", "memory"
        );
        return;
}


void set_process_tss(int32_t pid) {
    tss.ss0 = KERNEL_DS;
    tss.esp0 = pcb_arr[pid]->stack_base_ptr;
}


/* HALT helper functions */

static void set_jtab_badcall(struct file_ops* jtab) {
    jtab->open = &badcall_open;
    jtab->close = &badcall_close;
    jtab->read = &badcall_read;
    jtab->write = &badcall_write;
}

void clear_fd_array(int32_t pid){
    int i;
    for(i = 0; i < 8; i++){
        UNSET_FD_FLAG_INUSE(pcb_arr[pid]->fd_arr[i].flags);		//set flags to unused
        set_jtab_badcall(&pcb_arr[pid]->fd_arr[i].ops_jtab);
    }
}
