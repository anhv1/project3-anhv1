
buffer_mon:test_mon.o buffer_mon.o
	$ gcc test_mon.o buffer_mon.o -o buffer_mon -lpthread -lrt

test_mon.o: test_mon.c
	$ gcc -c test_mon.c

buffer_mon.o: buffer_mon.c buffer_mon.h
	$ gcc -c buffer_mon.c

run:
	./buffer_mon
clean:
	rm *.o buffer_mon

