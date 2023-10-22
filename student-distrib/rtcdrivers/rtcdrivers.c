#include "rtcdrivers.h"
#include "../lib.h"
#include "../interrupts/idt_handlers.h"

int32_t rtc_open(const uint8_t* fname){
    uint8_t init_rate = 0x0F;                     //set frequency rate to 2

    //enable interrupts
    
    outb(0x8A,RTC_INDEX);		                    // set index to register A, disable NMI
    char prev=inb(RTC_DATA);	                    // get initial value of register A
    outb(0x8A,RTC_INDEX);
    outb((prev & 0xF0) | init_rate,RTC_DATA);   //write frequency rate to A
    //disable interrupts

    return 0;
}

int32_t rtc_read(int32_t fd, void* buf, int32_t nbytes){
    while (RTC_FLAG == 0);  //wait for rtc interrupt
    RTC_FLAG = 0;           //reset RTC flag to 0
    return 0;               //return 0 when rtc interrupt is recieved
}

int32_t rtc_write(int32_t fd, const void* buf, int32_t nbytes){
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


int32_t rtc_close(int32_t fd){
    return 0;
}