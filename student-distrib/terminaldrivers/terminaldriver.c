#include "terminaldriver.h"
#include "../interrupts/idt_handlers.h"

uint32_t terminal_read(int32_t fd, void* buf, int32_t nbytes)
{
    //initialize buf buffer
    uint32_t count;

    if (nbytes > 128) //check if valid
    {
        return -1;
    }

    while(enterflag == 0) //copy from keybuff to buffer
    {
        memcpy((int8_t*)buf, keybuff, nbytes);
    }

    enterflag = 0;
    count = keybuffbackup; //copy the count
    return count;
}

uint32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes)
{
    cli();
    printf("%s", buf); //print the buffer
    sti();
    return strlen(buf); //return the length of the buffer
}
