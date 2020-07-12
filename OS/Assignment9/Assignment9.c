#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
char name[25];
char str[300];
void print(char *str){
	write(1,str,strlen(str));
}


char * scan(){

	int i=0;
	do {
	read(0,&str[i],1);
	i++;
	} while (str[i-1] != '#');
	str[i-1]='\0';
	return str;
}

void create()
{
	int i=0,out;
	print("\tEnter name of file : ");
	strcpy(name,scan());
	out = open(name, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	write(out,"\tyour file is empty !\n",22);
	print("\tName of file created : ");
	print(name);	
}



void closef()
{
	int i=0,out;
	char buffer[25];
	print("File truncated and closed !\n");

	out = open(name, O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);	
	close(out);
}


void readin()
{
	int in,nread;
	char buffer[100];
	in = open(name, O_RDONLY);
	while((nread = read(in,buffer,sizeof(buffer))) > 0)
	print("\tThe File contents are :\n\t");
	print(buffer);
	close(in);
}

void append()
{
	int out;
	char buffer[25];
	print("\tEnter sentence to append in file:\n");
	strcpy(buffer,scan());
	out = open(name, O_WRONLY|O_APPEND, S_IRUSR|S_IWUSR);
	write(out,buffer,strlen(buffer));
	print("\tYou Entered :\n\t");
	print(buffer);
	close(out);
}

void clear_file()
{
	int i=0,out;
	out = open(name, O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);

}


int main() 
{
	int chi;
	do{
		print("\nMENU:\n1.Create file\n2.Read from file\n3.Write to file\n4.Clear File contents\n5.Close file\nEnter your input :: ");
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
		case 4:
			clear_file();
			break;
		case 5:
			closef();
			break;
		default:
				print("PLEASE ENTER VALID INPUT.");
		}
	}while(chi != 5);
	return 0; 
}
