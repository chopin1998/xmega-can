/*
 * based on https://code.google.com/p/avr-drv/
 *                     thank you guys
 */

#include "common.h"
#include "mcp2515.h"
#include "mcp2515reg.h"

static void mcp2515_io_init(void);
static void mcp2515_spi_init(void);
void bit_modify(unsigned char reg, unsigned char mask, unsigned char val);


ISR (MCP2515_vect)
{
}


void spi_writeread(unsigned char in, unsigned char *out)
{
    MCP2515_SPI.DATA = in;
    loop_until_bit_is_set(MCP2515_SPI.STATUS, SPI_IF_bp);
    
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
    
    MCP2515_CS_HI();
}

void mcp2515_spi_init(void)
{
    MCP2515_SPI.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm |
        SPI_MODE_0_gc | SPI_PRESCALER_DIV16_gc /*| SPI_CLK2X_bm */;
}

void mcp2515_init(void)
{
    int rev;
    
    printf("mcp2515 init..\n");
    
    mcp2515_io_init();
    printf("    io ok\n");
    
    mcp2515_spi_init();
    printf("    spi ok\n");

    mcp2515_reset();
    printf("    software reset\n");

    _delay_ms(10);
    
    mcp2515_set_baudrate(500000, 8000000, 75, 4);
    printf("    baudrate: %d\n", rev);

    mcp2515_set_rx_op_mode(MCP2515_RX_0, MCP2515_RX_OP_MODE_ANY);
    printf("    recv all packet on rx0\n");

    mcp2515_set_op_mode(MCP2515_OP_MODE_NORMAL);
    // mcp2515_set_op_mode(MCP2515_OP_MODE_LOOPBACK);
    printf("    set op mode\n");

    printf("\n\n");
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

    spi_writeread(0, &data); /* read XXXnSIDH */
    id = (((unsigned long)data) << 21);

    spi_writeread(0, &data); /* read XXXnSIDL */
    id |= ( ((unsigned long)(data & 0xe0)) << 13);
    id |= ( ((unsigned long)(data & 0x03)) << 16);

    if (data & 0x08)            /* ext id ? */
    {
        id |= 0x20000000;
    }

    spi_writeread(0, &data); /* read XXXnEID8 */
    id |= (((unsigned long)data) << 8);
    spi_writeread(0, &data); /* read XXXnEID0 */
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

    spi_writeread((unsigned char)(id>>21), NULL); /* send XXXnSIDH */
    tmp = ( (unsigned char)(id >> 13) ) & 0xe0;
    tmp |= ( (unsigned char)(id) >> 16 ) & 0x03;

    if (id & 0x20000000)        /* ext id ? */
    {
        tmp |= 0x08;
    }

    spi_writeread(tmp, NULL); /* send XXXnSIDL */

    spi_writeread((unsigned char)(id >> 8), NULL); /* send XXXnEID8 */
    spi_writeread((unsigned char)(id), NULL);      /* send XXXnEID0 */
}

/*
 * mcp2515 register read function
 */
void mcp2515_read(unsigned char reg, unsigned char *data)
{
    MCP2515_CS_LOW();

    spi_writeread(MCP2515_READ, NULL);
    spi_writeread(reg, NULL);
    spi_writeread(0x00, data);

    MCP2515_CS_HI();
}

void mcp2515_read_burst(unsigned char reg, unsigned char *buf, unsigned char size)
{
    MCP2515_CS_LOW();
    
    spi_writeread(MCP2515_READ, NULL);
    spi_writeread(reg, NULL);
    for (unsigned char i=0; i<size; i++,buf++)
    {
        spi_writeread(0x00, buf);
    }

    MCP2515_CS_HI();
}

/*
 * mcp2515 register write function
 */
void mcp2515_write(unsigned char reg, unsigned char data)
{
    MCP2515_CS_LOW();

    spi_writeread(MCP2515_WRITE, NULL);
    spi_writeread(reg, NULL);
    spi_writeread(data, NULL);

    MCP2515_CS_HI();
}

