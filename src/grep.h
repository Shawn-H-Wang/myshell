//
//  grep.h
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#ifndef grep_h
#define grep_h

#include <stdio.h>
#include <string.h>

void clear_buf(void);

char *get_buf(void);

void add_to_buf(char*);

int is_in(char*, char*);

char *grep(char*, char *);

#endif /* grep_h */
