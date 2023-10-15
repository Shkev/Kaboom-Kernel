#include "paging.h"

//WHAT TO DO
// 3 FUNCTIONS; page_init (C), load_page_directory (ASM), enablePaging (ASM), extra one in case needed: flushTLB (C)

// make an array of structs for the directories and tables
// pagedirectory_t pdarray[PAGEDIREC_SIZE] __attribute__((aligned (PAGE_SIZE))); //fix this line
// struct pageTable_t ptarray[PAGETABLE_SIZE] __attribute__((aligned (PAGE_SIZE)));

///////////////////////////////////////////////// INITIALIZING EVERYTHING IN REGARDS TO PAGES //////////////////////////////////////////

void page_init()
{
    unsigned int i;
    unsigned int j;
    // INITIALIZE THE PAGE TABLE STRUCT
    for (i = 0; i < PAGETABLE_SIZE; i++)
    {
        ptarray[i].availabilitypt = 0;               /* SET THE AVAILABILITY BITS TO ZERO */
        ptarray[i].global = 0;                       /* SET THE GLOBAL SIZE BITS */
        ptarray[i].pageattribute = 0;                /* SET THE PAGE ATTRIBUTE BITS */
        ptarray[i].dirty = 0;                        /* SET THE DIRTY BITS */
        ptarray[i].accessedpt = 0;                   /* SET THE ACCESSED BITS */
        ptarray[i].cachedisablept = 0;               /* SET THE CACHE DISABLE BITS */
        ptarray[i].writethroughpt = 0;               /* SET THE WRITE THROUGH BITS */
        ptarray[i].user_supervisorpt = 0;            /* SET THE USER SUPERVISOR BITS */
        
        if (i != 184)
        {
            ptarray[i].ptbaseaddress = i * PAGE_SIZE;     /* SET THE INITIAL 20 BITS TO THE PAGE ADDRESS */       //as each page is 4096, and you are determining what page to go to
            ptarray[i].read_writept = 1;                 /* SET THE READ WRITE BITS */               //since a page exists, allow read and writes
            ptarray[i].presentpt = 0;                    /* SET THE PRESENT BITS */                  //initializing some pages
        }

        if (i == 184)
        {
            ptarray[i].ptbaseaddress = 0xB8000 / PAGE_SIZE;     /* SET THE INITIAL 20 BITS TO PAGE ADDRESS */       //as each page is 4096, and you are determining what page to go to
            ptarray[i].read_writept = 1;                 /* SET THE READ WRITE BITS */               //since a page exists, allow read and writes
            ptarray[i].presentpt = 1;                    /* SET THE PRESENT BITS */                  //initializing some pages
        }
    }

    // INITIALIZE THE PAGE DIRECTORY WITHOUT THE 4 MB STRUCT
    for (j = 0; j < PAGEDIREC_SIZE; j++)
    {
        if (j == 0)
        {
            pdarray[j].pageKB.pdbaseaddress = (((unsigned int)ptarray) >> 12);           //(uint32_t)(&ptarray[0][0] >> 12);             /* SET THE INITIAL 20 BITS */
            pdarray[j].pageKB.availabilitypd = 0;                                           /* SET THE AVAILABILITY BITS */
            pdarray[j].pageKB.ps0 = 0;                       /* SET THE PAGE SIZE BITS */
            pdarray[j].pageKB.avl = 0;                       /* SET THE AVAILABILITY BITS */
            pdarray[j].pageKB.accessedpd = 0;                /* SET THE ACCESSED BITS */
            pdarray[j].pageKB.cachedisablepd = 0;            /* SET THE CACHE DISABLE BITS */
            pdarray[j].pageKB.writethroughpd = 0;            /* SET THE WRITE-THROUGH BITS */
            pdarray[j].pageKB.user_supervisorpd = 0;         /* SET THE USER SUPERVISOR BITS */
            pdarray[j].pageKB.read_writepd = 1;              /* SET THE READ WRITE BITS */               //according to setting up page tables
            pdarray[j].pageKB.presentpd = 0;                 /* SET THE PRESENT BITS */
        } else if (j == 1)
        {
            pdarray[j].pageMB.bit31_22pd = 1;                /* SET THE INITIAL 10 BITS TO ZERO */
            pdarray[j].pageMB.rsvd = 0;                      /* SET THE RESERVED BITS TO ZERO */
            pdarray[j].pageMB.bit39_32pd = 0;                /* SET THE RANDOM BITS TO ZERO */
            pdarray[j].pageMB.page_attribute_table = 0;      /* SET THE PAGE ATTRIBUTE TABLE BITS TO ZERO */
            pdarray[j].pageMB.availabilitypd4mb = 0;         /* SET THE AVAILABILITY BITS TO ZERO */
            pdarray[j].pageMB.global4mb = 1;                 /* SET THE GLOBAL BITS TO ONE */
            pdarray[j].pageMB.ps14mb = 1;                    /* SET THE PAGE SIZE BITS TO ZERO */
            pdarray[j].pageMB.dirty4mb = 0;                  /* SET THE DIRTY BITS TO ZERO */
            pdarray[j].pageMB.accessedpd4mb = 0;             /* SET THE ACCESS BITS TO ZERO */
            pdarray[j].pageMB.cachedisablepd4mb = 0;         /* SET THE CACHE DISABLE BITS TO ZERO */
            pdarray[j].pageMB.writethroughpd4mb = 0;         /* SET THE WRITE-THROUGH BITS TO ZERO */
            pdarray[j].pageMB.user_supervisorpd4mb = 0;      /* SET THE USER SUPERVISOR BITS TO ZERO */
            pdarray[j].pageMB.read_writepd4mb = 1;           /* SET THE READ WRITE BITS TO ZERO */
            pdarray[j].pageMB.presentpd4mb = 0;              /*  SET THE PRESENT BITS TO ZERO */
        } else {
            pdarray[j].pageKB.pdbaseaddress = 0;             /* SET THE INITIAL 20 BITS */
            pdarray[j].pageKB.availabilitypd = 0;            /* SET THE AVAILABILITY BITS */
            pdarray[j].pageKB.ps0 = 0;                       /* SET THE PAGE SIZE BITS */
            pdarray[j].pageKB.avl = 0;                       /* SET THE AVAILABILITY BITS */
            pdarray[j].pageKB.accessedpd = 0;                /* SET THE ACCESSED BITS */
            pdarray[j].pageKB.cachedisablepd = 0;            /* SET THE CACHE DISABLE BITS */
            pdarray[j].pageKB.writethroughpd = 0;            /* SET THE WRITE-THROUGH BITS */
            pdarray[j].pageKB.user_supervisorpd = 0;         /* SET THE USER SUPERVISOR BITS */
            pdarray[j].pageKB.read_writepd = 1;              /* SET THE READ WRITE BITS */               //according to setting up page tables
            pdarray[j].pageKB.presentpd = 0;                 /* SET THE PRESENT BITS */
        }
    }

    load_page_directory((unsigned int*) pdarray);
    enablePaging();
    allowMixedPages();
}
