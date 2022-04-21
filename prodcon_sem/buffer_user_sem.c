#include <stdlib.h>
#include <stdio.h>
#include "buffer_sem.h"
#include <string.h>
#include <semaphore.h>

static bb_buffer_421_t buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;

bb_node_421_t *head = NULL;
bb_node_421_t *ptr = NULL;

long init_buffer_421(void) {
	// Write your code to initialize buffer
	if(head != NULL)
	{
	printf("Fail to initialize buffer. \n");
	return -1;
	}
	
	
	head = malloc(sizeof(bb_node_421_t));
	head->next = head;
	
	buffer.write = head;
	buffer.read = head;
	buffer.length = 0;
	
	for(int i = 0; i < SIZE_OF_BUFFER; i++){
	ptr = malloc(sizeof(bb_node_421_t));
	ptr->next = buffer.write->next;
	buffer.write->next = ptr;
	buffer.write = buffer.write->next;
	}
	
	buffer.write->next = head;
	buffer.write = head;
	
	buffer.write->next = buffer.read;
	
	// Initialize your semaphores here.
	sem_init(&mutex, 0, 1);
	sem_init(&empty_count, 0, 20);
	sem_init(&fill_count, 0, 20);
	
	return 0;
		
}
long enqueue_buffer_421(char * data) {
	// Write your code to enqueue data into the buffer
	if(head ==NULL){
	printf("error: enqueue into an uninitialized buffer\n");
	return -1;
	}
	sem_wait(&fill_count);
	sem_wait(&mutex);
	//coping contents of data to ptr->data
	memcpy (buffer.write->data, data, DATA_LENGTH);
	buffer.write = buffer.write->next;
	buffer.length++;
	
	sem_post(&mutex);
	sem_post(&fill_count);
	return 0;		
}

long dequeue_buffer_421(char * data) {
	// Write your code to dequeue data from the buffer
	if(head == NULL){
	printf("dequeue into an uninitialized buffer\n");
	return -1;
	}
	
	sem_wait(&empty_count);
	sem_wait(&mutex);
	//coping contents of data to ptr->data
	memcpy (data, buffer.read->data, DATA_LENGTH);
	buffer.read->next = ptr;
	
	ptr = buffer.read->next;
	
	memcpy (buffer.read->data,"", DATA_LENGTH);
	
	buffer.read->next = ptr;
	buffer.read = buffer.read->next;
	buffer.length--;
	sem_post(&mutex);
	sem_post(&fill_count);
	return 0;
}


long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	// write your code to delete buffer and other unwanted components
	if(head == NULL){
	printf("error: delete an uninitialized buffer\n");
	return -1;
	}
	
	buffer.write = head;

	for(int i = 0; i < 20; i++){
		ptr = buffer.write->next;
		free(buffer.write);
		buffer.write = ptr;
		buffer.length--;
	}
	
	sem_destroy(&empty_count);
	sem_destroy(&fill_count);
	sem_destroy(&mutex);
	head = NULL; 
	
	return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}
