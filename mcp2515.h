#ifndef _MCP2515_H
#define _MCP2515_H 1

#include <avr/io.h>

#define MCP2515_PORT   PORTD
    #define MCP2515_SS_PIN PIN4_bm
    #define MCP2515_SI_PIN PIN5_bm
    #define MCP2515_SO_PIN PIN6_bm
    #define MCP2515_SCK_PIN PIN7_bm
#define MCP2515_SPI SPID


#define MCP2515_CS_LOW() do { MCP2515_PORT.OUTCLR = MCP2515_SS_PIN; } while (0)
#define MCP2515_CS_HI()  do { MCP2515_PORT.OUTSET = MCP2515_SS_PIN; } while (0)

#define MCP2515_INT_PORT PORTD
    #define MCP2515_INT_PIN PIN1_bm
    #define MCP2515_INT_PINCTRL PIN1CTRL
#define MCP2515_vect PORTD_INT0_vect


void mcp2515_init(void);

#define MCP2515_CANINT_MERR 0x80
#define MCP2515_CANINT_WAKI 0x40
#define MCP2515_CANINT_ERRI 0x20
#define MCP2515_CANINT_TX2I 0x10
#define MCP2515_CANINT_TX1I 0x08
#define MCP2515_CANINT_TX0I 0x04
#define MCP2515_CANINT_RX1I 0x02
#define MCP2515_CANINT_RX0I 0x01

typedef struct mcp2515_can_frame_s {
    unsigned long id;           /* standard or extented ID */
    unsigned char data[8];      /* data, up to 8bytes */
    unsigned char len;          /* len of data */
} mcp2515_can_frame_t;

typedef enum mcp2515_rx_e {
    MCP2515_RX_0,
    MCP2515_RX_1
} mcp2515_rx_t;

typedef enum mcp2515_tx_e {
    MCP2515_TX_0,
    MCP2515_TX_1,
    MCP2515_TX_2
} mcp2515_tx_t;

typedef enum mcp2515_op_mode_e {
    MCP2515_OP_MODE_NORMAL = 0,
    MCP2515_OP_MODE_SLEEP,
    MCP2515_OP_MODE_LOOPBACK,
    MCP2515_OP_MODE_LISTEN,
    MCP2515_OP_MODE_CONFIG
}  mcp2515_op_mode_t;

typedef enum mcp2515_rx_op_mode_e {
    MCP2515_RX_OP_MODE_FILTER_ANY = 0,
    MCP2515_RX_OP_MODE_FILTER_STANDARD,
    MCP2515_RX_OP_MODE_FILTER_EXTENDED,
    MCP2515_RX_OP_MODE_ANY
} mcp2515_rx_op_mode_t;

typedef enum mcp2515_rx_filter_mask_e {
    MCP2515_RX_FILTER_MASK_RXF0 = 0x00,
    MCP2515_RX_FILTER_MASK_RXF1 = 0x04,
    MCP2515_RX_FILTER_MASK_RXF2 = 0x08,
    MCP2515_RX_FILTER_MASK_RXF3 = 0x10,
    MCP2515_RX_FILTER_MASK_RXF4 = 0x14,
    MCP2515_RX_FILTER_MASK_RXF5 = 0x18,
    MCP2515_RX_FILTER_MASK_RXM0 = 0x20,
    MCP2515_RX_FILTER_MASK_RXM1 = 0x24
} mcp2515_rx_filter_mask_t;

void mcp2515_reset(void);

void mcp2515_read_rx_buf(mcp2515_rx_t channel, mcp2515_can_frame_t *frame);
void mcp2515_load_tx_buf(mcp2515_tx_t channel, mcp2515_can_frame_t *frame);

void mcp2515_rtx(mcp2515_tx_t channel);
void mcp2515_read_txrx_status(unsigned char *result);
void mcp2515_rx_status(unsigned char *result);

void mcp2515_set_rx_filter_mask(mcp2515_rx_filter_mask_t reg, long id);
void mcp2515_set_op_mode(mcp2515_op_mode_t mode);
void mcp2515_set_rx_op_mode(mcp2515_rx_t channel, mcp2515_rx_op_mode_t mode);
int mcp2515_set_baudrate(unsigned long ulBaudrate, unsigned long ulMCP2515Clk,
                         unsigned char ubSamplingTime, unsigned char ubTsjw);

int mcp2515_get_int_flag(void);
void mcp2515_clear_interrupt(void);
void mcp2515_enable_rx_int(mcp2515_rx_t channel);
void mcp2515_enable_tx_int(mcp2515_tx_t channel);





#endif
