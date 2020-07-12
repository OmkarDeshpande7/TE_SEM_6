#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
void *reader_func(void *arg);
void *writer_func(void *arg);
pthread_mutex_t bmutex;
sem_t wrt;
int number,reader_count=0;
int main() {
	int res,r_no,w_no,temp;
	pthread_t readers[10],writers[10];
	void *thread_result;
	printf("ENTER THE  NUMBER OF READERS : ");
	scanf("%d",&r_no);
	
	printf("ENTER THE  NUMBER OF WRITERS : ");
	scanf("%d",&w_no);
	

	
	res = pthread_mutex_init(&bmutex, NULL);
	
	res = sem_init(&wrt, 0, 1);
	if (res != 0) {
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}
	


	for(int i=0;i<r_no;i++){	
			int *ref=&i;
			res = pthread_create(&(readers[i]), NULL, reader_func, ref);
			if (res != 0) {
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
	}
	for(int i=0;i<w_no;i++){	
			int *ref=&i;
			res = pthread_create(&(writers[i]), NULL, writer_func, ref);
			if (res != 0) {
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
		}

	for(int i=0;i<r_no;i++){
			res = pthread_join(readers[i], &thread_result);
			if (res != 0) {
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}	
	}
	for(int i=0;i<w_no;i++){	
		res = pthread_join(writers[i], &thread_result);
			if (res != 0) {
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}
		}

	
	sem_destroy(&wrt);
	pthread_mutex_destroy(&bmutex);
	exit(EXIT_SUCCESS);
}


void *writer_func(void *arg) {
int temp=*(int *)arg;
int random ;
while(1){
	
	sleep((rand() % 5));
	printf("\nReader count is %d.\n\n",reader_count);
	printf("Writer %d wants to write...\n",temp);
	sem_wait(&wrt);
	random = rand() % 20;
	printf("Writer %d found %d and changed to \t\t:%d \n",temp,number,random);
	number = random;
	sem_post(&wrt);
	printf("Writer %d has finished writing...\n",temp);
	}
	pthread_exit(NULL);
	

	
}

void *reader_func(void *arg) {
int temp=*(int *)arg;
while(1){
	sleep((rand() % 8 ));
	printf("\nReader %d wants to read...\n",temp);
	pthread_mutex_lock(&bmutex);
	reader_count++;
	printf("Reader count is %d.\n",reader_count);
	if(reader_count == 1)
		sem_wait(&wrt);
	pthread_mutex_unlock(&bmutex);

		printf("Reader %d is reading and found\t\t\t:%d \n",temp,number);

		
	pthread_mutex_lock(&bmutex);
	reader_count--;
	printf("Reader %d has finished reading...\n\n",temp);
		if(reader_count == 0)
		sem_post(&wrt);
	pthread_mutex_unlock(&bmutex);

	}
	pthread_exit(NULL);
	

}
	

