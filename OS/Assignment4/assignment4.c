#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
void *producer_func(void *arg);
void *consumer_func(void *arg);
pthread_mutex_t bmutex;
sem_t full,empty;
int Buffer[10],top=-1;
int main() {
	int res,p_no,c_no,temp;
	pthread_t producers[10],consumers[10];
	void *thread_result;
	printf("ENTER THE  NUMBER OF PRODUCERS : ");
	scanf("%d",&p_no);
	
	printf("ENTER THE  NUMBER OF CONSUMERS : ");
	scanf("%d",&c_no);
	

	
	res = pthread_mutex_init(&bmutex, NULL);
	
	res = sem_init(&full, 0, 0);
	if (res != 0) {
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	
	
	res = sem_init(&empty, 0, 10);
	if (res != 0) {
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	


	for(int i=0;i<p_no;i++){	
			int *ref=&i;
			res = pthread_create(&(producers[i]), NULL, producer_func, ref);
			/*if (res != 0) {
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}*/
	}
	for(int i=0;i<c_no;i++){	
			int *ref=&i;
			res = pthread_create(&(consumers[i]), NULL, consumer_func, ref);
			/*if (res != 0) {
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}*/
		}

	for(int i=0;i<p_no;i++){
			res = pthread_join(producers[i], &thread_result);
			/*if (res != 0) {
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}	*/
	}
	for(int i=0;i<c_no;i++){	
		res = pthread_join(consumers[i], &thread_result);
			/*if (res != 0) {
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}*/
		}

	
	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&bmutex);
	exit(EXIT_SUCCESS);
}


void *producer_func(void *arg) {
int temp=*(int *)arg;
while(1){
	sleep((rand() % 5));
	sem_wait(&empty);
	pthread_mutex_lock(&bmutex);

	printf("In Producer %d is adding in buffer \t\t: ",temp);
	Buffer[++top] = rand() % 10;
	for(int i=0;i<=top;i++)
		printf("%d ",Buffer[i]);
	printf("\n");


	pthread_mutex_unlock(&bmutex);
	sem_post(&full);
	}
	pthread_exit(NULL);
	
	/*int pro = *(int *)arg;
	int i=rand()%10;
	int j;
	while(1){
	sleep(rand()%10);
	sem_wait(&empty);
    pthread_mutex_lock(&bmutex);
	printf("\n\nproducer no %d added :: %d",pro,i);
	Buffer[top]=i;
	top++;
	printf("\n\nbuffer is:: ");
	for(j=0;j<=top;j++)
	{
		printf("\t%d",Buffer[j]);
	}
	pthread_mutex_unlock(&bmutex);
	sem_post(&full);
	}
	pthread_exit(NULL);*/
	
	
}

void *consumer_func(void *arg) {
int temp=*(int *)arg;
while(1){
	sleep((rand() % 5 ));
	sem_wait(&full);
	pthread_mutex_lock(&bmutex);

	printf("In Consumer %d is consuming from buffer \t\t: ",temp);
	top--;
	for(int i=0;i<=top;i++)
		printf("%d ",Buffer[i]);
	printf("\n");


	pthread_mutex_unlock(&bmutex);
	sem_post(&empty);
	}
	pthread_exit(NULL);
	
		/*int con = *(int *)arg;
	int j;
	while(1)
	{
	sleep(rand()%10);
	sem_wait(&full);
	pthread_mutex_lock(&bmutex);
	printf("\n\nconsumer no. %d removes :: %d",con,Buffer[top-1]);
	Buffer[top-1]=0;
	top--;
	printf("\n\nBuffer is:: ");
	for(j=0;j<top;j++)
	{
		printf("\t%d",Buffer[j]);
	}
	pthread_mutex_unlock(&bmutex);
	sem_post(&empty);
	}
	pthread_exit(NULL);*/
}
	

