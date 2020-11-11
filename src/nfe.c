//
//  nfe.c
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#include "nfe.h"
#include "Shell.h"
#include "cd.h"
#include "pwd.h"
#include "mkdir.h"
#include "rmdir.h"

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
        clear_path();
        get_current_path(get_inode("."));
        if (strlen(get_path())==0) {
            printf("/\n");
        } else {
            printf("%s\n", get_path());
        }
        return 1;
    }
    else if (strcmp(argv[0], "cp") == 0) {
        return 1;
    }
    else if (strcmp(argv[0], "history") == 0) {
        char *args = split_blank(cmd, 1);
        if (args == NULL || strlen(args) == 0)
            print_hist(hist);
        else
            print_hist_arg(hist, args);
        return 1;
    }
    else if (strcmp(argv[0], "ls") == 0) {
        
        return 1;
    }
    else if (strcmp(argv[0], "cat") == 0) {
        
        return 1;
    }
    else if (strcmp(argv[0], "mv") == 0) {
        return 1;
    }
    else if (strcmp(argv[0], "rm") == 0) {
        return 1;
    }
    else if (strcmp(argv[0], "touch") == 0) {
        return 1;
    }
    else if (strcmp(argv[0], "mkdir") == 0) {
        return exec_mkdir(cmd);
    }
    else if (strcmp(argv[0], "su") == 0) {
        return 1;
    }
    else if (strcmp(argv[0], "grep")==0) {
        printf("-myshell: %s: command used wrong\n", argv[0]);
        return 1;
    }
    else {
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
