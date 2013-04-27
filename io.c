#include "io.h"

void io_init(void)
{
    PORTD.DIRSET = PIN3_bm;     /* serial tx pin */
    PORTD.DIRCLR = PIN2_bm;     /* serial rx pin */
    
    LED_PORT.DIRSET = 0xff;
    LED_PORT.OUT = 0xff;
}
