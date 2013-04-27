#include "uart.h"


signed char uart_dequeue(void)
{
    char rev;

    if (Q_RAW.rx_count == 0)
    {                           /* no data */
        rev = -1;
    }
    else
    {                           /* dequeue normally */
        Q_RAW.in_dequeue = 1;
        
        rev = Q_RAW.queue[Q_RAW.rx_out];
        Q_RAW.rx_out = (Q_RAW.rx_out + 1) % UART_RAW_RXBUF_MAX;
        Q_RAW.rx_count--;

        Q_RAW.in_dequeue = 0;
    }

    return rev;
}

inline void uart_join(unsigned char data)
{
    if (Q_RAW.rx_count >= UART_RAW_RXBUF_MAX)
    {                           /* buffer full, reset */
        Q_RAW.queue[0] = data;
        Q_RAW.rx_in = 1;
        Q_RAW.rx_out = 0;
        Q_RAW.rx_count = 1;
    }
    else
    {
        Q_RAW.queue[Q_RAW.rx_in] = data;
        Q_RAW.rx_in = (Q_RAW.rx_in + 1) % UART_RAW_RXBUF_MAX;
        Q_RAW.rx_count++;
    }
}
    

ISR (UART_M_RXC_vect)
{
    if (Q_RAW.in_dequeue)
    {
        printf("in dequeue!!");
        
        Q_RAW.buf2[Q_RAW.buf2_index] = UART_M.DATA;

        Q_RAW.buf2_index++;
        if (Q_RAW.buf2_index >= UART_RAW_RXBUF2_MAX)
        {
            Q_RAW.buf2_index = 0;
        }
    }
    else if (Q_RAW.buf2_index)
    {
        for (unsigned char i=0; i<Q_RAW.buf2_index; i++ )
        {
            uart_join(Q_RAW.buf2[i]);
        }
        uart_join(UART_M.DATA);

        Q_RAW.buf2_index = 0;
    }
    else
    {
        uart_join(UART_M.DATA);
    }
}

void uart_init(void)
{
    USART_t *dev = &UART_M;
        
    
    /* 115200bps @ 36Mhz */
    // int bsel = 1186;
    // unsigned char bscale = 10;
    /* 115200bps @ 36Mhz */

    /* 576000bps @ 36MHz */
    // int bsel = 186;
    // unsigned char bscale = 10;
    /* 576000bps @ 36MHz */

    /* 57600bps @ 36Mhz */
    int bsel = 2436;
    unsigned char bscale = 10;
    /* 57600 @ 36Mhz */
    
    dev->CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc;

    dev->BAUDCTRLA = (unsigned char)bsel;
    dev->BAUDCTRLB = (bscale << 4) | (bsel >> 8);

    dev->CTRLB |= USART_RXEN_bm | USART_TXEN_bm;

    // dev->CTRLA |= USART_RXCINTLVL_HI_gc;
    dev->CTRLA |= USART_RXCINTLVL_LO_gc; 
}

void uart_queue_init(void)
{
    // memset(Q_RAW.queue, 0x00, UART_RAW_RXBUF_MAX);
    Q_RAW.queue[0] = 0x00;
    Q_RAW.rx_in = 0;
    Q_RAW.rx_out = 0;
    Q_RAW.rx_count = 0;
}

inline void uart_sendc(unsigned char data)
{
    loop_until_bit_is_set(UART_M.STATUS, USART_DREIF_bp);
    UART_M.DATA = data;
}

void uart_sends(const char *data)
{
    unsigned int len = strlen(data);
    for (unsigned int i=0; i<len; i++)
    {
        uart_sendc(data[i]);
    }
}
