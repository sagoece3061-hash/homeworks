CC = g++
CFLAGS = -Wall -std=c++11

all: test1
	run

test1: main.cpp BinarySearchTree.cpp
	$(CC) $(CFLAGS) main.cpp BinarySearchTree.cpp -o test1.exe

run: ./text1.exe

clean:
	rm -f test1.exe