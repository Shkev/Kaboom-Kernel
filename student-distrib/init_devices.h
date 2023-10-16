#ifndef INIT_DEV_H
#define INIT_DEV_H

#define RTC_IRQ 8
#define KBD_IRQ 1

#define RTC_INDEX 0x70
#define RTC_DATA 0X71

/* initialize the RTC enabling periodic interrupts */
extern void init_rtc();

/* initializing the keyboard device to allow of keyboard interrupts*/
extern void init_kbd();

#endif
