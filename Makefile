SOURCES=lexem.cpp syntax_analyser.cpp syntax_tree.cpp test_syntax_analyser.cpp
HEADERS=lexem.h syntax_analyser.h syntax_tree.h

EXECUTABLE=dbms.exe

CC=g++
CFLAGS=-Wall -std=c++11

all: $(EXECUTABLE)

$(EXECUTABLE): 
	$(CC) $(SOURCES) $(HEADERS) $(CFLAGS) -o $(EXECUTABLE) 

clean:
	rm -f *.o $(EXECUTABLE)
