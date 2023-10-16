#ifndef PAGING_H
#define PAGING_H

#define PAGEDIR_SIZE 1024	/* size of the non 4 mb page directory */
#define PAGETABLE_SIZE 1024	/* size of the page table */
#define PAGE_SIZE 4096		/* size of an individual page */
#define KERNEL_ADDR 0x400000

#ifndef ASM

#include "types.h"
#include "lib.h"

// Implemented in paging.c //

/* initalize page directory and page table entries and enable in x86  */
extern void paging_init();

// Functions implemented in paging_asm.S //

/* load address of page directory array into registers */
extern void load_page_directory(unsigned int*);

/* enable paging in x86 */
extern void enable_paging();

/* enable mixed pages in x86 */
extern void allow_mixed_pages();

// Data structures for page directory entries and page table entries //

////////////////////////////////////////////////// PAGE DIRECTORY NON 4MB STRUCT /////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) pagedirkb_entry_t {
    uint32_t present             : 1; /* whether page tables/pages present for this entry */
    uint32_t rw                  : 1; /* read/write permissions flags */
    uint32_t us                  : 1; /* User/supervisor access control bit */
    uint32_t pwt                 : 1; /* write-through */
    uint32_t pcd                 : 1; /* cache disable */
    uint32_t accessed            : 1; /* whether the page directory was accessed in memory translation */
    uint32_t avl1                : 1; /* available (?) */
    uint32_t ps0                 : 1; /* page size for entry. Always 0 for 4kb dir entries */
    uint32_t avl2                : 4; /* idk why there's two AVL entries */
    uint32_t pt_baseaddr         : 20; /* addr to start of page table */
} pagedirkb_entry_t;

////////////////////////////////////////////////// PAGE DIRECTORY 4MB STRUCT /////////////////////////////////////////////////////
/* note these don't point to a page table; point directly to a page */
typedef struct __attribute__ ((packed)) pagedirmb_entry_t {
    uint32_t present                : 1;
    uint32_t rw                     : 1;
    uint32_t us                     : 1;
    uint32_t pwt                    : 1;
    uint32_t pcd                    : 1;
    uint32_t accessed               : 1;
    uint32_t d                      : 1;
    uint32_t ps1                    : 1; /* page size for entry. Always 1 for 4MB entries */
    uint32_t global                 : 1; /* tells processor to not invalidate TLB entry on reload of CR3 */
    uint32_t avl                    : 3;
    uint32_t pat                    : 1; /* page attribute table (set to 0 for now...) */
    uint32_t page_baseaddr_bit39_32 : 8; /* used for metadata */
    uint32_t rsvd                   : 1; /* reserved for CPU use (set to 0) */
    uint32_t page_baseaddr_bit31_22 : 10; /* addr to start of 4MB page */
} pagedirmb_entry_t;

////////////////////////////////////////////////// UNION THE TWO PAGE DIRECTORY STRUCTS /////////////////////////////////////////////
typedef union pagedir_entry_t {
    pagedirkb_entry_t kb;
    pagedirmb_entry_t mb;
} pagedir_entry_t;

////////////////////////////////////////////////// PAGE TABLE STRUCT /////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)) page_table_entry_t {
    uint32_t present         : 1;
    uint32_t rw              : 1;
    uint32_t us              : 1;
    uint32_t pwt             : 1;
    uint32_t pcd             : 1;
    uint32_t accessed        : 1;
    uint32_t d               : 1;
    uint32_t pat             : 1;
    uint32_t global          : 1;
    uint32_t avl             : 3;
    uint32_t page_baseaddr   : 20;
} page_table_entry_t;

/* only has 1 page directory. All memory can be accessed through it */
pagedir_entry_t pd[PAGEDIR_SIZE] __attribute__((aligned (PAGE_SIZE)));
/* one page table for now for first 4MB in mem. Add more as needed by programs */
page_table_entry_t pt0[PAGETABLE_SIZE] __attribute__((aligned (PAGE_SIZE)));

#endif // ASM

#endif // PAGING_H
