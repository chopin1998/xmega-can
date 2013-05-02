#include "common.h"
#include "clock.h"
#include "io.h"


volatile unsigned char rtc_flag = 0;

ISR (RTC_OVF_vect)
{    
    rtc_flag++;

    for (unsigned char i=0; i<RTC_HANDLER_NUMBER; i++)
    {
        if (rtc_handler[i])
        {
            rtc_handler[i]();
        }
    }

    LED_PORT.OUTTGL = LED_1;
}

void clock_pll_init(void)
{
    OSC.CTRL |= OSC_RC2MEN_bm;
    loop_until_bit_is_set(OSC.STATUS, OSC_RC2MRDY_bp);
    
    OSC.PLLCTRL = OSC_PLLSRC_RC2M_gc | 18; /* setup pll source and fac */
    OSC.CTRL |= OSC_PLLEN_bm;             /* enable PLL */

    CCP = CCP_IOREG_gc;                                /* ccp write */
    CLK.PSCTRL = CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc; /* peri no preClock, also cpu */

    loop_until_bit_is_set(OSC.STATUS, OSC_PLLRDY_bp); /* wating for PLL */

    CCP = CCP_IOREG_gc;
    CLK.CTRL = CLK_SCLKSEL_PLL_gc;
}

void clock_rtc_init(void)
{
    OSC.CTRL |= OSC_RC32KEN_bm;
    loop_until_bit_is_set(OSC.STATUS, OSC_RC32KRDY_bp);
    
    // CLK.RTCCTRL = CLK_RTCEN_bm | CLK_RTCSRC_RCOSC_gc;
    CLK.RTCCTRL = CLK_RTCEN_bm | CLK_RTCSRC_TOSC_gc;
    loop_until_bit_is_clear(RTC.STATUS, WDT_SYNCBUSY_bp);
    
    RTC.PER = (128 - 1);         /* 16 */
    RTC.CNT = 0;
    RTC.CTRL = RTC_PRESCALER_DIV1_gc;

    RTC.INTCTRL = RTC_OVFINTLVL_LO_gc;
}

