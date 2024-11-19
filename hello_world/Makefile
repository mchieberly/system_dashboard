compile: hello_world.c
	gcc -c -Wall hello_world.c
	gcc -Wall -o hello_world hello_world.c

test: hello_world
	readelf -sW hello_world.o

clean:
	rm hello_world hello_world.o
