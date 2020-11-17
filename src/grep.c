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
    strcat(BUF, token);
    strcat(BUF, "\n");
}

int is_in(char *token, const char *args)
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
            if (strlen(args) == j)
                return 1;
        }
    }
    return 0;
}

char *grep(char *args, char *buf)
{
    char *token;
    token = strtok(buf, "\n");
    int i=1;
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