void mcp2515_write_burst(unsigned char reg, unsigned char *buf, unsigned char size)
{
    MCP2515_CS_LOW();

    spi_writeread(MCP2515_WRITE, NULL);
    spi_writeread(reg, NULL);
    for (unsigned char i=0; i<size; i++,buf++)
    {
        spi_writeread(*buf, NULL);
    }

    MCP2515_CS_HI();
}

/*
 * mcp2515 bit modify function
 */
void bit_modify(unsigned char reg, unsigned char mask, unsigned char val)
{
    MCP2515_CS_LOW();

    spi_writeread(MCP2515_BIT_MODIFY, NULL);
    spi_writeread(reg, NULL);
    spi_writeread(mask, NULL);
    spi_writeread(val, NULL);

    MCP2515_CS_HI();
}

////////////////////////////////////////////////////////////////

void mcp2515_reset(void)
{
    MCP2515_CS_LOW();

    spi_writeread(MCP2515_RESET, NULL);

    MCP2515_CS_HI();
}

void mcp2515_read_rx_buf(mcp2515_rx_t channel, mcp2515_can_frame_t *frame)
{
    MCP2515_CS_LOW();

    switch (channel)
    {
    case MCP2515_RX_0:
        spi_writeread(MCP2515_READ_BUF_RXB0SIDH, NULL);
        
        break;
    case MCP2515_RX_1:
        spi_writeread(MCP2515_READ_BUF_RXB1SIDH, NULL);
        
        break;
    default:
        return;
    }
    id_read(&frame->id);

    spi_writeread(0, &frame->len); /* read length of the frame */
    frame->len &= 0x0f;

    for (unsigned char i=0; i<frame->len; i++)
    {
        spi_writeread(0x00, &frame->data[i]);
    }

    MCP2515_CS_HI();
}

void mcp2515_load_tx_buf(mcp2515_tx_t channel, mcp2515_can_frame_t *frame)
{
    MCP2515_CS_LOW();

    switch (channel)
    {
    case MCP2515_TX_0:
        spi_writeread(MCP2515_LOAD_BUF_TXB0SIDH, NULL);

        break;
    case MCP2515_TX_1:
        spi_writeread(MCP2515_LOAD_BUF_TXB1SIDH, NULL);

        break;
    case MCP2515_TX_2:
        spi_writeread(MCP2515_LOAD_BUF_TXB2SIDH, NULL);

        break;
    default:
        return;
    }

    id_write(frame->id);
    spi_writeread(frame->len & 0x0f, NULL);

    for(unsigned char i=0; i<frame->len; i++)
    {
        spi_writeread(frame->data[i], NULL);
    }
    
    MCP2515_CS_HI();
}

void mcp2515_rts(mcp2515_tx_t channel)
{
    MCP2515_CS_LOW();

    switch (channel)
    {
    case MCP2515_TX_0:
        spi_writeread(MCP2515_RTS_TXB0, NULL);

        break;
    case MCP2515_TX_1:
        spi_writeread(MCP2515_RTS_TXB1, NULL);

        break;
    case MCP2515_TX_2:
        spi_writeread(MCP2515_RTS_TXB2, NULL);
        
        break;
    default:
        return;
    }
    
    MCP2515_CS_HI();
}

void mcp2515_read_rxtx_status(unsigned char *result)
{
    mcp2515_read(MCP2515_READ_RXTX_STATUS, result);
}

void mcp2515_rx_status(unsigned char *result)
{
    mcp2515_read(MCP2515_READ_RXTX_STATUS, result);
}

void mcp2515_set_rx_filter_mask(mcp2515_rx_filter_mask_t reg, unsigned long id)
{
    MCP2515_CS_LOW();

    spi_writeread(MCP2515_WRITE, NULL);
    spi_writeread(reg, NULL);
    id_write(id);
    
    MCP2515_CS_HI();
}

