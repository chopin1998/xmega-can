#ifndef _MCP2515REG_H_
#define _MCP2515REG_H_


//MCP2515 RX/TX buffers selection
#define MCP2515_RX_BUF_0	0
#define MCP2515_RX_BUF_1	1

#define MCP2515_TX_BUF_0	0
#define MCP2515_TX_BUF_1	1
#define MCP2515_TX_BUF_2	2


//MCP2515 SPI instructions
#define MCP2515_RESET				0xC0
#define MCP2515_READ				0x03
#define MCP2515_READ_BUF_RXB0SIDH	0x90	//read data from begin address of Standard ID (MSB) of RX buffer 0
#define MCP2515_READ_BUF_RXB0D0		0x92	//read data from begin address of data byte 0 of RX buffer 0
#define MCP2515_READ_BUF_RXB1SIDH	0x94	//...RX buffer 1
#define MCP2515_READ_BUF_RXB1D0		0x96	//...RX buffer 1
#define MCP2515_WRITE				0x02
#define MCP2515_LOAD_BUF_TXB0SIDH	0x40	//load data from begin address of Standard ID (MSB) of TX buffer 0
#define MCP2515_LOAD_BUF_TXB0D0		0X41	//load data from begin address of data byte 0 of TX buffer 0
#define MCP2515_LOAD_BUF_TXB1SIDH	0x42	//...TX buffer 1
#define MCP2515_LOAD_BUF_TXB1D0		0X43	//...TX buffer 1
#define MCP2515_LOAD_BUF_TXB2SIDH	0x44	//...TX buffer 2
#define MCP2515_LOAD_BUF_TXB2D0		0X45	//...TX buffer 2
#define MCP2515_RTS_TXB0			0x81	//activate the RTS of TX buffer 0.
#define MCP2515_RTS_TXB1			0x82	//...TX buffer 1.
#define MCP2515_RTS_TXB2			0x84	//...TX buffer 2.
#define MCP2515_RTS_ALL				0x87	//...TX buffer 0, 1 and 2.
#define MCP2515_READ_RXTX_STATUS	0xA0
#define MCP2515_RX_STATUS			0xB0
#define MCP2515_BIT_MODIFY			0x05


//MCP2515 control settings register address.
//All can be used with the Bit Modify command, except the CANSTAT register.
#define MCP2515_BFPCTRL		0x0C	//RXnBF pin control/status
#define MCP2515_TXRTSCTRL	0x0D	//TXnRTS pin control/status
#define MCP2515_CANSTAT		0x0E	//CAN status. any addr of MSB will give the same info???
#define MCP2515_CANCTRL		0x0F	//CAN control status. any addr of MSB will give the same info???
#define MCP2515_TEC			0x1C	//Transmit Error Counter
#define MCP2515_REC			0x1D	//Receive Error Counter
#define MCP2515_CNF3		0x28	//Phase segment 2
#define MCP2515_CNF2		0x29	//Propagation segment & Phase segment 1 & n sample setting
#define MCP2515_CNF1		0x2A	//Baud rate prescaler & Sync Jump Width
#define MCP2515_CANINTE		0x2B	//CAN interrupt enable
#define MCP2515_CANINTF		0x2C	//Interrupt flag
#define MCP2515_EFLG		0x2D	//Error flag
#define MCP2515_TXB0CTRL	0x30	//TX buffer 0 control
#define MCP2515_TXB1CTRL	0x40	//TX buffer 1 control
#define MCP2515_TXB2CTRL	0x50	//TX buffer 2 control
#define MCP2515_RXB0CTRL	0x60	//RX buffer 0 control
#define MCP2515_RXB1CTRL	0x70	//RX buffer 1 control


