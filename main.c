#include "common.h"

#include "uart.h"
#include "clock.h"
#include "uart_process.h"

#include "io.h"

#include "mcp2515.h"
#include "mcp2515reg.h"

void init_uart(void)
{
    uart_init();
    uart_queue_init();
    
    uart_process_init_linebuf();
    LB_M.packet_status = OUT_PACKET;
    
    fdevopen(uart_sendc, NULL);
    // rtc_handler[UART_RTC_TASK_NO] = uart_process_tick_main;
}

void test_send_can_frame(void)
{
    static unsigned char count = 0;    
    mcp2515_can_frame_t frame;

    // mcp2515_clear_interrupt();
    frame.id = 0x04500000UL;
    snprintf(frame.data, 8, "c: %d", count++);
    frame.len = strlen(frame.data);

    bit_modify(MCP2515_TXB0CTRL, 0x80, 0x00);
    mcp2515_load_tx_buf(MCP2515_TX_0, &frame);

    mcp2515_rts(MCP2515_TX_0);
}

void test_recv_can_frame(void)
{
    int flag;
    mcp2515_can_frame_t frame;

    flag = mcp2515_get_int_flag();
    if (flag & MCP2515_CANINTF_RX0IF)
    {
        printf("got a frame\n");
        mcp2515_read_rx_buf(MCP2515_RX_0, &frame);
        mcp2515_clear_interrupt();

        printf("    id: 0x%011x -->", frame.id);
        for(unsigned char i=0; i<frame.len; i++)
        {
            printf("%c", frame.data[i]);
        }
        printf("<--\n\n");
        LED_PORT.OUTTGL = LED_2;
    }
    else if (flag)
    {
        printf("int flag: 0x%02x\n", flag);
    }
}

int main(void)
{
    unsigned char mode;
    
    clock_pll_init();
    clock_rtc_init();

    io_init();
    init_uart();

    mcp2515_init();
    
    PMIC.CTRL |= PMIC_HILVLEX_bm | PMIC_LOLVLEX_bm | PMIC_RREN_bm;
    sei();

    if (MODE_PORT.IN & MODE_PIN)
    {
        mode = 1;
        printf("tx mode\n");

        bit_modify(MCP2515_CANCTRL, 0x08, 0x08);
    }
    else
    {
        mode = 0;
        printf("rx mode\n");
    }
    
    for (;;)
    {
        if (1)
        {
            if (mode == 1)
            {
                if (rtc_flag == 11)
                {
                    rtc_flag = 0;

                    test_send_can_frame();
                }

                test_recv_can_frame();
            }
            else
            {
                test_recv_can_frame();
            }

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
