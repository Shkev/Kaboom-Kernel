#include "terminaldriver.h"

uint32_t terminal_read(uint32_t fd, void* buf, uint32_t nbytes)
{
    //initialize buf buffer
    uint32_t count;

    if (nbytes > 128)
    {
        return -1;
    }

    while(enterflag == 0)
    {
        //int i = 0;
        memcpy((int8_t*)buf, keybuff, nbytes);
        // for (i = 0; i < keybuffbackup; i++)
        // {
        //     // char value = *((char*)buf + i);
        //     *((char*)buf + i) = keybuff[i];//[i];
        // }
    }

    enterflag = 0;
    count = keybuffbackup;
    return count;
}

uint32_t terminal_write(uint32_t fd, const void* buf, uint32_t nbytes)
{
    // const char* testbuff = (const char*)buf;

    cli();
    // int j = 0;
    // int bytescount = 0;
    printf("%s", buf);
    // for (j = 0; j < nbytes; j++)
    // {
    //     if (*((char*)buf + j) == '\0')
    //     {
    //     } else {
    //         putc(*((char*)buf + j));
    //         bytescount++;
    //     }
    // }
    sti();
    return strlen(buf);
}
