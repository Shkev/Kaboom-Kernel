#include "terminaldriver.h"
#include "../interrupts/idt_handlers.h"
#include "../process/sched.h"

/* terminal_read()
 * 
 * DESCRIPTION:   reads from terminal
 * INPUTS:        fd - file directory entry
 *                buf - input buffer
 *                nbytes - number of bytes to read
 * OUTPUTS:       none
 * RETURNS:       number of bytes read, -1 otherwise
 * SIDE EFFECTS:  none
 */
int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes)
{
    if (buf == NULL) {
	return -1;
    }
    //initialize buf buffer
    uint32_t count;

    if (nbytes > KEYBUF_MAX_SIZE) //check if valid
    {
        nbytes = KEYBUF_MAX_SIZE;
    }

    sti();
    while (get_bit(terminals[pcb_arr[curr_pid]->term_id].key_flags, ENTER_FLAG_BITNUM) == 0);
    //while (curr_pid != terminals[curr_term].curr_pid);
    
    cli();
    memcpy((int8_t*)buf, terminals[pcb_arr[curr_pid]->term_id].keybuf, nbytes);
    terminals[pcb_arr[curr_pid]->term_id].key_flags = unset_bit(terminals[pcb_arr[curr_pid]->term_id].key_flags, ENTER_FLAG_BITNUM);
    count = terminals[curr_term].prev_keybufcnt; // copy the count
    memset(terminals[curr_term].keybuf, '\0', KEYBUF_MAX_SIZE); //clear the buffer
    sti();
    
    return count;
}


/* terminal_write
 * 
 * DESCRIPTION:   writes to terminal
 * INPUTS:        fd - file directory entry
 *                buf - buffer to write to
 *                nbytes - number of bytes to write
 * OUTPUTS:       none
 * RETURNS:       number of bytes wrote to buffer, -1 otherwise
 * SIDE EFFECTS:  none
 */
int32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes)
{
    cli();
    if (buf == NULL) return -1;
    int i;
    for (i = 0; i < nbytes; ++i) {
        putc(*((int8_t*)buf + i));
    }
    terminals[pcb_arr[curr_pid]->term_id].key_flags = unset_bit(terminals[pcb_arr[curr_pid]->term_id].key_flags, ENTER_FLAG_BITNUM);
    sti();
    return strlen(buf); //return the length of the buffer
}

