//
//  touch.h
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#ifndef touch_h
#define touch_h

#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CH_ATIME 1
#define CH_MTIME 2
#define MODE_RW_UGO (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

bool mytouch(const char *file);

#endif /* touch_h */