//MCP2515 relate to CAN settings/status register address.
//Only the most used are listed below. please see the datasheet MCP2515.pdf p61 for complete info.
#define MCP2515_RXF0SIDH	0x00	//RX standard ID (High bits) filter 0
#define MCP2515_RXF0SIDL	0x01	//RX standard ID (Low bits) filter 0
#define MCP2515_RXF0EID8	0x02	//RX Extended ID (High bits) filter 0 ->can be reached by bust read/write Standard ID then Ext. ID
#define MCP2515_RXF0EID0	0x03	//RX Extended ID (Low bits) filter 0
#define MCP2515_RXF1SIDH	0x04	//RX standard ID (High bits) filter 1
#define MCP2515_RXF1SIDL	0x05	//RX standard ID (Low bits) filter 1
#define MCP2515_RXF1EID8	0x06	//RX Extended ID (High bits) filter 1
#define MCP2515_RXF1EID0	0x07	//RX Extended ID (Low bits) filter 1
#define MCP2515_RXF2SIDH	0x08	//RX standard ID (High bits) filter 2
#define MCP2515_RXF2SIDL	0x09	//RX standard ID (Low bits) filter 2
#define MCP2515_RXF2EID8	0x0A	//RX Extended ID (High bits) filter 2
#define MCP2515_RXF2EID0	0x0B	//RX Extended ID (Low bits) filter 2
#define MCP2515_RXF3SIDH	0x10	//RX standard ID (High bits) filter 3
#define MCP2515_RXF3SIDL	0x11	//RX standard ID (Low bits) filter 3
#define MCP2515_RXF3EID8	0x12	//RX Extended ID (High bits) filter 3
#define MCP2515_RXF3EID0	0x13	//RX Extended ID (Low bits) filter 3
#define MCP2515_RXF4SIDH	0x14	//RX standard ID (High bits) filter 4
#define MCP2515_RXF4SIDL	0x15	//RX standard ID (Low bits) filter 4
#define MCP2515_RXF4EID8	0x16	//RX Extended ID (High bits) filter 4
#define MCP2515_RXF4EID0	0x17	//RX Extended ID (Low bits) filter 4
#define MCP2515_RXF5SIDH	0x18	//RX standard ID (High bits) filter 5
#define MCP2515_RXF5SIDL	0x19	//RX standard ID (Low bits) filter 5
#define MCP2515_RXF5EID8	0x1A	//RX Extended ID (High bits) filter 5
#define MCP2515_RXF5EID0	0x1B	//RX Extended ID (Low bits) filter 5
#define MCP2515_RXM0SIDH	0x20	//RX standard ID (High bits) mask filter 0
#define MCP2515_RXM0SIDL	0x21	//RX standard ID (Low bits) mask filter 0
#define MCP2515_RXM0EID8	0x22	//RX Extended ID (High bits) mask filter 0
#define MCP2515_RXM0EID0	0x23	//RX Extended ID (Low bits) mask filter 0
#define MCP2515_RXM1SIDH	0x24	//RX standard ID (High bits) mask filter 1
#define MCP2515_RXM1SIDL	0x25	//RX standard ID (Low bits) mask filter 1
#define MCP2515_RXM1EID8	0x26	//RX Extended ID (High bits) mask filter 1
#define MCP2515_RXM1EID0	0x27	//RX Extended ID (Low bits) mask filter 1
#define MCP2515_RXB0SIDH	0x61	//RX buffer 0 standard ID (High bits)
#define MCP2515_RXB0SIDL	0x62	//RX buffer 0 standard ID (Low bits)
#define MCP2515_RXB0EID8	0x63	//RX buffer 0 Extended ID (High bits) ->can be reached by bust read/write Standard ID then Ext. ID
#define MCP2515_RXB0EID0	0x64	//RX buffer 0 Extended ID (Low bits)
#define MCP2515_RXB0DLC		0x65	//RX buffer 0 DLC  ->can be reached by bust read/write Standard ID, Ext. ID then DLC
#define MCP2515_RXB0D0		0x66	//RX buffer 0 data byte0
#define MCP2515_RXB1SIDH	0x71	//RX buffer 1 standard ID (High bits)
#define MCP2515_RXB1SIDL	0x72	//RX buffer 1 standard ID (Low bits)
#define MCP2515_RXB1EID8	0x73	//RX buffer 1 Extended ID (High bits)
#define MCP2515_RXB1EID0	0x74	//RX buffer 1 Extended ID (Low bits)
#define MCP2515_RXB1DLC		0x75	//RX buffer 1 DLC
#define MCP2515_RXB1D0		0x76	//RX buffer 1 data byte0

