#!/bin/bash

# Define a cleanup function to run 'make clean' on interrupt
cleanup() {
	printf "\nCleaning up...\n"
	make clean
	exit
}

# Trap the SIGINT (Ctrl + C) for cleanup
trap cleanup SIGINT

# Compile the program and print the readelf
make
make test
echo ""

# Every 3 seconds, run the system stats
while true; do
	./system_stats
	sleep 3
done

