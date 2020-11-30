#ifndef rmdir_h
#define rmdir_h

#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

int exec_rmdir(char*);

int myrmdir(char* a);

#endif /* rmdir_h */
