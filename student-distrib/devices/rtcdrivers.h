#ifndef _RTCDRIVER_H
#define _RTCDRIVER_H

#include "../types.h"
#include "../interrupts/idt_handlers.h"

#define RTC_MAGIC_RATENUM 32768
#define RTC_MAX_FREQ 1024

////////// VIRTUALIZING RTC PARAMS /////////////

/* RTC freq seen by programs */
extern uint16_t virt_rtc_freq;

/* number of rtc interrupts to wait before noifying program of rtc interrupt ("virtual interrupt")
 * acts as a frequency divider. */
extern uint16_t rtc_counter;

/* number of rtc interrupts occured since last virtual interrupt sent */
extern uint16_t rtc_interrupt_cnt;

////////////////////////////////////////////////

extern int32_t rtc_open(const int8_t* fname);
extern int32_t rtc_read(int32_t fd, void* buf, int32_t nbytes);
extern int32_t rtc_write(int32_t fd, const void* buf, int32_t nbytes);
extern int32_t rtc_close(int32_t fd);


#endif /* _RTCDRIVER_H */
