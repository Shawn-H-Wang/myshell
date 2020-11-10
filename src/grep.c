//
//  grep.c
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#include "grep.h"

char BUF[BUFSIZ*2];

void clear_buf()
{
    int i;
    for (i=0; i<BUFSIZ; i++) {
        BUF[i]='\0';
    }
}

char *get_buf()
{
    return BUF;
}

void add_to_buf(char *token)
{
    size_t l = strlen(BUF);
    int i = (int)l;
    for (; i<l+strlen(token)+1; i++) {
        BUF[i] = token[i-l];
    }
    BUF[strlen(BUF)] = '\n';
}

int is_in(char *token, char *args)
{
    int i;
    for (i=0; i<strlen(token); i++) {
        int j=0;
        if (token[i] == args[j]) {
            int k = i;
            for (j=0; j<strlen(args); j++) {
                if (token[k++] != args[j])
                    break;
            }
            if (k-i == j)
                return 1;
        }
        else
            continue;
    }
    return 0;
}

char *grep(char *args, char *buf)
{
    char *token;
    token = strtok(buf, "\n");
    while (1) {
        if (token == NULL)
            break;
        if (is_in(token, args)) {
            add_to_buf(token);
        }
        token = strtok(NULL, "\n");
    }
    return BUF;
}
