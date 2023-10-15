void loadPageDirectory(unsigned int*);
void enablePaging();

////////////////////////////////////////////////// PAGE DIRECTORY NON 4MB STRUCT /////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)){
    // uint32_t pdbaseaddress : 20; //setting the values for all sub parts
    // uint32_t availabilitypd : 4;
    // uint32_t ps0 : 1;
    // uint32_t avl : 1;
    // uint32_t accessedpd : 1;
    // uint32_t cachedisablepd : 1;
    // uint32_t writethroughpd : 1;
    // uint32_t user_supervisorpd : 1;
    // uint32_t read_writepd : 1;
    // uint32_t presentpd   : 1;
    
    // flip the order maybe?
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
} pagedirectKB;

////////////////////////////////////////////////// PAGE DIRECTORY NON 4MB STRUCT /////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)){
    // uint32_t bit31_22pd : 10; //setting the values for all sub parts
    // uint32_t rsvd : 1;
    // uint32_t bit39_32pd : 8;
    // uint32_t page_attribute_table : 1;
    // uint32_t availabilitypd4mb : 3;
    // uint32_t global4mb : 1;
    // uint32_t ps14mb : 1;
    // uint32_t dirty4mb : 1;
    // uint32_t accessedpd4mb : 1;
    // uint32_t cachedisablepd4mb : 1;
    // uint32_t writethroughpd4mb : 1;
    // uint32_t user_supervisorpd4mb : 1;
    // uint32_t read_writepd4mb : 1;
    // uint32_t presentpd4mb : 1;

    //flip the order maybe?
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

} pagedirectMB;

////////////////////////////////////////////////// UNION THE TWO PAGE DIRECTORY STRUCTS /////////////////////////////////////////////
typedef union {
    pagedirectKB pageKB;
    pagedirectMB pageMB;
} pagedirectory;

////////////////////////////////////////////////// PAGE TABLE STRUCT /////////////////////////////////////////////////////
typedef struct __attribute__ ((packed)){
    // uint32_t ptbaseaddress : 20; //setting the values for all sub parts
    // uint32_t availabilitypt : 3;
    // uint32_t global : 1;
    // uint32_t pageattribute : 1;
    // uint32_t dirty : 1;
    // uint32_t accessedpt : 1;
    // uint32_t cachedisablept : 1;
    // uint32_t writethroughpt : 1;
    // uint32_t user_supervisorpt : 1;
    // uint32_t read_writept : 1;
    // uint32_t presentpt   : 1;

    //flip the order maybe?
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
} pageTable;

