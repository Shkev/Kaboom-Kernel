#include "sched.h"
#include "../lib.h"

uint8_t curr_term = 0;
term_info_t terminals[MAX_TERMINAL];


/* init_term()
 * 
 * DESCRIPTION:   initialize new terminal and set curr_term to its terminal id
 * INPUTS:        none
 * OUTPUTS:       none
 * RETURNS:       terminal id of new terminal; negative value if failed
 * SIDE EFFECTS:  new term info struct populated in global terminals state.
 *                modifies curr_term
 */
int32_t init_term() {
    // TODO
    static uint8_t num_term = 0;

    if (num_term >= MAX_TERMINAL) {
	return -1;
    }
    
    const uint32_t term_vidmem_addr = TERM0_VIDMEM_ADDR + num_term*PAGE_SIZE_4KB;
    
    // set page to present
    pt0[term_vidmem_addr].present = 1;
    terminals[num_term].vidmem_addr = term_vidmem_addr;
    terminals[num_term].cursor_x = 0;
    terminals[num_term].cursor_y = 0;
    terminals[num_term].term_id = num_term;
    terminals[num_term].nprocess = 0;
    terminals[num_term].keybufcnt = 0;
    terminals[num_term].prev_keybufcnt = 0;
    terminals[num_term].key_flags = 0;
    memset(terminals[num_term].keybuf, '\0', KEYBUF_MAX_SIZE);
    
    num_term++;
    return num_term-1;
}

