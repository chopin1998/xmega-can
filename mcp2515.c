#include "common.h"
#include "mcp2515.h"
#include "mcp2515reg.h"

static void mcp2515_io_init(void);
static void mcp2515_spi_init(void);


ISR (MCP2515_vect)
{
}


void mcp2515_writeread(unsigned char in, unsigned char *out)
{
    MCP2515_SPI.DATA = in;
    loop_until_bit_is_set(MCP2515_SPI.STATUS, SPI_IF_bm);
    
    *out = MCP2515_SPI.DATA;
}

void mcp2515_io_init(void)
{
    MCP2515_PORT.DIRSET = MCP2515_SS_PIN | MCP2515_SI_PIN | MCP2515_SCK_PIN;
    MCP2515_PORT.DIRCLR = MCP2515_SO_PIN;
    
    MCP2515_INT_PORT.DIRCLR = MCP2515_INT_PIN;
    MCP2515_INT_PORT.MCP2515_INT_PINCTRL = PORT_ISC_FALLING_gc | PORT_OPC_PULLUP_gc;
    MCP2515_PORT.INT0MASK = MCP2515_INT_PIN;
    MCP2515_PORT.INTCTRL = PORT_INT0LVL_HI_gc;
    MCP2515_PORT.INTFLAGS = 0x00;

    MCP2515_DISABLE();
}

void mcp2515_spi_init(void)
{
    MCP2515_SPI.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm |
        SPI_MODE_0_gc | SPI_PRESCALER_DIV4_gc;
}

void mcp2515_init(void)
{
    mcp2515_io_init();
    mcp2515_spi_init();
}

////////////////////////////////////////////////////////////////

/*
 * be use alone under the bust mode(CS low), and the next address mush XXXnSIDH
 *
 * result *ID means std or ext id with 29th bit = 0 for std or bit = 1 for ext id
 */
static void id_read(unsigned long *result)
{
    unsigned char data;
    unsigned long id = 0;

    mcp2515_writeread(0, &data); /* read XXXnSIDH */
    id = (((unsigned long)data) << 21);

    mcp2515_writeread(0, &data); /* read XXXnSIDL */
    id |= ( ((unsigned long)(data & 0xe0)) << 13);
    id |= ( ((unsigned long)(data & 0x03)) << 16);

    if (data & 0x08)            /* ext id ? */
    {
        id |= 0x20000000;
    }

    mcp2515_writeread(0, *data); /* read XXXnEID8 */
    id |= (((unsigned long)data) << 8);
    mcp2515_writeread(0, &data); /* read XXXnEID0 */
    id |= (unsigned long)data;
    *result = id;
}

/*
 * be use alone under the bust mode(CS low), and the next address mush XXXnSIDH
 *
 * id is the std or ext ID with 29th bit = 0 for std ID or 29th bit = 1 for ext ID
 */
static void id_write(unsigned long id)
{
    unsigned char tmp = 0;

    mcp2515_writeread((unsigned char)(id>>21), NULL); /* send XXXnSIDH */
    tmp = ( (unsigned char)(id >> 13) ) & 0xe0;
    tmp |= ( (unsigned char)(id) >> 16 ) & 0x03;

    if (id & 0x20000000)        /* ext id ? */
    {
        tmp |= 0x08;
    }

    mcp2515_writeread(tmp, NULL); /* send XXXnSIDL */

    mcp2515_writeread((unsigned char)(id >> 8), NULL); /* send XXXnEID8 */
    mcp2515_writeread((unsigned char)(id), NULL);      /* send XXXnEID0 */
}

/*
 * mcp2515 register read function
 */
static void read(unsigned char reg, unsigned char *data)
{
    MCP2515_CS_LOW();

    mcp2515_writeread(MCP25)
}
