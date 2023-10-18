#include "filesystem.h"
#include "../ece391support.h"
#include "../ece391syscall.h"

boot_block_t* fs_boot_block;


// typedef struct boot_block_t{
//     uint32_t dir_count; //number of directory entires
//     uint32_t inode_count; //number of inodes
//     uint32_t data_count; //number of data blocks
//     uint8_t reserved[BOOT_BLOCK_RESERVED];   //reserved bytes for struct
//     dentry_t dir_entries[FILES_IN_DIR]; //supports up to 63 files
// } boot_block_t;


void init_ext2_filesys(uint32_t boot_block_start){

    fs_boot_block = (boot_block_t*) boot_block_start;

}