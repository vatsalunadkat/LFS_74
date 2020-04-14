#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

void *myfunc1 (void *ptr);
void *myfunc2 (void *ptr);

sem_t mutex;

char buf[24];

int main(int argc, char *argv[]){

	pthread_t thread1, thread2;

	char *msg1 = "First thread";
	char *msg2 = "Second thread";

	sem_init(&mutex, 0, 1);

//	int ret1, ret2;

	pthread_create(&thread1, NULL, (void *) &myfunc1, (void *) msg1);
	pthread_create(&thread2, NULL, (void *) &myfunc2, (void *) msg2);

//	printf("Main function after creation of threads \n");


	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

//	printf("First thread ret1 = %d \n", ret1);
//	printf("Second thread ret2 = %d \n", ret2);

	sem_destroy(&mutex);

	return 0;

}

void *myfunc1 (void *ptr){

	char *msg = (char *) ptr;
	printf("%s\n", msg);
	
	sem_wait(&mutex);
	sprintf(buf, "%s", "Hello There");
	sem_post(&mutex);

	pthread_exit(0);

	return NULL;

}

void *myfunc2 (void *ptr){

	char *msg = (char *) ptr;
	printf("%s\n", msg);
	
	sem_wait(&mutex);
	printf("%s\n", buf);
	sem_post(&mutex);

	pthread_exit(0);

	return NULL;
}


















