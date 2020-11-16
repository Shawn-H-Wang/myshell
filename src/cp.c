#include "cp.h"
#include "Shell.h"

int exec_cp(char *cmd)
{
    int sourfd, dstfd, numRead, numWrite;
	int totalByte=0;
	char buf[BUFSIZE];

	char *args = split_blank(cmd, 1);
	if(args == NULL) 
	{
		printf("you don't input args .\n");
		exit(0);
	}
	else
	{
		if((sourfd=open(args, O_RDONLY))==-1) 
		{
			perror("open \n");	
		}
		char *token = split_blank(cmd,1);
	   	if(token == NULL)
		{
			printf("you input few args \n");
		}
		else
		{
			if (token[strlen(token)-1] == '/') {
				int i;
				for (i=strlen(args)-1; args[i] != '/'; i--);
				++i;
				char *p = (char*)malloc(strlen(args)-i);
				int j;
				for (j=0; j < sizeof(p)+1; j++, i++) {
					p[j] = args[i];
				}
				strcat(token, p);
				free(p);
			}
			if (access(token, F_OK) == 0) {
				printf("cp: \'%s\' and \'%s\' are the same file\n", token, args);
				return 1;
			}
			if((dstfd=open(token, O_CREAT|O_WRONLY,777))==-1) 
			{
				perror("open \n");
			}
		}
	}
	
	while((numRead=read(sourfd,buf,BUFSIZE))>0) 
	{
		if(((numWrite=write(dstfd,buf,numRead)))!=numRead) 
		{
			perror("write \n");
		}
	}	
	close(sourfd);
	close(dstfd);
	return 1;
}
