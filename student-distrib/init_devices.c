#include "init_devices.h"
#include "i8259.h"
#include "lib.h"

void init_rtc() {
    disable_all_irq();
    outb(0x8B, 0x70); // disable NMI and set read from reg B
    char prev = inb(0x71); // get previous value in reg B
    outb(0x8B, 0x70); // set read again
    outb(prev | 0x40, 0x71); // set bit 6 in reg B (IRQ 8)
    // enable irq 8
    enable_irq(RTC_IRQ);
}

void init_kbd() {
    
}
