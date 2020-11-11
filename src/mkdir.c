//
//  mkdir.c
//  t
//
//  Created by Shawn H Wang on 2020/11/8.
//

#include "mkdir.h"
#include "cd.h"

int exec_mkdir(char *cmd)
{
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

// Create dir without any arguments
void creat_dir(const char *path)
{
    if (path == NULL || strlen(path) <= 0) {
        puts("Your path is NULL or BLANK, please check your input!");
        return;
    }
    if (!access(path, F_OK)) {  // Test if the file exist in the path. If exist, return 0.
        printf("mkdir: cannot create directory %s: File exists\n", path);
        return;
    }
    char *buf = (char*)malloc(strlen(path)+1);
    strcpy(buf, path);
    int tag = mkdir(buf, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);    // The permission is "755"
    free(buf);
    if (tag != 0) {
        perror("Error: mkdir create directory failed!");
        return;
    }
}

void creat_dirs(const char* path)
{
    if (path == NULL) { // End tag for recursion.
        puts("Your path is NULL or BLANK, please check your input!");
        return;
    }
    if (path[0] == '/') {
        cd("/");
    }
    
    char *buf = (char*)malloc(strlen(path)+1);
    strcpy(buf, path);
    char *token = strtok(buf, "/");
    
    if (strcmp(token, ".")==0) {
        token = strtok(NULL, "/");
    }
    
    if (access(token, F_OK)==0) {  // Test if the file exist in the path. If exist, return 0.
        cd(token);
        token = strtok(NULL, "/");
    }
    else {
        int tag = mkdir(token, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);    // The permission is "755"
        if (tag != 0) {
            perror("Error: mkdir create directory failed!");
            free(buf);
            return;
        }
        cd(token);
        token = strtok(NULL, "/");
    }
    if (token != NULL) {
        size_t l = strlen(token);
        token[strlen(token)] = '/';
        if (strlen(token) == l+1)
            return;
        else
            creat_dirs(token);
    }
    free(buf);
}
