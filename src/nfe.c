#include "nfe.h"
#include "Shell.h"
#include "mv.h"
#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "mkdir.h"
#include "rmdir.h"
#include "cat.h"
#include "cp.h"
#include "touch.h"
#include "rm.h"

int TAG=1;

int f_execmd(char *argv[], char *cmd, history *hist)
{
    if (strcmp(argv[0], "exit") == 0  || strcmp(argv[0], "quit")==0) {
        puts("Shell is exiting...");
        return -1;
    }
    else if (strcmp(argv[0], "clear") == 0) {
        fflush(stdout);
        fputs("\x1b[2J\x1b[H", stdout);
        return 1;
    }
    else if (strcmp(argv[0], "pwd") == 0) {
        exec_pwd();
        return 1;
    }
    else if (strcmp(argv[0], "cp") == 0) {
        return exec_cp(cmd);
    }
    else if (strcmp(argv[0], "history") == 0) {
        exec_history(cmd, hist);
        return 1;
    }
    else if (strcmp(argv[0], "ls") == 0) {
        exec_ls(cmd, 0);
        return 1;
    }
    else if (strcmp(argv[0], "ll") == 0) {
        exec_ll(cmd, 0);
        return 1;
    }
    else if (strcmp(argv[0], "cat") == 0) {
        return exec_cat(cmd);
    }
    else if (strcmp(argv[0], "mv") == 0) {
        return exec_mv(cmd);
    }
    else if (strcmp(argv[0], "rm") == 0) {
        return exec_rm(cmd);
    }
    else if (strcmp(argv[0], "touch") == 0) {
        return exec_touch(cmd);
    }
    else if (strcmp(argv[0], "mkdir") == 0) {
        return exec_mkdir(cmd);
    }
    else if (strcmp(argv[0], "rmdir") == 0) {
        return exec_rmdir(cmd);
    }
    else if (strcmp(argv[0], "grep")==0) {
        printf("-myshell: %s: command used wrong\n", argv[0]);
        return 1;
    }
    else {
        // char *args = split_blank(cmd, 1);
        // int i=0, j=0;
        // char *cpy = (char*)malloc(sizeof(args)+1);
        // strcpy(cpy, args);
        // char *token = split_blank(cpy, 0);
        // while (token != NULL) {
        //     ++i;
        //     token = split_blank(cpy, 1);
        // }
        // char *as[i+2];
        // token = split_blank(args, 0);
        // for (j=0; j<=i+1; j++) {
        //     if (j == 0) {
        //         as[j] = (char*)malloc(sizeof(argv[0]));
        //         strcpy(as[j], argv[0]);
        //     }
        //     else if (j == i+1) {
        //         as[j] = NULL;
        //     }
        //     else {
        //         as[j] = (char*)malloc(sizeof(token));
        //         strcpy(as[j], token);
        //         token = split_blank(args, 1);
        //     }
        // }
        // execvp(as[0], as);
        printf("-myshell: %s: command not found\n", argv[0]);
        return 1;
    }
}

int fork_exec(char *argv[], char *cmd, history *hist)
{
    pid_t pid=-1;
    
    if ((pid=vfork()) < 0) {
        perror("fork failed");
        TAG = -2;
    }
    else if (pid == 0) {
        TAG = f_execmd(argv, cmd, hist);
        exit(0);
    }
    else {
        wait(NULL);
    }
    return TAG;
}
