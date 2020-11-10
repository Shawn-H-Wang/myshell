//
//  pipe.h
//  t
//
//  Created by Shawn H Wang on 2020/11/7.
//

#ifndef pipe_h
#define pipe_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hist.h"

#define BUF_MAX 1024

void exec_with_pipe(char**, history*);

char *exec_cmd_pipd(char*, history*);

void exec_cmd_pipd2(char*, char*, history*);

#endif /* pipe_h */
