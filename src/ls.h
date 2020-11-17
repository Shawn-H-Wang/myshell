#ifndef ls_h
#define ls_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

#define MAXB 4096

void clear_message(void);

char* get_message(void);

void exec_ll(char*, int);

void exec_ls(char*, int);

void getInfo(int, char*);

void showInfo(int, char*);

void mode_to_letters(int,char*);

char *uid_to_name(uid_t);

char *gid_to_name(gid_t);

#endif /* ls_h */
