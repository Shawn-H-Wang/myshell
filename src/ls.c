//
//  ls.c
//  t
//
//  Created by Shawn H Wang on 2020/11/9.
//

#include "ls.h"
#include "Shell.h"

char MESSAGE[BUFSIZ*2]; // Save message

void clear_message()
{
    int i;
    for (i=0; i<MAXB; i++) {
        MESSAGE[i] = '\0';
    }
}

char* get_message()
{
    return MESSAGE;
}

void exec_ll(char *cmd, int tag)
{
    int isL;
    isL = 1;
    char *path;
    char *args = split_blank(cmd, 1);
    if (args == NULL)
    {
        path = ".";
    }
    else {
        path = args;
    }
    while (path != NULL) {
        if (access(path, F_OK) != 0) {   // If directory is not existed!
            printf("ls: cannot access %s: No such file or directory\n", path);
            path = split_blank(cmd, 1);
            continue;
        }
        if (strcmp(path, ".")==0 || strcmp(path, "..")==0) {
            printf("%s/:\n", path);
        }
        else {
            printf("%s:\n", path);
        }
        if (tag == 0) {
            showInfo(isL, path);
        }
        else {
            getInfo(isL , path);
        }
        path = split_blank(cmd, 1);
    }
}

void exec_ls(char *cmd, int tag)
{
    int isL ;
    isL = 0;
    char *path;
    char *args = split_blank(cmd, 1);
    if (args == NULL)
    {
        path = ".";
    }
    else
    {
        if(strcmp(args , "-l")==0)
        {
            isL = 1;
            
            char *token = split_blank(cmd,1);
            if(token == NULL)
            {
                path = ".";
            }
            else
            {
                path = token;
            }
        }
        else
        {
            path = args;
        }
    }
    while (path != NULL) {
        if (access(path, F_OK) != 0) {   // If directory is not existed!
            printf("ls: cannot access %s: No such file or directory\n", path);
            path = split_blank(cmd, 1);
            continue;
        }
        if (strcmp(path, ".")==0 || strcmp(path, "..")==0) {
            printf("%s/:\n", path);
        }
        else {
            printf("%s:\n", path);
        }
        if (tag == 0) {
            showInfo(isL, path);
        }
        else {
            getInfo(isL , path);
        }
        path = split_blank(cmd, 1);
    }
}

void getInfo(int isL, char* path)
{
    struct dirent* ent = NULL;
    DIR* dir = opendir(path);
    if (dir == NULL) {
        int j = 0;
        if (isL == 0) {
            j += sprintf(MESSAGE+j, "%s\n", path);
        }
        else {
            struct stat info;
            char temp[80];
            strcpy(temp, path);
            if(lstat(temp,&info) == -1)
            {
                j += sprintf(MESSAGE+j, "Cannot open the directory: %s", temp);
            }
            else {
                char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
                void mode_to_letters();
                char modestr[11];

                mode_to_letters(info.st_mode,modestr);
                j += sprintf(MESSAGE+j, "%s ",modestr);
                j += sprintf(MESSAGE+j, "%d ",(int)info.st_nlink);
                j += sprintf(MESSAGE+j, "%s ",uid_to_name(info.st_uid));
                j += sprintf(MESSAGE+j, "%s ",gid_to_name(info.st_gid));
                j += sprintf(MESSAGE+j, "%6ld ",(long)info.st_size);
                j += sprintf(MESSAGE+j, "%.12s ",4+ctime(&info.st_mtime));
                
                j += sprintf(MESSAGE+j, "%s", path);

                static char linkPath[1024];
                    
                readlink(path,linkPath,1024);
                if(S_ISLNK(info.st_mode))
                {
                    j += sprintf(MESSAGE+j, "->%s",linkPath);
                }

                j += sprintf(MESSAGE+j, "\n");
            }
        }
        return;
    }
    int newLine = 0;
    int j=0;
    while((ent = readdir(dir)))
    {
        if(isL == 0)
        {
            if((ent->d_type == 4 || ent->d_type == 8) && ent->d_name[0]!='.')
            {
                j += sprintf(MESSAGE+j, "%-14s",ent->d_name);
                newLine++;
                if(newLine % 3 == 0) {
                    j += sprintf(MESSAGE+j, "\n");
                }
            }
        }
        else
        {
            struct stat info;
            char temp[80];
            strcpy(temp,path);
            strcat(temp,"/");
            strcat(temp,ent->d_name);
            if(lstat(temp,&info) == -1)
            {
                j += sprintf(MESSAGE+j, "Cannot open the directory: %s",temp);
                break;
            }
            else
            {
                if(ent->d_name[0]!='.')
                {
                    char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
                    void mode_to_letters();
                    char modestr[11];
                    
                    mode_to_letters(info.st_mode,modestr);
                    
                    j += sprintf(MESSAGE+j, "%s ",modestr);
                    j += sprintf(MESSAGE+j, "%d ",(int)info.st_nlink);
                    j += sprintf(MESSAGE+j, "%s ",uid_to_name(info.st_uid));
                    j += sprintf(MESSAGE+j, "%s ",gid_to_name(info.st_gid));
                    j += sprintf(MESSAGE+j, "%6ld ",(long)info.st_size);
                    j += sprintf(MESSAGE+j, "%.12s ",4+ctime(&info.st_mtime));

                    j += sprintf(MESSAGE+j, "%s",ent->d_name);

                    
                    static char linkPath[1024];
                    
                    readlink(temp,linkPath,1024);
                    if(S_ISLNK(info.st_mode))
                    {
                        j += sprintf(MESSAGE+j, "->%s",linkPath);
                    }

                    j += sprintf(MESSAGE+j, "\n");
                }
            }
        }
    }
    closedir(dir);
    j += sprintf(MESSAGE+j, "\n");
}