#define MCP2515_TXB0SIDH	0x31	//TX buffer 0 standard ID (High bits)
#define MCP2515_TXB0SIDL	0x32	//TX buffer 0 standard ID (Low bits)
#define MCP2515_TXB0EID8	0x33	//TX buffer 0 Extended ID (High bits) ->can be reached by bust read/write Standard ID then Ext. ID
#define MCP2515_TXB0EID0	0x34	//TX buffer 0 Extended ID (Low bits)
#define MCP2515_TXB0DLC		0x35	//TX buffer 0 DLC  ->can be reached by bust read/write Standard ID, Ext. ID then DLC
#define MCP2515_TXB0D0		0x36	//TX buffer 0 data byte0
#define MCP2515_TXB1SIDH	0x41	//TX buffer 1 standard ID (High bits)
#define MCP2515_TXB1SIDL	0x42	//TX buffer 1 standard ID (Low bits)
#define MCP2515_TXB1EID8	0x43	//TX buffer 1 Extended ID (High bits)
#define MCP2515_TXB1EID0	0x44	//TX buffer 1 Extended ID (Low bits)
#define MCP2515_TXB1DLC		0x45	//TX buffer 1 DLC
#define MCP2515_TXB1D0		0x46	//TX buffer 1 data byte0
#define MCP2515_TXB2SIDH	0x51	//TX buffer 2 standard ID (High bits)
#define MCP2515_TXB2SIDL	0x52	//TX buffer 2 standard ID (Low bits)
#define MCP2515_TXB2EID8	0x53	//TX buffer 2 Extended ID (High bits)
#define MCP2515_TXB2EID0	0x54	//TX buffer 2 Extended ID (Low bits)
#define MCP2515_TXB2DLC		0x55	//TX buffer 2 DLC
#define MCP2515_TXB2D0		0x56	//TX buffer 2 data byte0


//MCP2515 limit values
#define MCP2515_MIN_TQ		0x07	//7 = Minimum TQ in 1 bit of CAN bus time
#define MCP2515_MAX_TQ		0x19	//25 = Maximum TQ in 1 bit of CAN bus time
#define MCP2515_MIN_BRP		0x00	//0 = Minimum baud rate prescaler clock
#define MCP2515_MAX_BRP		0x3F	//63 = Maximum baud rate prescaler clock
#define MCP2515_MAX_SJW		0x03	//4 = Maximum Synchronization Jump Width. 4-1 = 3 actually
#define MCP2515_MAX_BYTE_CANFRM	0x08//8 = Maximun bytes in a CAN frame


//MCP2515 register values: CANCTRL register
#define MCP2515_MODE_NORMAL		0x00
#define MCP2515_MODE_SLEEP		0x20
#define MCP2515_MODE_LOOPBACK	0x40
#define MCP2515_MODE_LISTENONLY	0x60
#define MCP2515_MODE_CONFIG		0x80
#define MCP2515_ABORT_TX		0x10
#define MCP2515_MODE_MASK		0xE0
#define MCP2515_MODE_ONESHOT	0x08
#define MCP2515_CLKOUT_ENABLE	0x04
#define MCP2515_CLKOUT_PS1		0x00	//Set CLK out prescaler to 1. Note: not the same as the CAN CLK prescaler.
#define MCP2515_CLKOUT_PS2		0x01	//... to 2
#define MCP2515_CLKOUT_PS4		0x02	//... to 4
#define MCP2515_CLKOUT_PS8		0x03	//... to 8


//MCP2515 CAN Status Register bits (CANSTAT 0xXE, ICOD)
#define MCP2515_CANSTAT_NO_INT 0x00
#define MCP2515_CANSTAT_ERR_INT 0x02
#define MCP2515_CANSTAT_WAK_INT 0x04 //Wake-up Interrupt
#define MCP2515_CANSTAT_TXB0_INT 0x06
#define MCP2515_CANSTAT_TXB1_INT 0x08
#define MCP2515_CANSTAT_TXB2_INT 0x0A
#define MCP2515_CANSTAT_RXB0_INT 0x0C
#define MCP2515_CANSTAT_RXB1_INT 0x0E

//MCP2515 CAN Interrupt Flag Define
#define MCP2515_CANINTF_MERRF	0x80
#define MCP2515_CANINTF_WAKIF	0x40
#define MCP2515_CANINTF_ERRIF	0x20
#define MCP2515_CANINTF_TX2IF	0x10
#define MCP2515_CANINTF_TX1IF	0x08
#define MCP2515_CANINTF_TX0IF	0x04
#define MCP2515_CANINTF_RX1IF	0x02
#define MCP2515_CANINTF_RX0IF	0x01

#endif /*MCP2515REG_H_*/
