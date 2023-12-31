CC=gcc
CFLAGS= -g -Wall -Wextra

objects = vec.o list.o

tests: $(objects) tests.c vec.h list.h
	$(CC) -L/usr/local/lib -lcunit -o tests tests.c $(objects)

vec.o: vec.h
list.o: list.h

.PHONY: clean run_tests mem_check
clean:
	rm tests $(objects)

run_tests:
	./tests

mem_check:
	valgrind ./tests
