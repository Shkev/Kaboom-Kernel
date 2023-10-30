#ifndef PROCESS_H
#define PROCESS_H

#include "../types.h"

#define MAXFILES_PER_TASK 8
#define NUM_PROCCESS 2

/* file operations jump table. Different for each file type */
struct file_ops {
    int32_t (*read) (int32_t, void*, int32_t);
    int32_t (*write) (int32_t, const void*, int32_t);
    int32_t (*open) (const int8_t*);
    int32_t (*close) (int32_t);
};


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


extern pcb_t* pcb_arr[NUM_PROCCESS];
/* pid of most recently created process */
extern int32_t curr_pid;

#endif /* endif PROCESS_H */
