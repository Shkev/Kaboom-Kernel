#include "sched.h"
#include "../lib.h"

uint8_t curr_term = 0;
term_info_t terminals[MAX_TERMINAL];


/* init_term()
 * 
 * DESCRIPTION:   initialize new terminal and set curr_term to its terminal id
 * INPUTS:        term_id  -  id of new terminal to initialize
 * OUTPUTS:       none
 * RETURNS:       0 on success, negative value on failure
 * SIDE EFFECTS:  new term info struct populated in global terminals state.
 */
int32_t init_term(term_id_t term_id) {
    if (invalid_term_id(term_id)) {
	return -1;
    }
    
    const uint32_t term_vidmem_addr = TERM0_VIDMEM_ADDR + term_id*PAGE_SIZE_4KB;
    
    // set page to present
    pt0[term_vidmem_addr].present = 1;
    terminals[term_id].vidmem_addr = term_vidmem_addr;
    terminals[term_id].cursor_x = 0;
    terminals[term_id].cursor_y = 0;
    terminals[term_id].term_id = term_id;
    terminals[term_id].nprocess = 0;
    terminals[term_id].keybufcnt = 0;
    terminals[term_id].prev_keybufcnt = 0;
    terminals[term_id].key_flags = 0;
    memset(terminals[term_id].keybuf, '\0', KEYBUF_MAX_SIZE);

    return 0;
}


/* invalid_term_id()
 * 
 * DESCRIPTION:   determines whether given terminal id is considered invalid
 * INPUTS:        term_id  -  id of new terminal to check
 * OUTPUTS:       none
 * RETURNS:       nonzero value if given id is invalid, otherwise 0.
 * SIDE EFFECTS:  new term info struct populated in global terminals state.
 */
int32_t invalid_term_id(term_id_t term_id) {
    return term_id >= MAX_TERMINAL;
}


int32_t switch_terminal(term_id_t term_id) {
    // TODO
    curr_term = term_id;
    return 0;
}
