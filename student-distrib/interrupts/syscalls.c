#include "syscalls.h"
#include "../filesystems/filesystem.h"
#include "../paging/paging.h"


/////////////////// SYSTEM EXECUTE HELPERS /////////////////////////////

static int32_t parse_args(const int8_t* arg, int8_t* const buf);
static int8_t setup_process_page(uint32_t pid, int8_t* const buf);
static pcb_t* create_pcb(uint32_t pid);

///////////////////////////////////////////////////////////////////////

uint32_t curr_pid = 0;
pcb_t pcb_arr[NUM_PROCCESS];

int32_t sys_halt(uint8_t status) {
	return 0;
}

int32_t sys_execute(const int8_t* cmd) {
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


int8_t setup_process_page(uint32_t pid, int8_t* const buf) {
	if (pid == 0){
		pd[PROCESS_DIR_IDX].mb.page_baseaddr_bit31_22 = PROCCESS_0_ADDR >> 22;
	} else {
		pd[PROCESS_DIR_IDX].mb.page_baseaddr_bit31_22 = PROCCESS_1_ADDR >> 22;
	}

	int32_t fd = fs_open(buf);
	uint32_t file_length = fs_inode_arr[fd_arr[fd].inode_num].length;
	
	int8_t buf_read[NUM_DATA_BLOCKS * DATABLOCK_SIZE];

	fs_read(fd, buf_read, file_length);

	if ((buf_read[0] != 0x7f) | (buf_read[1] != 0x45) | (buf_read[2] != 0x4C) | (buf_read[3] != 0x46)){
		return -1;
	}

	uint32_t *first_instruction = (uint32_t*) &buf_read[24];

	uint32_t baseaddr = 0;
	baseaddr += pd[PROCESS_DIR_IDX].mb.page_baseaddr_bit31_22;

	uint32_t *page_address = (uint32_t *)baseaddr;

	int i;
	int offset =  0x048000 >> 22;

	for(i = 0; i < file_length; i++){
		memcpy(page_address+offset+i,&buf_read[i],1);
	}

	asm volatile("				\n\
			mov %0, %%eax		\n\
	 		mov %%eax, %%cr3  	\n\
			mov %1, %%eax     	\n\
			mov %%eax, %%eip	\n\
			"
			: "r"(pd) 
			: "r"(*first_instruction) 
			: "%eax"
	);

	return 0;
}

pcb_t* create_pcb(uint32_t pid) {
	return 0;
}
