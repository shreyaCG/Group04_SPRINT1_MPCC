CC=g++
CPPFLAGS=-c -g -Wall 
UTFLAGS=-lcppunit
OBJ=obj/
SRC=src/
BIN=bin/
INC=inc/

all:server_test

server_test:$(OBJ)server_main.o $(OBJ)server_test.o 
	$(CC) -o server_test $(OBJ)server_main.o $(OBJ)server_test.o $(UTFLAGS)
	mv server_test $(BIN)
	
$(OBJ)server_main.o:$(SRC)server_main.cpp
	$(CC) $(CPPFLAGS) $(SRC)server_main.cpp -I $(INC)
	mv server_main.o $(OBJ)
	
$(OBJ)server_test.o:$(SRC)server_test.cpp
	$(CC) $(CPPFLAGS) $(SRC)server_test.cpp -I $(INC)
	mv server_test.o $(OBJ)

clean:
	rm -f $(OBJ)*.o 
	rm -f $(BIN)server_test
	@echo "Cleaning Done!"
