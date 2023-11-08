#include "syscalls.h"
#include "../filesystems/filesystem.h"

/* sys_halt()
 * 
 * DESCRIPTION:   system call for halt
 * INPUTS:        status - return value for system execute call
 * OUTPUTS:       none
 * RETURNS:       value for execute to return
 * SIDE EFFECTS:  sets return value for execute
 */
int32_t sys_halt(uint8_t status) {
    return squash_process(status);
}

/* sys_execute()
 * 
 * DESCRIPTION:   system call for execute
 * INPUTS:        cmd - program to execute
 * OUTPUTS:       none
 * RETURNS:       0-255 status, 256 is exception is raised, -1 otherwise
 * SIDE EFFECTS:  starts program
 */
int32_t sys_execute(const int8_t* cmd) {
    if (cmd == NULL) {
        return -1;
    }
    return start_process(cmd);
}

/* sys_read()
 * 
 * DESCRIPTION:   system call for read
 * INPUTS:        fd - file descriptor index
 *                buf - buffer to read
 *                nbytes - number of bytes to read
 * OUTPUTS:       none
 * RETURNS:       number of bytes read
 * SIDE EFFECTS:  none
 */
int32_t sys_read(int32_t fd, void* buf, int32_t nbytes) {
    int32_t res = fs_read(fd, buf, nbytes);
    return res;
}

/* sys_write()
 * 
 * DESCRIPTION:   system call for write
 * INPUTS:        fd - file descriptor index
 *                buf - buffer to write to
 *                nbytes - number of bytes to write
 * OUTPUTS:       none
 * RETURNS:       number of bytes written
 * SIDE EFFECTS:  fills buffer with characters to write
 */
int32_t sys_write(int32_t fd, const void* buf, int32_t nbytes) {
    int32_t res = fs_write(fd, buf, nbytes);
    return res;
}

/* sys_open()
 * 
 * DESCRIPTION:   system call for open
 * INPUTS:        file - file to open
 * OUTPUTS:       none
 * RETURNS:       0 if success, -1 otherwise
 * SIDE EFFECTS:  opens file
*/
int32_t sys_open(const int8_t* fname) {
    cli();
    int32_t res = fs_open(fname);
    sti();
    return res;
}

/* sys_close()
 * 
 * DESCRIPTION:   system call for close
 * INPUTS:        fd - file directory index
 * OUTPUTS:       none
 * RETURNS:       0 if success, -1 otherwise
 * SIDE EFFECTS:  closes corresponding file descriptor entry
*/
int32_t sys_close(int32_t fd) {
    cli();
    int32_t res = fs_close(fd);
    sti();
    return res;
}

/* sys calls not yet implemented*/

int32_t sys_getargs(int8_t* buf, int32_t nbytes) {
    return get_command_line_args(buf,nbytes);
}

int32_t sys_vidmap(int8_t** screen_start) {
    return 0;
}

int32_t sys_set_handler(int32_t signum, void* handler_addr) {
    return 0;
}

int32_t sys_sigreturn() {
    return 0;
}

