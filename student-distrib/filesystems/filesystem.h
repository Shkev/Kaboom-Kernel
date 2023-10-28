#ifndef FILESYS_H
#define FILESYS_H

#include "../types.h"
#include "../lib.h"
#include "../rtcdrivers/rtcdrivers.h"
#include "../terminaldrivers/terminaldriver.h"

#define STDIN_FD 0
#define STDOUT_FD 1
#define BOOT_BLOCK_RESERVED 52
#define DIR_ENTRY_RESERVED  24
#define FILES_IN_DIR    63
#define NUM_DATA_BLOCKS 1023
#define FILENAME_LEN    32
#define DATABLOCK_SIZE 4096	/* size of file data blocks in memory */

#define FD_FLAG_INUSE(flag) ((flag & 0x1) == 1)
#define SET_FD_FLAG_INUSE(flag) flag |= 0x1
#define UNSET_FD_FLAG_INUSE(flag) flag &= 0xFFFFFFFE

enum filetype {
    DEVICE = 0,
    DIRECTORY = 1,
    FILE = 2
};

#pragma pack(1)
typedef struct dentry {
    int8_t filename[FILENAME_LEN];         /* supports up to 32 character length file names */
    enum filetype filetype;                 /* defined file type */
    uint32_t inode_num;                     /* specific inode number (i.e., index of associated inode) for the file */
    int8_t reserved[DIR_ENTRY_RESERVED];   /* reserved bytes for dentry */
} dentry_t;
#pragma pack()

#pragma pack(1)
typedef struct boot_block {
    uint32_t direntry_count;		   /* number of directory entries */
    uint32_t inode_count;		   /* number of inodes */
    uint32_t data_count;		   /* number of data blocks */
    int8_t reserved[BOOT_BLOCK_RESERVED]; /* reserved bytes for struct */
    dentry_t dir_entries[FILES_IN_DIR];	   /* supports up to 63 files */
} boot_block_t;
#pragma pack()

#pragma pack(1)
typedef struct inode {
    uint32_t length;			     /* length of file in bytes */
    uint32_t data_blocks[NUM_DATA_BLOCKS];   /* indices into data blocks */
} inode_t;
#pragma pack()

/* file operations jump table. Different for each file type */
struct file_ops {
	int32_t (*read) (int32_t, const char*, int32_t);
	int32_t (*write) (int32_t, const char*, int32_t);
	int32_t (*open) (const int8_t*);
	int32_t (*close) (int32_t);
};


///////////// Pointers to fileystem data in memory /////////

/* pointer to start of boot block in memory */
extern boot_block_t* fs_boot_block;

/* pointer to start of inodes in memory. i-th inode can be accessed by fs_inode_arr[i] */
extern inode_t* fs_inode_arr;

/* pointer to the start of data blocks in memory. i-th block can be accessed by data_blocks[i] */
extern uint32_t fs_data_blocks;

/* array containing file info indexed by file descriptor */
extern fd_arr_entry_t fd_arr[MAXFILES_PER_TASK];

/////////// Functions for filesystem API ///////////////

extern int32_t read_dentry_by_name(const int8_t* fname, dentry_t* dentry);

extern int32_t read_dentry_by_index(uint32_t index, dentry_t* dentry);

extern int32_t read_data(uint32_t inode, uint32_t offset, int8_t* buf, int32_t length);

extern void init_ext2_filesys(uint32_t boot_block_start);

/* Generic system calls for fileystem */
extern int32_t fs_open(const int8_t* fname);
extern int32_t fs_close(int32_t fd);
extern int32_t fs_read(int32_t fd, const char* buf, int32_t nbytes);
extern int32_t fs_write(int32_t fd, const char* buf, int32_t nbytes);

extern int32_t badcall(int,...);

/* System call functions for directories */
extern int32_t directory_open(const int8_t* fname);
extern int32_t directory_read(int32_t fd, int8_t* buf, int32_t nbytes);
extern int32_t directory_write(int32_t fd, const void* buf, int32_t nbytes);
extern int32_t directory_close(int32_t fd);

/* System call functions for files */
extern int32_t file_open(const int8_t* fname);
extern int32_t file_read(int32_t fd, int8_t* buf, int32_t nbytes);
extern int32_t file_write(int32_t fd, const void* buf, int32_t nbytes);
extern int32_t file_close(int32_t fd);

// other helpers
extern uint32_t get_file_size(int32_t fd);

#endif  //FILESYS_H
