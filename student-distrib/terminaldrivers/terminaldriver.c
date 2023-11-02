#include "terminaldriver.h"
#include "../interrupts/idt_handlers.h"

int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes)
{
    if (buf == NULL) return -1;
    //initialize buf buffer
    uint32_t count;

    if (nbytes > KEYBUF_MAX_SIZE) //check if valid
    {
        nbytes = KEYBUF_MAX_SIZE;
    }

    while (enterflag == 0) //copy from keybuff to buffer
    {
        memcpy((int8_t*)buf, keybuff, nbytes);
    }

    enterflag = 0;
    count = keybuffbackup; //copy the count
    fill_buffer(keybuff, '\0', 128); //clear the buffer

    return count;
}

int32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes)
{
    if (buf == NULL) return -1;
    int i;
    cli();
    for (i = 0; i < nbytes; ++i) {
        putc(*((int8_t*)buf + i));
    }
    enterflag = 0;
    sti();
    return strlen(buf); //return the length of the buffer
}
