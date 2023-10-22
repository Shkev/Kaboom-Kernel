#include "rtcdrivers.h"
#include "../lib.h"

/* write new rate to RTC */
static int32_t write_rtc_rate(uint32_t rate);

/* check if input is power of 2 */
static uint8_t is_power_of_2(uint32_t);

/* compute RTC rate corresponding to given frequency */
static uint32_t compute_rtc_rate_from_freq(uint32_t freq);

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
    write_rtc_rate(init_rate);
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
    uint32_t write_freq =  (uint32_t)buf;     /* convert write value to integer */
    if (write_freq > 1024 || !is_power_of_2(write_freq)) {
	return -1
    }
    uint32_t rate = compute_rtc_rate_from_freq(write_freq);
    if (rate == 0 || rate == 1 || rate == 2) {  /* rate faster than 3 causes issues */
	return -1;
    }
    write_rtc_rate(rate);
    return 0;
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


/////////////////// HELPER FUNCTIONS ////////////////////

/* write_rtc_rate(uint32_t)
 *
 * DESCRIPTION:  write new rate to RTC
 * INPUTS:       rate   - the rate to write
 * OUTPUTS:      none
 * RETURNS:      0
 * SIDE EFFECTS: changes RTC rate (value in register A)
 */
int32_t write_rtc_rate(uint32_t rate) {
    // disable interrupts
    cli();

    /* note : RTC_INDEX and RTC_DATA defined in init_devices.h */
    outb(0x8A, RTC_INDEX);	              /* set index to register A, disable NMI */
    char prev = inb(RTC_DATA);	              /* get initial value of register A */
    outb(0x8A, RTC_INDEX);
    outb((prev & 0xF0) | rate, RTC_DATA);     /* write frequency rate to A; bottom 4 bits are the rate */

    // enable interrupts
    sti();
}


/* is_power_of_2(uint32_t)
 * DESCRIPTION:     check if input is power of 2
 * INPUTS:          n - number to check
 * OUTPUTS:         none
 * RETURNS;         0 if n not a power of 2, nonzero value otherwise
 * SIDE EFFECTS:    none
 */
uint8_t is_power_of_2(uint32_t n) {
    return (n & (x - n)) == 0;
}


/* compute_rtc_rate_from_freq(uint32_t)
 * DESCRIPTION:     compute the corresponding rtc rate from given frequency
 * INPUTS:          freq - frequency to convert to rate. Assumes it's a power of 2
 * OUTPUTS:         none
 * RETURNS;         rate for RTC converted from given frequency
 * SIDE EFFECTS:    none
 */
uint32_t compute_rtc_rate_from_freq(uint32_t freq) {
    /* freq = 2^n = 2^(15 - (rate-1))    =>    rate = 16 - n
     * where n = where first 1 occurs in binary repr of freq */
    uint32_t n = 0;
    while ((freq >> n) != 1) ++n;
    return 16 - n;
}
