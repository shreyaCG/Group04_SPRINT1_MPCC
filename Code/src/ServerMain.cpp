#include <SockServer.h>
#include<details.h>
//take command line arguments for ip and port number
int main(int argc, char *argv[])
{
	Server s1;//class object created
	int port=atoi(argv[2]);//port number 
	string ip =argv[1];//ip address
	s1.create_socket();//socket creation
	s1.bind_listen();//bind listen to the client
	s1.serv_select(port,ip);//check if the sockets are ready to read
	
	return 0;
}


