#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/semaphore.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
struct bb_node_421 *head = NULL;
struct bb_node_421 *ptr = NULL;
struct semaphore mutex;
struct semaphore fill_count;
struct semaphore empty_count;

SYSCALL_DEFINE0(init_buffer_sem_421) {
	// Write your code to initialize buffer
	if(head != NULL)
	{
	printk("Fail to initialize buffer. \n");
	return -1;
	}
	
	head = kmalloc(sizeof(bb_node_421_t), GFP_KERNEL);
	head->next = head;
	
	buffer.write = head;
	buffer.read = head;
	buffer.length = 0;
	
	int count = 1;
	while(i < SIZE_OF_BUFFER){
	ptr = kmalloc(sizeof(bb_node_421_t), GFP_KERNEL);
	ptr->next = buffer.write->next;
	
	buffer.write->next = ptr;
	buffer.write = buffer.write->next;
	count++;
	}
	
	buffer.write->next = head;
	buffer.write = head;
	
	// Initialize your semaphores here.
	sem_init(&mutex, 1);
	sem_init(&empty_count, 20);
	sem_init(&fill_count, 20);
	
	return 0;	
}
SYSCALL_DEFINE1(enqueue_buffer_sem_421, char *, data) {
	// Write your code to enqueue data into the buffer
	if(head == NULL){
	printk("Error: enqueue uninitialized buffer\n");
	return -1;
	}
	down(&fill_count);
	down(&mutex);
	int copy = _copy_from_user(buffer.write->data, data, DATA_LENGTH);
	buffer.write = buffer.write->next;
	buffer.length++;
	
	up(&mutex);
	up(&fill_count);
	
	return 0;
}

SYSCALL_DEFINE1(dequeue_buffer_sem_421, char *, data) {
	// Write your code to dequeue data from the buffer
	if (shead == NULL) {
		printk("error: dequeue into an uninitialized buffer.\n");
		return -1;
	}
	
	down(&empty_count);
	down(&mutex);
	int copy = __copy_to_user(data, buffer.read->data, DATA_LENGTH);
	ptr = buffer.read->next;
	copy = __copy_from_user(buffer.read->data, "", DATA_LENGTH);
	buffer.read->next = ptr;
	buffer.read = buffer.read->next;
	buffer.length--;

	up(&mutex);
	up(&empty_count);

	return 0;
}


SYSCALL_DEFINE0(delete_buffer_sem_421) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	// write your code to delete buffer and other unwanted components
	if(head == NULL){
	printk("error: delete an uninitialized buffer\n");
	return -1;
	}
	
	buffer.write = head;
	int count=0;
	while (count < SIZE_OF_BUFFER) {
		ptr = buffer.write->next;
		kfree(buffer.write);
		buffer.write = ptr;
		buffer.length--;
		count++;
	}
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
