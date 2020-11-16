#include "touch.h"
#include "Shell.h"

int exec_touch(char *cmd)
{
    char *args = split_blank(cmd, 1);
    if (args == NULL) 
    {
        printf("you don't input args");
    }
    else
    {
        while(args != NULL)
        {
            FILE *file;
            file = fopen(args,"r");
            
            if(access(args,F_OK)==0)
            {
                printf("the file : \' %s \' is already exist   \n",args);
            }
            else{
                if(file == NULL)
                {
                    file = fopen(args,"w");
                }
            }
            
            fclose(file);
            args = split_blank(cmd, 1);
        }
    }
}