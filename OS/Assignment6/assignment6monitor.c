#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
   
  
enum {	THINKING , HUNGRY , EATING} state[5];
int phil[5] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex; 
sem_t self[5];
void test(int i) 
{ 
    if (state[i] == HUNGRY 
        && state[(i + 4) % 5] != EATING 
        && state[(i + 1) % 5] != EATING) { 
        state[i] = EATING; 
        printf("Philosopher %d is eating\n", i + 1); 
        sem_post(&self[i]); 
    } 
} 
  
void pickup(int i) 
{ 
    printf("\nPhilosopher %d is thinking\n", i + 1); 
    sem_wait(&mutex); 
    state[i] = HUNGRY;   
    printf("Philosopher %d is hungry\n", i + 1); 
    test(i);   
    sem_post(&mutex); 
    sem_wait(&self[i]);  
} 
  

void putdown(int i) 
{ 
  
    sem_wait(&mutex);   
    state[i] = THINKING;  
    printf("Philosopher %d putting down chopsticks...\n",i + 1); 
    test((i + 4) % 5); 
    test((i + 1) % 5); 
    sem_post(&mutex); 
} 
  
void* philospher(void* num) 
{ 
    while (1) { 
        int* i = num; 
        pickup(*i);
        sleep(rand()%5);  
        putdown(*i); 
    } 
} 
  
int main() 
{ 
  
    int i; 
    pthread_t thread_id[5]; 
    sem_init(&mutex, 0, 1);  
    for (i = 0; i < 5; i++) 
        sem_init(&self[i], 0, 0); 
  
    for (i = 0; i < 5; i++) { 
        pthread_create(&thread_id[i], NULL,philospher, &phil[i]);  
    } 
  
    for (i = 0; i < 5; i++)   
        pthread_join(thread_id[i], NULL); 
} 



