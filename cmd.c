#include "common.h"
#include "uart.h"
#include "uart_process.h"
#include "util.h"

#include "io.h"
#include "mcp2515.h"

void cmd_process(unsigned char *cmd_buf)
{
    // printf("%s", LB_BT.buf);

    P_LIST_t *para_head, *curr;
    char *p = NULL;
    unsigned char p_count = 0;

    unsigned char reg, val;
    signed char rev;
    signed int offset;

    unsigned char buf[64];

    para_head = (P_LIST_t *)malloc(sizeof(P_LIST_t));

    p = strtok(cmd_buf, ",");
    curr = para_head;

    while (p)
    {
        p_count++;

        curr->para = p;
        curr->next = (P_LIST_t *)malloc(sizeof(P_LIST_t));
        curr = curr->next;

        p = strtok(NULL, ",");
    }
    curr->next = NULL;

    do 
    {        
        if ( !strcmp(para_head->para, "hi") )
        {
            printf("compiled @ %s\n", __DATE__ "," __TIME__);
            if (MODE_PORT.IN & MODE_PIN)
            {
                printf("tx mode\n");
            }
            else
            {
                printf("rx mode\n");
            }
        }
        else if ( !strcmp(para_head->para, "read") )
        {
            if (p_count != 2)
            {
                printf("read [reg_addr]\n");
                break;
            }

            unsigned char addr = decode_hexbyte(para_head->next->para);
            unsigned char val;
            mcp2515_read(addr, &val);
            printf("reg: 0x%02x -> 0x%02x\n", addr, val);
        }
        else if ( !strcmp(para_head->para, "write") )
        {
            if (p_count != 3)
            {
                printf("write [reg_addr] [value]\n");
                break;
            }

            unsigned char addr = decode_hexbyte(para_head->next->para);
            unsigned char val = decode_hexbyte(para_head->next->next->para);
            mcp2515_write(addr, val);
            printf("set reg: 0x%02x -> 0x%02x\n", addr, val);
        }
        else if ( !strcmp(para_head->para, "trig") )
        {
            printf("led trigged\n");
            LED_PORT.OUTTGL = LED_2;
        }
        else if ( !strcmp(para_head->para, "test") )
        {
            for (unsigned char i=0; i<3; i++)
            {
                mcp2515_can_frame_t frame;
                unsigned char reg;

                frame.id = 0x04500000UL;
                snprintf(frame.data, 8, "abcdefg");
                frame.len = 7;
                mcp2515_load_tx_buf(MCP2515_TX_0, &frame);

                for (unsigned char i=0x31; i<0x31+5; i++)
                {
                    mcp2515_read(i, &reg);
                    printf("0x%02x -> 0x%02x\n", i, reg);
                }
                printf("\n\n");
            }
        }
        else
        {
            printf("unknow cmd\n");
        }

    } while (0);
    
    p_list_clear(para_head);
}

