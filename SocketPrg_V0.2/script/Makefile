CC = g++

CCFLAGS = -c -g

LDFLAGS = -o
INC = inc
OBJ = obj
SRC = src
BIN = bin

all: server client

server: $(OBJ)/MainServer.o $(OBJ)/Server.o
	$(CC) $(LDFLAGS) $(BIN)/server  $(OBJ)/MainServer.o $(OBJ)/Server.o -lpthread

$(OBJ)/MainServer.o: $(SRC)/MainServer.cpp
	$(CC) $(CCFLAGS) $(SRC)/MainServer.cpp -I $(INC)/ 
	mv *.o $(OBJ)

$(OBJ)/Server.o: $(SRC)/Server.cpp
	$(CC) $(CCFLAGS) $(SRC)/Server.cpp -I $(INC)/ 
	mv *.o $(OBJ)

client: $(OBJ)/MainClient.o $(OBJ)/Client.o
	$(CC) $(LDFLAGS) $(BIN)/client  $(OBJ)/MainClient.o $(OBJ)/Client.o -lpthread

$(OBJ)/MainClient.o: $(SRC)/MainClient.cpp
	$(CC) $(CCFLAGS) $(SRC)/MainClient.cpp -I $(INC)/ 
	mv *.o $(OBJ)

$(OBJ)/Client.o: $(SRC)/Client.cpp
	$(CC) $(CCFLAGS) $(SRC)/Client.cpp -I $(INC)/ 
	mv *.o $(OBJ)


clean:
	rm -f a.out *.o
	rm -f $(OBJ)/*.o
	@echo "Cleaning Done!"
