#include "filesystem.h"
#include "../ece391support.h"
#include "../ece391syscall.h"

boot_block_t* fs_boot_block;
/* pointer to start of inodes in memory. i-th inode can be accessed by fs_inode_arr[i] */
inode_t* fs_inode_arr;


// typedef struct boot_block_t{
//     uint32_t dir_count; //number of directory entires
//     uint32_t inode_count; //number of inodes
//     uint32_t data_count; //number of data blocks
//     uint8_t reserved[BOOT_BLOCK_RESERVED];   //reserved bytes for struct
//     dentry_t dir_entries[FILES_IN_DIR]; //supports up to 63 files
// } boot_block_t;

// extern int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry);
// extern int32_t read_dentry_by_index(uint32_t index, dentry_t* dentry);
// extern int32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf,uint32_t length);

// typedef struct inode_t{
//     uint32_t len_data_blocks;               //len of data blocks that make up file
//     uint32_t data_blocks[NUM_DATA_BLOCKS];  //pointers to the data blocks
// } inode_t;


void init_ext2_filesys(uint32_t boot_block_start){
    if (boot_block_start == NULL) return -1;
    fs_boot_block = (boot_block_t*) boot_block_start;
    fs_inode_arr = fs_boot_block + sizeof(boot_block_t); // start of inode array in memory after boot block
}

/* read_dentry_by_name(uint8_t* fname, dentry_t dentry)
 * DESCRIPTION: Search through the directory's files for a file with the given name.
 *              If the file is found, then read it's info to given dentry.
 * INPUTS:      fname  - name of the file to search for
 *              dentry - directory entry to read contents of file into. Acts as a buffer to write to.
 * OUTPUTS:     none
 * RETURNS 0 on successfully finding and reading file, -1 otherwise.
 * SIDE EFFECTS: Writes to dentry pointed to by input dentry */
 
int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry){
    if (fname == NULL || dentry == NULL) return -1;
    int dir;           // loop counter
    for (dir = 0; dir < fs_boot_block->dir_count; dir++) {
        if (strings_equal(fname, fs_boot_block->dir_entries[dir].filename)) {
            return read_dentry_by_index(dir, dentry);
        }
    }
    return -1;
}

/* read_dentry_by_index
* DESCRIPTION:  reads each element of the directory entry at the given index in the boot block
* INPUTS:       uint32_t index - index number of where to find the direcory in the boot block
*               dentry_t* dentry - pointer to a dentry_t variable to write the contents of file to
* OUTPUTS:      integer that determines validity of read  
* RETURN VALUE: 0 if read is successful, -1 is read fails
* SIDE EFFECTS: populates a temporary dentry_t variable with the specifed directory contents
*/
int32_t read_dentry_by_index(uint32_t index, dentry_t* dentry) {
    if (dentry == NULL) return -1;
    dentry->filename = fs_boot_block->dir_entries[index].filename;
    dentry->filetype = fs_boot_block->dir_entries[index].filetype;
    dentry->inode_num = fs_boot_block->dir_entries[index].inode_num;
    dentry->reserved = fs_boot_block->dir_entries[index].reserved;
    return 0;
}

/* read_data
* DESCRIPTION:  
* INPUTS:      
*               
* OUTPUTS:       
* RETURN VALUE: 
* SIDE EFFECTS: 
*/
int32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf,uint32_t length){
    uint32_t num_inodes = fs_boot_block->inode_count;
    int find_inodes;

    for(find_inodes = 0; find_inodes < num_inodes; find_inodes++){
        if( fs_boot_block->dir_entries[find_inodes].inode_num == inode) {
            buf = 
        }
    } 
}