compile: system_stats.c
	gcc -c -Wall system_stats.c
	gcc -Wall -o system_stats system_stats.c

test: system_stats
	readelf -sW system_stats.o

clean:
	rm system_stats system_stats.o
