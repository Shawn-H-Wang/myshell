//
//  cd.c
//  t
//
//  Created by Shawn H Wang on 2020/11/7.
//

#include "cd.h"

void cd(char *dir) {
    if (dir == NULL) {
        printf("insufficient arguments!!\n");
    } else {
        int tag;
        tag = chdir(dir);
        if(tag == -1) {
            printf("Wrong path! Directory: %s does not exist\n", dir);
        }
    }
}
