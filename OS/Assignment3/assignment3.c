#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
void *thread_function(void *arg);
void multiply(int [][8],int [][8],int [][8],int,int,int,int);
char message[] = "Hello World";
	clock_t start,end;
struct argument
{
	int i,j,r1,r2,c1,c2,M1[8][8],M2[8][8];
};
int main() {

	int res,r1,r2,c1,c2,M1[8][8],M2[8][8],M3[8][8],no=0,choice,**M4;
	pthread_t *a_thread;
	void *thread_result;
	printf("Enter no. of rows of matrix 1: ");
	scanf("%d",&r1);
	printf("Enter no. of columns of matrix 1: ");
	scanf("%d",&c1);
	printf("Enter no. of rows of matrix 2: ");
	scanf("%d",&r2);
	printf("Enter no. of columns of matrix 2: ");
	scanf("%d",&c2);
	if (c1 != r2)
	{
		printf("These matrix cannnot be multiplied !\n");
		return 0;
	}
	a_thread = (pthread_t *)malloc(r1 * c2 *sizeof(pthread_t));
	for(int i=0;i<r1;i++)
		for(int j=0;j<c1;j++)	
			{
				printf("Enter the element M1[%d][%d] : ",i+1,j+1);
				scanf("%d",&M1[i][j]);
			}

	for(int i=0;i<r2;i++)
		for(int j=0;j<c2;j++)	
			{
				printf("Enter the element M2[%d][%d] : ",i+1,j+1);
				scanf("%d",&M2[i][j]);
			}
	
	
	
	printf("How do you want to do the multiplication ?\n1.THREADS\n2.NORMAL : ");
	scanf("%d",&choice);
	switch (choice){
		case 1:

			/*int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);*/
			start = clock();
			for (int i=0;i<r1;i++)
			{
				for(int j=0;j<c2;j++){
				struct argument arg = {i,j,r1,r2,c1,c2,NULL,NULL};
		
				for(int k=0;k<r1;k++)
				for(int l=0;l<c1;l++)	
					arg.M1[l][k] = M1[l][k];
				for(int k=0;k<r1;k++)
				for(int l=0;l<c1;l++)	
					arg.M2[l][k] = M2[l][k];
						
				res = pthread_create(&(a_thread[no]), NULL, thread_function, (void *)&arg);	
	
	
	
				res = pthread_join(a_thread[no++], &thread_result);
			
				//printf("Thread result : %d\n", (char *)thread_result);
				if (res != 0) {
				perror("Thread join failed");
				exit(EXIT_FAILURE);
				}
	
				M3[i][j] = 	(void *)thread_result;
				}
			}
						end = clock();

			printf("thread result is :\n");	
			for (int i=0;i<r1;i++)
			{
				for(int j=0;j<c2;j++){
					printf("%d ",M3[i][j]);
		
				}
				printf("\n");
				}
		double time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
		printf("The execution time for thread : %f\n",time_taken);	
		break;
		
		case 2:
		start = clock();
		multiply(M1,M2,M3,r1,r2,c1,c2);
		end = clock();
		time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
		printf("The execution time for normal : %f\n",time_taken);
			printf("Normal result is :\n");	
			for (int i=0;i<r1;i++)
			{
				for(int j=0;j<c2;j++){
					printf("%d ",M3[i][j]);
		
				}
				printf("\n");
				}
			break;
		
	}
}

void *thread_function(void *arg) {

	struct argument *a = (struct argument * )arg;
	char * res = 0;
	for (int i=0;i<a->c1;i++)
	{
		res = res + (a->M1[a->i][i])*(a->M2[i][a->j]);
	}
	//printf("result is %d\n",res);

	

	pthread_exit( res);
}

void multiply(int M1[8][8],int M2[8][8],int M3[8][8],int r1,int r2,int c1,int c2)
{
int res = 0;
for (int i=0;i<r1;i++)
			{
				for(int j=0;j<c2;j++){
					res = 0;
					for (int i=0;i<c1;i++)
					{
						res = res + M1[i][i] * M2[i][j] ;
					}
					M3[i][j] = res;
				}
			}
}
