//
//  Shell.h
//  t
//
//  Created by Shawn H Wang on 2020/11/3.
//

#ifndef Shell_h
#define Shell_h

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include "hist.h"

#define MAX 1024
#define MAX_CMD 85
#define MAX_ARG 100

#define UP "^[[A"
#define DOWN "^[[B"
#define LEFT "^[[C"
#define RIGHT "^[[D"

void Shell_Looper(void);

void PrintAbout(void);

void PrintBye(void);

void print_prompt(void);

void input_line(char*);

void replace_char(char*);

void split_inline(char*);

int execute_cmd(char*);

int exec_cmd(char*);

char *split_blank(char*, int);

char *split_and(char*, int);

char *split_pipe(char*, int);

int is_in_list(char*[], const char*, int);

#endif /* Shell_h */
