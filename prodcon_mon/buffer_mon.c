#include <semaphore.h>
#include "buffer_mon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

struct ring_buffer_421* buffer;
struct node_421* head = NULL;
struct node_421* ptr = NULL;
pthread_mutex_t mutex;
pthread_cond_t fill_buffer;
pthread_cond_t empty_buffer;

long init_buffer_421(void) {
	// Write your code to initialize buffer
	if(buffer != NULL)
	{
	printf("Fail to initialize buffer. \n");
	return -1;
	}
	
	buffer = malloc(DATA_LENGTH * SIZE_OF_BUFFER);
	
	head = malloc(sizeof(node_421_t));
	head->next = head;
	
	buffer->write = head;
	buffer->read = head;
	buffer->length = 0;
	
	for(int i = 1; i < 20; i++){
	ptr = malloc(sizeof(node_421_t));
	ptr->next = buffer->write->next;
	
	buffer->write->next = ptr;
	buffer->write = buffer->write->next;
	}
	
	buffer->write->next = head;
	
	buffer->write = head;
	
	//pthread initialization
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&empty_buffer, NULL);
	pthread_cond_init(&fill_buffer, NULL);
	
	return 0;
		
}
long enqueue_buffer_421(char * data) {
	// Write your code to enqueue data into the buffer
	if(buffer == NULL){
	printf("error: enqueue into an uninitialized buffer\n");
	return -1;
	}
	
	pthread_mutex_lock(&mutex);

	while(buffer->length == SIZE_OF_BUFFER){
	printf("enqueue to buffer full\n");
	pthread_cond_wait(&fill_buffer, &mutex);
	}
	//coping contents of data to ptr->data
	memcpy (buffer->write->data, data, DATA_LENGTH);
	buffer->write = buffer->write->next;
	buffer->length += 1;
	
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&empty_buffer);
	
	return 0;
}

long dequeue_buffer_421(char * data) {
	// Write your code to dequeue data from the buffer
	if(buffer == NULL) {
	printf("error: dequeue into an uninitialized buffer.\n");
	return -1;
	}

	pthread_mutex_lock(&mutex);

	while(buffer->length == 0) {
		printf("Dequeue called while buffer is empty, waiting...\n");
		pthread_cond_wait(&empty_buffer, &mutex);
	}

	memcpy(data, buffer->read->data, DATA_LENGTH);
	ptr = buffer->read->next;
	memcpy(buffer->read->data, "", DATA_LENGTH);
	buffer->read->next = ptr;
	buffer->length--;

	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&fill_buffer);

	return 0;
}


long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	// write your code to delete buffer and other unwanted components
	if(buffer == NULL){
	printf("error: delete an uninitialized\n");
	return -1;
	}
	
	buffer->write = head;
	
	for(int i = 0; i<SIZE_OF_BUFFER; i++){
		ptr = buffer->write->next;
		free(buffer->write);
		buffer->write = ptr;
		buffer->length--;
	}
	
	free(buffer);
	buffer = NULL;
	
	return 0;
}
