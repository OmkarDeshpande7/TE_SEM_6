#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

void create()
{
	int i=0,out;
	char buffer[25];
	printf("Enter sentence to write in file:\n");
	do {
	scanf("%c",&buffer[i]);
	i++;
	} while (buffer[i-1] != '#');
	buffer[i-1]='\0';
	out = open("a.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	write(out,buffer,i-1);
	printf("You Entered:\n%s\n",buffer);	
	close(out);
}

void readin()
{
	int in,nread;
	char buffer[100];
	in = open("a.txt", O_RDONLY);
	while((nread = read(in,buffer,sizeof(buffer))) > 0)
	printf("The File contents are:%s\n",buffer);
	close(in);
}

void append()
{
	int i=0,out;
	char buffer[25];
	printf("Enter sentence to append in file:\n");
	do {
	scanf("%c",&buffer[i]);
	i++;
	} while (buffer[i-1] != '#');
	buffer[i-1]='\0';
	out = open("a.txt", O_WRONLY|O_APPEND, S_IRUSR|S_IWUSR);
	write(out,buffer,i-1);
	printf("You Entered:\n%s\n",buffer);
	close(out);
}

int main() 
{
	int chi;
	do{
		printf("MENU:\n1)CREATE A NEW FILE\n2)READ FROM A FILE\n3)WRITE TO THE FILE \n4)CLOSE THE FILE\nENTER AN INPUT :: ");
		scanf("%d",&chi);
		switch(chi)
		{
		case 1:
			create();
			break;
		case 2:
			readin();
			break;
		case 3:
			append();
			
			break;
		default:
			if(chi !=4)
				printf("PLEASE ENTER VALID INPUT.");
		}
	}while(chi != 4);
	return 0; 
}
