#include "rm.h"
#include "Shell.h"


int exec_rm(char* cmd)
{
    char* args = split_blank(cmd, 1);
    char* token = split_blank(cmd, 1);
    char* input_yn = (char*)malloc(4);
    if (args == NULL) {
        puts("None arguments for rmdir! Please check your input!");
        return 1;
    }
    if (token == NULL) {
        while (1) {
            printf("If you want to remove the file: %s? Please input [yes/no] ", args);
            ssize_t buffer;
            size_t buf_bytes = 4;
            buffer = getline(&input_yn, &buf_bytes, stdin);
            input_yn[(int)--buffer] = '\0';
            if (strcmp(input_yn, "no") == 0 || strcmp(input_yn, "yes") == 0) {
                break;
            }
            else {
                puts("Your input is wrong! Please check and re_input!");
            }
        }
        if (strcmp(input_yn, "yes") == 0) {
            myrm(args);
        }
        else {
            if (strcmp(args, "-rf") == 0) {
                struct stat file_message = {};
                if (S_ISDIR(file_message.st_mode)) // 判断是否为目录
                {
                    printf("路径[%s]下的目录将会被删除，按‘enter’确认，其他任意键取消\n", token); // 防止误操作
                }
                else {
                    printf("It is not dir!\n");
                }
            }
            else
            {
                printf("error\n");
            }
            return 0;
        }
    }
}

int myrm(char* a) {
    struct stat file_message = {}; // 定义stat函数返回的结构体变量,stat:获取文件信息
    int ret_stat = lstat(a, &file_message); // 获取文件信息，错误返回-1
    if (ret_stat == -1) // stat读取文件错误则输出提示信息
    {
        printf("%s error!", a);
    }
    else {
        remove(a);
    }
}

void myrm_dir(char* pathname)
{
    char nextpath[PATH_MAX + 1];

    DIR* ret_opendir = opendir(pathname); // 打开目录"pathname"
    if(ret_opendir == NULL)
        printf("open path error!\n");

    struct dirent* ret_readdir = NULL; // 定义readdir函数返回的结构体变量
    while(ret_readdir = readdir(ret_opendir)) // 判断是否读取到目录尾
    {
        char* filename = ret_readdir->d_name; // 获取文件名

        int end = 0; // 优化路径 (其实无论几个“/”叠加都不会影响路径）
        while (pathname[end])
            end++;
        strcpy(nextpath, pathname);
        if (pathname[end - 1] != '/')
            strcat(nextpath, "/");
        strcat(nextpath, filename);

        struct stat file_message = {}; // 定义stat函数返回的结构体变量
        int ret_stat;
        ret_stat=lstat(nextpath, &file_message); // 获取文件信息
        if(ret_stat == -1) // stat读取文件错误则输出提示信息
        {
            printf("%s error!", filename);
        }
        // 注意屏蔽当前目录和上一级目录，但不能用filename[0]='.'来判断，这样会导致无法删除隐藏文件，从而导致目录文件删除失败
        else if (S_ISDIR(file_message.st_mode) && strcmp(filename, ".") && strcmp(filename, ".."))
        {
            myrm_dir(nextpath);
            printf("delete dir :%s\n", nextpath);
            remove(nextpath);
        }
        else if (strcmp(filename, ".") && strcmp(filename, "..")) // 同上
        {
            struct passwd* pwd = getpwuid(file_message.st_uid);

            if (pwd->pw_uid == getuid()) // 再次检查，双重保险
            {
                printf("delete file:%s\n", nextpath);
                remove(nextpath);
            }
        }
    }
    closedir(ret_opendir);
    printf("delete dir :%s\n", pathname);
    remove(pathname); // 删除完目录中的文件后将自身删除
}
