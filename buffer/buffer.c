#include "buffer.h"
#include <linux/kernel.h>
#include <linux/syscalls.h>

ring_buffer_421_t *buffer;
node_421_t *head = NULL;
node_421_t *ptr = NULL;

SYSCALL_DEFINE0(init_buffer_421){
	
	int count=1;
	
	if(buffer != NULL){
	printk("buffer already initialized\n");
	return -1;
	}
	
	buffer = kmalloc(sizeof(int)*SIZE_OF_BUFFER, GFP_KERNEL);
	head = kmalloc(sizeof(node_421_t), GFP_KERNEL);
	head->next = head;
	head->data = 0;
	
	buffer->write = head;
	buffer->read = head;
	buffer->length = 0;
	
	while(i<SIZE_OF_BUFFER){
	ptr = Kmalloc(sizeof(node_421_t), GFP_KERNEL);
	ptr->data = 0;
	ptr->next = buffer->write->next;
	
	buffer->write->next = ptr;
	buffer->write = buffer->write->next;
	count++;
	}
	buffer->write->next = head;
	
	buffer->write = head;
		
	return 0;
}
SYSCALL_DEFINE1(insert_buffer_421, int, i){
	
	if(buffer==NULL){
	printk("error: insert into an uninitialized buffer\n");
	return -1;
	}
	if(buffer->length == SIZE_OF_BUFFER){
	printk("error: insert into an full buffer\n");
	return -1;
	}
	buffer->write->data = i;
	buffer->write = buffer->write->next;
	buffer->length++;
	return 0;
}
SYSCALL_DEFINE0(print_buffer_421){
	int count = 1;
	
	if (buffer == NULL){
	printk("error: print uninitialized buffer\n");
	return -1;
	}
	
	do{
	printk("%d ->", buffer->read->data);
	buffer->read = buffer->read->next;
	count++;
	}while(buffer->read != head);
	
	printf("\n");
	
	return 0;	
}
SYSCALL_DEFINE0(delete_buffer_421){
	int count = 1;
	
	if(buffer == NULL){
	printk("error: delete an uninitialized buffer\n");
	return -1;
	}
	
	buffer->write = head;
	while(count < SIZE_OF_BUFFER){
	ptr = buffer->write->next;
	kfree(buffer->write);
	buffer->write = pointer;
	buffer->length--;
	count++;
	}
	
	kfree(buffer);
	buffer = NULL;
	
	return 0;
}
