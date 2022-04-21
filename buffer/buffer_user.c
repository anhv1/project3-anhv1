#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

ring_buffer_421_t *buffer;
node_421_t *head=NULL;
node_421_t *ptr = NULL;

int insert_helper(int i) { //helper function for init_buffer_421
	if (buffer == NULL) {
		printf("Error\n");
		return -1;
	}

	ptr = malloc(sizeof(node_421_t));
	ptr->data = i;
	ptr->next = buffer->write->next;

	buffer->write->next = ptr;
	buffer->write = buffer->write->next;
	return 0;
}
long init_buffer_421(void){

	if(buffer != NULL){
	printf("buffer already initialized\n");
	return -1;
	}
	
	buffer = malloc(sizeof(int)*SIZE_OF_BUFFER);
	head = malloc(sizeof(node_421_t));
	head->next = head;
	head->data = 0;
	
	buffer->write = head;
	buffer->read = head;
	buffer->length = 0;
	
	for(int i = 0; i < SIZE_OF_BUFFER; i++){
	insert_helper(0);
	}
	
	buffer->write->next = head;
	buffer->write = head;	
	return 0;
}
long insert_buffer_421(int i){
	
	if(buffer==NULL){
	printf("error: insert into an uninitialized buffer\n");
	return -1;
	}
	if(buffer->length == SIZE_OF_BUFFER){
	printf("error: insert into an full buffer\n");
	return -1;
	}
	buffer->write->data = i;
	buffer->write = buffer->write->next;
	buffer->length++;
	return 0;
}
long print_buffer_421(void){
	if (buffer == NULL){
	printf("error: print uninitialized buffer\n");
	return -1;
	}
	int i=1;
	do{
	printf("%d ->", buffer->read->data);
	buffer->read = buffer->read->next;
	i++;
	}while(buffer->read != head);
	
	printf("\n");
	
	return 0;	
}
long delete_buffer_421(void){
	if(buffer == NULL){
	printf("erorr: delete an uninitialized buffer\n");
	return -1;
	}
	buffer->write = head;
	for(int i = 0; i< SIZE_OF_BUFFER; i++){
		ptr = buffer->write->next;
		free(buffer->write);
		buffer->write = ptr;
		buffer->length--;
		
	}
	free(buffer);
	buffer=NULL;
	return 0;
}
