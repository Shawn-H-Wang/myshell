#ifndef cat_h
#define cat_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_content(void);

char *get_content(void);

void exec_cat_pipe(char*);

int exec_cat(char*);

#endif /*cat_h*/