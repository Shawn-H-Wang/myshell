//
//  mkdir.h
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#ifndef mkdir_h
#define mkdir_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void creat_dir(const char*);

void creat_dirs(const char*);

#endif /* mkdir_h */
