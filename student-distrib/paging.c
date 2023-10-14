#include "paging.h"
// I'M PRETTY SURE WE NEED TO INCLUDE SOME STUFF
// FIGURE OUT WHAT TO INCLUDE/IMPORT OR DEFINE
#define pdn4size 1
#define pdsize 1024
#define ptsize 1024
#define pagesize 4096

//WHAT TO DO
// 3 FUNCTIONS; page_init (C), loadPageDirectory (ASM), enablePaging (ASM), extra one in case needed: flushTLB (C)

// make an array of structs for the directories and tables
paging_directoryno4mb pdn4array[pdn4size] __attribute__((aligned (4096)));
paging_directoryvalid4mb pd4array[pdsize] __attribute__((aligned (4096)));
paging_table ptarray[ptsize][ptsize] __attribute__((aligned (4096)));

///////////////////////////////////////////////// INITIALIZING PAGE DIRECTORY //////////////////////////////////////////
unsigned i;
unsigned j;
void page_init()
{
    // INITIALIZE THE PAGE TABLE STRUCT
    for (j = 0; j < ptsize; j++)
    {
        /* SET THE INITIAL 20 BITS TO ZERO */
        ptarray[j][0].ptbaseaddress = j * pagesize;  //as each page is 4096, and you are determining what page to go to
        /* SET THE AVAILABILITY BITS TO ZERO */
        ptarray[j][0].availabilitypt = 0;    
        /* SET THE GLOBAL SIZE BITS */
        ptarray[j][0].global = 0;
        /* SET THE PAGE ATTRIBUTE BITS */
        ptarray[j][0].pageattribute = 0;
        /* SET THE DIRTY BITS */
        ptarray[j][0].dirty = 0;
        /* SET THE ACCESSED BITS */
        ptarray[j][0].accessedpt = 0;
        /* SET THE CACHE DISABLE BITS */
        ptarray[j][0].cachedisablept = 0;
        /* SET THE WRITE THROUGH BITS */
        ptarray[j][0].writethroughpt = 0;
        /* SET THE USER SUPERVISOR BITS */
        ptarray[j][0].user_supervisorpt = 0;
        /* SET THE READ WRITE BITS */
        ptarray[j][0].read_writept = 1; //since a page exists, allow read and writes
        /* SET THE PRESENT BITS */
        ptarray[j][0].presentpt = 1; //initializing some pages
    }

    // INITIALIZE THE PAGE DIRECTORY WITHOUT THE 4 MB STRUCT
    for (i = 0; i < pdsize; i++)
    {
        /* SET THE INITIAL 20 BITS */
        pdn4array[i].pdbaseaddress = 0;
        /* SET THE AVAILABILITY BITS */
        pdn4array[i].availabilitypd = 0;
        /* SET THE PAGE SIZE BITS */
        pdn4array[i].ps0 = 0;
        /* SET THE AVAILABILITY BITS */
        pdn4array[i].avl = 0;
        /* SET THE ACCESSED BITS */
        pdn4array[i].accessedpd = 0;
        /* SET THE CACHE DISABLE BITS */
        pdn4array[i].cachedisablepd = 0;
        /* SET THE WRITE-THROUGH BITS */
        pdn4array[i].writethroughpd = 0;
        /* SET THE USER SUPERVISOR BITS */
        pdn4array[i].user_supervisorpd = 0;
        /* SET THE READ WRITE BITS */
        pdn4array[i].read_writepd = 1;  //according to setting up page tables
        /* SET THE PRESENT BITS */
        pdn4array[i].presentpd = 0;
    }
    pdn4array[0].pdbaseaddress = (uint32_t)(&ptarray[0][0] >> 12);

    // INITIALIZE THE PAGE DIRECTORY WITH THE 4 MB STRUCT
    // NOT SURE ABOUT THE FOLLOWING, CHECK WITH SOMEONE IF THIS IS RIGHT

    for (i = 0; i < pdn4size; i++)
    {
        /* SET THE INITIAL 10 BITS TO ZERO */
        pd4array[i].bit31_22pd = 0;
        /* SET THE RESERVED BITS TO ZERO */
        pd4array[i].rsvd = 0;
        /* SET THE RANDOM BITS TO ZERO */
        pd4array[i].bit39_32pd = 0;
        /* SET THE PAGE ATTRIBUTE TABLE BITS TO ZERO */
        pd4array[i].page_attribute_table = 0;
        /* SET THE AVAILABILITY BITS TO ZERO */
        pd4array[i].availabilitypd4mb = 0;
        /* SET THE GLOBAL BITS TO ZERO */
        pd4array[i].global4mb = 0;
        /* SET THE PAGE SIZE BITS TO ZERO */
        pd4array[i].ps14mb = 1;
        /* SET THE DIRTY BITS TO ZERO */
        pd4array[i].dirty4mb = 0;
        /* SET THE ACCESS BITS TO ZERO */
        pd4array[i].accessedpd4mb = 0;
        /* SET THE CACHE DISABLE BITS TO ZERO */
        pd4array[i].cachedisablepd4mb = 0;
        /* SET THE WRITE-THROUGH BITS TO ZERO */
        pd4array[i].writethroughpd4mb = 0;
        /* SET THE USER SUPERVISOR BITS TO ZERO */
        pd4array[i].user_supervisorpd4mb = 0;
        /* SET THE READ WRITE BITS TO ZERO */
        pd4array[i].read_writepd4mb = 1;
        /* SET THE PRESENT BITS TO ZERO */
        pd4array[i].presentpd4mb = 0;
    }
}