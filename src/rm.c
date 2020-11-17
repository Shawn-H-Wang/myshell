#include "rm.h"
#include "Shell.h"

int exec_rm(char *cmd)
{
    char *args = split_blank(cmd, 1);
    if (args == NULL) {
        printf("The arguments are empty! Please check your input!!\n");
        return 1;
    }
    if (args[0] == '-') {
        if (strlen(args) == 1) {
            printf("Wrong arguments for command: rm\n");
            return 1;
        }
        if (strcmp(args, "-f") == 0) {
            // Execute the command remove_f(Force to remove the file)
        }
        else if (strcmp(args, "-r") == 0) {
            int tag = print_yn();
            if (tag == 1) {
                // Execute the command rmdir
            }
        }
        else if (strcmp(args, "-rf") == 0) {
            // Execute the command remove_f(Force to remove the file and the directory)
        }
        else {
            printf("Wrong arguments for command: rm\n");
        }
        return 1;
    }
    else {
        int tag = print_yn();
        if (tag == 1) {
            // Execute the command remove_f
            
        }
    }
    return 1;
}

void remove_f(char *args)
{
    
}

int print_yn()
{
    char *t = (char*)malloc(4);
    while(1) {
        printf("Dou you want to remove this file or directory? [yes or no] ");
        char c;
        int i=0;
        while ((c=getchar()) != '\n') {
            t[i++] = c;
        }
        t[i] = '\0';
        if (strcmp(t, "no") == 0) {
            free(t);
            return 0;
        }
        else if (strcmp(t, "yes") == 0) {
            free(t);
            return 1;
        }
        else {
            continue;
        }
    }
}

