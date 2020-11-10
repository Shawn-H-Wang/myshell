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
    if (strcmp(argv[0], "exit") == 0) {
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
        char *args = split_blank(cmd, 1);
        if (args == NULL) {
            puts("None arguments for mkdir! Please check your input!");
            return 1;
        }
        char *token = split_blank(cmd, 1);
        if (token == NULL) {
            creat_dir(args);
        }
        else {
            if (strcmp(args, "-p")==0) {
                if (strcmp(token, "/")==0 || strcmp(token, "./")==0 || strcmp(token, ".")==0) {
                    puts("Your path is root or current directory, please check your input!");
                    return 1;
                }
                creat_dirs(token);
            }
            else if (strcmp(args, "--p")==0) {
                puts("Please input the argument: \"-p\" to create directory in recursion.");
            }
            else {
                puts("Wrong arguments for mkdir! Please check your input!");
            }
        }
        return 1;
    }
    else if (strcmp(argv[0], "rmdir") == 0) {
        char *args = split_blank(cmd, 1);
        if (args == NULL) {
            puts("None arguments for rmdir! Please check your input!");
            return 1;
        }
        char *token = split_blank(cmd, 1);
        char *input_yn = (char*)malloc(4);
        if (token == NULL) {
            while (1) {
                printf("If you wang to remove the directory: %s? Please input [yes/no] ", args);
                ssize_t buffer;
                size_t buf_bytes = 4;
                buffer = getline(&input_yn, &buf_bytes, stdin);
                input_yn[(int)--buffer] = '\0';
                if (strcmp(input_yn, "no")==0 || strcmp(input_yn, "yes")==0) {
                    break;
                }
                else {
                    puts("Your input is wrong! Please check and re_input!");
                }
            }
            if (strcmp(input_yn, "yes")==0) {
                
            }
        }
        else {
            if (strcmp(args, "-f")==0) {
                
            }
            else {
                puts("Wrong arguments for rmdir! Please check your input!");
            }
        }
        free(input_yn);
        return 1;
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
