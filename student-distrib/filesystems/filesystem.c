#include "filesystem.h"
#include "../ece391support.h"
#include "../ece391syscall.h"
#include "../lib.h"

boot_block_t* fs_boot_block;

/* pointer to start of inodes in memory. i-th inode can be accessed by fs_inode_arr[i] */
inode_t* fs_inode_arr;

/* pointer to the start of data blocks in memory. i-th block can be accessed by data_blocks[i]*/
uint32_t* fs_data_blocks;


void init_ext2_filesys(uint32_t boot_block_start){
    fs_boot_block = (boot_block_t*) boot_block_start;     //cast boot block pointer to struct pointer
    fs_inode_arr = fs_boot_block + sizeof(boot_block_t); // start of inode array in memory after boot block
    fs_data_blocks = fs_inode_arr + (sizeof(boot_block_t) * fs_boot_block->inode_count);   //start of data blocks in memory
}

/* read_dentry_by_name(uint8_t* fname, dentry_t dentry)
 * DESCRIPTION: Search through the directory's files for a file with the given name.
 *              If the file is found, then read it's info to given dentry.
 * INPUTS:      fname  - name of the file to search for
 *              dentry - directory entry to read contents of file into. Acts as a buffer to write to.
 * OUTPUTS:     none
 * RETURNS 0 on successfully finding and reading file, -1 otherwise.
 * SIDE EFFECTS: Writes to dentry pointed to by input dentry 
 */
 
int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry){
    if (fname == NULL || dentry == NULL) return -1;
    int dir;           // loop counter
    for (dir = 0; dir < fs_boot_block->dir_count; dir++) {
        if (strings_equal(fname, fs_boot_block->dir_entries[dir].filename) && dentry != NULL) {
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
    strcpy(dentry->filename,fs_boot_block->dir_entries[index].filename); //SHAYAN YOU DEBUG GOD FIX THIS
    dentry->filetype = fs_boot_block->dir_entries[index].filetype;
    dentry->inode_num = fs_boot_block->dir_entries[index].inode_num;
    memcpy(dentry->reserved,fs_boot_block->dir_entries[index].reserved,52);
    return 0;
}


/* read_data
* DESCRIPTION:  reads the data in each file by parsing through the data blocks.
* INPUTS:       uint32_t inode - inode number of the file to read from
*               uint32_t offset - offset into data to start reading from
*               uint8_t* buf - buffer to store data read
*               uint32_t length - length of data being read
* OUTPUTS:      integer that determines validity of data read
* RETURN VALUE: -1 if bad data block, 0 if end of file, or length of bytes read by the function
* SIDE EFFECTS: none
*/
int32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf,uint32_t length){
    uint32_t length_curr_file = fs_inode_arr[inode].length;
    int i;
    for(i = 0; i < length; i++){
        uint32_t curr_block = (offset+i) / 4096;    //curr block to read from in inode
        uint32_t curr_byte = (offset+i) % 4096;     //curr byte to read from in data block
        uint32_t block_number = fs_inode_arr[inode].data_block[curr_block]; //find the block number where data is stored for given inode
        
        if((fs_data_blocks + (block_number * 4096)) == NULL) return -1;     //checks if bad data block number is found in inode
        
        uint32_t* curr_read = fs_data_blocks + (block_number * 4096) + curr_byte;   //pointer to the index of the actual data in data blocks array
        memcpy(buf[i],curr_read,1);     //copy character from data to buffer

        if((i+offset) >= length_curr_file) return 0; //if you have reached the end of the file return 0
    }

    return length;      //returns number of bytes copied into buffer
}


/* directory_open
* DESCRIPTION:  opens a directory file based on the name
* INPUTS:       const uint8_t fname - name of the directory to open
*               dentry_t* dentry - local directory entry to populate
* OUTPUTS:      returns whether or not open was successful
* RETURN VALUE: 0 if successful, -1 otherwise
* SIDE EFFECTS: calls read_dentry_by_name() to populate directory entry
*/
extern int32_t directory_open(const uint8_t* fname, dentry_t* dentry){
    return read_dentry_by_name(fname,dentry);
}
extern int32_t directory_read();

/* directory_write
* DESCRIPTION:  write function for directories in file system, does nothing in our OS
* INPUTS:       none
* OUTPUTS:      returns whether or not write was successful
* RETURN VALUE: -1
* SIDE EFFECTS: none
*/
extern int32_t directory_write(){
    return -1;
}

/* directory_close
* DESCRIPTION:  closes the directory, does nothing in our OS
* INPUTS:       none
* OUTPUTS:      returns whether or close was successful
* RETURN VALUE: 0
* SIDE EFFECTS: none
*/
extern int32_t directory_close(){
    return 0;
}

extern int32_t file_open();
extern int32_t file_read();

/* file_write
* DESCRIPTION:  write function for files in file system, does nothing
* INPUTS:       none
* OUTPUTS:      returns whether or not write was successful
* RETURN VALUE: -1
* SIDE EFFECTS: none
*/
extern int32_t file_write(){
    return -1;
}

extern int32_t file_close();