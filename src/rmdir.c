//
//  rmdir.c
//  t
//
//  Created by Shawn H Wang on 2020/11/9.
//

#include "rmdir.h"

void remove_dir(char* path) {
    if (path == NULL) {
        return;
    }
    if (access(path, F_OK) != 0) {   // If directory is not existed!
        printf("rmdir: failed to remove %s: No such file or directory\n", path);
        return;
    }
    
}