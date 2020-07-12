#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
void BubbleSort(int []);
void SelectSort(int []);
void swap(int *xp, int *yp);
int main(int argc, char *argv[])
       {
            pid_t cpid;
			int array[10];
			printf("Enter 5 array elements !\n");
			
			for(int i=0;i<5;i++)
				scanf("%d",&array[i]);
				
            cpid = fork();
            printf("The cpid is %d\n",cpid);
           
         	if (cpid < 0) {
				printf("Error in fork command !\n");
         	   	exit(EXIT_FAILURE);
          	}
			
	        if (cpid == 0) {   
              	printf("\nIn child process !\n");
              	printf("Running pid is : %d\n",getpid());
              	printf("Old Parent pid is : %d\n",getppid());
              	SelectSort(array);
				sleep(10);
              	printf("New Parent pid is : %d\n",getppid());
              	printf("exit child process !\n");
              	exit(EXIT_SUCCESS);

          	} else {
	          	printf("\nIn parent process !\n");        
              	BubbleSort(array);
              	printf("Exit parent process !\n");      
              	exit(EXIT_SUCCESS);
           }
       }
       
       
void BubbleSort(int array[]){

for(int i=0;i<5;i++)
	for(int j=0;j<4;j++)
		if (array[j] > array[j+1] )
		{
		int temp = array[j];
		array[j] = array[j+1];
		array[j+1] = temp;
		}
		
		for(int i=0;i<5;i++)
				printf("%d ",array[i]);
				printf("\n");
	
}

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
void SelectSort(int array[])  
{  
    int i, j, min_idx;  
  

    for (i = 0; i < 4; i++)  
    {  

        min_idx = i;  
        for (j = i+1; j < 5; j++)  
        if (array[j] < array[min_idx])  
            min_idx = j;  
 
        swap(&array[min_idx], &array[i]);  
    }
    for(int i=0;i<5;i++)
				printf("%d ",array[i]);
				printf("\n");  
}  
