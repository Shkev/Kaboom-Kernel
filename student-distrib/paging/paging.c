#include "paging.h"


page_table_entry_t pt1[PAGETABLE_SIZE];

/*
 * void paging_init(void):
 *    DESCRIPTION: initalize page directory and page table entries and enable in x86
 *    INPUTS: none
 *    OUTPUTS: none
 *    RETURN VALUE: none
 *    SIDE EFFECTS: Initialize entries in pd and pt0 arrays and set registers cr0, cr3, cr4
 */
void paging_init()
{
    unsigned int j;

    /* initialize page directory entries 
     * Note: all entries in pd and pt0 are set to 0 in x86_desc.S
     */
    for (j = 0; j < PAGEDIR_SIZE; j++) {
	    /* first 4MB block in physical mem. Uses 4KB pages */
        if (j == 0) {
	        ZERO_PAGEDIR_KB(pd[j].kb);
            pd[j].kb.present = 1;
            pd[j].kb.pt_baseaddr = ((unsigned int)pt0) >> 12;
	        pd[j].kb.rw = 1;
        } else if (j == 1) { // 2nd 4MB physical mem block for kernel
	        ZERO_PAGEDIR_MB(pd[j].mb);
            pd[j].mb.present = 1;
            pd[j].mb.ps1 = 1;
	        pd[j].mb.rw = 1;
            pd[j].mb.global = 1;
            pd[j].mb.page_baseaddr_bit31_22 = KERNEL_ADDR >> 22;
        } else { // eveything else allocated as needed by programs
	        ZERO_PAGEDIR_KB(pd[j].kb);
	    }
    }
    
    // set up process image page (base address changed dynamically as new processes created)
    ZERO_PAGEDIR_MB(pd[PROCESS_DIR_IDX].mb);
    pd[PROCESS_DIR_IDX].mb.present = 1;
    pd[PROCESS_DIR_IDX].mb.ps1 = 1;
    pd[PROCESS_DIR_IDX].mb.rw = 1;
    pd[PROCESS_DIR_IDX].mb.us = 1;

    // initializing page table 0 and 1 for first 4MB block
    for (j = 0; j < PAGETABLE_SIZE; j++)
    {
        ZERO_PAGETAB_ENTRY(pt0[j]);
        ZERO_PAGETAB_ENTRY(pt1[j]);
        pt0[j].rw = 1;
        pt1[j].rw = 1;
        pt0[j].page_baseaddr = j;
        /* if page not for video memory */
        if (j == (VIDEO >> 12)) { // for video mem
            pt0[j].present = 1;
        }
    }

    // assembly stuff
    load_page_directory((unsigned int*)pd);
    allow_mixed_pages();
    enable_paging();
}
