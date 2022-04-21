#include "buffer_sem.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

void *producer( void *ptr )
{
	char* input;
	input = (char *) ptr;

	long i = enqueue_buffer_421(input);
	if (i < 0) {
		printf("Producer unsuccessful\n");
	}
	else {
		printf("Producer successful\n");
	}
	return (void *) i;
}

void *consumer( void *ptr )
{
	char* output;
	output = (char *) ptr;

	long i = dequeue_buffer_421(output);
	if (i < 0) {
		printf("Consumer unsuccessful\n");
	}
	else {
		printf("Consumer successful\n");
	}
	return (void *) i;
}

int main() {

	pthread_t th1, th2;
	int p1, p2;
	char* input;
	char* output;
	init_buffer_421();

	for(int i = 0; i < 1000; i++) {
		printf("\tRun %d\n", i+1);
		input = malloc(DATA_LENGTH);
		output = malloc(DATA_LENGTH);

		for(int j = 0; j < DATA_LENGTH; j++) {
			input[j] = (char)(i%10+48);
		}

		p1 = pthread_create(&th1, NULL, producer, input);
		p2 = pthread_create(&th2, NULL, consumer, output);

		pthread_join(th1, NULL);
		pthread_join(th2, NULL);

		printf("Thread 1 returns %d\nThread 2 returns %d\n", p1, p2);
		free(input);
		free(output);
	}

	delete_buffer_421();
	return 0;
}


