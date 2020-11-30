#ifndef rm_h
#define rm_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdbool.h>

int exec_rm(char* cmd);

void myrm_dir(char* pathname);

int myrm(char* a);

#endif /* rm_h */
