//
//  nf.c
//  t
//
//  Created by Shawn H Wang on 2020/11/7.
//  Create new process by the system function "fork"

#include "nf.h"

pid_t wpid;
int status=0;
int tag=-1;

// We need to execute two or more processes in a same time.
// If flag
void exec_fork(char *commands[], int cl)
{
    pid_t pid = -1;
    int i;
    for (i=0; i<cl; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(0);
        }
        tag = i;
        /*In the for loop, we need to judge the created fork
         becasue in the son process,it will copy all the code
         and the data. To prevent the son process create a new
         process and run, we need to break the grand_process. */
        if (pid == 0) {
            break;
        }
    }
    if (pid == 0) { // Parent process need to execute...
        exec_cmd(commands[tag]);
        exit(0);
    }
    else if (pid > 0) { // Son process need to execute...
        while ((wpid=wait(&status))>0); // ~~~~!!!!HELP!!!!~~~~
        printf("[%d] %d\n", cl, getpid());
    }
}
