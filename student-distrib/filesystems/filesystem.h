#ifndef FILESYS_H
#define FILESYS_H

#include "../types.h"
#define BOOT_BLOCK_RESERVED 52
#define DIR_ENTRY_RESERVED  24
#define FILES_IN_DIR    63
#define NUM_DATA_BLOCKS 1023
#define FILENAME_LEN    32

typedef struct boot_block_t{
    uint32_t dir_count; //number of directory entires
    uint32_t inode_count; //number of inodes
    uint32_t data_count; //number of data blocks
    uint8_t reserved[BOOT_BLOCK_RESERVED];   //reserved bytes for struct
    dentry_t dir_entries[FILES_IN_DIR]; //supports up to 63 files
} boot_block_t;

typedef struct dentry_t{
    uint8_t filename[FILENAME_LEN];         //supports up to 32 character length file names
    uint32_t filetype;                      //define file type
    uint32_t inode_num;                     //specific inode number for the file
    uint8_t reserved[DIR_ENTRY_RESERVED];   //reseved bytes for dentry
} dentry_t;

typedef struct inode_t{
    uint32_t len_data_blocks;               //len of data blocks that make up file
    uint32_t data_blocks[NUM_DATA_BLOCKS];  //pointers to the data blocks
} inode_t;

extern int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry);
extern int32_t read_dentry_by_index(uint32_t index, dentry_t* dentry);
extern int32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf,uint32_t length);

extern void init_ext2_filesys(uint32_t boot_block_start);

#endif  //FILESYS_H