void showInfo(int isL,char *path)
{
    struct dirent* ent = NULL;
    DIR* dir = opendir(path);
    if (dir == NULL) {
        if (isL == 0) {
            printf("%s\n", path);
        }
        else {
            struct stat info;
            char temp[80];
            strcpy(temp, path);
            if(lstat(temp,&info) == -1)
            {
                printf("Cannot open the directory: %s",temp);
            }
            else {
                char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
                void mode_to_letters();
                char modestr[11];

                mode_to_letters(info.st_mode,modestr);

                printf("%s ",modestr);
                printf("%d ",(int)info.st_nlink);
                printf("%s ",uid_to_name(info.st_uid));
                printf("%s ",gid_to_name(info.st_gid));
                printf("%6ld ",(long)info.st_size);
                printf("%.12s ",4+ctime(&info.st_mtime));
                
                printf("%s",path);

                static char linkPath[1024];
                    
                readlink(path,linkPath,1024);
                if(S_ISLNK(info.st_mode))
                {
                    printf("->%s",linkPath);
                }

                printf("\n");
            }
        }
        return;
    }
    int newLine = 0;
    while((ent = readdir(dir)))
    {
        if(isL == 0)
        {
            if((ent->d_type == 4 || ent->d_type == 8) && ent->d_name[0]!='.')
            {
                printf("%-14s",ent->d_name);
                newLine++;
                if(newLine % 3 == 0) printf("\n");
            }
        }
        else
        {
            struct stat info;
            char temp[80];
            strcpy(temp,path);
            strcat(temp,"/");
            strcat(temp,ent->d_name);
            if(lstat(temp,&info) == -1)
            {
                printf("Cannot open the directory: %s",temp);
                break;
            }
            else
            {
                if(ent->d_name[0]!='.')
                {
                    char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
                    void mode_to_letters();
                    char modestr[11];
                    
                    mode_to_letters(info.st_mode,modestr);
                    
                    printf("%s ",modestr);
                    printf("%d ",(int)info.st_nlink);
                    printf("%s ",uid_to_name(info.st_uid));
                    printf("%s ",gid_to_name(info.st_gid));
                    printf("%6ld ",(long)info.st_size);
                    printf("%.12s ",4+ctime(&info.st_mtime));
                    
                    printf("%s",ent->d_name);
                    
                    static char linkPath[1024];
                    
                    readlink(temp,linkPath,1024);
                    if(S_ISLNK(info.st_mode))
                    {
                        printf("->%s",linkPath);
                    }

                    printf("\n");
                }
            }
        }
    }
    closedir(dir);
    puts("");
    
}

void mode_to_letters(int mode,char str[])
{
    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0] = 'd';     //directory
    if(S_ISCHR(mode)) str[0] = 'c';     //characteristic
    if(S_ISBLK(mode)) str[0] = 'b';     //block
    if(S_ISLNK(mode)) str[0] = 'l';     //link
    
    if(mode & S_IRUSR) str[1]= 'r';
    if(mode & S_IWUSR) str[2]= 'w';
    if(mode & S_IXUSR) str[3]= 'x';
    
    if(mode & S_IRGRP) str[4]= 'r';
    if(mode & S_IWGRP) str[5]= 'w';
    if(mode & S_IXGRP) str[6]= 'x';
    
    if(mode & S_IROTH) str[7]= 'r';
    if(mode & S_IWOTH) str[8]= 'w';
    if(mode & S_IXOTH) str[9]= 'x';
}

char *uid_to_name(uid_t uid)
{
    struct passwd *getpwuid(),*pw_ptr;
    static char numstr[10];
    if((pw_ptr = getpwuid(uid)) == NULL)
    {
        sprintf(numstr,"%d",uid);
        return numstr;
    }
    return pw_ptr->pw_name;
}

char *gid_to_name(gid_t gid)
{
    struct group *getgrgid(),*grp_ptr;
    static char numstr[10];
    if((grp_ptr = getgrgid(gid)) == NULL)
    {
        sprintf(numstr,"%d",gid);
        return numstr;
    }
    return grp_ptr->gr_name;
}
