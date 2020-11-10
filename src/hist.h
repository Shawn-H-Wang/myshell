//
//  hist.h
//  t
//
//  Created by Shawn H Wang on 2020/11/7.
//

#ifndef hist_h
#define hist_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HIS 100

typedef struct {
    int length;
    char *his[MAX_HIS];
}history;

void init_hist(history*);

void add_hist(history*, const char*);

void print_hist(const history*);

void print_hist_arg(const history*, const char*);

char *p_hist(const history*);

char *p_hist_arg(const history*, const char*);

#endif /* hist_h */
