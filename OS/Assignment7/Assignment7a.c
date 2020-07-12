 #include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>

       int main(int argc, char *argv[])
       {
           int pipefd[2],pipefd1[2];
           char filename[20];
           FILE *fp;
           pid_t cpid;
           char buf[20],ch,bf;        
               
           if (pipe(pipefd) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }
           
           if (pipe(pipefd1) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child reads from pipe */
               close(pipefd[1]);          /* Close unused write end */
               read(pipefd[0], &buf, 20);
               close(pipefd[0]);
               
               fp = fopen(buf, "r");
               if (fp == NULL)
					{
					printf("Cannot open file \n");
					exit(0);
					}
				ch = fgetc(fp);
				while (ch != EOF)
				{
					write(pipefd1[1], &ch, 1);
					ch = fgetc(fp); 
				}
				
				fclose(fp);              
               _exit(EXIT_SUCCESS);

           }
           else {            /* Parent writes argv[1] to pipe */
           	   printf("Parent Says...Enter the filename : ");
           	   scanf("%s",filename);
               write(pipefd[1], filename, strlen(filename));   
               close(pipefd1[1]);
               while (read(pipefd1[0], &bf, 1) > 0)
                   write(STDOUT_FILENO, &bf, 1);

               wait(NULL);                /* Wait for child */
               exit(EXIT_SUCCESS);
           }
       }

