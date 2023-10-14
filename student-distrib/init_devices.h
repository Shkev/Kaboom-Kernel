#ifndef INIT_DEV_H
#define INIT_DEV_H

#define RTC_IRQ 8

/* initialize the RTC enabling periodic interrupts */
extern void init_rtc();

extern void init_kbd();

#endif
