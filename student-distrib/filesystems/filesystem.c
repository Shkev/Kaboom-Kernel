#include "filesystem.h"
// #include "../ece391support.h"
// #include "../ece391syscall.h"
#include "../lib.h"

static int32_t find_file_index(const uint8_t* fname);
static int32_t find_open_fd();

void init_ext2_filesys(uint32_t boot_block_start){
    fs_boot_block = (boot_block_t*) boot_block_start;     // cast boot block pointer to struct pointer
    fs_inode_arr = fs_boot_block + sizeof(boot_block_t);  // start of inode array in memory after boot block
    fs_data_blocks = fs_inode_arr + (sizeof(inode_t) * fs_boot_block->inode_count);  // start of data blocks in memory
    // initialize fd_arr?? (jump table, etc.)
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
    int32_t dir = find_file_index(fname);
    if (dir < 0) {
	return dir
    }
    return read_dentry_by_index(dir, dentry);
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
*               uint32_t length - number of bytes of data being read
* OUTPUTS:      none
* RETURN VALUE: -1 if bad data block, 0 if end of file, or length of bytes read by the function
* SIDE EFFECTS: none
*/
int32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length){
    uint32_t length_curr_file = fs_inode_arr[inode].length; /* num bytes of file */
    uint32_t curr_block;                                    /* curr block to read from in inode */
    uint32_t curr_byte;                                     /* curr byte to read from in data block */
    uint32_t block_number;				    /* block number where data is stored for given inode */
    uint32_t curr_block_ptr;				    /* pointer to start of current data block */
    int32_t curr_read;					    /* pointer to start of where we want to read */
    uint32_t nblock;					    /* number of blocks read covers */
    uint32_t write_pos;					    /* curr position to start writing in buffer (number of bytes written so far) */
    int i;						    /* loop counter */

    if (length > length_curr_file) { // can't read more than the file contains
	length = length_curr_file;
    }
    nblock = (length+offset) / DATABLOCK_SIZE + 1;
    curr_block = offset / 4096;
    curr_byte = offset % 4096;
    write_pos = 0;
    block_number = fs_inode_arr[inode].data_block[curr_block];
    curr_read = fs_data_blocks + (block_number * DATABLOCK_SIZE) + curr_byte;
    // handle reading first block where we may not be reading the entire thing
    if (DATABLOCK_SIZE - curr_byte > length) {
	memcpy(buf, curr_read, length);
	return length;
    }
    memcpy(buf, curr_read, DATABLOCK_SIZE - curr_byte); // read till end of first datablock
    write_pos = DATABLOCK_SIZE - curr_byte;
    curr_byte = 0; // at start of next block
    curr_block++;
    block_number = fs_inode_arr[inode].data_block[curr_block];
    curr_read = fd_data_blocks + (block_number * DATABLOCK_SIZE);
    for (i = 1; i < nblock-1; i++) {
	// read intermediary blocks in their entirety
	memcpy(buf + write_pos, curr_read, DATABLOCK_SIZE);
	write_pos += DATABLOCK_SIZE;
	curr_block++;
	block_number = fs_inode_arr[inode].data_block[curr_block];
	curr_read = fd_data_blocks + (block_number * DATABLOCK_SIZE);
    }
    // handle reading last block where we may not be reading the entire thing (like the first one)
    memcpy(buff + write_pos, curr_read, length - write_pos); 
    
    return length;      //returns number of bytes copied into buffer
}


/* int32_t directory_open(uint32_t)
* DESCRIPTION:  opens a directory file based on the name
* INPUTS:       const uint8_t fname - name of the directory to open
* OUTPUTS:      none
* RETURN VALUE: 0 if successful, -1 otherwise
* SIDE EFFECTS: 
*/
int32_t directory_open(const uint8_t* fname) {
    if (name == NULL) {
	return -1;
    }
    int32_t idx = find_file_index(fname);
    if (idx < 0) {
	return idx;
    }
    int32_t fd_idx = find_open_fd();
    if (fd_idx < 0) { // can't open; no available file descriptors
	return -1;
    }
    // open directory to use the open fd
    SET_FD_FLAG_INUSE(fd_arr[fd_idx].flags);
    // later initialize other fields of array entry...
}


/* int32_t directory_read(uint8_t*, uint8_t*, uint32_t)
* DESCRIPTION:  Read next entry in the current directory.
* INPUTS:       fname   - name of the directory to open
*               buf     - the buffer to write contents to
*               buf_len - The max len of the input buffer
*               
* OUTPUTS:      none
* RETURN VALUE: 0 if successful, -1 otherwise
* SIDE EFFECTS: 
*/
int32_t directory_read(const uint8_t* fname, uint8_t* buf, uint32_t buf_len){
    dentry d;
    read_dentry_by_name(fname, &d);
    return -1;
}


/* directory_write
* DESCRIPTION:  write function for directories in file system, does nothing in our OS
* INPUTS:       none
* OUTPUTS:      returns whether or not write was successful
* RETURN VALUE: -1
* SIDE EFFECTS: none
*/
int32_t directory_write() {
    return -1;
}

/* directory_close
* DESCRIPTION:  closes the directory, does nothing in our OS
* INPUTS:       none
* OUTPUTS:      returns whether or close was successful
* RETURN VALUE: 0
* SIDE EFFECTS: none
*/
int32_t directory_close() {
    return 0;
}

int32_t file_open() {
    return 0;
}

int32_t file_read() {
    return 0;
}

/* file_write
* DESCRIPTION:  write function for files in file system, does nothing
* INPUTS:       none
* OUTPUTS:      returns whether or not write was successful
* RETURN VALUE: -1
* SIDE EFFECTS: none
*/
int32_t file_write() {
    return -1;
}

int32_t file_close() {
    return -1;
}


/* find_file_index(uint8_t* fname)
 * DESCRIPTION: Find the index of file with given name in filesystem.
 * INPUTS:      fname  - name of the file to search for
 * OUTPUTS:     none
 * RETURNS:     0 on successfully finding file, -1 otherwise.
 * SIDE EFFECTS: none
 */
int32_t find_file_index(const uint8_t* fname) {
    uint32_t dir;
    for (dir = 0; dir < fs_boot_block->direntry_count; dir++) {
        if (strings_equal(fname, fs_boot_block->dir_entries[dir].filename) && dentry != NULL) {
            return dir;
        }
    }
    return -1;
}


/* int32_t find_open_fd(void)
 * DESCRIPTION: Find an available file descripter (int) if one exists.
 * INPUTS: none
 * OUTPUTS: none
 * RETURNS: An available fd if one is avaiable, otherwise -1.
 * SIDE EFFECTS: none
 */
int32_t find_open_fd() {
    int i;
    for (i = 0; i < MAXFILES_PER_TASK; ++i) {
	if (!FD_FLAG_INUSE(fd_arr[i].flags)) {
	    return i;
	}
    }
    return -1;
}
