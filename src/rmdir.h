#ifndef rmdir_h
#define rmdir_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int exec_rmdir(char*);

void remove_dir(char*);

#endif /* rmdir_h */
