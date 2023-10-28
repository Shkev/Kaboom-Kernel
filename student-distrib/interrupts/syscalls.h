#ifndef SYSCALL_H
#define SYSCALL_H

#include "../types.h"
#include "../filesystems/filesystem.h"

#define MAXFILES_PER_TASK 8

/* Stores info about a file in the file descriptor array
 * Note that read_pos is interpretted differently for each file type.
 * For directories it indicates 1 + the number of directory entrie that have been read so far. */
typedef struct fd_arr_entry {
    struct file_ops ops_jtab;		/* jmp table containing type-specific open,read,write,close fncs */
    uint32_t inode_num;				/* inode number for the file */
    uint32_t read_pos;              /* offset (in bytes) from start of file to start reading from */
    uint32_t flags;	                /* first bit 1 indicates in use, 0 indicates not in use. */
} fd_arr_entry_t;


/* Current state of a task. UPDATE LATER TO ADD MORE STATES AS NEEDED */
enum task_state {
    ACTIVE = 0,
    STOPPED
};

/* Process control block stored in kernel*/
typedef struct pcb {
    uint32_t pid;
    uint32_t parent_pid;
    fd_arr_entry_t fd_arr[MAXFILES_PER_TASK];  /* file descriptor array. A given file descriptor indexes into this array to get info about the file. */
    uint32_t stack_ptr;
    uint32_t stack_base_ptr;
    enum task_state state;
} pcb_t;


/* system calls referenced by the system call handler. */

extern int32_t sys_halt(uint8_t status);
extern int32_t sys_execute(const int8_t* cmd);
extern int32_t sys_read(int32_t fd, const char* buf, int32_t nbytes);
extern int32_t sys_write(int32_t fd, const char* buf, int32_t nbytes);
extern int32_t sys_open(const int8_t* fname);
extern int32_t sys_close(int32_t fd);
extern int32_t sys_getargs(int8_t* buf, int32_t nbytes);
extern int32_t sys_vidmap(int8_t** screen_start);
extern int32_t sys_set_handler(int32_t signum, void* handler_addr);
extern int32_t sys_sigreturn(void);

#endif	/* endif SYSCALL_H */
