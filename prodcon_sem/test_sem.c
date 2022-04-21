#include "buffer_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_init_buffer_sem_421 446
long init_buffer_421_syscall(void){
	return syscall(__NR_init_buffer_sem_421);
}

#define __NR_enqueue_buffer_sem_421 447
long enqueue_buffer_421_syscall(char* i){
	return syscall(__NR_enqueue_buffer_sem_421, i);
}

#define __NR_dequeue_buffer_sem_421 448
long dequeue_buffer_421_syscall(char* i){
	return syscall(__NR_dequeue_buffer_sem_421, i);
}

#define __NR_delete_buffer_sem_421 449
long delete_buffer_421_syscall(void) {
	return syscall(__NR_delete_buffer_sem_421);
}

void *producer( void *ptr )
{
	char* input;
	input = (char *) ptr;

	long i = enqueue_buffer_421_syscall(input);
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

	long i = dequeue_buffer_421_syscall(output);
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
	init_buffer_421_syscall();
	
	for(int i = 0; i < 1000; i++) {
		printk("\tRun %d\n", i+1);
		input = malloc(DATA_LENGTH);
		output = malloc(DATA_LENGTH);

		for(int j = 0; j < DATA_LENGTH; j++) {
			input[j] = (char)(i%10+48);
		}

		p1 = pthread_create(&th1, NULL, producer, input);
		p2 = pthread_create(&th2, NULL, consumer, output);

		pthread_join(th1, NULL);
		pthread_join(th2, NULL);

		printk("Thread 1 returns %d\nThread 2 returns %d\n", p1, p2);
		free(input);
		free(output);
	}

	delete_buffer_421_syscall();
	return 0;
}


