#ifndef PAGING_H
#define PAGING_H

#define PAGEDIREC_SIZE 1024	/* size of the non 4 mb page directory */
#define PAGETABLE_SIZE 1024	/* size of the page table */
#define PAGE_SIZE 4096		/* size of an individual page */

#include "types.h"

void load_page_directory(unsigned int*);
void enablePaging();
void allowMixedPages();
// void page_init();

////////////////////////////////////////////////// PAGE DIRECTORY NON 4MB STRUCT /////////////////////////////////////////////////////
typedef struct __attribute__ ((packed, aligned(4))) pagedirectKB_t {
    uint32_t presentpd   : 1;
    uint32_t read_writepd : 1;
    uint32_t user_supervisorpd : 1;
    uint32_t writethroughpd : 1;
    uint32_t cachedisablepd : 1;
    uint32_t accessedpd : 1;
    uint32_t avl : 1;
    uint32_t ps0 : 1;
    uint32_t availabilitypd : 4;
    uint32_t pdbaseaddress : 20;
} pagedirectKB_t;

////////////////////////////////////////////////// PAGE DIRECTORY 4MB STRUCT /////////////////////////////////////////////////////
typedef struct __attribute__ ((packed,  aligned(4))) pagedirectMB_t {
    uint32_t presentpd4mb : 1;
    uint32_t read_writepd4mb : 1;
    uint32_t user_supervisorpd4mb : 1;
    uint32_t writethroughpd4mb : 1;
    uint32_t cachedisablepd4mb : 1;
    uint32_t accessedpd4mb : 1;
    uint32_t dirty4mb : 1;
    uint32_t ps14mb : 1;
    uint32_t global4mb : 1;
    uint32_t availabilitypd4mb : 3;
    uint32_t page_attribute_table : 1;
    uint32_t bit39_32pd : 8;
    uint32_t rsvd : 1;
    uint32_t bit31_22pd : 10;
} pagedirectMB_t;

////////////////////////////////////////////////// UNION THE TWO PAGE DIRECTORY STRUCTS /////////////////////////////////////////////
typedef union pagedirectory_t {
    struct pagedirectKB_t pageKB;
    struct pagedirectMB_t pageMB;
} pagedirectory_t;

////////////////////////////////////////////////// PAGE TABLE STRUCT /////////////////////////////////////////////////////
typedef struct __attribute__ ((packed,  aligned(4))) pageTable_t {
    uint32_t presentpt   : 1;
    uint32_t read_writept : 1;
    uint32_t user_supervisorpt : 1;
    uint32_t writethroughpt : 1;
    uint32_t cachedisablept : 1;
    uint32_t accessedpt : 1;
    uint32_t dirty : 1;
    uint32_t pageattribute : 1;
    uint32_t global : 1;
    uint32_t availabilitypt : 3;
    uint32_t ptbaseaddress : 20;
} pageTable_t;


pagedirectory_t pdarray[PAGEDIREC_SIZE] __attribute__((aligned (PAGE_SIZE))); //fix this line
struct pageTable_t ptarray[PAGETABLE_SIZE] __attribute__((aligned (PAGE_SIZE)));

#endif
