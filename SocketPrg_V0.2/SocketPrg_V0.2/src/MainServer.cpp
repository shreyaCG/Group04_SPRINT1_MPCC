#include <ServerSocket.h>

int main(int argc, char *argv[])
{
	ServerSocket s1;

	for(int i=0;i<max_clients;i++)
		client_sock[i] = 0;
	s1.serv_accept();
	
	return 0;
}


