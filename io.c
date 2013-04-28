#include "io.h"

void io_init(void)
{
    PORTD.DIRSET = PIN3_bm;     /* serial tx pin */
    PORTD.DIRCLR = PIN2_bm;     /* serial rx pin */
    
    LED_PORT.DIRSET = 0xff;
    LED_PORT.OUT = LED_1 | LED_2;

    MODE_PORT.DIRCLR = MODE_PIN;
    MODE_PORT.MODE_PINCTRL = PORT_OPC_PULLUP_gc;
}
