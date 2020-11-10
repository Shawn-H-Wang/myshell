//
//  wc.c
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#include "wc.h"

char *change_int_char(unsigned int count)
{
    int i=0, num=count;
    if (count < 10) {
        i=1;
    }
    else {
        while (num != 0) {
            num/=10;
            i++;
        }
    }
    num = count;
    char *c = (char*)malloc(num+1);
    int j = i;
    c[j] = '\0';
    --i;
    while (i >= 0) {
        c[i] = num%10 + '0';
        num /= 10;
        --i;
    }
    return c;
}

unsigned int count_buf(char *buf)
{
    if (buf == NULL || strlen(buf)==0) {
        return 0;
    }
    int count=0;
    change_nl_blank(buf);
    char *token = strtok(buf, " ");
    while (1) {
        if (token == NULL) {
            break;
        }
        ++count;
        token = strtok(NULL, " ");
    }
    return count;
}

void change_nl_blank(char *line)
{
    int i=0;
    for (; i<strlen(line); i++) {
        if (line[i] == '\n')
            line[i] = ' ';
    }
}
