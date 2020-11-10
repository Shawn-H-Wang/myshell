//
//  touch.c
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#include "touch.h"

int change_times;
bool no_create;
struct timespec newtime[2];

bool mytouch(const char *file)
{
    bool ok;
    int fd = -1;
    if ( no_create != 1)
        fd = open(file, O_CREAT | O_WRONLY, MODE_RW_UGO);

    if (change_times != (CH_ATIME | CH_MTIME))
    {
        if (change_times == CH_ATIME)
            newtime[1].tv_nsec = UTIME_OMIT;
        else
            newtime[0].tv_nsec = UTIME_OMIT;
    }
    ok = (utimensat(AT_FDCWD, file,  newtime, 0) == 0);
    return ok;
}

