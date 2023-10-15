#include "paging.h"

/*
 * paging_init:
 *    DESCRIPTION: initalize page directory and page table entries and enable in x86
 *    INPUTS: none
 *    OUTPUTS: none
 *    RETURN VALUE: none
 *    SIDE EFFECTS: Initialize entries in pd and pt0 arrays and set registers cr0, cr3, cr4
 */
void paging_init()
{
    unsigned int j;

    // initialize page directory entries
    for (j = 0; j < PAGEDIR_SIZE; j++)
    {
	/* first 4MB block in physical mem. Uses 4KB pages */
        if (j == 0) {
	    pd[j].kb = 0;

	    pd[j].kb.rw = 1;
	    pd[j].kb.pt_baseaddr = ((uint32_t)pt0) >> 12;
        } else if (j == 1) { // 4MB physical mem block for kernel
	    pd[j].mb = 0;

	    pd[j].mb.rw = 1;
	    pd[j].mb.ps1 = 1;
	    pd[j].mb.global = 1;
	    pd[j].mb.page_baseaddr = KERNEL_ADDR >> 22;
        } else { // everything else; initialized as needed by programs
	    pd[j].kb = 0;
        }
    }
    
    // initializing page table 0
    for (j = 0; j < PAGETABLE_SIZE; j++)
    {
        pt0[j] = 0;

	/* if page not for video memory */
        if (j != (VIDEO >> 12)) {
            pt0[j].page_baseaddr = j;
        } else { // for video mem
            pt0[j].page_baseaddr = VIDEO >> 12;
            pt0[j].rw = 1;
	    pt0[j].us = 1;
            pt0[j].present = 1;
        }
    }

    // assembly stuff
    load_page_directory((unsigned int*) pd);
    enable_paging();
    allow_mixed_pages();
}
