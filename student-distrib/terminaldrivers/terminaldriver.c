#include "terminaldriver.h"
#include "../interrupts/idt_handlers.h"

uint32_t terminal_read(int32_t fd, void* buf, int32_t nbytes)
{
    //initialize buf buffer
    uint32_t count;

    if (nbytes > 128)
    {
        return -1;
    }

    while(enterflag == 0)
    {
        memcpy((int8_t*)buf, keybuff, nbytes);
    }

    enterflag = 0;
    count = keybuffbackup;
    return count;
}

uint32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes)
{
    cli();
    printf("%s", buf);
    sti();
    return strlen(buf);
}
