#include "syscalls.h"
#include "../filesystems/filesystem.h"


int32_t sys_halt(uint8_t status) {
    return squash_process(status);
}

int32_t sys_execute(const int8_t* cmd) {
    if (cmd == NULL) {
        return -1;
    }
    return start_process(cmd);
}

int32_t sys_read(int32_t fd, void* buf, int32_t nbytes) {
    if (buf == NULL) return -1;
    return fs_read(fd, buf, nbytes);
}

int32_t sys_write(int32_t fd, const void* buf, int32_t nbytes) {
    if (buf == NULL) return -1;
    return fs_write(fd, buf, nbytes);
}

int32_t sys_open(const int8_t* fname) {
    if (fname == NULL) return -1;
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

