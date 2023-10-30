#include "syscalls.h"
#include "../x86_desc.h"
#include "../filesystems/filesystem.h"

static void flush_tlb();

/////////////////// SYSTEM EXECUTE HELPERS /////////////////////////////

/* parse args from shell */
static int32_t parse_args(const int8_t* arg, int8_t* const buf);

/* setup process page addresses for process with given pid */
static void setup_process_page(int32_t pid);

/* initialize pcb memory block in kernel for given pid */
static pcb_t* create_pcb(int32_t pid);

/* set entries in TSS for process */
static void set_process_tss(int32_t pid);

/* set up stack and iret to user space */
static void switch_to_user(uint32_t user_eip);

//////////////// SYSTEM HALT HELPERS //////////////////////////////////

/* clear all entries in file descriptor array of given process */
static void clear_fd_array(int32_t pid);

/* set all entries in file operations jtab to a badcall fnc */
static void set_jtab_badcall(struct file_ops* jtab);

///////////////////////////////////////////////////////////////////////

int32_t curr_pid = -1;
pcb_t* pcb_arr[NUM_PROCCESS];

int32_t sys_halt(uint8_t status) {
    if (curr_pid == 0) {
	sys_execute("shell");
    } else {
	clear_fd_array(curr_pid);
	setup_process_page(pcb_arr[curr_pid]->parent_pid);
	flush_tlb();
	set_process_tss(pcb_arr[curr_pid]->parent_pid);
	curr_pid--;
	return status;
    }
    return 0;
}

int32_t sys_execute(const int8_t* cmd) {
    int32_t res;    /* check whether file system operations succeeded */

    int8_t fname[DATABLOCK_SIZE];
    (void)parse_args(cmd, fname);
    setup_process_page(curr_pid);

    // Obtain directory entry info for file
    dentry_t file_dentry;
    res = read_dentry_by_name(fname, &file_dentry);
    if (res < 0) {
	return -1;
    }

    // reads file contents
    int8_t buf_read[NUM_DATA_BLOCKS * DATABLOCK_SIZE];
    uint32_t file_len = fs_inode_arr[file_dentry.inode_num].length;
    res = read_data(file_dentry.inode_num, 0, buf_read, file_len);
    if (res < 0) { // read failed
	return -1;
    }

    // if file is not execuable return -1
    if ((buf_read[0] != 0x7f) | (buf_read[1] != 0x45) | (buf_read[2] != 0x4C) | (buf_read[3] != 0x46)) {
	return -1;
    }

    curr_pid++;

    // copies file contents in memory
    memcpy((uint32_t*)PROGRAM_VIRTUAL_ADDR, buf_read, file_len);

    flush_tlb();

    (void)create_pcb(curr_pid);
    set_process_tss(curr_pid);

    // set up stack for iret
    uint32_t *first_instr_addr = (uint32_t*)(buf_read + 24);
    switch_to_user(*first_instr_addr);

    // asm volatile("execute_return:");
    return 0;
}

int32_t sys_read(int32_t fd, void* buf, int32_t nbytes) {
    return fs_read(fd, buf, nbytes);
}

int32_t sys_write(int32_t fd, const void* buf, int32_t nbytes) {
    return fs_write(fd, buf, nbytes);
}

int32_t sys_open(const int8_t* fname) {
    return fs_open(fname);
}

int32_t sys_close(int32_t fd) {
    return fs_close(fd);
}

int32_t sys_getargs(int8_t* buf, int32_t nbytes) {
    return 0;
}

int32_t sys_vidmap(int8_t** screen_start) {
    return 0;
}

int32_t sys_set_handler(int32_t signum, void* handler_addr) {
    return 0;
}

int32_t sys_sigreturn() {
    return 0;
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
    return idx;
}


void setup_process_page(int32_t pid) {
    //Chooses correct page directory entry offset based on page
    if (pid == 0){
	pd[PROCESS_DIR_IDX].mb.page_baseaddr_bit31_22 = PROCCESS_0_ADDR >> 22;
    } else {
	pd[PROCESS_DIR_IDX].mb.page_baseaddr_bit31_22 = PROCCESS_1_ADDR >> 22;
    }
}

pcb_t* create_pcb(int32_t pid) {
    //ADD PARENT ID
	
    uint32_t pcb_bottom_addr = KERNEL_END_ADDR - (pid)*PCB_SIZE;
    pcb_arr[pid] = (pcb_t*)(pcb_bottom_addr - PCB_SIZE);

    pcb_arr[pid]->pid = pid;
    pcb_arr[pid]->parent_pid = 0; // figure this out later... should work for now
	
    //Initializes fd array for PCB with stdin and stdout
    SET_FD_FLAG_INUSE(pcb_arr[pid]->fd_arr[STDIN_FD].flags); // stdin
    FILL_STDIN_OPS(pcb_arr[pid]->fd_arr[STDIN_FD].ops_jtab);
    SET_FD_FLAG_INUSE(pcb_arr[pid]->fd_arr[STDOUT_FD].flags); // stdout
    FILL_STDOUT_OPS(pcb_arr[pid]->fd_arr[STDOUT_FD].ops_jtab);

    //Saves Kernel stack pointer
    pcb_arr[pid]->stack_base_ptr = pcb_bottom_addr;
    pcb_arr[pid]->stack_ptr = pcb_bottom_addr;
	
    //Sets PCB status to active
    pcb_arr[pid]->state = ACTIVE;

    return pcb_arr[pid];
}


static void switch_to_user(uint32_t user_eip) {
    asm volatile(
    	"pushl %P1;"       // push user_ds
    	"movl %P2, %%eax;"
	"addl %P3, %%eax;" // process_img_addr + page_size_4mb
	"pushl %%eax;"     
	"pushfl;"
	"pushl %P4;"       // push user_cs
	"pushl %0;"
	"iret;"
    	:
    	: "r"(user_eip),
	  "p"(USER_DS),
	  "p"(PROCESS_IMG_ADDR),
	  "p"(PAGE_SIZE_4MB),
	  "p"(USER_CS)
    	: "%eax", "memory"
	);
}


void set_process_tss(int32_t pid) {
    tss.ss0 = KERNEL_DS;
    tss.esp0 = pcb_arr[curr_pid]->stack_base_ptr;
}


static void switch_to_user(uint32_t user_esp);

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
