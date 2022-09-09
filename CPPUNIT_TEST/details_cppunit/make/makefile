CC=g++
CPPFLAGS=-c -g -Wall 
UTFLAGS=-lcppunit
OBJ=obj/
SRC=src/
BIN=bin/
INC=inc/

all:details_test

details_test:$(OBJ)details_main.o $(OBJ)details_test.o 
	$(CC) -o details_test $(OBJ)details_main.o $(OBJ)details_test.o $(UTFLAGS)
	mv details_test $(BIN)
	
$(OBJ)details_main.o:$(SRC)details_main.cpp
	$(CC) $(CPPFLAGS) $(SRC)details_main.cpp -I $(INC)
	mv details_main.o $(OBJ)
	
$(OBJ)details_test.o:$(SRC)details_test.cpp
	$(CC) $(CPPFLAGS) $(SRC)details_test.cpp -I $(INC)
	mv details_test.o $(OBJ)

clean:
	rm -f $(OBJ)*.o 
	rm -f $(BIN)details_test
	@echo "Cleaning Done!"
