//
//  pipe.c
//  t
//
//  Created by Shawn H Wang on 2020/11/7.
//

#include "pipe.h"
#include "pwd.h"
#include "cd.h"
#include "Shell.h"
#include "grep.h"
#include "wc.h"
#include "ls.h"

char *NONE_PRINT_CMDS[]={"exit", "cd", "cp", "mv", "rm", "touch", "mkdir", "rmdir", "su"};
int TAGPIPE=1;

void exec_cmd_pipd2(char *cmd, char *buf, history *hist)
{
    char *commds[2];
    size_t l = strlen(cmd);
    commds[0] = NULL;
    commds[0] = split_pipe(cmd, 0);
    if (strlen(commds[0]) == l) {    // Without '|'
        char *argv[MAX_ARG]; // The array for arguments
        argv[0] = NULL;
        argv[0] = split_blank(cmd, 0); // Get the name of the cmd
        // Judge some commands could without any special characters.
        if (is_in_list(NONE_PRINT_CMDS, argv[0], 9)) {
            printf("Command %s: can't be executed with pipe!\n", argv[0]);
            return;
        }
        else {
            if (strcmp(argv[0], "wc")==0) {
                char *args = split_blank(cmd, 1);
                if (args != NULL) {
                    puts("Too many arguments for wc! Please check your input!");
                    return;
                }
                unsigned int count = count_buf(buf);
                strcpy(buf, change_int_char(count));
                if (TAGPIPE == 0) {
                    printf("\twc: word count: %d\n", count);
                }
                return;
            }
            else if (strcmp(argv[0], "grep")==0) {
                char *args = split_blank(cmd, 1);
                if (args == NULL || strlen(args)==0) {
                    puts("None arguments for grep! Please check your input!");
                    return;
                }
                clear_buf();
                grep(args, buf);
                strcpy(buf, get_buf());
                if (TAGPIPE == 0)
                    printf("%s", get_buf());
                return;
            }
            else if (strcmp(argv[0], "history")==0 || strcmp(argv[0], "cat")==0 || strcmp(argv[0], "ls")==0 || strcmp(argv[0], "pwd")==0) {
                printf("Command %s: can't be executed with pipe!\n", argv[0]);
                return;
            }
            else {
                printf("-myshell: %s: command not found\n", argv[0]);
                return;
            }
        }
    }
    else {
        cmd[strlen(cmd)] = '|';
        commds[0] = split_pipe(cmd, 0);
        commds[1] = split_pipe(cmd, 1);
        if (split_pipe(commds[1], 1) == NULL) {
            exec_cmd_pipd2(commds[0], buf, hist);
            TAGPIPE = 0;
            exec_cmd_pipd2(commds[1], buf, hist);
        }
        else {
            commds[1][strlen(commds[1])] = '|';
            exec_cmd_pipd2(commds[0], buf, hist);
            exec_cmd_pipd2(commds[1], buf, hist);
        }
    }
}

char *exec_cmd_pipd(char *cmd, history *hist)
{
    char *argv[MAX_ARG];
    char *buf;
    argv[0] = NULL;
    buf = NULL;
    argv[0] = split_blank(cmd, 0);
    if (is_in_list(NONE_PRINT_CMDS, argv[0], 9)) {
        printf("Command %s: can't be executed with pipe!\n", argv[0]);
        return NULL;
    }
    else {
        if (strcmp(argv[0], "history")==0) {
            char *args = NULL;
            args = split_blank(cmd, 1);
            if (args == NULL || strlen(args) == 0)
                buf = p_hist(hist);
            else
                buf = p_hist_arg(hist, args);
            return buf;
        }
        else if (strcmp(argv[0], "cat")==0) {
            
        }
        else if (strcmp(argv[0], "ls")==0) {
            
        }
        else if (strcmp(argv[0], "pwd")==0) {
            clear_path();
            get_current_path(get_inode("."));
            if (strlen(get_path())==0) {
                strcat(buf, "/");
            }
            else {
                buf = get_path();
            }
            return buf;
        }
        else if (strcmp(argv[0], "grep")==0) {
            printf("-myshell: %s: command used wrong\n", argv[0]);
            return NULL;
        }
        else {
            printf("-myshell: %s: command not found\n", argv[0]);
            return NULL;
        }
    }
    return buf;
}

void exec_with_pipe(char *commds[2], history *hist)
{
    pid_t pid;
    int fd[2];
    char buffer[BUF_MAX];
    int i;
    for (i=0; i<BUF_MAX; i++) {
        buffer[i]='\0';
    }
    
    if (pipe(fd) == -1) {    // Pipe System Call Error
        perror("pipe create error");
        exit(0);
    }
    
    pid = fork();
    if (pid < 0) {
        perror("fork create error");
        exit(0);
    }
    else if (pid == 0) {
        close(fd[0]);
        char *buf = exec_cmd_pipd(commds[0], hist);
        if (buf != NULL) {
            write(fd[1], buf, strlen(buf));
        }
        close(fd[1]);
        exit(0);
    }
    else {
        close(fd[1]);
        wait(NULL);     // Wait for the son_progess.
        TAGPIPE=1;
        ssize_t len = read(fd[0], buffer, sizeof(buffer));  // Read buffer data from the pipe
        close(fd[0]);
        if (len>0) {
            if (strlen(commds[1]) == strlen(split_pipe(commds[1], 0))) {
                TAGPIPE = 0;
            }
            else {
                commds[1][strlen(commds[1])] = '|';
            }
            exec_cmd_pipd2(commds[1], buffer, hist);
        }
    }
}
