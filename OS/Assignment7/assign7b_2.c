#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
  
int main()
{
	int returnValue;
	char data[80],c,d[100];
	FILE *fp;
	int fd1,l,w,fd,i;
	int open_mode=O_RDONLY;
	int letter=0,word=0,sente[3];
	sente[0]=0;sente[1]=0;sente[2]=0;
	int res=mkfifo("my_fifo",0777);
	int res1=mkfifo("my_fifo1",0777);
	printf("\nSentences readed are ::");

	while(1)
	{
	
		fd1=open("my_fifo",O_RDONLY);
		read(fd1,data,80);
				printf("\n%s",data);
		sente[0] = sente[0] + strlen(data);
		sente[2]++;
		sente[1]++;
		for(i=0;data[i]!='\0';i++)
		{
			if(data[i]==' ')
			{
					sente[1]++;
			}
		}
		if(strcmp(data,"stop")==0)
			{
				break;
				}
	
		
			close(fd1); 
			
	}
	    
	    //File operations::
	    fp=fopen("b.txt", "w");
	    fprintf(fp,"\nThe number of letters are  ::\t%d",sente[0]);
		fprintf(fp,"\nThe number of words are    ::\t%d",sente[1]);
		fprintf(fp,"\nThe number of sentences are::\t%d\n\n",sente[2]);
		fclose(fp);
	
		fp=fopen("b.txt","r");  
        if(fp==NULL){printf("jdhgf");}
		
			fd=open("my_fifo1",O_WRONLY);
			 char line[300]; 
			 while (fgets(line, sizeof(line), fp))
        {
            int len = strlen(line);
            int num = write(fd, line, len);
            if (num != len)
                perror("write");
        }
			close(fd);

		fclose(fp);  
	
			/*fd=open("my_fifo1",O_WRONLY);
		
			write(fd,&sente[0],sizeof(int));
			write(fd,&sente[1],sizeof(int));
			write(fd,&sente[2],sizeof(int));
			close(fd);   	
	    */
	    
	    
	    
}	
