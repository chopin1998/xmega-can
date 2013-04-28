#ifndef _IO_H
#define _IO_H

#include "common.h"

#define LED_PORT   PORTA
    #define LED_1  PIN6_bm
    #define LED_2  PIN7_bm

#define MODE_PORT  PORTD
    #define MODE_PIN PIN0_bm
    #define MODE_PINCTRL PIN0CTRL


void io_init(void);


#endif
