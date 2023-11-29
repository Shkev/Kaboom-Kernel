#include "sched.h"
#include "../lib.h"

uint8_t curr_term = 0;
term_info_t terminals[MAX_TERMINAL];

/////////// HELPER FUNCTIONS ///////////////////

static void setup_term_page(term_id_t term_id);
static void swap_out_curr_term();
static void swap_in_next_term(term_id_t term_id);

////////////////////////////////////////////////


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
    terminals[term_id].vidmem_addr = term_vidmem_addr;
    setup_term_page(term_id);
    
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


/* switch_terminal()
 * 
 * DESCRIPTION:   switch active terminal to terminal with given id
 * INPUTS:        term_id  -  id of terminal to switch to
 * OUTPUTS:       none
 * RETURNS:       none
 * SIDE EFFECTS:  change current terminal and modify page tables
 */
void switch_terminal(term_id_t term_id) {
    // TODO
    swap_out_curr_term();
    swap_in_next_term(term_id);
}


/* setup_term_page()
 * 
 * DESCRIPTION:   setup page in page table for terminal's vidmem
 * INPUTS:        term_id  -  id of terminal to setup
 * OUTPUTS:       none
 * RETURNS:       none
 * SIDE EFFECTS:  modifies page tables
 */
static void setup_term_page(term_id_t term_id) {
    uint32_t pt_idx = get_pt_idx(terminals[term_id].vidmem_addr);

    pt0[pt_idx].present = 1;
    pt0[pt_idx].rw = 1;
    // vmem and physical address are the same (like for actual vidmem and kernel)
    pt0[pt_idx].page_baseaddr = terminals[term_id].vidmem_addr >> 12;
}


void swap_out_curr_term() {
    // saving screen x, y done through lib.c function (i.e., printf, putc, etc.)
    // doing video memory copying stuff here...
    const uint32_t term_vidmem_addr = TERM0_VIDMEM_ADDR + curr_term*PAGE_SIZE_4KB;
    terminals[curr_term].vidmem_addr = term_vidmem_addr;
    memcpy((char*)term_vidmem_addr, (char*)VIDEO, PAGE_SIZE_4KB);
}


void swap_in_next_term(term_id_t term_id) {
    curr_term = term_id; 	/* handles restoring cursor position */
    const uint32_t term_vidmem_addr = TERM0_VIDMEM_ADDR + term_id*PAGE_SIZE_4KB;
    memcpy((char*)VIDEO, (char*)term_vidmem_addr, PAGE_SIZE_4KB);
    terminals[term_id].vidmem_addr = VIDEO;
    update_cursor(terminals[term_id].cursor_x, terminals[term_id].cursor_y);
}

