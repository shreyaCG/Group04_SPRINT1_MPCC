CC=g++
CPPFLAGS=-c -g -Wall 
UTFLAGS=-lcppunit
OBJ=obj/
SRC=src/
BIN=bin/
INC=inc/

all:client_test

client_test:$(OBJ)client_main.o $(OBJ)client_test.o 
	$(CC) -o client_test $(OBJ)client_main.o $(OBJ)client_test.o $(UTFLAGS)
	mv client_test $(BIN)
	
$(OBJ)client_main.o:$(SRC)client_main.cpp
	$(CC) $(CPPFLAGS) $(SRC)client_main.cpp -I $(INC)
	mv client_main.o $(OBJ)
	
$(OBJ)client_test.o:$(SRC)client_test.cpp
	$(CC) $(CPPFLAGS) $(SRC)client_test.cpp -I $(INC)
	mv client_test.o $(OBJ)

clean:
	rm -f $(OBJ)*.o 
	rm -f $(BIN)client_test
	@echo "Cleaning Done!"
