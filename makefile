# nicole cranon <nicole.cranon@ucdenver.edu>
# csci 4640, fall 2015
# assignment 8 - ll1 parser driver
# makefile

CC=g++ -std=c++11
CFLAGS=-c -Wall -g
INC=-I include/

parser: main.o driver.o uscanner.o predictGenerator.o grammerAnalyzer.o generator.o helper.o
	$(CC) main.o driver.o uscanner.o predictGenerator.o grammerAnalyzer.o generator.o helper.o -o parser

main.o: src/main.cpp
	$(CC) $(INC) $(CFLAGS) src/main.cpp -o main.o

driver.o: src/driver.cpp
	$(CC) $(INC) $(CFLAGS) src/driver.cpp -o driver.o

uscanner.o: src/uscanner.cpp
	$(CC) $(INC) $(CFLAGS) src/uscanner.cpp -o uscanner.o

generator.o: src/generator.cpp
	$(CC) $(INC) $(CFLAGS) src/generator.cpp -o generator.o

predictGenerator.o: src/predictGenerator.cpp
	$(CC) $(INC) $(CFLAGS) src/predictGenerator.cpp -o predictGenerator.o

grammerAnalyzer.o: src/grammerAnalyzer.cpp
	$(CC) $(INC) $(CFLAGS) src/grammerAnalyzer.cpp -o grammerAnalyzer.o

helper.o: src/helper.cpp
	$(CC) $(INC) $(CFLAGS) src/helper.cpp -o helper.o

clean:
	rm *.o -f; rm parser -f
