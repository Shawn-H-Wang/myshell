//
//  pwd.h
//  t
//
//  Created by Shawn H Wang on 2020/11/7.
//

#ifndef pwd_h
#define pwd_h

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void clear_path(void);

char* get_path(void);

void add_to_path(char*);

void get_current_path(ino_t);

void inum_to_dname(ino_t, char*, int);

ino_t get_inode(const char*);

#endif /* pwd_h */