void mcp2515_set_op_mode(mcp2515_op_mode_t mode)
{
    bit_modify(MCP2515_CANCTRL, 0xe0, mode<<5);
}

void mcp2515_set_rx_op_mode(mcp2515_rx_t channel, mcp2515_rx_op_mode_t mode)
{
    switch (channel)
    {
    case MCP2515_RX_0:
        bit_modify(MCP2515_RXB0CTRL, 0x60, mode<<5);

        break;
    case MCP2515_RX_1:
        bit_modify(MCP2515_RXB1CTRL, 0x60, mode<<5);

        break;
    default:
        return;
    }
}

int mcp2515_set_baudrate(unsigned long ulBaudrate, unsigned long ulMCP2515Clk,
                         unsigned char ubSamplingTime, unsigned char ubTsjw)
{
    static unsigned char ubDivider;
    static unsigned char ubTbit;
    static unsigned char ubTprs;
    static unsigned char ubTphs1;
    static unsigned char ubTphs2;
    static unsigned char ubBRP = 1;

    ubDivider = ulMCP2515Clk / ulBaudrate;

    ubTbit = ubDivider/2;
    while ( (ubTbit >= MCP2515_MAX_TQ) | (ubTbit <= MCP2515_MIN_TQ))
    {
        ubTbit = (ubTbit >> 1);
        ubBRP*=2;
    }

    ubTphs2 = (ubTbit * (100 - ubSamplingTime) / 100);
    ubTphs1 = 0;

    for(ubTprs = 8; ubTprs > 0; ubTprs--)
    {
        if((1 + ubTprs + ubTphs2 + ubTphs2) <= (ubTbit + 8 - ubTphs2)
           && ((ubTbit - 1 - ubTprs - ubTphs2) >= ubTphs2))
        {
            ubTphs1 = ubTbit - 1 - ubTprs - ubTphs2;
            break;
        }
    }

    /*
    MCP2515_CS_LOW();
    
    spi_writeread(MCP2515_WRITE, NULL);
    spi_writeread(MCP2515_CNF3, NULL);
    spi_writeread(0x07 & (ubTphs2-1), NULL); // CF3
    spi_writeread((0x07 & (ubTprs-1))|(0x38 & ((ubTphs1-1)<<3))|(0x80), NULL); // CF2
    spi_writeread((0x03 & ((ubTsjw-1)<<6))|(0x20 & (ubBRP-1)), NULL); // CF1 : 1TQ for SJW and BRP = 5 for 1TQ = 12/F_CPU

    MCP2515_CS_HI();
    */

    mcp2515_write(MCP2515_CNF3, 0x01);
    mcp2515_write(MCP2515_CNF2, 0xac);
    mcp2515_write(MCP2515_CNF1, 0x03);

    if (ubDivider == (ubBRP) * (ubTprs + ubTphs1 + ubTphs2 + 1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int mcp2515_get_int_flag(void)
{
    unsigned char rev;

    mcp2515_read(MCP2515_CANINTF, &rev);    

    return (int)rev;
}

void mcp2515_clear_interrupt(void)
{
    mcp2515_write(MCP2515_CANINTF, 0x00);
}

void mcp2515_enable_rx_int(mcp2515_rx_t channel)
{
    switch(channel)
    {
    case MCP2515_RX_0:
        bit_modify(MCP2515_CANINTE, 0x01, 0x01);
        
        break;
    case MCP2515_RX_1:
        bit_modify(MCP2515_CANINTE, 0x02, 0x02);
        
        break;
    default:
        return;
    }
}

void mcp2515_enable_tx_int(mcp2515_tx_t channel)
{
    switch(channel)
    {
    case MCP2515_TX_0:
        bit_modify(MCP2515_CANINTE, 0x04, 0x04);

        break;
    case MCP2515_TX_1:
        bit_modify(MCP2515_CANINTE, 0x08, 0x08);

        break;
    case MCP2515_TX_2:
        bit_modify(MCP2515_CANINTE, 0x10, 0x10);

        break;
    default:
        return;
    }
}

