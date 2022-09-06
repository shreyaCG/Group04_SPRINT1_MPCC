#include "sock_server.h"

int main(int argc, char *argv[])
{
	if(argc==1){
		cout<<"[-] ERROR: NO INPUT"<<endl;
		exit(EXIT_FAILURE);
	}
	if(argv[1] == NULL){
		cout<<"[-] ERROR: PROVIDE IP ADDRESS"<<endl;
		exit(EXIT_FAILURE);
	}
	if(argv[2] == NULL){
		cout<<"[-] ERROR: PROVIDE PORT NUMBER"<<endl;
		exit(EXIT_FAILURE);
	}
	myServer ms;
	string ip = argv[1];
	int port = atoi(argv[2]);

	ms.create_socket(ip,port);
	ms.bind_server();
	ms.accept_client();
	return 0;
}
