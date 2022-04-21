
buffer_user_sem:test_user_sem.o buffer_user_sem.o
	$ gcc test_user_sem.o buffer_user_sem.o -o buffer_user_sem -lpthread -lrt

test_user_sem.o: test_user_sem.c
	$ gcc -c test_user_sem.c

buffer_user_sem.o: buffer_user_sem.c buffer_sem.h
	$ gcc -c buffer_user_sem.c

run:
	./buffer_user_sem
clean:
	rm *.o buffer_user_sem

