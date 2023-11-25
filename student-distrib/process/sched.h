#ifndef SCHED_H
#define SCHED_H


/* terminal info struct. stores info about current state of a terminal
 * to allow recovering terminal state when switching to it */
typedef struct term_info {
    uint8_t term_id;		     /* unique id for terminal (8 bits - support up to 255 open terminals) */
    int32_t cursor_x;		     /* x-pos of cursor on screen */
    int32_t cursor_y;		     /* y-pos of cursor on screen */
    char keybuf[KEYBUF_MAX_SIZE];    /* characters in terminal's keyboard buffer */
} term_info_t;



/* currently active terminal id */
extern uint8_t curr_term;

extern term_info_t terminals[MAX_TERMINAL];

#endif
