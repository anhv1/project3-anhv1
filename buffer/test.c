#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_hello 441
long hello_syscall(void){
	return syscall(__NR_hello);
}

#define __NR_init_buffer_421 442
long init_buffer_421_syscall(void){
	return syscall(__NR_init_buffer_421);
}

#define __NR_insert_buffer_421 443
long insert_buffer_421_syscall(int i){
	return syscall(__NR_insert_buffer_421, i);
}

#define __NR_print_buffer_421 444
long print_buffer_421_syscall(void){
	return syscall(__NR_print_buffer_421);
}

#define __NR_delete_buffer_421 445
long delete_buffer_421_syscall(void) {
	return syscall(__NR_delete_buffer_421);
}


int main(){
	long r1;
	r1 = init_buffer_421_syscall();
	if(r1 < 0){
	perror("init_buffer syscall failed \n");
	}else{
	printf("init_buffer ran successfully\n");
	}
	
	long r2;
	r2 = insert_buffer_421_syscall();
	if(r2 < 0){
	perror("insert_buffer syscall failed \n");
	}else{
	printf("insert_buffer ran successfully\n");
	}
	
	long r3;
	r3 = print_buffer_421_syscall();
	if(r3 < 0){
	perror("print_buffer syscall failed \n");
	}else{
	printf("print_buffer ran successfully\n");
	}
	
	long r4;
	r1 = delete_buffer_421_syscall();
	if(r4 < 0){
	perror("delete_buffer syscall failed \n");
	}else{
	printf("delete_buffer ran successfully\n");
	}
	
	return 0;
}
