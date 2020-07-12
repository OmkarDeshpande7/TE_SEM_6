#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int * BubbleSort(int *,int no);
void SelectSort(int []);
void swap(int *xp, int *yp);
int main(int argc, char *argv[])
       {
            pid_t cpid;
			int *arr=NULL,no;
			char str[10];
			int *array=(int*)malloc(10*sizeof(int));
			printf("How many elements in the array : \n");
			scanf("%d",&no);
			printf("Enter array elements !\n");
			for(int i=0;i<no;i++)
			scanf("%d",&array[i]);
			array = BubbleSort(array,no);	
            cpid = fork();
            printf("\nThe cpid is %d\n",cpid);
           
         	if (cpid < 0) {
				printf("Error in fork command !\n");
         	   	exit(EXIT_FAILURE);
          	}
          	
			if (cpid > 0) {
                
                for(int i=0;i<no;i++)
				   	printf("%d ",array[i]);
				   	printf("\n");
              	wait(NULL);
              	exit(EXIT_SUCCESS);
           }
	     
           else if (cpid == 0) {
            	for(int i=0;i<no;i++)
				{
				str[i] =array[i] + '0';
				}
				str[5]='\0'; 
            	char *const arg[] = { str };  
              	execv("./p2",arg);
              	exit(EXIT_SUCCESS);

          	} 
          	 
       }
       
       
int * BubbleSort(int * array,int no){
for(int i=0;i<no;i++)
	for(int j=0;j<no-1;j++)
		if (*(array+j) > *(array+j+1) )
		{
		int temp = *(array+j);
		*(array+j) = *(array+j+1);
		*(array+j+1) = temp;
		}
		return array;
		
	
}

