#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
void *philosopher_func(void *arg);
sem_t *chopsticks;
int number,reader_count=0;
int main() {
	int res,p_no,id[10]={0,1,2,3,4,5,6,7,8,9};
	pthread_t philosophers[10];
	void *thread_result;
	printf("ENTER THE  NUMBER OF PHILOSOPHERS : ");
	scanf("%d",&p_no);
	
	chopsticks= (sem_t *)malloc(p_no * sizeof(sem_t));
	
	for(int i=0;i<p_no;i++){
		res = sem_init(&chopsticks[i], 0, 1);
		if (res != 0) {
			perror("Semaphore initialization failed");
			exit(EXIT_FAILURE);
		}
	}
	


	for(int i=0;i<p_no;i++){	
			res = pthread_create(&(philosophers[i]), NULL, philosopher_func, &id[i]);
			if (res != 0) {
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
	}
	
	for(int i=0;i<p_no;i++){	
		res = pthread_join(philosophers[i], &thread_result);
			if (res != 0) {
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}
		}

	for(int i=0;i<p_no;i++){
	sem_destroy(&chopsticks[i]);
	}
	exit(EXIT_SUCCESS);
}


void *philosopher_func(void *arg) {
int temp=*(int *)arg;
while(1){


	printf("\nphilosopher %d is hungry...\n",temp);
	if(temp % 2 == 0)
		{
		sem_wait(&chopsticks[temp]);
		sem_wait(&chopsticks[(temp+1)%5]);
		}
		else
		{
		sem_wait(&chopsticks[(temp+1)%5]);
		sem_wait(&chopsticks[temp]);
		}
		
		printf("philosopher %d is eating...\n",temp);
			sleep((rand() % 9));
		printf("philosopher %d has put down chopsticks...\n",temp);
		sem_post(&chopsticks[(temp+1)%5]);
		sem_post(&chopsticks[temp]);

	}
	pthread_exit(NULL);
	

	
}

