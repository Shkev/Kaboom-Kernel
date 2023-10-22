#ifndef _TERMINALDRIVER_H
#define _TERMINALDRIVER_H
#include "../lib.h"
#include "../types.h"

extern void terminal_read(int32_t fd, void* buf, int32_t nbytes);
extern void terminal_write(int32_t fd, const void* buf, int32_t nbytes);

#endif /* _TERMINALDRIVER_H */
