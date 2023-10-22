#ifndef _TERMINALDRIVER_H
#define _TERMINALDRIVER_H

#include "lib.h"
#include "./interrupts/idt_handlers.h"
#include "types.h"

uint32_t terminal_read(uint32_t fd, void* buf, uint32_t nbytes);
uint32_t terminal_write(uint32_t fd, const void* buf, uint32_t nbytes);

#endif /* _TERMINALDRIVER_H */
