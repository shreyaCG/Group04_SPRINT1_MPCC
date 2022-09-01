#include <ServerSocket.h>

int main(int argc, char *argv[])
{
	int csockfd, client_sock[30];
	
	int max_clients = 30;

	int serverfd, sd, max_sd;
	
	int readVal;

	vector <int> vs_csock;
	char buff[MAX_BUF];
	//create master socket
	fd_set master;
	// set of sock_desc...
	fd_set readfds;
	int socketCount=0;

	for(int i=0;i<max_clients;i++)
		client_sock[i] = 0;

	
	return 0;
}


