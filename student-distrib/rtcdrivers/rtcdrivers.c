#include "rtcdrivers.h"
#include "../lib.h"
#include "../interrupts/idt_handlers.h"


/* rtc_open(uint8_t*)
 * 
 * DESCRIPTION:   Open the RTC and set the frequency to 2Hz
 * INPUTS:        fname - ignore(?)
 * OUTPUTS:       none
 * RETURNS:       0
 * SIDE EFFECTS:  Changes RTC rate (value in register A)
 */
int32_t rtc_open(const uint8_t* fname) {
    const uint8_t init_rate = 0x0F;           /* set frequency rate to 2 */

    // disable interrupts
    
    outb(0x8A, RTC_INDEX);	              /* set index to register A, disable NMI */
    char prev = inb(RTC_DATA);	              /* get initial value of register A */
    outb(0x8A, RTC_INDEX);
    outb((prev & 0xF0) | init_rate,RTC_DATA); /* write frequency rate to A; bottom 4 bits are the rate */

    // enable interrupts

    return 0;
}


/* rtc_read(int32_t, void*, int32_t)
 * 
 * DESCRIPTION:   Waits for an interrupt and then returns 0
 * INPUTS:        ignore all
 * OUTPUTS:       none
 * RETURNS:       0 on rtc interrupt
 * SIDE EFFECTS:  Changes rtc flag
 */
int32_t rtc_read(int32_t fd, void* buf, int32_t nbytes) {
    // some basic synchronization
    while (RTC_FLAG == 0);   /* wait for rtc interrupt */
    RTC_FLAG = 0;	     /* reset RTC flag to 0 */
    return 0;		     /* return 0 when rtc interrupt received */
}


/* rtc_open(int32_t, const void*, int32_t)
 * 
 * DESCRIPTION:   Set rate of periodic interrupts for RTC
 * INPUTS:        fd     - ignore(?)
                  buf    - interrupt rate in Hz to set RTC to
 * OUTPUTS:       none
 * RETURNS:       0 on succeess, -1 on failure
 * SIDE EFFECTS:  Changes RTC rate (value in register A)
 */
int32_t rtc_write(int32_t fd, const void* buf, int32_t nbytes) {
    uint32_t buf_frequency =  buf;   //convert buffer value to integer
    //this is a little wrong, gotta fix it
    if (((buf_frequency % 2) % 2) == 0){
        //enable interrupts
        outb(0x8A,RTC_INDEX);		                    // set index to register A, disable NMI
        char prev=inb(RTC_DATA);	                    // get initial value of register A
        outb(0x8A,RTC_INDEX);
        outb((prev & 0xF0) | buf_frequency,RTC_DATA);   //write frequency rate to A
        //disable interrupts
        return 0;
    }
    return -1;
}


/* rtc_close(int32_t)
 * 
 * DESCRIPTION:   close RTC, disable future writes/reads from it
 *                note: this function pretty  much does nothing, the parent fnc that
 *                      interacts with the fd_arr will do most of the work (i think)
 * INPUTS:        fd - ignore(?)
 * OUTPUTS:       none
 * RETURNS:       0
 * SIDE EFFECTS:  none
 */
int32_t rtc_close(int32_t fd) {
    return 0;
}
