#ifndef _UART_PROCESS_H
#define _UART_PROCESS_H 1


#define STX     '['
#define ETX     ']'

#define ACK     0x06
#define NAK     0x15
#define HANDSHAKE  'H'
#define DAT        'D'

#define SEQ_MIN (0x80 | 0x00)
#define SEQ_MAX (0x80 | 0x0f)


enum {IN_PACKET, OUT_PACKET};

#define LINE_BUF_MAX 96
typedef struct
{
    unsigned char packet_status;
    
    unsigned char buf[LINE_BUF_MAX];
    unsigned char index;

} LINE_BUF_t;
volatile LINE_BUF_t LB_M;


#define UART_RTC_TASK_NO 2

void uart_process_init_linebuf(void);

signed char uart_process_tick(void);

void uart_process_lb_m(void);

#endif
