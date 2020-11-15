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
	//	printf("open %s succeed\n",args);
		
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
				char *p = (char*)malloc(strlen(args)-i);
				int j;
				for (j=0; j < sizeof(p); j++, i++) {
					p[j] = args[i];
				}
				strcat(token, p);
				free(p);
			}
			if((dstfd=open(token,O_CREAT|O_WRONLY,777))==-1) 
			{
				perror("open \n");
			}
	
	//	printf("open %s succeed\n",token);
		}
	}
	
	while((numRead=read(sourfd,buf,BUFSIZE))>0) 
	{
		//printf("read:%d\n",numRead);
		if(((numWrite=write(dstfd,buf,numRead)))!=numRead) 
		{
			perror("write \n");
		}
	//	printf("write total %d byte to %s\n",totalByte+=numWrite,argv[2]);
	}	
	close(sourfd);  
	//printf("close sourfd\n");
	close(dstfd);
	//printf("close dstfd\n");
	return 1;
}
