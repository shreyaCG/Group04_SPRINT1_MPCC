#include "sock_server.h"

int main(int argc, char *argv[])
{
	myServer ms;
	string ip = argv[1];
	int port = atoi(argv[2]);

	ms.create_socket(ip,port);
	ms.bind_server();
	ms.accept_client();
	return 0;
}
