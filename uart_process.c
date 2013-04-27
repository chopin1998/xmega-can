#include "common.h"
#include "uart.h"
#include "uart_process.h"
#include "util.h"

#include "cmd.h"
#include "clock.h"

void uart_process_init_linebuf(void)
{
    LB_M.buf[0] = 0x00;
    LB_M.index = 0;

}

signed char uart_process_tick(void)
{
    signed char recv;
    
    recv = uart_dequeue();

    if (recv == -1)
    {
        return -1;
    }

    if (LB_M.packet_status == OUT_PACKET)
    {
        if (recv == STX)
        {
            LB_M.packet_status = IN_PACKET;
            
            uart_process_init_linebuf();
        }
        else
        {
            /* ignor */
        }
    }
    else
    {                           /* packet_status == IN_PACK */
        if (recv == ETX)
        {                       /* end of a packet */
            LB_M.packet_status = OUT_PACKET;
            LB_M.buf[LB_M.index] = 0x00; /* padding a terminal char */

            uart_process_lb_m();
        }
        else
        {                       /* normally */
            LB_M.buf[LB_M.index] = recv;            
            LB_M.index++;

            if (LB_M.index >= LINE_BUF_MAX)
            {                   /* a huge packet ? */
                LB_M.packet_status = OUT_PACKET;

                uart_process_init_linebuf();
            }
        }
    }

    return 0;
}

void uart_process_lb_m(void)
{
    cmd_process(&LB_M.buf);    
}

