#include <ServerSocket.h>

int main(int argc, char *argv[])
{
	Server s1;
	int port=atoi(argv[2]);
	string ip =argv[1];
	s1.create_socket();
	s1.bind_listen();
	s1.serv_select(port,ip);
	
	return 0;
}


