#include "init_devices.h"
#include "i8259.h"
#include "lib.h"

/*init_rtc()
* DESCRIPTION: initialize rtc
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: enables the PIC IRQ 8 to allow rtc interrupts
*/
void init_rtc() {
    outb(0x8B, RTC_INDEX); // disable NMI and set read from reg B
    char prev = inb(RTC_DATA); // get previous value in reg B
    outb(0x8B, RTC_INDEX); // set read again
    outb(prev | 0x40, RTC_DATA); // set bit 6 in reg B (IRQ 8)
    // enable irq 8 (RTC irq line)
    enable_irq(RTC_IRQ);
}

/*init_kbd()
* DESCRIPTION: initializes keyboard interrupts
* INPUTS: none
* OUTPUTS: none
* RETURN VALUE: none
* SIDE EFFECTS: enables PIC IRQ1 to allow for keyboard interrupts
*/
void init_kbd() {
    // enable irq 1 (keyboard irq line)
    enable_irq(KBD_IRQ);
}
