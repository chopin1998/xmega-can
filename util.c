#include "common.h"
#include "util.h"


void p_list_clear(P_LIST_t *head)
{
    P_LIST_t *curr, *tmp;

    curr = head;
    while (curr)
    {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}


void limit_int(signed int *val, signed int down, signed int top)
{
    if (*val > top)
    {
        *val = top;
    }
    else if (*val < down)
    {
        *val = down;
    }
}


unsigned char decode_hexbyte(unsigned char* buf)
{
    unsigned char n;
    unsigned char digit[2] = {0, 0};

    for (unsigned char i = 0; i < 2; i++)
    {
        if (buf[i] > 0x29 && buf[i] < 0x40 )  // 0-9
        {
            digit[i] = buf[i] & 0x0f;
        }
        else if (buf[i] >='a' && buf[i] <= 'f') //if a to f
        {
            digit[i] = (buf[i] & 0x0f) + 9;
        }
        else if (buf[i] >='A' && buf[i] <= 'F') //if A to F
        {
            digit[i] = (buf[i] & 0x0f) + 9;
        }
    }
    
    n = digit[0] << 4 | digit[1];

    return n;
}


unsigned char* encode_hexbyte(unsigned char num, unsigned char* buf)
{
    unsigned char n;

    for (unsigned char i = 0; i < 2; i++)
    {
        n = (num >> (1 - i) * 4) & 0x0f ;

        if (n < 0x0A)
        {
            buf[i] = n + 0x30;
        }
        else
        {
            buf[i] = n + 0x37;
        }
    }

    return buf;
}

unsigned char chksum(unsigned char *buf, unsigned char len)
{
    unsigned char sum = 0x00;
    
    for (unsigned char i=0; i<len; i++)
    {
        sum += buf[i];
    }

    return sum;
}
