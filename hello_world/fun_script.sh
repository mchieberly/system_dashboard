#!/bin/bash

echo "Hello, World!"

make
make test

echo ""
echo "Running C executable..."
./hello_world

make clean

