#include "sock_client.h"

int main(int argc, char *argv[])
{
	myClient mc;
	string ip = argv[1];
	int port = atoi(argv[2]);

	mc.create_socket(ip,port);
	mc.connect_client();
	return 0;
}
