#include "Shell.h"
#include "rmdir.h"

int exec_rmdir(char *cmd){
    char* args = split_blank(cmd, 1);
    char* token = split_blank(cmd, 1);
    char* input_yn = (char*)malloc(4);
    if (args == NULL) {
        puts("None arguments for rmdir! Please check your input!");
        return 1;
    }
    if (token == NULL) {
        while (1) {
            printf("If you want to remove the directory: %s? Please input [yes/no] ", args);
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
            myrmdir(args);
            
        }
    }
    else {
        if (strcmp(args, "-p") == 0) {
            int tag;
            int tag1;
            char* sonpath;
            char* path_now = (char*)malloc(100);
            char* pathnow = (char*)malloc(100);
            //char* process_path;
            char* token1;
            char* fatherpath = "NULL";
            token1 = malloc(4);
            strcpy(token1, token);
            getcwd(pathnow, sizeof(pathnow));
            fatherpath = dirname(token1);
            sonpath = basename(token);
            tag = chdir(fatherpath);
            if (tag == -1) {
                printf("Wrong path! Directory: %s does not exist\n", fatherpath);
            }
            
            else {
                
                tag1=myrmdir(sonpath);
                if (tag1=1){
                    while (strcmp(fatherpath, pathnow) < 0 || strcmp(fatherpath, pathnow) > 0) {
                        getcwd(path_now, sizeof(path_now));
                        sonpath = basename(path_now);
                        fatherpath = dirname(path_now);
                        chdir(fatherpath);
                        getcwd(path_now, sizeof(path_now));
                        fatherpath = path_now;
                        DIR* fd;
                        int ret;
                        fd = opendir(sonpath);
                        if (fd == NULL)
                        {
                            printf("error,it is a file,or it is not exist -- %s\n", sonpath);
                            break;
                        }
                        closedir(fd);
                        
                        ret = rmdir(sonpath);
                        if (ret == -1)
                        {
                            printf("filed to delete it-%s\n", sonpath);
                            break;
                        }
                        else
                            printf("rm dir: %s\n", sonpath);
                        
                        
                    }
                }
                
                
            }
            free(token1);
        }
        
        else {
            char* token_new;
            if (args != NULL) {
                myrmdir(args);
            }
            if (token != NULL) {
                myrmdir(token);
            }
            while (token_new = split_blank(cmd, 1)) {
                myrmdir(token_new);
            }
        }
        free(input_yn);
        return 1;
    }
}
int myrmdir(char* a) {
    DIR* fd;
    int ret;
    fd = opendir(a);
    if (fd == NULL)
    {
        printf("error,it is a file,or it is not exist -- %s\n", a);
    }
    closedir(fd);
    
    ret = rmdir(a);
    if (ret == -1)
    {
        printf("filed to delete it-%s\n", a);
        return 0;
    }
    else {
        printf("rm dir: %s\n", a);
        return 1;
    }
}
