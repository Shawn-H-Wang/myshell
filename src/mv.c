#include "mv.h"
#include "Shell.h"

int exec_mv(char *cmd)
{
    DIR* dir_ptr;    
    struct dirent* direntp;
    
    char *src_folder;
    char *dest_folder;
    
    char *args = split_blank(cmd, 1);
    if(args==NULL) 
    {
        printf("Your source argements are empty! Please check your input!\n");
        return 1;
    }
    else
    {
        src_folder = (char*)malloc(sizeof(args)+1);
        strcpy(src_folder, args);
        char *token = split_blank(cmd,1);
        if(token == NULL)
        {
            printf("Your target argements are empty! Please check your input!\n");
        }
        else
        {
            if(token[strlen(token)-1] == '/')
            {
                int i;
                for(i = strlen(args)-1;args[i] != '/'; i--);
                ++i;
                char *p = (char*)malloc(strlen(args)-i);
                int j;
                for(j = 0; j< sizeof(p)+1; j++,i++)
                {
                    p[j] = args[i];
                }
                strcat(token,p);
                free(p);
            }
            dest_folder = (char*)malloc(sizeof(token)+1);
            strcpy(dest_folder, token);	 
        }
        
        if(access(token,F_OK) == 0)
        {
            printf("mv: \'%s\' is already exist \n",token);
            return 1;
        }
    }
    
    dir_ptr = opendir("."); 
    if ( dir_ptr == NULL )
    {
        perror( "error: '.'" );
        exit( 1 );
    }
    
    while((direntp=readdir(dir_ptr)) != NULL ) 
    {
        if (strcmp(direntp->d_name, dest_folder) != 0) 
        {
            break;
        }
        else {
            printf("Target path not found\n");
        }
    }
    
    rename(src_folder, dest_folder);
    closedir(dir_ptr);
    
    free(src_folder);
    free(dest_folder);
    return 1;
}
