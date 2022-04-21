
buffer_user:test_user.o buffer_user.o
	gcc test_user.o buffer_user.o -o buffer_user

test_user.o: test_user.c
	gcc -c test_user.c

buffer_user.o: buffer_user.c buffer.h
	gcc -c buffer_user.c

run:
	./buffer_user
clean:
	rm *.o buffer_user

