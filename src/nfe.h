//
//  nfe.h
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#ifndef nfe_h
#define nfe_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "hist.h"

int f_execmd(char**, char*, history*);

int fork_exec(char**, char*, history*);

#endif /* nfe_h */
