# nicole cranon <nicole.cranon@ucdenver.edu>
# csci 4640, fall 2015
# assignment 8 - ll1 parser driver
# makefile

CC=g++ -std=c++11
CFLAGS=-c -Wall -g
INC=-I include/

parser: main.o driver.o
	$(CC) main.o driver.o -o parser
	# parser: main.o driver.o helper.o
	# $(CC) main.o driver.o helper.o -o parser

main.o: src/main.cpp
	$(CC) $(INC) $(CFLAGS) src/main.cpp -o main.o

driver.o: src/driver.cpp
	$(CC) $(INC) $(CFLAGS) src/driver.cpp -o driver.o

# helper.o: src/helper.cpp
# 	$(CC) $(INC) $(CFLAGS) src/helper.cpp -o helper.o

clean:
	rm *.o -f; rm parser -f
