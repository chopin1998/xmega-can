#ifndef _UTIL_H
#define _UTIL_H


typedef struct _p_list
{
    char *para;
    struct _p_list *next;
} P_LIST_t;
void p_list_clear(P_LIST_t *head);

void limit_int(signed int *val, signed int down, signed int top);

unsigned char decode_hexbyte(unsigned char* buf);
unsigned char* encode_hexbyte(unsigned char num, unsigned char* buf);

unsigned char chksum(unsigned char *buf, unsigned char len);

#endif
