#include "paging.h"

#define ZERO_PAGEDIR_KB(name)     \
    name.present = 0       ;\
    name.rw = 0            ;\
    name.us = 0            ;\
    name.pwt = 0           ;\
    name.pcd = 0           ;\
    name.accessed = 0      ;\
    name.avl1 = 0          ;\
    name.ps0 = 0           ;\
    name.avl2 = 0          ;\
    name.pt_baseaddr = 0    \


#define ZERO_PAGEDIR_MB(name)         \
    name.present = 0                 ;\
    name.rw = 0                      ;\
    name.us = 0                      ;\
    name.pwt = 0                     ;\
    name.pcd = 0                     ;\
    name.accessed = 0                ;\
    name.d = 0                       ;\
    name.ps1 = 0                     ;\
    name.global = 0                  ;\
    name.avl = 0                     ;\
    name.pat = 0                     ;\
    name.page_baseaddr_bit39_32 = 0  ;\
    name.rsvd = 0                    ;\
    name.page_baseaddr_bit31_22 = 0   \


#define ZERO_PAGETAB_ENTRY(name)      \
    name.present = 0                 ;\
    name.rw = 0                      ;\
    name.us = 0                      ;\
    name.pwt = 0                     ;\
    name.pcd = 0                     ;\
    name.accessed = 0                ;\
    name.d = 0                       ;\
    name.global = 0                  ;\
    name.avl = 0                     ;\
    name.page_baseaddr = 0            \


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
	    ZERO_PAGEDIR_KB(pd[j].kb);
	    pd[j].kb.rw = 1;
	    pd[j].kb.pt_baseaddr = ((uint32_t)pt0) >> 12;
        } else if (j == 1) { // 4MB physical mem block for kernel
	    ZERO_PAGEDIR_MB(pd[j].mb);
	    pd[j].mb.present = 1;
	    pd[j].mb.rw = 1;
	    pd[j].mb.ps1 = 1;
	    pd[j].mb.global = 1;
	    pd[j].mb.page_baseaddr_bit31_22 = KERNEL_ADDR >> 22;
        } else { // everything else; initialized as needed by programs
	    ZERO_PAGEDIR_KB(pd[j].kb);
        }
    }
    
    // initializing page table 0
    for (j = 0; j < PAGETABLE_SIZE; j++)
    {
	ZERO_PAGETAB_ENTRY(pt0[j]);

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
    load_page_directory((uint32_t)pd);
    enable_paging();
    allow_mixed_pages();
}
