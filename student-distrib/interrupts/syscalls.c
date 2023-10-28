#include "syscalls.h"
#include "../filesystems/filesystem.h"


/////////////////// SYSTEM EXECUTE HELPERS /////////////////////////////

static int32_t parse_args(const int8_t* arg, int8_t* const buf);
static int8_t allocate_process_page(uint32_t pid);
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

int32_t sys_read(int32_t fd, const char* buf, int32_t nbytes) {
	return fs_read(fd, buf, nbytes);
}

int32_t sys_write(int32_t fd, const char* buf, int32_t nbytes) {
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
