#ifndef _CLOCK_H
#define _CLOCK_H 1

extern volatile unsigned char rtc_flag;


#define RTC_HANDLER_NUMBER 10
void (*rtc_handler[RTC_HANDLER_NUMBER])(void);

void clock_pll_init(void);
void clock_rtc_init(void);

#endif
