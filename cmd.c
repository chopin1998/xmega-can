#include "common.h"
#include "uart.h"
#include "uart_process.h"
#include "util.h"

#include "io.h"

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
        }
        else if ( !strcmp(para_head->para, "trig") )
        {
            printf("led trigged\n");
            LED_PORT.OUTTGL = 0xff;
        }
        else
        {
            printf("unknow cmd\n");
        }

    } while (0);
    
    p_list_clear(para_head);
}

