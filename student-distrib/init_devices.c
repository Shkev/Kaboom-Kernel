#include "init_devices.h"
#include "i8259.h"
#include "lib.h"

void init_rtc() {
    //disable_all_irq();
    outb(0x8B, RTC_INDEX); // disable NMI and set read from reg B
    char prev = inb(RTC_DATA); // get previous value in reg B
    outb(0x8B, RTC_INDEX); // set read again
    outb(prev | 0x40, RTC_DATA); // set bit 6 in reg B (IRQ 8)
    // enable irq 8
    enable_irq(RTC_IRQ);
}

void init_kbd() {
    enable_irq(KBD_IRQ);
}
