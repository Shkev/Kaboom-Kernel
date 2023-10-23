// #ifndef FILESYS_H
// #define FILESYS_H

// #include "../types.h"
// #include "../lib.h"
// #define BOOT_BLOCK_RESERVED 52
// #define DIR_ENTRY_RESERVED  24
// #define FILES_IN_DIR    63
// #define NUM_DATA_BLOCKS 1023
// #define FILENAME_LEN    32
// #define DATABLOCK_SIZE 4096	/* size of file data blocks in memory */
// #define MAXFILES_PER_TASK 8


// #define FD_FLAG_INUSE(flag) ((flag & 0x1) == 1)
// #define SET_FD_FLAG_INUSE(flag) flag |= 0x1

// enum filetype {
//     DEVICE = 0,
//     DIRECTORY = 1,
//     FILE = 2
// };


// typedef struct dentry {
//     uint8_t filename[FILENAME_LEN];         /* supports up to 32 character length file names */
//     enum filetype filetype;                      /* defined file type */
//     uint32_t inode_num;                     /* specific inode number (i.e., index of associated inode) for the file */
//     uint8_t reserved[DIR_ENTRY_RESERVED];   /* reserved bytes for dentry */
// } dentry_t;

// #pragma pack(1)
// typedef struct boot_block_t {
//     uint32_t direntry_count;			   /* number of directory entries */
//     uint32_t inode_count;		   /* number of inodes */
//     uint32_t data_count;		   /* number of data blocks */
//     uint8_t reserved[BOOT_BLOCK_RESERVED]; /* reserved bytes for struct */
//     dentry_t dir_entries[FILES_IN_DIR];	   /* supports up to 63 files */
// }boot_block_t; //__attribute__((packed));
// #pragma pack()

// #pragma pack(1)
// typedef struct inode {
//     uint32_t length;			     /* length of file in bytes */
//     uint32_t data_blocks[NUM_DATA_BLOCKS];   /* indices into data blocks */
// } inode_t; // __attribute__((packed));
// #pragma pack()

// /* Stores info about a file in the file descriptor array
//  * Note that read_pos is interpretted differently for each file type.
//  * For directories it indicates 1 + the number of directory entrie that have been read so far. */
// typedef struct fd_arr_entry {
//     uint32_t ops_jtab;		/* ptr to jmp table containing type-specific open,read,write,close fncs */
//     uint32_t inode_num;		/* inode number for the file */
//     uint32_t read_pos;		/* offset (in bytes) from start of file to start reading from */
//     uint32_t flags;		/* first bit 1 indicates in use, 0 indicates not in use. */
// } fd_arr_entry_t;


// /* file descriptor array. A given file descriptor indexes into this array to get info about the file */
// extern fd_arr_entry_t fd_arr[MAXFILES_PER_TASK];


// ///////////// Pointers to fileystem data in memory /////////

    
// extern boot_block_t* fs_boot_block;

// /* pointer to start of inodes in memory. i-th inode can be accessed by fs_inode_arr[i] */
// extern inode_t* fs_inode_arr;

// /* pointer to the start of data blocks in memory. i-th block can be accessed by data_blocks[i]*/
// extern uint32_t fs_data_blocks;



// /////////// Functions for filesystem API ///////////////

// extern int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry);

// extern int32_t read_dentry_by_index(uint32_t index, dentry_t* dentry);

// extern int32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);

// extern void init_ext2_filesys(uint32_t boot_block_start);

// /*System call functions for directories*/
// extern int32_t directory_open(const uint8_t* fname);
// extern int32_t directory_read(int32_t fd, void* buf, int32_t nbytes);
// extern int32_t directory_write(int32_t fd, const void* buf, int32_t nbytes);
// extern int32_t directory_close(int32_t fd);

// /*System call functions for files*/
// extern int32_t file_open(const uint8_t* fname);
// extern int32_t file_read(int32_t fd, void* buf, int32_t nbytes);
// extern int32_t file_write(int32_t fd, const void* buf, int32_t nbytes);
// extern int32_t file_close(int32_t fd);

// #endif  //FILESYS_H
