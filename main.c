#include "common.h"

#include "uart.h"
#include "clock.h"
#include "uart_process.h"

#include "io.h"

#include "mcp2515.h"

void init_uart(void)
{
    uart_init();
    uart_queue_init();
    
    uart_process_init_linebuf();
    LB_M.packet_status = OUT_PACKET;
    
    fdevopen(uart_sendc, NULL);
    // rtc_handler[UART_RTC_TASK_NO] = uart_process_tick_main;
}


int main(void)
{
    clock_pll_init();
    clock_rtc_init();

    io_init();
    init_uart();

    mcp2515_init();
    
    PMIC.CTRL |= PMIC_HILVLEX_bm | PMIC_LOLVLEX_bm | PMIC_RREN_bm;
    sei();

    for (;;)
    {
        if (rtc_flag)
        {
            rtc_flag = 0;
        }
        
        if (1)
        {
            uart_process_tick();
        }
        
        if (1)
        {
            // SLEEP.CTRL = SLEEP_SEN_bm | SLEEP_SMODE_PSAVE_gc;
            SLEEP.CTRL = SLEEP_SEN_bm | SLEEP_SMODE_IDLE_gc;
            __asm__ __volatile__ ("sleep");
        }
    }
}
