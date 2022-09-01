CC=g++
CPPFLAGS=-c -g -Wall -std=c++11
OBJ=obj/
SRC=src/
BIN=bin/
INCLUDE=inc/

all:server.out client.out


server.out: $(OBJ)servermain.o $(OBJ)Serv_Client.o
	    $(CC) -o Serv_Client.out $(OBJ)servermain.o $(OBJ)Serv_Client.o
	    mv server.out $(BIN)
client.out: $(OBJ)clientmain.o $(OBJ)Serv_Client.o
	    $(CC) -o Serv_Client.out $(OBJ)clientmain.o $(OBJ)Serv_Client.o
	    mv client.out $(BIN)
$(OBJ)servermain.o: $(SRC)main.cpp
	                $(CC) $(CPPFLAGS) $(SRC)main.cpp -I $(INCLUDE)
			                mv main.o $(OBJ)

$(OBJ)map.o: $(SRC)map.cpp
	                $(CC) $(CPPFLAGS) $(SRC)map.cpp -I $(INCLUDE)
			                 mv map.o $(OBJ)
valgrind:$(BIN) map.out
	                valgrind --leak-check=full --show-reachable=yes $(BIN)map.out 1>$(BIN)/valgrind.txt

clean:
	                rm -f $(OBJ)*.o
			                rm -f $(BIN)map.out
					                rm -f $(BIN)/valgrind.txt
