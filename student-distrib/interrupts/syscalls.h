#ifndef SYSCALL_H
#define SYSCALL_H

#include "../types.h"
#include "../filesystems/filesystem.h"
#include "../paging/paging.h"

#define NUM_PROCCESS 2


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

/* pid of most recently created process */
extern uint32_t curr_pid;

extern pcb_t pcb_arr[NUM_PROCCESS];

/* system calls referenced by the system call handler. */

extern int32_t sys_halt(uint8_t status);
extern int32_t sys_execute(const int8_t* cmd);
extern int32_t sys_read(int32_t fd, void* buf, int32_t nbytes);
extern int32_t sys_write(int32_t fd, const void* buf, int32_t nbytes);
extern int32_t sys_open(const int8_t* fname);
extern int32_t sys_close(int32_t fd);
extern int32_t sys_getargs(int8_t* buf, int32_t nbytes);
extern int32_t sys_vidmap(int8_t** screen_start);
extern int32_t sys_set_handler(int32_t signum, void* handler_addr);
extern int32_t sys_sigreturn(void);


#endif	/* endif SYSCALL_H */
