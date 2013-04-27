#ifndef _UART_H
#define _UART_H 1

#include "common.h"


#define UART_M_RXC_vect    USARTD0_RXC_vect
#define UART_M             USARTD0


#define UART_RAW_RXBUF_MAX 256
#define UART_RAW_RXBUF2_MAX 16
typedef struct
{
    unsigned char queue[UART_RAW_RXBUF_MAX];
    unsigned int rx_in, rx_out;
    unsigned int rx_count;

    unsigned char buf2[UART_RAW_RXBUF2_MAX];
    unsigned char buf2_index;
    unsigned char in_dequeue;
    
} RAW_QUEUE_t;
volatile RAW_QUEUE_t Q_RAW;


void uart_init(void);
void uart_queue_init(void);

void uart_sendc(unsigned char data);
void uart_sends(const char *data);
signed char uart_dequeue(void);
inline void uart_join(unsigned char data);


#endif
