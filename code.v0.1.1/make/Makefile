CC = g++

CCFLAGS = -c -g -std=c++11

LDFLAGS = -o
INC = inc
OBJ = obj
SRC = src
BIN = bin

all: server client

server: $(OBJ)/ServerMain.o $(OBJ)/SockServer.o $(OBJ)/details.o
	$(CC) $(LDFLAGS) $(BIN)/server  $(OBJ)/ServerMain.o $(OBJ)/SockServer.o $(OBJ)/details.o -lpthread

$(OBJ)/ServerMain.o: $(SRC)/ServerMain.cpp
	$(CC) $(CCFLAGS) $(SRC)/ServerMain.cpp -I $(INC)/ 
	mv *.o $(OBJ)
$(OBJ)/userdata.o: $(SRC)/details.cpp
	$(CC) $(CCFLAGS) $(SRC)/details.cpp -I $(INC)/ 
	mv *.o $(OBJ)

$(OBJ)/SockServer.o: $(SRC)/SockServer.cpp
	$(CC) $(CCFLAGS) $(SRC)/SockServer.cpp -I $(INC)/ 
	mv *.o $(OBJ)

client: $(OBJ)/Clientmain.o $(OBJ)/SockClient.o $(OBJ)/details.o
	$(CC) $(LDFLAGS) $(BIN)/client  $(OBJ)/Clientmain.o $(OBJ)/SockClient.o $(OBJ)/details.o -lpthread

$(OBJ)/Clientmain.o: $(SRC)/Clientmain.cpp
	$(CC) $(CCFLAGS) $(SRC)/Clientmain.cpp -I $(INC)/ 
	mv *.o $(OBJ)

$(OBJ)/SockClient.o: $(SRC)/SockClient.cpp
	$(CC) $(CCFLAGS) $(SRC)/SockClient.cpp -I $(INC)/ 
	mv *.o $(OBJ)

clean:
	rm -f a.out *.o
	rm -f $(OBJ)/*.o
	@echo "Cleaning Done!"
