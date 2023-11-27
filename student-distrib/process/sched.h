#ifndef SCHED_H
#define SCHED_H

#include "../types.h"
#include "process.h"

#define MAX_TERMINAL 3
#define KEYBUF_MAX_SIZE 128

/* term info key pressed flag bitnumber for each key */
#define SHIFT_FLAG_BITNUM 0
#define CAPSLOCK_FLAG_BITNUM 1
#define BKSPC_FLAG_BITNUM 2
#define TAB_FLAG_BITNUM 3
#define CTRL_FLAG_BITNUM 4
#define ALT_FLAG_BITNUM 5


/* terminal info struct. stores info about current state of a terminal
 * to allow recovering terminal state when switching to it */
typedef struct term_info {
    uint8_t term_id;		     /* unique id for terminal (8 bits - support up to 255 open terminals) */
    int32_t cursor_x;		     /* x-pos of cursor on screen */
    int32_t cursor_y;		     /* y-pos of cursor on screen */
    char keybuf[KEYBUF_MAX_SIZE];    /* characters in terminal's keyboard buffer */
    uint32_t keybufcnt;		     /* count characters typed in buffer */
    uint32_t prev_keybufcnt;	     /* num chars typed in previous buffer (before enter pressed) */
    uint8_t key_flags;               /* flags indicating whether key is pressed */
} term_info_t;


/* currently active terminal id */
extern uint8_t curr_term;

/* store info about all terminals in system */
extern term_info_t terminals[MAX_TERMINAL];

#endif	/* SCHED_H */
